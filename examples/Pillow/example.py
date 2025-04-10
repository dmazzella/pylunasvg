import SvgImagePlugin  # noqa: F401
from PIL import Image


with Image.open("example.svg") as svg_img:
    # Perform operations on the SVG image
    print(f"SVG image size: {svg_img.size}")
    print(f"SVG image mode: {svg_img.mode}")
    print(f"SVG image format: {svg_img.format}")
    # Save the SVG image as a PNG file
    svg_img.save("example.png", "PNG")
    # Show the SVG image
    svg_img.show(title="SVG Image")
