import pylunasvg
import pathlib
import argparse


def convert_svg_to_png(svg_path, png_path, width=-1, height=-1, bg_color=0x000000):
    # Load the SVG file
    svg = pylunasvg.Document.load_from_file(svg_path)
    if svg is None:
        raise ValueError(f"Could not load SVG file {svg_path}.")
    print("Loaded SVG:", svg)

    svg.render_to_bitmap(width, height, bg_color).write_to_png(png_path)
    print(f"Converted {svg_path} to {png_path}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Convert an SVG file to a PNG file.")
    parser.add_argument(
        "svg_path", type=pathlib.Path, help="Path to the input SVG file."
    )
    parser.add_argument(
        "--width",
        type=int,
        default=-1,
        help="Width of the output PNG (default: original size).",
    )
    parser.add_argument(
        "--height",
        type=int,
        default=-1,
        help="Height of the output PNG (default: original size).",
    )
    parser.add_argument(
        "--bg_color",
        type=lambda x: int(x, 16),
        default=0x00000000,
        help="Background color in hex format (default: 0x00000000).",
    )

    args = parser.parse_args()

    svg_file = args.svg_path
    if svg_file.suffix.lower() != ".svg":
        raise ValueError("Input file must be an SVG file.")

    if not svg_file.exists():
        raise FileNotFoundError(f"SVG file {svg_file} does not exist.")

    png_file = svg_file.with_suffix(".png")

    convert_svg_to_png(svg_file, png_file, args.width, args.height, args.bg_color)
