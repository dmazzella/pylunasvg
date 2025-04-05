import pylunasvg
from qrcodegen import QrCode


def to_svg_str(qr: QrCode, border: int) -> str:
    """Returns a string of SVG code for an image depicting the given QR Code, with the given number
    of border modules. The string always uses Unix newlines (\n), regardless of the platform.
    """
    if border < 0:
        raise ValueError("Border must be non-negative")
    parts: list[str] = []
    for y in range(qr.get_size()):
        for x in range(qr.get_size()):
            if qr.get_module(x, y):
                parts.append(f"M{x+border},{y+border}h1v1h-1z")
    return f"""<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN" "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd">
<svg xmlns="http://www.w3.org/2000/svg" version="1.1" viewBox="0 0 {qr.get_size()+border*2} {qr.get_size()+border*2}" stroke="none">
    <rect width="100%" height="100%" fill="#FFFFFF"/>
    <path d="{" ".join(parts)}" fill="#000000"/>
</svg>
"""


def main():
    qr = QrCode.encode_text("Hello, World!", QrCode.Ecc.HIGH)
    qr_svg = to_svg_str(qr, 10)

    svg = pylunasvg.Document.load_from_data(qr_svg)
    if svg is None:
        raise ValueError("Could not load SVG file.")
    svg.render_to_bitmap().write_to_png("qrcode.png")
    print("QR Code generated and saved as qrcode.png")


if __name__ == "__main__":
    main()
