"""
Python bindings for lunasvg, a standalone SVG rendering library.
This module provides classes and functions for loading, manipulating,
and rendering SVG documents.
"""

class Matrix:
    """
    A 2D transformation matrix representing affine transformations.
    
    The matrix is represented in the form:
    [a c e]
    [b d f]
    [0 0 1]
    """
    def __init__(self, a: float = 1.0, b: float = 0.0, c: float = 0.0, d: float = 1.0, e: float = 0.0, f: float = 0.0) -> None:
        """
        Initialize a new transformation matrix.
        
        Args:
            a: The value at position (0,0)
            b: The value at position (1,0)
            c: The value at position (0,1)
            d: The value at position (1,1)
            e: The translation in x direction
            f: The translation in y direction
        """
        ...
    
    def __repr__(self) -> str:
        """Return string representation of the matrix."""
        ...
    
    def multiply(self, other: 'Matrix') -> 'Matrix':
        """
        Multiply this matrix with another.
        
        Args:
            other: The matrix to multiply with
            
        Returns:
            A new matrix with the result of multiplication
        """
        ...
    
    def translate(self, tx: float, ty: float) -> 'Matrix':
        """
        Apply a translation to the matrix.
        
        Args:
            tx: Translation along x-axis
            ty: Translation along y-axis
            
        Returns:
            A new matrix with the translation applied
        """
        ...
    
    def scale(self, sx: float, sy: float) -> 'Matrix':
        """
        Apply scaling to the matrix.
        
        Args:
            sx: Scale factor for x-axis
            sy: Scale factor for y-axis
            
        Returns:
            A new matrix with the scaling applied
        """
        ...
    
    def rotate(self, angle: float, cx: float = 0.0, cy: float = 0.0) -> 'Matrix':
        """
        Apply rotation to the matrix.
        
        Args:
            angle: Rotation angle in degrees
            cx: X coordinate of the rotation center
            cy: Y coordinate of the rotation center
            
        Returns:
            A new matrix with the rotation applied
        """
        ...
    
    def shear(self, shx: float, shy: float) -> 'Matrix':
        """
        Apply shearing to the matrix.
        
        Args:
            shx: Shear factor along x-axis
            shy: Shear factor along y-axis
            
        Returns:
            A new matrix with the shearing applied
        """
        ...
    
    def invert(self) -> 'Matrix':
        """
        Invert the matrix and return the result.
        
        Returns:
            A new matrix containing the inverted matrix
        """
        ...
    
    def inverse(self) -> 'Matrix':
        """
        Return the inverse of the matrix.
        
        Returns:
            A new matrix representing the inverse of this matrix
        """
        ...
    
    def reset(self) -> None:
        """Reset the matrix to identity."""
        ...
    
    @staticmethod
    def translated(tx: float, ty: float) -> 'Matrix':
        """
        Create a translation matrix.
        
        Args:
            tx: Translation along x-axis
            ty: Translation along y-axis
            
        Returns:
            A new translation matrix
        """
        ...
    
    @staticmethod
    def scaled(sx: float, sy: float) -> 'Matrix':
        """
        Create a scaling matrix.
        
        Args:
            sx: Scale factor for x-axis
            sy: Scale factor for y-axis
            
        Returns:
            A new scaling matrix
        """
        ...
    
    @staticmethod
    def rotated(angle: float, cx: float = 0.0, cy: float = 0.0) -> 'Matrix':
        """
        Create a rotation matrix.
        
        Args:
            angle: Rotation angle in degrees
            cx: X coordinate of the rotation center
            cy: Y coordinate of the rotation center
            
        Returns:
            A new rotation matrix
        """
        ...
    
    @staticmethod
    def sheared(shx: float, shy: float) -> 'Matrix':
        """
        Create a shear matrix.
        
        Args:
            shx: Shear factor along x-axis
            shy: Shear factor along y-axis
            
        Returns:
            A new shear matrix
        """
        ...
    
    @property
    def a(self) -> float:
        """Get the value at position (0,0)."""
        ...
    
    @a.setter
    def a(self, value: float) -> None:
        """Set the value at position (0,0)."""
        ...
    
    @property
    def b(self) -> float:
        """Get the value at position (1,0)."""
        ...
    
    @b.setter
    def b(self, value: float) -> None:
        """Set the value at position (1,0)."""
        ...
    
    @property
    def c(self) -> float:
        """Get the value at position (0,1)."""
        ...
    
    @c.setter
    def c(self, value: float) -> None:
        """Set the value at position (0,1)."""
        ...
    
    @property
    def d(self) -> float:
        """Get the value at position (1,1)."""
        ...
    
    @d.setter
    def d(self, value: float) -> None:
        """Set the value at position (1,1)."""
        ...
    
    @property
    def e(self) -> float:
        """Get the translation in x direction."""
        ...
    
    @e.setter
    def e(self, value: float) -> None:
        """Set the translation in x direction."""
        ...
    
    @property
    def f(self) -> float:
        """Get the translation in y direction."""
        ...
    
    @f.setter
    def f(self, value: float) -> None:
        """Set the translation in y direction."""
        ...
    
    def __len__(self) -> int:
        """Return the number of elements in the matrix (always 6)."""
        ...
    
    def __getitem__(self, index: int) -> float:
        """
        Access matrix components by index.
        
        Args:
            index: Index between 0 and 5 corresponding to a, b, c, d, e, f
            
        Returns:
            The value at the specified index
            
        Raises:
            IndexError: If index is out of range
        """
        ...
    
    def __mul__(self, other: 'Matrix') -> 'Matrix':
        """
        Multiply this matrix with another matrix.
        
        Args:
            other: The matrix to multiply with
            
        Returns:
            A new matrix with the result of multiplication
        """
        ...
    
    def __imul__(self, other: 'Matrix') -> 'Matrix':
        """
        In-place multiplication with another matrix.
        
        Args:
            other: The matrix to multiply with
            
        Returns:
            This matrix after multiplication
        """
        ...
    
    def __invert__(self) -> 'Matrix':
        """
        Return the inverse of this matrix.
        
        Returns:
            A new matrix representing the inverse of this matrix
        """
        ...

class Box:
    """
    A 2D bounding box representing a rectangular area.
    """
    def __init__(self, x: float = 0.0, y: float = 0.0, width: float = 0.0, height: float = 0.0) -> None:
        """
        Initialize a new bounding box.
        
        Args:
            x: X coordinate of the top-left corner
            y: Y coordinate of the top-left corner
            width: Width of the box
            height: Height of the box
        """
        ...
    
    def __repr__(self) -> str:
        """Return string representation of the box."""
        ...
    
    def transform(self, matrix: Matrix) -> 'Box':
        """
        Transform the box with the given matrix.
        
        Args:
            matrix: Transformation matrix to apply
            
        Returns:
            A new box with the transformation applied
        """
        ...
    
    def transformed(self, matrix: Matrix) -> 'Box':
        """
        Return a copy of the box transformed with the given matrix.
        
        Args:
            matrix: Transformation matrix to apply
            
        Returns:
            A new box that is a transformed copy of this box
        """
        ...
    
    @property
    def x(self) -> float:
        """Get the X coordinate of the top-left corner."""
        ...
    
    @x.setter
    def x(self, value: float) -> None:
        """Set the X coordinate of the top-left corner."""
        ...
    
    @property
    def y(self) -> float:
        """Get the Y coordinate of the top-left corner."""
        ...
    
    @y.setter
    def y(self, value: float) -> None:
        """Set the Y coordinate of the top-left corner."""
        ...
    
    @property
    def width(self) -> float:
        """Get the width of the box."""
        ...
    
    @width.setter
    def width(self, value: float) -> None:
        """Set the width of the box."""
        ...
    
    @property
    def height(self) -> float:
        """Get the height of the box."""
        ...
    
    @height.setter
    def height(self, value: float) -> None:
        """Set the height of the box."""
        ...
    
    def __len__(self) -> int:
        """Return the number of elements in the box (always 4)."""
        ...
    
    def __getitem__(self, index: int) -> float:
        """
        Access box components by index.
        
        Args:
            index: Index between 0 and 3 corresponding to x, y, width, height
            
        Returns:
            The value at the specified index
            
        Raises:
            IndexError: If index is out of range
        """
        ...

class Bitmap:
    """
    A bitmap representation for rendering SVG content.
    
    The bitmap stores pixel data in RGBA format, 8 bits per channel.
    """
    def __init__(self, width: int, height: int) -> None:
        """
        Initialize a new bitmap with the specified dimensions.
        
        Args:
            width: Width of the bitmap in pixels
            height: Height of the bitmap in pixels
            
        Raises:
            RuntimeError: If bitmap creation fails (e.g., out of memory)
        """
        ...
    
    @staticmethod
    def create_for_data(data: bytes, width: int, height: int, stride: int) -> 'Bitmap':
        """
        Create a bitmap using the provided pixel data.
        
        Args:
            data: Raw pixel data
            width: Width of the bitmap in pixels
            height: Height of the bitmap in pixels
            stride: Number of bytes per row
            
        Returns:
            A new bitmap using the provided pixel data
            
        Raises:
            RuntimeError: If bitmap creation fails
        """
        ...
    
    def __repr__(self) -> str:
        """Return string representation of the bitmap."""
        ...
    
    def convert_to_rgba(self) -> None:
        """
        Convert the bitmap to RGBA format.
        
        Raises:
            RuntimeError: If the bitmap is null
        """
        ...
    
    def write_to_png(self, filename: str) -> None:
        """
        Write the bitmap to a PNG file with the specified filename.
        
        Args:
            filename: Path to write the PNG file
            
        Raises:
            RuntimeError: If writing the PNG file fails
            ValueError: If filename is None
        """
        ...
    
    def write_to_png_data(self) -> bytes:
        """
        Write the bitmap to a PNG and return the data as bytes.
        
        Returns:
            PNG encoded data as bytes
            
        Raises:
            RuntimeError: If encoding to PNG fails
        """
        ...
    
    @property
    def data(self) -> bytes:
        """
        Get the raw pixel data of the bitmap as bytes.
        
        Returns:
            Raw pixel data in RGBA format
            
        Raises:
            RuntimeError: If the bitmap is null
        """
        ...
    
    @property
    def width(self) -> int:
        """Get the width of the bitmap in pixels."""
        ...
    
    @property
    def height(self) -> int:
        """Get the height of the bitmap in pixels."""
        ...
    
    @property
    def stride(self) -> int:
        """Get the stride (bytes per row) of the bitmap."""
        ...
    
    def clear(self, color: int = 0) -> None:
        """
        Clear the bitmap with the specified color.
        
        Args:
            color: RGBA color value to fill the bitmap with (default: transparent)
        """
        ...

class Element:
    """
    Represents an SVG element within a Document.
    
    Elements can be rendered individually and have attributes that can be
    manipulated.
    """
    def __repr__(self) -> str:
        """Return string representation of the element."""
        ...
    
    def has_attribute(self, name: str) -> bool:
        """
        Check if the element has the specified attribute.
        
        Args:
            name: Name of the attribute to check
            
        Returns:
            True if the attribute exists, False otherwise
        """
        ...
    
    def get_attribute(self, name: str) -> str:
        """
        Get the value of the specified attribute.
        
        Args:
            name: Name of the attribute to get
            
        Returns:
            Value of the attribute as a string
        """
        ...
    
    def set_attribute(self, name: str, value: str) -> None:
        """
        Set the value of the specified attribute.
        
        Args:
            name: Name of the attribute to set
            value: Value to set the attribute to
        """
        ...
    
    def render(self, bitmap: Bitmap, matrix: Matrix | None = None) -> None:
        """
        Render the element to a bitmap.
        
        Args:
            bitmap: Target bitmap to render to
            matrix: Optional transformation matrix to apply
        """
        ...
    
    def render_to_bitmap(self, width: int = -1, height: int = -1, background_color: int = 0) -> Bitmap:
        """
        Render the element to a new bitmap.
        
        Args:
            width: Width of the output bitmap (-1 for automatic sizing)
            height: Height of the output bitmap (-1 for automatic sizing)
            background_color: Background color for the bitmap (default: transparent)
            
        Returns:
            A new bitmap containing the rendered element
            
        Raises:
            RuntimeError: If rendering fails
        """
        ...
    
    def get_local_matrix(self) -> Matrix:
        """
        Get the local transformation matrix.
        
        Returns:
            Local transformation matrix of the element
        """
        ...
    
    def get_global_matrix(self) -> Matrix:
        """
        Get the global transformation matrix.
        
        Returns:
            Global transformation matrix of the element (including parent transformations)
        """
        ...
    
    def get_local_bounding_box(self) -> Box:
        """
        Get the local bounding box.
        
        Returns:
            Local bounding box of the element
        """
        ...
    
    def get_global_bounding_box(self) -> Box:
        """
        Get the global bounding box.
        
        Returns:
            Global bounding box of the element (including transformations)
        """
        ...
    
    def get_bounding_box(self) -> Box:
        """
        Get the element's bounding box.
        
        Returns:
            Bounding box of the element
        """
        ...
    
    def parent_element(self) -> 'Element | None':
        """
        Get the parent element.
        
        Returns:
            Parent element or None if there is no parent
        """
        ...
    
    def owner_document(self) -> 'Document | None':
        """
        Get the owner document.
        
        Returns:
            Owner document or None if the element is not associated with a document
        """
        ...

class Document:
    """
    Represents an SVG document.
    
    This is the main class for loading, manipulating and rendering SVG content.
    """
    def __repr__(self) -> str:
        """Return string representation of the document."""
        ...
    
    @staticmethod
    def load_from_file(filename: str) -> 'Document':
        """
        Load an SVG document from a file.
        
        Args:
            filename: Path to the SVG file to load
            
        Returns:
            A new Document containing the loaded SVG
            
        Raises:
            RuntimeError: If loading the SVG file fails
            ValueError: If filename is None
        """
        ...
    
    @staticmethod
    def load_from_data(data: str | bytes | bytearray) -> 'Document':
        """
        Load an SVG document from data.
        
        Args:
            data: SVG content as string, bytes or bytearray
            
        Returns:
            A new Document containing the loaded SVG
            
        Raises:
            RuntimeError: If loading the SVG data fails
            ValueError: If data is None or empty
            TypeError: If data is not a string, bytes or bytearray
        """
        ...
    
    def apply_style_sheet(self, content: str) -> None:
        """
        Apply a CSS stylesheet to the document.
        
        Args:
            content: CSS content to apply
            
        Raises:
            ValueError: If content is None
            TypeError: If content is not a string
        """
        ...
    
    def render_to_bitmap(self, width: int = -1, height: int = -1, background_color: int = 0) -> Bitmap:
        """
        Render the SVG document to a bitmap.
        
        Args:
            width: Width of the output bitmap (-1 uses the document's width)
            height: Height of the output bitmap (-1 uses the document's height)
            background_color: Background color for the bitmap (default: transparent)
            
        Returns:
            A new bitmap containing the rendered document
            
        Raises:
            RuntimeError: If rendering fails
        """
        ...
    
    @property
    def width(self) -> float:
        """Get the width of the document."""
        ...
    
    @property
    def height(self) -> float:
        """Get the height of the document."""
        ...
    
    @property
    def bounding_box(self) -> Box:
        """Get the bounding box of the document."""
        ...
    
    def update_layout(self) -> None:
        """Update the layout of the document."""
        ...
    
    def render(self, bitmap: Bitmap, matrix: Matrix | None = None) -> None:
        """
        Render the document to a bitmap.
        
        Args:
            bitmap: Target bitmap to render to
            matrix: Optional transformation matrix to apply
        """
        ...
    
    def get_element_by_id(self, id: str) -> Element | None:
        """
        Get an element by its ID.
        
        Args:
            id: ID of the element to find
            
        Returns:
            Element with the specified ID or None if not found
        """
        ...
    
    def document_element(self) -> Element | None:
        """
        Get the root element of the document.
        
        Returns:
            Root element of the document or None if the document is empty
        """
        ...

def add_font_face_from_file(family: str, bold: bool, italic: bool, filename: str) -> None:
    """
    Add a font face from a font file.
    
    Args:
        family: Font family name
        bold: Whether the font is bold
        italic: Whether the font is italic
        filename: Path to the font file
        
    Raises:
        RuntimeError: If adding the font face fails
    """
    ...

def add_font_face_from_data(family: str, bold: bool, italic: bool, data: bytes) -> None:
    """
    Add a font face from font data.
    
    Args:
        family: Font family name
        bold: Whether the font is bold
        italic: Whether the font is italic
        data: Raw font data as bytes
        
    Raises:
        RuntimeError: If adding the font face fails
    """
    ...

# Module attributes
__version__: str  # Version of the pylunasvg package
__author__: str  # Author of the pylunasvg package
__license__: str  # License of the pylunasvg package
__lunasvg_version__: str  # Version of the underlying lunasvg library