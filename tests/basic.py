import pylunasvg


def test_main():
    assert hasattr(pylunasvg, "Matrix")
    assert hasattr(pylunasvg, "Box")
    assert hasattr(pylunasvg, "Document")
    assert hasattr(pylunasvg, "Element")
    assert hasattr(pylunasvg, "Bitmap")
    assert hasattr(pylunasvg, "__lunasvg_version__")
