from typing import Any, Optional

import pylunasvg
from PIL import Image, ImageFile


class SvgImageFile(ImageFile.ImageFile):
    format = "SVG"
    format_description = "Scalable Vector Graphics"

    def _open(self) -> None:
        document = pylunasvg.Document.load_from_data(self.fp.read())
        bitmap = document.render_to_bitmap()
        bitmap.convert_to_rgba()
        self._data = bitmap.data
        self._size = (bitmap.width, bitmap.height)
        self._mode = "RGBA"
        self._tile = [ImageFile._Tile("SVG", (0, 0, *self._size), 0)]

    def load(self) -> Any | None:
        image = Image.frombytes(self._mode, self._size, self._data)
        return image

    def convert(
        self, mode=None, matrix=None, dither=None, palette=Image.Palette.WEB, colors=256
    ):
        image = Image.frombytes(self._mode, self._size, self._data)
        if mode:
            image = image.convert(mode, matrix, dither, palette, colors)
        return image

    def copy(self) -> Any | None:
        image = Image.frombytes(self._mode, self._size, self._data)
        return image

    def show(self, title: Optional[str] = None) -> None:
        image = Image.frombytes(self._mode, self._size, self._data)
        image.show(title=title)

    def save(self, fp: Any, format: Optional[str] = None, **params: Any) -> None:
        if format is None:
            format = self.format
        if format.lower() == "svg":
            raise ValueError("Cannot save SVG format directly")
        image = Image.frombytes(self._mode, self._size, self._data)
        image.save(fp, format=format, **params)

    def transform(
        self,
        size,
        method,
        data=None,
        resample=Image.Resampling.NEAREST,
        fill=1,
        fillcolor=None,
    ):
        image = Image.frombytes(self._mode, self._size, self._data)
        transformed_image = image.transform(
            size, method, data, resample, fill, fillcolor
        )
        return transformed_image


# Register the plugin with Pillow
Image.register_open(SvgImageFile.format, SvgImageFile)
Image.register_extension(SvgImageFile.format, ".svg")
Image.register_mime(SvgImageFile.format, "image/svg+xml")
