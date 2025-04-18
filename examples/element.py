# This example demonstrates how to manipulate SVG elements using the pylunasvg library.
# It includes loading an SVG document, modifying attributes, rendering elements,
# and navigating the element hierarchy.
import pylunasvg

example_svg = """<?xml version="1.0" encoding="UTF-8"?>
<svg width="200" height="200" xmlns="http://www.w3.org/2000/svg">
    <rect id="myrect" x="50" y="50" width="100" height="100" fill="blue" />
    <circle id="mycircle" cx="100" cy="100" r="40" fill="red" />
</svg>
"""


def main():
    # 1. Load an SVG document
    doc = pylunasvg.Document.load_from_data(example_svg)

    # 2. Retrieve elements from the document
    rect_element = doc.get_element_by_id("myrect")
    circle_element = doc.get_element_by_id("mycircle")
    root_element = doc.document_element()

    # 3. Read the attributes of the elements
    if rect_element.has_attribute("fill"):
        print(f"Rectangle fill color: {rect_element.get_attribute('fill')}")

    # 4. Modify the attributes of the elements
    rect_element.set_attribute("fill", "green")
    circle_element.set_attribute("r", "50")  # Aumenta il raggio

    # 5. Get geometric information
    rect_box = rect_element.get_bounding_box()
    print(
        f"Rectangle bounding box: x={rect_box.x}, y={rect_box.y}, width={rect_box.width}, height={rect_box.height}"
    )

    # 6. Get the transformation matrix
    rect_matrix = rect_element.get_local_matrix()
    print(f"Rectangle transformation matrix: {rect_matrix}")

    # 7. Apply a transformation (rotate the rectangle)
    rect_element.set_attribute("transform", "rotate(45, 100, 100)")

    # 8. Rendering of the single element
    bitmap = rect_element.render_to_bitmap(
        width=200, height=200, background_color=0xFFFFFFFF
    )
    bitmap.write_to_png("rect_only.png")

    # 9. Rendering of the entire modified document
    doc_bitmap = doc.render_to_bitmap(
        width=200, height=200, background_color=0xFFFFFFFF
    )
    doc_bitmap.write_to_png("modified_document.png")

    # 10. Navigate the element hierarchy
    parent = circle_element.parent_element()
    if parent:
        print(f"Circle's parent is the root element: {parent == root_element}")

    # 11. Verify the owner document
    doc_owner = circle_element.owner_document()
    if doc_owner:
        print("Circle element has a reference to its owner document")

    print(
        "Example completed. Images generated: rect_only.png and modified_document.png"
    )


if __name__ == "__main__":
    main()
