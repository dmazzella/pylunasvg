#include <lunasvg.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

struct PyBitmap
{
private:
    std::shared_ptr<lunasvg::Bitmap> bitmap;

public:
    PyBitmap(const std::shared_ptr<lunasvg::Bitmap> &bmp) : bitmap(bmp) {}
    PyBitmap(int width, int height)
        : bitmap(std::make_shared<lunasvg::Bitmap>(width, height))
    {
        if (bitmap->isNull())
        {
            throw std::runtime_error("Failed to create bitmap: out of memory");
        }
    }

    static PyBitmap create_for_data(py::buffer data, int width, int height, int stride)
    {
        py::buffer_info info = data.request(true);
        if (height * stride > info.size)
        {
            throw std::runtime_error("Buffer is not long enough");
        }

        auto bitmap = std::make_shared<lunasvg::Bitmap>(
            static_cast<uint8_t *>(info.ptr), width, height, stride);
        if (bitmap->isNull())
        {
            throw std::runtime_error("Failed to create bitmap from data");
        }

        return PyBitmap(bitmap);
    }

    std::shared_ptr<lunasvg::Bitmap> get_bitmap() const { return bitmap; }

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

    py::int_ get_stride() const
    {
        return bitmap->stride();
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

    py::object clear(uint32_t color = 0)
    {
        bitmap->clear(color);
        return py::none();
    }
};

struct PyMatrix
{
private:
    std::shared_ptr<lunasvg::Matrix> matrix;

public:
    PyMatrix() : matrix(std::make_shared<lunasvg::Matrix>()) {}
    PyMatrix(float a, float b, float c, float d, float e, float f)
        : matrix(std::make_shared<lunasvg::Matrix>(a, b, c, d, e, f)) {}
    PyMatrix(const std::shared_ptr<lunasvg::Matrix> &m) : matrix(m) {}

    py::object __repr__(void)
    {
        return py::str("<Matrix [" + std::to_string(matrix->a) + " " + std::to_string(matrix->b) + " " + std::to_string(matrix->c) + " " + std::to_string(matrix->d) + " " + std::to_string(matrix->e) + " " + std::to_string(matrix->f) + "]>");
    }

    PyMatrix multiply(const PyMatrix &other)
    {
        auto result = std::make_shared<lunasvg::Matrix>(*matrix);
        result->multiply(*other.matrix);
        return PyMatrix(result);
    }

    PyMatrix translate(float tx, float ty)
    {
        auto result = std::make_shared<lunasvg::Matrix>(*matrix);
        result->translate(tx, ty);
        return PyMatrix(result);
    }

    PyMatrix scale(float sx, float sy)
    {
        auto result = std::make_shared<lunasvg::Matrix>(*matrix);
        result->scale(sx, sy);
        return PyMatrix(result);
    }

    PyMatrix rotate(float angle, float cx = 0.0f, float cy = 0.0f)
    {
        auto result = std::make_shared<lunasvg::Matrix>(*matrix);
        result->rotate(angle, cx, cy);
        return PyMatrix(result);
    }

    PyMatrix shear(float shx, float shy)
    {
        auto result = std::make_shared<lunasvg::Matrix>(*matrix);
        result->shear(shx, shy);
        return PyMatrix(result);
    }

    PyMatrix invert()
    {
        auto result = std::make_shared<lunasvg::Matrix>(*matrix);
        result->invert();
        return PyMatrix(result);
    }

    PyMatrix inverse() const
    {
        return PyMatrix(std::make_shared<lunasvg::Matrix>(matrix->inverse()));
    }

    void reset()
    {
        matrix->reset();
    }

    static PyMatrix translated(float tx, float ty)
    {
        return PyMatrix(std::make_shared<lunasvg::Matrix>(lunasvg::Matrix::translated(tx, ty)));
    }

    static PyMatrix scaled(float sx, float sy)
    {
        return PyMatrix(std::make_shared<lunasvg::Matrix>(lunasvg::Matrix::scaled(sx, sy)));
    }

    static PyMatrix rotated(float angle, float cx = 0.0f, float cy = 0.0f)
    {
        return PyMatrix(std::make_shared<lunasvg::Matrix>(lunasvg::Matrix::rotated(angle, cx, cy)));
    }

    static PyMatrix sheared(float shx, float shy)
    {
        return PyMatrix(std::make_shared<lunasvg::Matrix>(lunasvg::Matrix::sheared(shx, shy)));
    }

    float get_a() const { return matrix->a; }
    float get_b() const { return matrix->b; }
    float get_c() const { return matrix->c; }
    float get_d() const { return matrix->d; }
    float get_e() const { return matrix->e; }
    float get_f() const { return matrix->f; }

    void set_a(float value) { matrix->a = value; }
    void set_b(float value) { matrix->b = value; }
    void set_c(float value) { matrix->c = value; }
    void set_d(float value) { matrix->d = value; }
    void set_e(float value) { matrix->e = value; }
    void set_f(float value) { matrix->f = value; }

    std::shared_ptr<lunasvg::Matrix> get_matrix() const { return matrix; }

    PyMatrix operator*(const PyMatrix &other) const
    {
        return PyMatrix(std::make_shared<lunasvg::Matrix>(*matrix * *other.matrix));
    }

    PyMatrix &operator*=(const PyMatrix &other)
    {
        *matrix *= *other.matrix;
        return *this;
    }

    PyMatrix operator~() const
    {
        return inverse();
    }

    py::ssize_t __len__() const
    {
        return 6;
    }

    py::float_ __getitem__(py::ssize_t index) const
    {
        switch (index)
        {
        case 0:
            return matrix->a;
        case 1:
            return matrix->b;
        case 2:
            return matrix->c;
        case 3:
            return matrix->d;
        case 4:
            return matrix->e;
        case 5:
            return matrix->f;
        default:
            throw py::index_error("Matrix index out of range");
        }
    }
};

struct PyBox
{
private:
    std::shared_ptr<lunasvg::Box> box;

public:
    PyBox() : box(std::make_shared<lunasvg::Box>()) {}
    PyBox(float x, float y, float w, float h) : box(std::make_shared<lunasvg::Box>(x, y, w, h)) {}
    PyBox(const std::shared_ptr<lunasvg::Box> &b) : box(b) {}

    py::object __repr__(void)
    {
        return py::str("<Box [x=" + std::to_string(box->x) + ", y=" + std::to_string(box->y) + ", width=" + std::to_string(box->w) + ", height=" + std::to_string(box->h) + "]>");
    }

    PyBox transform(const PyMatrix &matrix)
    {
        auto result = std::make_shared<lunasvg::Box>(*box);
        result->transform(*matrix.get_matrix());
        return PyBox(result);
    }

    PyBox transformed(const PyMatrix &matrix) const
    {
        return PyBox(std::make_shared<lunasvg::Box>(box->transformed(*matrix.get_matrix())));
    }

    float get_x() const { return box->x; }
    float get_y() const { return box->y; }
    float get_w() const { return box->w; }
    float get_h() const { return box->h; }

    void set_x(float value) { box->x = value; }
    void set_y(float value) { box->y = value; }
    void set_w(float value) { box->w = value; }
    void set_h(float value) { box->h = value; }

    std::shared_ptr<lunasvg::Box> get_box() const { return box; }

    py::ssize_t __len__() const
    {
        return 4;
    }

    py::float_ __getitem__(py::ssize_t index) const
    {
        switch (index)
        {
        case 0:
            return box->x;
        case 1:
            return box->y;
        case 2:
            return box->w;
        case 3:
            return box->h;
        default:
            throw py::index_error("Box index out of range");
        }
    }
};

struct PyDocument;

struct PyElement
{
private:
    std::shared_ptr<lunasvg::Element> element;
    PyDocument *owner_document_ref; // Non-owning reference to the owner document

public:
    PyElement(std::shared_ptr<lunasvg::Element> elem, PyDocument *doc)
        : element(elem), owner_document_ref(doc) {}

    py::object __repr__(void)
    {
        return py::str("<Element>");
    }

    py::object __richcompare__(PyElement *other, int op)
    {
        if (op == Py_EQ)
        {
            if (*element == *other->element)
                return py::bool_(true);
            return py::bool_(false);
        }
        else if (op == Py_NE)
        {
            if (*element != *other->element)
                return py::bool_(true);
            return py::bool_(false);
        }
        return py::none();
    }

    py::bool_ has_attribute(const std::string &name)
    {
        return py::bool_(element->hasAttribute(name));
    }

    py::str get_attribute(const std::string &name)
    {
        return py::str(element->getAttribute(name));
    }

    py::object set_attribute(const std::string &name, const std::string &value)
    {
        element->setAttribute(name, value);
        return py::none();
    }

    py::object render(PyBitmap &bitmap, py::object pymatrix = py::none())
    {
        lunasvg::Matrix matrix;
        if (!pymatrix.is_none())
        {
            PyMatrix *matrix_obj = pymatrix.cast<PyMatrix *>();
            matrix = *matrix_obj->get_matrix();
        }

        element->render(*(bitmap.get_bitmap()), matrix);
        return py::none();
    }

    py::object render_to_bitmap(int width = -1, int height = -1, uint32_t background_color = 0)
    {
        auto bitmap = element->renderToBitmap(width, height, background_color);
        if (bitmap.isNull())
        {
            throw std::runtime_error("Failed to render element to bitmap");
        }
        return py::cast(PyBitmap(std::make_shared<lunasvg::Bitmap>(std::move(bitmap))));
    }

    PyMatrix get_local_matrix()
    {
        return PyMatrix(std::make_shared<lunasvg::Matrix>(element->getLocalMatrix()));
    }

    PyMatrix get_global_matrix()
    {
        return PyMatrix(std::make_shared<lunasvg::Matrix>(element->getGlobalMatrix()));
    }

    PyBox get_local_bounding_box()
    {
        return PyBox(std::make_shared<lunasvg::Box>(element->getLocalBoundingBox()));
    }

    PyBox get_global_bounding_box()
    {
        return PyBox(std::make_shared<lunasvg::Box>(element->getGlobalBoundingBox()));
    }

    PyBox get_bounding_box()
    {
        return PyBox(std::make_shared<lunasvg::Box>(element->getBoundingBox()));
    }

    py::object parent_element()
    {
        auto parent = element->parentElement();
        if (parent.isNull())
        {
            return py::none();
        }
        return py::cast(PyElement(std::make_shared<lunasvg::Element>(parent), owner_document_ref));
    }

    py::object owner_document()
    {
        if (owner_document_ref)
        {
            return py::cast(owner_document_ref);
        }
        return py::none();
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

    py::object apply_style_sheet(const py::object &pycontent)
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

    py::float_ get_width() const
    {
        return document->width();
    }

    py::float_ get_height() const
    {
        return document->height();
    }

    PyBox get_bounding_box() const
    {
        return PyBox(std::make_shared<lunasvg::Box>(document->boundingBox()));
    }

    py::object update_layout()
    {
        document->updateLayout();
        return py::none();
    }

    py::object render(PyBitmap &bitmap, py::object pymatrix = py::none())
    {
        lunasvg::Matrix matrix;
        if (!pymatrix.is_none())
        {
            PyMatrix *matrix_obj = pymatrix.cast<PyMatrix *>();
            matrix = *matrix_obj->get_matrix();
        }

        document->render(*(bitmap.get_bitmap()), matrix);
        return py::none();
    }

    py::object get_element_by_id(const std::string &id)
    {
        auto element = document->getElementById(id);
        if (element.isNull())
        {
            return py::none();
        }
        return py::cast(PyElement(std::make_shared<lunasvg::Element>(element), this));
    }

    py::object document_element()
    {
        auto element = document->documentElement();
        if (element.isNull())
        {
            return py::none();
        }
        return py::cast(PyElement(std::make_shared<lunasvg::Element>(element), this));
    }
};

PYBIND11_MODULE(pylunasvg, m)
{
    m.doc() = "Python bindings for lunasvg";

    m.attr("__version__") = VERSION_INFO;
    m.attr("__author__") = "Damiano Mazzella";
    m.attr("__license__") = "MIT";
    m.attr("__lunasvg_version__") = lunasvg_version_string();

    // Definition of Matrix class
    py::class_<PyMatrix> PyMatrixClass(m, "Matrix");
    PyMatrixClass.def(py::init<>());
    PyMatrixClass.def(py::init<float, float, float, float, float, float>(),
                      py::arg("a") = 1.0f, py::arg("b") = 0.0f, py::arg("c") = 0.0f,
                      py::arg("d") = 1.0f, py::arg("e") = 0.0f, py::arg("f") = 0.0f);
    PyMatrixClass.def("__repr__", &PyMatrix::__repr__);
    PyMatrixClass.def("multiply", &PyMatrix::multiply, py::arg("other"), "Multiply this matrix with another");
    PyMatrixClass.def("translate", &PyMatrix::translate, py::arg("tx"), py::arg("ty"), "Apply a translation to the matrix");
    PyMatrixClass.def("scale", &PyMatrix::scale, py::arg("sx"), py::arg("sy"), "Apply a scaling to the matrix");
    PyMatrixClass.def("rotate", &PyMatrix::rotate, py::arg("angle"), py::arg("cx") = 0.0f, py::arg("cy") = 0.0f, "Apply a rotation to the matrix");
    PyMatrixClass.def("shear", &PyMatrix::shear, py::arg("shx"), py::arg("shy"), "Apply a shear to the matrix");
    PyMatrixClass.def("invert", &PyMatrix::invert, "Invert the matrix and return the result");
    PyMatrixClass.def("inverse", &PyMatrix::inverse, "Return the inverse of the matrix");
    PyMatrixClass.def("reset", &PyMatrix::reset, "Reset the matrix to identity");
    PyMatrixClass.def_static("translated", &PyMatrix::translated, py::arg("tx"), py::arg("ty"), "Create a translation matrix");
    PyMatrixClass.def_static("scaled", &PyMatrix::scaled, py::arg("sx"), py::arg("sy"), "Create a scaling matrix");
    PyMatrixClass.def_static("rotated", &PyMatrix::rotated, py::arg("angle"), py::arg("cx") = 0.0f, py::arg("cy") = 0.0f, "Create a rotation matrix");
    PyMatrixClass.def_static("sheared", &PyMatrix::sheared, py::arg("shx"), py::arg("shy"), "Create a shear matrix");
    PyMatrixClass.def_property("a", &PyMatrix::get_a, &PyMatrix::set_a);
    PyMatrixClass.def_property("b", &PyMatrix::get_b, &PyMatrix::set_b);
    PyMatrixClass.def_property("c", &PyMatrix::get_c, &PyMatrix::set_c);
    PyMatrixClass.def_property("d", &PyMatrix::get_d, &PyMatrix::set_d);
    PyMatrixClass.def_property("e", &PyMatrix::get_e, &PyMatrix::set_e);
    PyMatrixClass.def_property("f", &PyMatrix::get_f, &PyMatrix::set_f);
    PyMatrixClass.def("__len__", &PyMatrix::__len__);
    PyMatrixClass.def("__getitem__", &PyMatrix::__getitem__);
    PyMatrixClass.def("__mul__", &PyMatrix::operator*, py::is_operator(), py::arg("other"), "Multiply this matrix with another matrix");
    PyMatrixClass.def("__imul__", &PyMatrix::operator*=, py::is_operator(), py::arg("other"), "Multiply this matrix with another matrix and assign the result to this matrix");
    PyMatrixClass.def("__invert__", &PyMatrix::operator~, py::is_operator(), "Return the inverse of this matrix");

    // Definition of Box class
    py::class_<PyBox> PyBoxClass(m, "Box");
    PyBoxClass.def(py::init<>());
    PyBoxClass.def(py::init<float, float, float, float>(),
                   py::arg("x") = 0.0f, py::arg("y") = 0.0f, py::arg("width") = 0.0f, py::arg("height") = 0.0f);
    PyBoxClass.def("__repr__", &PyBox::__repr__);
    PyBoxClass.def("transform", &PyBox::transform, py::arg("matrix"), "Transform the box with the given matrix");
    PyBoxClass.def("transformed", &PyBox::transformed, py::arg("matrix"), "Return a copy of the box transformed with the given matrix");
    PyBoxClass.def_property("x", &PyBox::get_x, &PyBox::set_x);
    PyBoxClass.def_property("y", &PyBox::get_y, &PyBox::set_y);
    PyBoxClass.def_property("width", &PyBox::get_w, &PyBox::set_w);
    PyBoxClass.def_property("height", &PyBox::get_h, &PyBox::set_h);
    PyBoxClass.def("__len__", &PyBox::__len__);
    PyBoxClass.def("__getitem__", &PyBox::__getitem__);

    py::class_<PyBitmap> PyBitmapClass(m, "Bitmap");
    PyBitmapClass.def(py::init<const std::shared_ptr<lunasvg::Bitmap> &>());
    PyBitmapClass.def(py::init<int, int>());
    PyBitmapClass.def_static("create_for_data", &PyBitmap::create_for_data, py::arg("data"), py::arg("width"), py::arg("height"), py::arg("stride"));
    PyBitmapClass.def("__repr__", &PyBitmap::__repr__);
    PyBitmapClass.def("convert_to_rgba", &PyBitmap::convert_to_rgba, "Convert the bitmap to RGBA format");
    PyBitmapClass.def("write_to_png", &PyBitmap::write_to_png, py::arg("filename"), "Write the bitmap to a PNG file with the specified filename");
    PyBitmapClass.def("write_to_png_data", &PyBitmap::write_to_png_data, "Write the bitmap to a PNG and return the data as bytes");
    PyBitmapClass.def_property_readonly("data", &PyBitmap::get_data, "Get the raw pixel data of the bitmap as bytes");
    PyBitmapClass.def_property_readonly("width", &PyBitmap::get_width, "Get the width of the bitmap");
    PyBitmapClass.def_property_readonly("height", &PyBitmap::get_height, "Get the height of the bitmap");
    PyBitmapClass.def_property_readonly("stride", &PyBitmap::get_stride, "Get the stride of the bitmap");
    PyBitmapClass.def("clear", &PyBitmap::clear, py::arg("color") = 0, "Clear the bitmap with the specified color");

    py::class_<PyDocument> PyDocumentClass(m, "Document");
    PyDocumentClass.def(py::init<const std::shared_ptr<lunasvg::Document> &>());
    PyDocumentClass.def("__repr__", &PyDocument::__repr__);
    PyDocumentClass.def_static("load_from_file", &PyDocument::load_from_file, py::arg("filename"), "Load an SVG document from a file");
    PyDocumentClass.def_static("load_from_data", &PyDocument::load_from_data, py::arg("data"), "Load an SVG document from a string containing SVG data");
    PyDocumentClass.def("apply_style_sheet", &PyDocument::apply_style_sheet, py::arg("content"), "Apply a CSS stylesheet to the document");
    PyDocumentClass.def("render_to_bitmap", &PyDocument::render_to_bitmap, py::arg("width") = -1, py::arg("height") = -1, py::arg("background_color") = 0x00000000, "Render the SVG document to a bitmap with the specified width, height, and background color");
    PyDocumentClass.def_property_readonly("width", &PyDocument::get_width, "Get the width of the document");
    PyDocumentClass.def_property_readonly("height", &PyDocument::get_height, "Get the height of the document");
    PyDocumentClass.def_property_readonly("bounding_box", &PyDocument::get_bounding_box, "Get the bounding box of the document");
    PyDocumentClass.def("update_layout", &PyDocument::update_layout, "Update the layout of the document");
    PyDocumentClass.def("render", &PyDocument::render, py::arg("bitmap"), py::arg("matrix") = py::none(), "Render the document to a bitmap");
    PyDocumentClass.def("get_element_by_id", &PyDocument::get_element_by_id, py::arg("id"), "Get an element by its ID");
    PyDocumentClass.def("document_element", &PyDocument::document_element, "Get the root element of the document");

    // Definition of Element class
    py::class_<PyElement> PyElementClass(m, "Element");
    PyElementClass.def("__repr__", &PyElement::__repr__);
    PyElementClass.def("has_attribute", &PyElement::has_attribute, py::arg("name"), "Check if the element has the specified attribute");
    PyElementClass.def("get_attribute", &PyElement::get_attribute, py::arg("name"), "Get the value of the specified attribute");
    PyElementClass.def("set_attribute", &PyElement::set_attribute, py::arg("name"), py::arg("value"), "Set the value of the specified attribute");
    PyElementClass.def("render", &PyElement::render, py::arg("bitmap"), py::arg("matrix") = py::none(), "Render the element to a bitmap");
    PyElementClass.def("render_to_bitmap", &PyElement::render_to_bitmap,
                       py::arg("width") = -1, py::arg("height") = -1, py::arg("background_color") = 0,
                       "Render the element to a new bitmap");
    PyElementClass.def("get_local_matrix", &PyElement::get_local_matrix, "Get the local transformation matrix");
    PyElementClass.def("get_global_matrix", &PyElement::get_global_matrix, "Get the global transformation matrix");
    PyElementClass.def("get_local_bounding_box", &PyElement::get_local_bounding_box, "Get the local bounding box");
    PyElementClass.def("get_global_bounding_box", &PyElement::get_global_bounding_box, "Get the global bounding box");
    PyElementClass.def("get_bounding_box", &PyElement::get_bounding_box, "Get the element's bounding box");
    PyElementClass.def("parent_element", &PyElement::parent_element, "Get the parent element");
    PyElementClass.def("owner_document", &PyElement::owner_document, "Get the owner document");

    m.def(
        "add_font_face_from_file",
        [](const std::string &family, bool bold, bool italic, const std::string &filename)
        {
            bool success = lunasvg_add_font_face_from_file(family.c_str(), bold, italic, filename.c_str());
            if (!success)
            {
                throw std::runtime_error("Failed to add font face from file");
            }
            return py::none();
        },
        py::arg("family"), py::arg("bold"), py::arg("italic"), py::arg("filename"));

    m.def(
        "add_font_face_from_data",
        [](const std::string &family, bool bold, bool italic, py::bytes data)
        {
            py::buffer_info info = py::buffer(data).request();
            bool success = lunasvg_add_font_face_from_data(family.c_str(), bold, italic, info.ptr, info.size, nullptr, nullptr);
            if (!success)
            {
                throw std::runtime_error("Failed to add font face from data");
            }
            return py::none();
        },
        py::arg("family"), py::arg("bold"), py::arg("italic"), py::arg("data"));
}