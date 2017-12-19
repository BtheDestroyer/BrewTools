/******************************************************************************/
/*!
\file graphics.h
\author Bryce Dixon
\par email: realbthedestroyer\@gmail.com
\par BrewTools
\date 12/11/2017
\par Created: v1.0
\par Updated: v1.0

\brief
Graphics management and implementation.
*/
/******************************************************************************/

#ifndef __BT_GRAPHICS_H_
#define __BT_GRAPHICS_H_
#include "brewtools/gfxwindow.h"
#include "brewtools/system.h"
#include "brewtools/macros.h"
#include <vector>

#ifdef _3DS //The following only exists in a 3DS build
#include <citro3d.h>
#elif _WIN32 //The following only exists in a Windows build
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif


/*****************************************/
/*!
\brief
Creates a new RGBA8 color.
Takes 4 8-bit values and outputs 1 64-bit value.

\param r
Red value of the color.

\param g
Green value of the color.

\param b
Blue value of the color.

\param a
Alpha value of the color.
*/
/*****************************************/
#define RGBA8(r, g, b, a) ((((a)&0xFF)<<24) | \
(((b)&0xFF)<<16) | \
(((g)&0xFF)<<8) | \
(((r)&0xFF)<<0))
//! Gets red value of a color
#define RGBA8_GET_R(c) (((c) >>  0) & 0xFF)
//! Gets green value of a color
#define RGBA8_GET_G(c) (((c) >>  8) & 0xFF)
//! Gets blue value of a color
#define RGBA8_GET_B(c) (((c) >> 16) & 0xFF)
//! Gets alpha value of a color
#define RGBA8_GET_A(c) (((c) >> 24) & 0xFF)

//! Default size of the GPU commands FIFO buffer
#define BT_GPUCMD_DEFAULT_SIZE 0x80000
//! Default size of the temporary memory pool
#define BT_TEMPPOOL_DEFAULT_SIZE 0x80000
//! Default depth (Z coordinate) to draw the textures to
#define BT_DEFAULT_DEPTH 0.5f

/*****************************************/
/*!
\brief
Brewtools namespace.
*/
/*****************************************/
namespace BrewTools
{
  /*****************************************/
  /*!
  \brief
  Graphics system class.
  Used for creating, managing, and updating Windows
  */
  /*****************************************/
  class Graphics : public System<Graphics>
  {
  public:
    /*****************************************/
    /*!
    \brief
    Texture formats.
    */
    /*****************************************/
    typedef enum {
      TEXFMT_RGBA8  =  0,
      TEXFMT_RGB8   =  1,
      TEXFMT_RGB5A1 =  2,
      TEXFMT_RGB565 =  3,
      TEXFMT_RGBA4  =  4,
      TEXFMT_IA8    =  5,
      
      TEXFMT_I8     =  7,
      TEXFMT_A8     =  8,
      TEXFMT_IA4    =  9,
      TEXFMT_I4     = 10,
      TEXFMT_A4     = 11,
      TEXFMT_ETC1   = 12,
      TEXFMT_ETC1A4 = 13
    } texfmt;
    
    /*****************************************/
    /*!
    \brief
    Gradient direction.
    */
    /*****************************************/
    typedef enum {
      TOP_TO_BOTTOM,
      LEFT_TO_RIGHT
    } gradient_dir;
    
    /*****************************************/
    /*!
    \brief
    Data allocation location.
    */
    /*****************************************/
    typedef enum {
      PLACE_RAM,
      PLACE_VRAM,
    } place;
    
    /*****************************************/
    /*!
    \brief
    Position in 2d space.
    */
    /*****************************************/
    class pos_2d
    {
    public:
      float x; //!< X Position
      float y; //!< Y Position
      
      /*****************************************/
      /*!
      \brief
      Default constructor
      */
      /*****************************************/
      pos_2d() {}
      
      /*****************************************/
      /*!
      \brief
      Constructor
      
      \param xpos
      Horizontal position of the point
      
      \param ypos
      Vertical position of the point
      */
      /*****************************************/
      pos_2d(float xpos, float ypos) : x(xpos), y(ypos) {}
      
      /*****************************************/
      /*!
      \brief
      Assignment operator
      
      \param rhs
      Object to the right of the =
      
      \return
      Reference to modified position
      */
      /*****************************************/
      pos_2d& operator=(pos_2d rhs);
      
      /*****************************************/
      /*!
      \brief
      Index operator
      
      \param rhs
      Object to the right of the =
      
      \return
      Reference to modified float
      */
      /*****************************************/
      float& operator[](unsigned rhs);
    };
    
    /*****************************************/
    /*!
    \brief
    Position in 3d space.
    */
    /*****************************************/
    class pos_3d : public pos_2d
    {
    public:
      float z; //!< Z Position
      
      /*****************************************/
      /*!
      \brief
      Default constructor
      
      \param zpos
      Depth of the point
      */
      /*****************************************/
      pos_3d(float zpos = BT_DEFAULT_DEPTH) : z(zpos) {}
      
      /*****************************************/
      /*!
      \brief
      Constructor
      
      \param xpos
      Horizontal position of the point
      
      \param ypos
      Vertical position of the point
      
      \param zpos
      Depth of the point
      */
      /*****************************************/
      pos_3d(float xpos, float ypos, float zpos = BT_DEFAULT_DEPTH)
      : pos_2d(xpos, ypos), z(zpos) {}
      
      /*****************************************/
      /*!
      \brief
      Assignment operator
      
      \param rhs
      Object to the right of the =
      
      \return
      Reference to modified position
      */
      /*****************************************/
      pos_3d& operator=(pos_3d rhs);
      
      /*****************************************/
      /*!
      \brief
      Assignment operator
      
      \param rhs
      Object to the right of the =
      
      \return
      Reference to modified position
      */
      /*****************************************/
      pos_3d& operator=(pos_2d rhs);
      
      /*****************************************/
      /*!
      \brief
      Index operator
      
      \param rhs
      Object to the right of the =
      
      \return
      Reference to indexed float
      */
      /*****************************************/
      float& operator[](unsigned rhs);
    };
    
    /*****************************************/
    /*!
    \brief
    Position in 4d space.
    */
    /*****************************************/
    class pos_4d : public pos_3d
    {
    public:
      float w; //!< W Position
      
      /*****************************************/
      /*!
      \brief
      Default constructor
      
      \param zpos
      Depth of the point
      
      \param wpos
      4D position of the point
      */
      /*****************************************/
      pos_4d(float zpos = BT_DEFAULT_DEPTH, float wpos = 0.0f)
      : pos_3d(zpos), w(wpos) {}
      
      /*****************************************/
      /*!
      \brief
      Constructor
      
      \param xpos
      Horizontal position of the point
      
      \param ypos
      Vertical position of the point
      
      \param zpos
      Depth of the point
      
      \param wpos
      4D position of the point
      */
      /*****************************************/
      pos_4d
      (float xpos, float ypos, float zpos = BT_DEFAULT_DEPTH, float wpos = 0.0f)
      : pos_3d(xpos, ypos, zpos), w(wpos) {}
      
      /*****************************************/
      /*!
      \brief
      Assignment operator
      
      \param rhs
      Object to the right of the =
      
      \return
      Reference to modified position
      */
      /*****************************************/
      pos_4d& operator=(pos_4d rhs);
      
      /*****************************************/
      /*!
      \brief
      Assignment operator
      
      \param rhs
      Object to the right of the =
      
      \return
      Reference to modified position
      */
      /*****************************************/
      pos_4d& operator=(pos_3d rhs);
      
      /*****************************************/
      /*!
      \brief
      Assignment operator
      
      \param rhs
      Object to the right of the =
      
      \return
      Reference to modified position
      */
      /*****************************************/
      pos_4d& operator=(pos_2d rhs);
      
      /*****************************************/
      /*!
      \brief
      Index operator
      
      \param rhs
      Object to the right of the =
      
      \return
      Reference to indexed float
      */
      /*****************************************/
      float& operator[](unsigned rhs);
      
      /*****************************************/
      /*!
      \brief
      Index operator
      
      \param rhs
      Object to the right of the =
      
      \return
      Indexed float
      */
      /*****************************************/
      float operator[](unsigned rhs) const;
    };
    
    /*****************************************/
    /*!
    \brief
    Matrix for 2d transformations
    */
    /*****************************************/
    class mat_3d
    {
      pos_3d index[3]; //!< 3x3 float array
    public:
      /*****************************************/
      /*!
      \brief
      Default constructor (Identity Matrix)
      
      \param scalar
      What to scale the matrix by
      */
      /*****************************************/
      mat_3d(float scalar = 1.0f);
      
      /*****************************************/
      /*!
      \brief
      Copy constructor
      
      \param mat
      Matrix to copy from
      */
      /*****************************************/
      mat_3d(const mat_3d& mat);
      
      /*****************************************/
      /*!
      \brief
      Constructor
      
      \param x1
      Column 1 row 1
      
      \param x2
      Column 1 row 2
      
      \param x3
      Column 1 row 3
      
      \param y1
      Column 2 row 1
      
      \param y2
      Column 2 row 2
      
      \param y3
      Column 2 row 3
      
      \param z1
      Column 3 row 1
      
      \param z2
      Column 3 row 2
      
      \param z3
      Column 3 row 3
      */
      /*****************************************/
      mat_3d(
        float x1, float y1, float z1,
        float x2, float y2, float z2,
        float x3, float y3, float z3
      );
      
      /*****************************************/
      /*!
      \brief
      Constructor
      
      \param c1
      Column 1
      
      \param c2
      Column 2
      
      \param c3
      Column 3
      */
      /*****************************************/
      mat_3d(pos_3d c1, pos_3d c2, pos_3d c3);
      
      /*****************************************/
      /*!
      \brief
      Multiplication operator
      
      \param lhs
      Point to multiply
      
      \param rhs
      Matrix to multiply with
      
      \return
      Newly created position
      */
      /*****************************************/
      friend pos_2d operator*(pos_2d lhs, mat_3d rhs);
      
      /*****************************************/
      /*!
      \brief
      Multiplication operator
      
      \param rhs
      Matrix to multiply with
      
      \return
      Newly created matrix
      */
      /*****************************************/
      mat_3d operator*(mat_3d rhs);
      
      /*****************************************/
      /*!
      \brief
      Index operator
      
      \param rhs
      Index to retrieve
      
      \return
      Reference to indexed column
      */
      /*****************************************/
      pos_3d& operator[](unsigned rhs);
      
      /*****************************************/
      /*!
      \brief
      Index operator
      
      \param rhs
      Index to retrieve
      
      \return
      Indexed column
      */
      /*****************************************/
      pos_3d operator[](unsigned rhs) const;
    };
    
    /*****************************************/
    /*!
    \brief
    Matrix for 3d transformations
    */
    /*****************************************/
    class mat_4d
    {
      pos_4d index[4]; //!< 4x4 float array
    public:
      /*****************************************/
      /*!
      \brief
      Default constructor (Identity matrix)
      
      \param scalar
      What to scale the matrix by
      */
      /*****************************************/
      mat_4d(float scalar = 1.0f);
      
      /*****************************************/
      /*!
      \brief
      Constructor
      
      \param x1
      Column 1 row 1
      
      \param x2
      Column 1 row 2
      
      \param x3
      Column 1 row 3
      
      \param x4
      Column 1 row 4
      
      \param y1
      Column 2 row 1
      
      \param y2
      Column 2 row 2
      
      \param y3
      Column 2 row 3
      
      \param y4
      Column 2 row 4
      
      \param z1
      Column 3 row 1
      
      \param z2
      Column 3 row 2
      
      \param z3
      Column 3 row 3
      
      \param z4
      Column 3 row 4
      
      \param w1
      Column 4 row 1
      
      \param w2
      Column 4 row 2
      
      \param w3
      Column 4 row 3
      
      \param w4
      Column 4 row 4
      */
      /*****************************************/
      mat_4d(
        float x1, float y1, float z1, float w1,
        float x2, float y2, float z2, float w2,
        float x3, float y3, float z3, float w3,
        float x4, float y4, float z4, float w4
      );
      
      /*****************************************/
      /*!
      \brief
      Copy constructor
      
      \param mat
      Matrix to copy from
      */
      /*****************************************/
      mat_4d(const mat_4d& mat);
      
      /*****************************************/
      /*!
      \brief
      Constructor
      
      \param c1
      Column 1
      
      \param c2
      Column 2
      
      \param c3
      Column 3
      
      \param c4
      Column 4
      */
      /*****************************************/
      mat_4d(pos_4d c1, pos_4d c2, pos_4d c3, pos_4d c4);
      
      /*****************************************/
      /*!
      \brief
      Multiplication operator
      
      \param lhs
      Point to multiply
      
      \param rhs
      Matrix to multiply with
      
      \return
      Newly created position
      */
      /*****************************************/
      friend pos_2d operator*(pos_2d lhs, mat_4d rhs);
      
      /*****************************************/
      /*!
      \brief
      Multiplication operator
      
      \param lhs
      Point to multiply
      
      \param rhs
      Matrix to multiply with
      
      \return
      Newly created position
      */
      /*****************************************/
      friend pos_3d operator*(pos_3d lhs, mat_4d rhs);
      
      /*****************************************/
      /*!
      \brief
      Multiplication operator
      
      \param rhs
      Matrix to multiply with
      
      \return
      Newly created matrix
      */
      /*****************************************/
      mat_4d operator*(mat_4d rhs);
      
      /*****************************************/
      /*!
      \brief
      Index operator
      
      \param rhs
      Index to retrieve
      
      \return
      Indexed column
      */
      /*****************************************/
      pos_4d& operator[](unsigned rhs);
      
      /*****************************************/
      /*!
      \brief
      Index operator
      
      \param rhs
      Index to retrieve
      
      \return
      Indexed column
      */
      /*****************************************/
      pos_4d operator[](unsigned rhs) const;
    };
    
    /*****************************************/
    /*!
    \brief
    Vertex in 3d space with a position.
    */
    /*****************************************/
    class vertex
    {
    public:
      /*****************************************/
      /*!
      \brief
      Pure virtual destructor for polymorphism
      */
      /*****************************************/
      virtual ~vertex() = 0;
      pos_3d pos; //!< Position
    };
    
    /*****************************************/
    /*!
    \brief
    Vertex in 3d space with a position and color.
    */
    /*****************************************/
    class vertex_col : public vertex
    {
    public:
      uint32_t color; //!< Color
      /*****************************************/
      /*!
      \brief
      Destructor
      */
      /*****************************************/
      ~vertex_col() {}
      
      /*****************************************/
      /*!
      \brief
      Assignment operator
      
      \param rhs
      Object to the right of the =
      */
      /*****************************************/
      virtual vertex_col& operator=(vertex_col rhs);
    };
    
    /*****************************************/
    /*!
    \brief
    Vertex in 3d space with a position and texture coordinate.
    */
    /*****************************************/
    class vertex_tex : public vertex
    {
    public:
      pos_2d uv; //!< Color
      /*****************************************/
      /*!
      \brief
      Destructor
      */
      /*****************************************/
      ~vertex_tex() {}
      
      /*****************************************/
      /*!
      \brief
      Assignment operator
      
      \param rhs
      Object to the right of the =
      */
      /*****************************************/
      virtual vertex_tex& operator=(vertex_tex rhs);
    };
    
    /*****************************************/
    /*!
    \brief
    Texture with metadata.
    */
    /*****************************************/
    class texture
    {
    public:
      #ifdef _3DS //The following only exists in a 3DS build
      C3D_Tex tex; //!< Texture
      #elif _WIN32 //The following only exists in a Windows build
      //TODO: Figure out windows equivalent
      #endif
      bool tile; //!< Determines if the texture is tiling
      unsigned width; //!< Width of texture
      unsigned height; //!< Height of texture
      
      /*****************************************/
      /*!
      \brief
      Assignment operator
      
      \param rhs
      Object to the right of the =
      */
      /*****************************************/
      virtual texture& operator=(texture rhs);
    };
    
    /*****************************************/
    /*!
    \brief
    Shape base class
    */
    /*****************************************/
    class Shape
    {
    protected:
      vertex_col *vc; //!< Pointer to allocated memory for color vertices
      vertex_tex *vt; //!< Pointer to allocated memory for texture vertices
      bool vc_isdirty; //!< Determines if vc needs to be regenerated
      bool vt_isdirty; //!< Determines if vt needs to be regenerated
      #ifdef _WIN32 // The following will only exist in a Windows build
      //! Vertex buffer, vertex array, and element buffer objects
      unsigned int VBO, VAO, EBO;
      #endif
      
    public:
      const unsigned vertexcount; //!< Number of vertices in the shape
      pos_3d position; //!< Position of the shape
      float rotation; //!< Rotation of the shape = r * pi. Currently unused.
      pos_2d scale; //!< Horizontal and vertical scale of the shape
      texture *tex; //!< Texture of the shape
      pos_3d *vertex; //!< Position of each vertex
      pos_2d *uv; //!< UV of each vertex
      uint32_t *color; //!< Color of each vertex
      std::vector<unsigned> indice; //!< List of indices to draw
      
      /*****************************************/
      /*!
      \brief
      Default Constructor
      
      \param count
      Number of vertices in the shape
      */
      /*****************************************/
      Shape(unsigned count = 0);
      
      /*****************************************/
      /*!
      \brief
      Destructor
      */
      /*****************************************/
      ~Shape()
      {
        SAFE_DELETE_ARR(vertex);
        SAFE_DELETE_ARR(color);
        SAFE_DELETE_ARR(uv);
        
        #ifdef _WIN32 // The following only exists in a Windows build
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        #endif
      }
      
      /*****************************************/
      /*!
      \brief
      Creates and returns a pointer to an array of color vertices
      
      \return
      Pointer to allocated vertex_col
      */
      /*****************************************/
      const vertex_col* GetColorVertices();
      
      /*****************************************/
      /*!
      \brief
      Creates and returns a pointer to an array of texture vertices
      */
      /*****************************************/
      const vertex_tex* GetTextureVertices();
      
      /*****************************************/
      /*!
      \brief
      Draws the shape to the screen at its current location
      */
      /*****************************************/
      void Draw();
      
      /*****************************************/
      /*!
      \brief
      Assignment operator
      
      \param rhs
      Object to the right of the =
      
      \return
      Reference to modified shape
      */
      /*****************************************/
      // Shape& operator=(Shape rhs);
      
    protected:
      /*****************************************/
      /*!
      \brief
      Generates the vertices with colors
      
      \return
      True if vertices were generated. False otherwise.
      */
      /*****************************************/
      bool GenerateColorVertices();
      
      /*****************************************/
      /*!
      \brief
      Generates the vertices with texture coordinates
      
      \return
      True if vertices were generated. False otherwise.
      */
      /*****************************************/
      bool GenerateTextureVertices();
    };
    
    /*****************************************/
    /*!
    \brief
    Triangle shape
    */
    /*****************************************/
    class Triangle : public Shape
    {
    public:
      /*****************************************/
      /*!
      \brief
      Default Constructor
      */
      /*****************************************/
      Triangle() : Shape(3)
      {
        for (unsigned i = 0; i < vertexcount; ++i) indice.push_back(i);
      }
      
      /*****************************************/
      /*!
      \brief
      Destructor
      */
      /*****************************************/
      ~Triangle() {}
      
      /*****************************************/
      /*!
      \brief
      Constructor
      
      \param x1
      X position of first vertex
      
      \param y1
      Y position of first vertex
      
      \param x2
      X position of second vertex
      
      \param y2
      Y position of second vertex
      
      \param x3
      X position of third vertex
      
      \param y3
      Y position of third vertex
      */
      /*****************************************/
      Triangle(
        float x1, float y1,
        float x2, float y2,
        float x3, float y3
      ) : Shape(3)
      {
        for (unsigned i = 0; i < vertexcount; ++i) indice.push_back(i);
        vertex[0] = pos_3d(x1, y1);
        vertex[1] = pos_3d(x2, y2);
        vertex[2] = pos_3d(x3, y3);
      }
      
      /*****************************************/
      /*!
      \brief
      Constructor
      
      \param x1
      X position of first vertex
      
      \param y1
      Y position of first vertex
      
      \param z1
      Z position of first vertex
      
      \param x2
      X position of second vertex
      
      \param y2
      Y position of second vertex
      
      \param z2
      Z position of second vertex
      
      \param x3
      X position of third vertex
      
      \param y3
      Y position of third vertex
      
      \param z3
      Z position of third vertex
      */
      /*****************************************/
      Triangle(
        float x1, float y1, float z1,
        float x2, float y2, float z2,
        float x3, float y3, float z3
      ) : Shape(3)
      {
        for (unsigned i = 0; i < vertexcount; ++i) indice.push_back(i);
        vertex[0] = pos_3d(x1, y1, z1);
        vertex[1] = pos_3d(x2, y2, z2);
        vertex[2] = pos_3d(x3, y3, z3);
      }
      
      /*****************************************/
      /*!
      \brief
      Constructor
      
      \param x1
      X position of first vertex
      
      \param y1
      Y position of first vertex
      
      \param c1
      Color of first vertex
      
      \param x2
      X position of second vertex
      
      \param y2
      Y position of second vertex
      
      \param c2
      Color of second vertex
      
      \param x3
      X position of third vertex
      
      \param y3
      Y position of third vertex
      
      \param c3
      Color of third vertex
      */
      /*****************************************/
      Triangle(
        float x1, float y1, uint32_t c1,
        float x2, float y2, uint32_t c2,
        float x3, float y3, uint32_t c3
      ) : Shape(3)
      {
        for (unsigned i = 0; i < vertexcount; ++i) indice.push_back(i);
        vertex[0] = pos_3d(x1, y1);
        vertex[1] = pos_3d(x2, y2);
        vertex[2] = pos_3d(x3, y3);
        color[0] = c1;
        color[1] = c2;
        color[2] = c3;
      }
      
      /*****************************************/
      /*!
      \brief
      Constructor
      
      \param x1
      X position of first vertex
      
      \param y1
      Y position of first vertex
      
      \param z1
      Z position of first vertex
      
      \param c1
      Color of first vertex
      
      \param x2
      X position of second vertex
      
      \param y2
      Y position of second vertex
      
      \param z2
      Z position of second vertex
      
      \param c2
      Color of second vertex
      
      \param x3
      X position of third vertex
      
      \param y3
      Y position of third vertex
      
      \param z3
      Z position of third vertex
      
      \param c3
      Color of third vertex
      */
      /*****************************************/
      Triangle(
        float x1, float y1, float z1, uint32_t c1,
        float x2, float y2, float z2, uint32_t c2,
        float x3, float y3, float z3, uint32_t c3
      ) : Shape(3)
      {
        for (unsigned i = 0; i < vertexcount; ++i) indice.push_back(i);
        vertex[0] = pos_3d(x1, y1, z1);
        vertex[1] = pos_3d(x2, y2, z2);
        vertex[2] = pos_3d(x3, y3, z3);
        color[0] = c1;
        color[1] = c2;
        color[2] = c3;
      }
    };
    
    /*****************************************/
    /*!
    \brief
    Quad shape
    */
    /*****************************************/
    class Quad : public Shape
    {
    public:
      /*****************************************/
      /*!
      \brief
      Default Constructor
      */
      /*****************************************/
      Quad() : Shape(4)
      {
        for (unsigned i = 0; i < vertexcount; ++i) indice.push_back(i);
      }
    };
    
    /*****************************************/
    /*!
    \brief
    Default Constructor
    */
    /*****************************************/
    Graphics();
    
    /*****************************************/
    /*!
    \brief
    Destructor
    */
    /*****************************************/
    ~Graphics();
    
    /*****************************************/
    /*!
    \brief
    Creates a color based on given inputs 
    
    \return
    Created color in RGBA8 format
    */
    /*****************************************/
    static uint32_t Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
      return RGBA8(r, g, b, a);
    }
    
    /*****************************************/
    /*!
    \brief
    Creates a color based on given inputs
    0.0f = minimum
    1.0f = maximum 
    
    \return
    Created color in RGBA8 format
    */
    /*****************************************/
    static uint32_t Color(float r, float g, float b, float a)
    {
      return RGBA8(
        uint8_t(uint8_t(-1) * r),
        uint8_t(uint8_t(-1) * g),
        uint8_t(uint8_t(-1) * b),
        uint8_t(uint8_t(-1) * a)
      );
    }
    
    /*****************************************/
    /*!
    \brief
    Updates graphics by flushing and swapping the buffers.
    */
    /*****************************************/
    void Update();
    
    /*****************************************/
    /*!
    \brief
    Adds a created window to the list of windows.
    
    \param window
    Pointer to window to add.
    
    \return
    ID of window
    */
    /*****************************************/
    unsigned AddWindow(GFXWindow *window);
    
    /*****************************************/
    /*!
    \brief
    Removes a created window from the list of windows.
    
    \param window
    Pointer to window to remove.
    */
    /*****************************************/
    void RemoveWindow(GFXWindow *window);
    
    /*****************************************/
    /*!
    \brief
    Selects a given window to be drawn to
    
    \param window
    Pointer to window to select.
    */
    /*****************************************/
    void SelectWindow(GFXWindow *window);
    
    /*****************************************/
    /*!
    \brief
    Selects a given window to be drawn to
    
    \param window
    ID of window to select.
    */
    /*****************************************/
    void SelectWindow(unsigned id);
    
    /*****************************************/
    /*!
    \brief
    Selects a default shaders
    */
    /*****************************************/
    void SelectDefaultShaders() { cspID = dspID; }

    #ifdef _WIN32 //The following only exists in a Windows build
    /*****************************************/
    /*!
    \brief
    Runs if this was the first window selected on Windows to set up GLAD

    \param window
    Window selected
    */
    /*****************************************/
    void FirstWindow(GLFWwindow *window);
    #endif
    
  private:
    std::vector<GFXWindow *> windows; //!< Vector of created GFXWindow
    GFXWindow *currentwindow; //!< Currently selected window
    #ifdef _WIN32 // The following only exists in a Windows build
    int dvsID; //!< ID of default vertex shader
    int dfsID; //!< ID of default fragment shader
    int dspID; //!< ID of default shader program
    int cspID; //!< ID of current shader program
    bool firstwindow; //!< Set to true if the first window has been created
    #endif
  };
}

#endif
