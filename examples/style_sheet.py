import pylunasvg

k_landspace_content = """
<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 800 600" width="800" height="600">
  <!-- Background (Sky) -->
  <rect width="800" height="600" class="sky"/>

  <!-- Sun -->
  <circle cx="650" cy="150" r="80" class="sun" />

  <!-- Clouds -->
  <ellipse cx="200" cy="150" rx="100" ry="40" class="cloud" />
  <ellipse cx="250" cy="200" rx="120" ry="50" class="cloud" />
  <ellipse cx="500" cy="80" rx="150" ry="60" class="cloud" />
  <ellipse cx="550" cy="120" rx="120" ry="50" class="cloud" />

  <!-- Mountains -->
  <polygon points="0,450 200,200 400,450" class="mountain" />
  <polygon points="200,450 400,100 600,450" class="mountain" />
  <polygon points="400,450 600,250 800,450" class="mountain" />

  <!-- Foreground (Ground) -->
  <rect y="450" width="800" height="150" class="ground" />
</svg>
"""

k_summer_style = """
.sky { fill: #4A90E2; }
.sun { fill: #FF7F00; }
.mountain { fill: #2E3A59; }
.cloud { fill: #FFFFFF; opacity: 0.8; }
.ground { fill: #2E8B57; }
"""

k_winter_style = """
.sky { fill: #87CEEB; }
.sun { fill: #ADD8E6; }
.mountain { fill: #2F4F4F; }
.cloud { fill: #FFFFFF; opacity: 0.8; }
.ground { fill: #FFFAFA; }
"""


def main():
    # Load the SVG data from a file
    svg = pylunasvg.Document.load_from_data(k_landspace_content)
    if svg is None:
        raise ValueError("Could not load SVG file.")

    # Print the loaded SVG document
    print("Loaded SVG:", svg)

    svg.apply_style_sheet(k_summer_style)
    svg.render_to_bitmap().write_to_png("summer.png")
    print("Saved rendered bitmap to summer.png")

    svg.apply_style_sheet(k_winter_style)
    svg.render_to_bitmap().write_to_png("winter.png")
    print("Saved rendered bitmap to winter.png")


if __name__ == "__main__":
    main()