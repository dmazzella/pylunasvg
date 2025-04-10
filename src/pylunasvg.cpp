#include <lunasvg.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

struct PyBitmap
{
private:
    std::shared_ptr<lunasvg::Bitmap> bitmap;

public:
    PyBitmap(const std::shared_ptr<lunasvg::Bitmap> &bmp) : bitmap(bmp) {}

    py::object __repr__(void)
    {
        return py::str("<Bitmap width=" + std::to_string(bitmap->width()) + " height=" + std::to_string(bitmap->height()) + ">");
    }

    py::object get_data(void) const
    {
        if (!bitmap)
        {
            throw std::runtime_error("Bitmap is null.");
        }
        return py::bytes(reinterpret_cast<const char *>(bitmap->data()), bitmap->width() * bitmap->height() * 4);
    }

    py::int_ get_width(void) const
    {
        return bitmap->width();
    }

    py::int_ get_height(void) const
    {
        return bitmap->height();
    }

    py::object convert_to_rgba(void) const
    {
        if (!bitmap)
        {
            throw std::runtime_error("Bitmap is null.");
        }
        bitmap->convertToRGBA();
        return py::none();
    }

    py::object write_to_png(const py::object &pyfilename) const
    {
        if (pyfilename.is_none())
        {
            throw std::invalid_argument("Filename cannot be None.");
        }
        std::string filename = py::str(pyfilename).cast<std::string>();
        if (!bitmap->writeToPng(filename))
        {
            throw std::runtime_error("Failed to write PNG file: " + filename);
        }
        return py::none();
    }

    py::object write_to_png_data(void) const
    {
        std::vector<uint8_t> png_data;
        png_data.reserve(bitmap->width() * bitmap->height() * 4);

        auto callback = [](void *closure, void *data, int size)
        {
            auto *output_vector = static_cast<std::vector<uint8_t> *>(closure);
            const auto *bytes = static_cast<const uint8_t *>(data);
            output_vector->assign(bytes, bytes + size);
        };

        if (!bitmap->writeToPng(callback, &png_data))
        {
            throw std::runtime_error("Failed to encode bitmap as PNG data.");
        }

        return py::bytes(reinterpret_cast<const char *>(png_data.data()), png_data.size());
    }
};

struct PyDocument
{
private:
    std::shared_ptr<lunasvg::Document> document;

public:
    PyDocument(const std::shared_ptr<lunasvg::Document> &doc) : document(doc)
    {
        if (!document)
        {
            throw std::runtime_error("Document is null.");
        }
    }

    py::object __repr__(void)
    {
        return py::str("<Document width=" + std::to_string(document->width()) + " height=" + std::to_string(document->height()) + ">");
    }

    static py::object load_from_file(const py::object &pyfilename)
    {
        if (pyfilename.is_none())
        {
            throw std::invalid_argument("Filename cannot be None.");
        }
        std::string filename = py::str(pyfilename).cast<std::string>();
        auto doc = lunasvg::Document::loadFromFile(filename);
        if (!doc)
        {
            throw std::runtime_error("Failed to load SVG file: " + filename);
        }
        return py::cast(PyDocument(std::shared_ptr<lunasvg::Document>(std::move(doc))));
    }

    static py::object load_from_data(const py::object &pydata)
    {
        if (pydata.is_none())
        {
            throw std::invalid_argument("Data cannot be None.");
        }
        std::string data;
        if (py::isinstance<py::bytes>(pydata))
        {
            data = py::bytes(pydata).cast<std::string>();
        }
        else if (py::isinstance<py::bytearray>(pydata))
        {
            data = py::bytearray(pydata).cast<std::string>();
        }
        else if (py::isinstance<py::str>(pydata))
        {
            data = py::str(pydata).cast<std::string>();
        }
        else
        {
            throw std::invalid_argument("Data must be bytes, bytearray, or string.");
        }
        if (data.empty())
        {
            throw std::invalid_argument("Data cannot be empty.");
        }
        auto doc = lunasvg::Document::loadFromData(data.c_str(), data.size());
        if (!doc)
        {
            throw std::runtime_error("Failed to load SVG data.");
        }
        return py::cast(PyDocument(std::shared_ptr<lunasvg::Document>(std::move(doc))));
    }

    py::object applyStyleSheet(const py::object &pycontent)
    {
        if (pycontent.is_none())
        {
            throw std::invalid_argument("Content cannot be None.");
        }
        if (!py::isinstance<py::str>(pycontent))
        {
            throw std::invalid_argument("Content must be a string.");
        }
        std::string content = py::str(pycontent).cast<std::string>();
        document->applyStyleSheet(content);
        return py::none();
    }

    py::object render_to_bitmap(std::int32_t width, std::int32_t height, std::uint32_t background_color)
    {
        if (width == 0)
        {
            width = static_cast<std::int32_t>(document->width());
        }
        if (height == 0)
        {
            height = static_cast<std::int32_t>(document->height());
        }
        if (!document)
        {
            throw std::runtime_error("Document is null.");
        }
        auto bitmap = document->renderToBitmap(width, height, background_color);
        if (bitmap.isNull())
        {
            throw std::runtime_error("Failed to render SVG document to bitmap.");
        }
        return py::cast(PyBitmap(std::make_shared<lunasvg::Bitmap>(std::move(bitmap))));
    }
};

PYBIND11_MODULE(pylunasvg, m)
{
    m.doc() = "Python bindings for lunasvg";

    m.attr("__version__") = VERSION_INFO;
    m.attr("__author__") = "Damiano Mazzella";
    m.attr("__license__") = "MIT";
    m.attr("__lunasvg_version__") = lunasvg_version_string();

    py::class_<PyBitmap> PyBitmapClass(m, "Bitmap");
    PyBitmapClass.def(py::init<const std::shared_ptr<lunasvg::Bitmap> &>());
    PyBitmapClass.def("__repr__", &PyBitmap::__repr__);
    PyBitmapClass.def("convert_to_rgba", &PyBitmap::convert_to_rgba, "Convert the bitmap to RGBA format");
    PyBitmapClass.def("write_to_png", &PyBitmap::write_to_png, py::arg("filename"), "Write the bitmap to a PNG file with the specified filename");
    PyBitmapClass.def("write_to_png_data", &PyBitmap::write_to_png_data, "Write the bitmap to a PNG and return the data as bytes");
    PyBitmapClass.def_property_readonly("data", &PyBitmap::get_data, "Get the raw pixel data of the bitmap as bytes");
    PyBitmapClass.def_property_readonly("width", &PyBitmap::get_width, "Get the width of the bitmap");
    PyBitmapClass.def_property_readonly("height", &PyBitmap::get_height, "Get the height of the bitmap");

    py::class_<PyDocument> PyDocumentClass(m, "Document");
    PyDocumentClass.def(py::init<const std::shared_ptr<lunasvg::Document> &>());
    PyDocumentClass.def("__repr__", &PyDocument::__repr__);
    PyDocumentClass.def_static("load_from_file", &PyDocument::load_from_file, py::arg("filename"), "Load an SVG document from a file");
    PyDocumentClass.def_static("load_from_data", &PyDocument::load_from_data, py::arg("data"), "Load an SVG document from a string containing SVG data");
    PyDocumentClass.def("apply_style_sheet", &PyDocument::applyStyleSheet, py::arg("content"), "Apply a CSS stylesheet to the document");
    PyDocumentClass.def("render_to_bitmap", &PyDocument::render_to_bitmap, py::arg("width") = -1, py::arg("height") = -1, py::arg("background_color") = 0x00000000, "Render the SVG document to a bitmap with the specified width, height, and background color");
}