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
#include "brewtools/window.h"
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
      Indexed float
      */
      /*****************************************/
      float& operator[](unsigned rhs);
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
      float index[4][4]; //!< 4x4 float array
    public:
      /*****************************************/
      /*!
      \brief
      Default constructor (Identity matrix)
      
      \param scalar
      What to scale the matrix by
      */
      /*****************************************/
      mat_4d(float scalar = 0.0f);
      
      /*****************************************/
      /*!
      \brief
      Copy constructor
      */
      /*****************************************/
      mat_4d(const mat_4d& mat);
      
      /*****************************************/
      /*!
      \brief
      Multiplication operator
      
      \param lhs
      Point to multiply
      
      \param rhs
      Matrix to multiply with
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
      pos_4d* operator[](unsigned rhs);
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
      
      /*****************************************/
      /*!
      \brief
      Generates the vertices with colors
      
      \return
      True if vertices were generated. False otherwise.
      */
      /*****************************************/
      virtual bool GenerateColorVertices();
      
      /*****************************************/
      /*!
      \brief
      Generates the vertices with texture coordinates
      
      \return
      True if vertices were generated. False otherwise.
      */
      /*****************************************/
      virtual bool GenerateTextureVertices();
      
    public:
      const unsigned vertexcount; //!< Number of vertices in the shape
      pos_3d position; //!< Position of the shape
      float rotation; //!< Rotation of the shape = r * pi. Currently unused.
      pos_2d scale; //!< Horizontal and vertical scale of the shape
      texture *tex; //!< Texture of the shape
      pos_3d *vertex; //!< Position of each vertex
      pos_2d *uv; //!< UV of each vertex
      uint32_t *color; //!< Color of each vertex
      unsigned *indice; //!< List of indices to draw
      
      /*****************************************/
      /*!
      \brief
      Default Constructor
      
      \param count
      Number of vertices in the shape
      */
      /*****************************************/
      Shape(unsigned count = 0) : vc(NULL), vt(NULL),
      vc_isdirty(true), vt_isdirty(true), vertexcount(count)
      {
        vertex = new pos_3d[vertexcount];
        color = new uint32_t[vertexcount];
        uv = new pos_2d[vertexcount];
        indice = new unsigned[vertexcount];
      }
      
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
        SAFE_DELETE_ARR(indice);
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
      virtual Shape& operator=(Shape rhs);
    };
    
    /*****************************************/
    /*!
    \brief
    Triangle shape
    */
    /*****************************************/
    class Triangle : public Shape
    {
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
    public:
      /*****************************************/
      /*!
      \brief
      Default Constructor
      */
      /*****************************************/
      Triangle() : Shape(3) {}
      
      /*****************************************/
      /*!
      \brief
      Destructor
      */
      /*****************************************/
      ~Triangle()
      {
        SAFE_DELETE(vertex);
        SAFE_DELETE(color);
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
    public:
      /*****************************************/
      /*!
      \brief
      Default Constructor
      */
      /*****************************************/
      Quad() : Shape(4) {}
      
      /*****************************************/
      /*!
      \brief
      Destructor
      */
      /*****************************************/
      ~Quad()
      {
        SAFE_DELETE(vertex);
        SAFE_DELETE(color);
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
    */
    /*****************************************/
    void AddWindow(Window *window);
    /*****************************************/
    /*!
    \brief
    Removes a created window from the list of windows.
    
    \param window
    Pointer to window to remove.
    */
    /*****************************************/
    void RemoveWindow(Window *window);
    
  private:
    std::vector<Window *> windows;
  };
}

#endif
