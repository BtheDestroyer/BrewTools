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
#include <iostream>
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
#define RGBA8(r, g, b, a) (uint32_t((((r)&0xFF)<<24) | \
(((g)&0xFF)<<16) | \
(((b)&0xFF)<<8) | \
(((a)&0xFF)<<0)))
//! Gets red value of a color
#define RGBA8_GET_R(c) (uint8_t(((c) >> 24) & 0xFF))
//! Gets green value of a color
#define RGBA8_GET_G(c) (uint8_t(((c) >> 16) & 0xFF))
//! Gets blue value of a color
#define RGBA8_GET_B(c) (uint8_t(((c) >>  8) & 0xFF))
//! Gets alpha value of a color
#define RGBA8_GET_A(c) (uint8_t(((c) >>  0) & 0xFF))

//! Default clear color
#define DEFAULT_BG_COLOR 0x68B0D8FF

#ifdef _3DS //The following only exists in a 3DS build
//! Default size of the GPU commands FIFO buffer
#define BT_GPUCMD_DEFAULT_SIZE 0x80000
//! Default size of the temporary memory pool
#define BT_TEMPPOOL_DEFAULT_SIZE 0x80000
#endif
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
      float r; //!<Red
      float g; //!<Green
      float b; //!<Blue
      float a; //!<Opacity
      float &red = r;   //!<Red
      float &green = g; //!<Green
      float &blue = b;  //!<Blue
      float &alpha = a; //!<Opacity
      /*****************************************/
      /*!
      \brief
      Default Constructor
      */
      /*****************************************/
      vertex_col() {}

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
    private:
      //! Color vertices directly used in drawing
      std::vector<vertex_col> vc;
      //! Texture vertices directly used in drawing
      std::vector<vertex_tex> vt;
    public:
      //! Number of vertices in the shape.
      const unsigned vertexcount;
      pos_3d position; //!< Position of the shape
      // TODO: Use rotation
      float rotation; //!< Rotation of the shape = r * pi.
      // TODO: Use scale
      pos_2d scale; //!< Horizontal and vertical scale of the shape
      texture *tex; //!< Texture of the shape
      std::vector<vertex_col> vertc; //!< Color vertices
      std::vector<vertex_tex> vertt; //!< Texture vertices
      std::vector<unsigned> indice; //!< Vertex indicies

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
      {}
      
      /*****************************************/
      /*!
      \brief
      Buffers everything for color drawing into the GPU for drawing
      */
      /*****************************************/
      void BufferColor();
      
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
      Shape& operator=(Shape rhs);

      /*****************************************/
      /*!
      \brief
      Prints for debugging
      */
      /*****************************************/
      void Print()
      {
        std::cout << "Shape: {" << std::endl;
        float *vcf = (float*)(vc.data());

        //// Used to determine offsets
        //std::cout << "vertex[0]:       " << &vertc[0] << std::endl;
        //std::cout << "vertex[0].pos:   " << &vertc[0].pos << std::endl;
        //std::cout << "vertex[0].pos.x: " << &vertc[0].pos.x << std::endl;
        //std::cout << "vertex[0].pos.y: " << &vertc[0].pos.y << std::endl;
        //std::cout << "vertex[0].pos.z: " << &vertc[0].pos.z << std::endl;
        //std::cout << "vertex[0].r:     " << &vertc[0].r << std::endl;
        //std::cout << "vertex[0].g:     " << &vertc[0].g << std::endl;
        //std::cout << "vertex[0].b:     " << &vertc[0].b << std::endl;
        //std::cout << "vertex[0].a:     " << &vertc[0].a << std::endl;
        //std::cout << "vertex[1]:       " << &vertc[1] << std::endl;

        for (unsigned i = 0; i < vertc.size(); ++i)
        {
          std::cout << "  {" << std::endl;
          // Print position
          // Start with 4 bytes of padding (1 float)
          std::cout << "    (" << *(vcf + 1 + i * 12)
                    << ","     << *(vcf + 2 + i * 12)
                    << ","     << *(vcf + 3 + i * 12)
                    << ")," << std::endl;
          // Print color
          std::cout << "    (" << *(vcf + 4 + i * 12)
                    << ","     << *(vcf + 5 + i * 12)
                    << ","     << *(vcf + 6 + i * 12)
                    << ","     << *(vcf + 7 + i * 12)
                    << ")" << std::endl;
          std::cout << "  }" << std::endl;
          // Skip the next 20 bytes of padding (5 floats)
          //   totalling a 12 float offset
        }
        std::cout << "}" << std::endl;
      }

      /*****************************************/
      /*!
      \brief
      Gets a color vertex modified by the shape's position.
      Defaults to ((0, 0, 0), (0, 0, 0, 0)) if the index doesn't exist

      \param i
      Index of the vertex to get.

      \return
      Modified vertex or ((0, 0, 0), (0, 0, 0, 0)) if the index doesn't exist
      */
      /*****************************************/
      vertex_col ColorVertex(unsigned i)
      {
        vertex_col v;
        if (i < vertc.size())
        {
          v = vertc[i];
          v.pos.x += position.x;
          v.pos.y += position.y;
          v.pos.z += position.z;
        }
        else
        {
          v = vertex_col();
        }

        return v;
      }

      /*****************************************/
      /*!
      \brief
      Gets a texture vertex modified by the shape's position.
      Defaults to ((0, 0, 0), (0, 0, 0, 0)) if the index doesn't exist

      \param i
      Index of the vertex to get.

      \return
      Modified vertex or ((0, 0, 0), (0, 0, 0, 0)) if the index doesn't exist
      */
      /*****************************************/
      vertex_tex TextureVertex(unsigned i)
      {
        vertex_tex v;
        if (i < vertt.size())
        {
          v = vertt[i];
          v.pos.x += position.x;
          v.pos.y += position.y;
          v.pos.z += position.z;
        }
        else
        {
          v = vertex_tex();
        }

        return v;
      }
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
      Triangle() : Shape(3) {}
      
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
      
      \param v1
      First color vertex
      
      \param v2
      Second color vertex
      
      \param v3
      Third color vertex
      */
      /*****************************************/
      Triangle(vertex_col v1, vertex_col v2, vertex_col v3) : Shape(3)
      {
        vertc[0] = v1;
        vertc[1] = v2;
        vertc[2] = v3;
      }

      /*****************************************/
      /*!
      \brief
      Constructor
      
      \param v1
      First texture vertex
      
      \param v2
      Second texture vertex
      
      \param v3
      Third texture vertex
      */
      /*****************************************/
      Triangle(vertex_tex v1, vertex_tex v2, vertex_tex v3) : Shape(3)
      {
        vertt[0] = v1;
        vertt[1] = v2;
        vertt[2] = v3;
      }

      /*****************************************/
      /*!
      \brief
      Constructor
      
      \param vc1
      First color vertex
      
      \param vc2
      Second color vertex
      
      \param vc3
      Third color vertex
      
      \param vt1
      First texture vertex
      
      \param vt2
      Second texture vertex
      
      \param vt3
      Third texture vertex
      */
      /*****************************************/
      Triangle(
        vertex_col vc1, vertex_col vc2, vertex_col vc3,
        vertex_tex vt1, vertex_tex vt2, vertex_tex vt3
      ) : Shape(3)
      {
        vertc[0] = vc1;
        vertc[1] = vc2;
        vertc[2] = vc3;
        vertt[0] = vt1;
        vertt[1] = vt2;
        vertt[2] = vt3;
      }

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
        vertc[0].pos = pos_3d(x1, y1);
        vertt[0].pos = pos_3d(x1, y1);

        vertt[1].pos = pos_3d(x2, y2);
        vertt[1].pos = pos_3d(x2, y2);

        vertt[2].pos = pos_3d(x3, y3);
        vertt[2].pos = pos_3d(x3, y3);
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
        vertc[0].pos = pos_3d(x1, y1, z1);
        vertt[0].pos = pos_3d(x1, y1, z1);

        vertc[1].pos = pos_3d(x2, y2, z2);
        vertt[1].pos = pos_3d(x2, y2, z2);

        vertc[2].pos = pos_3d(x3, y3, z3);
        vertt[2].pos = pos_3d(x3, y3, z3);
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
          float x3, float y3, uint32_t c3) : Shape(3)
      {
        vertc[0].pos = pos_3d(x1, y1);
        vertc[0].r = RGBA8_GET_R(c1);
        vertc[0].g = RGBA8_GET_G(c1);
        vertc[0].b = RGBA8_GET_B(c1);
        vertc[0].a = RGBA8_GET_A(c1);

        vertc[1].pos = pos_3d(x2, y2);
        vertc[1].r = RGBA8_GET_R(c2);
        vertc[1].g = RGBA8_GET_G(c2);
        vertc[1].b = RGBA8_GET_B(c2);
        vertc[1].a = RGBA8_GET_A(c2);

        vertc[2].pos = pos_3d(x3, y3);
        vertc[2].r = RGBA8_GET_R(c3);
        vertc[2].g = RGBA8_GET_G(c3);
        vertc[2].b = RGBA8_GET_B(c3);
        vertc[2].a = RGBA8_GET_A(c3);
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
          float x3, float y3, float z3, uint32_t c3) : Shape(3)
      {
        vertc[0].pos = pos_3d(x1, y1, z1);
        vertc[0].r = RGBA8_GET_R(c1);
        vertc[0].g = RGBA8_GET_G(c1);
        vertc[0].b = RGBA8_GET_B(c1);
        vertc[0].a = RGBA8_GET_A(c1);

        vertc[1].pos = pos_3d(x2, y2, z2);
        vertc[1].r = RGBA8_GET_R(c2);
        vertc[1].g = RGBA8_GET_G(c2);
        vertc[1].b = RGBA8_GET_B(c2);
        vertc[1].a = RGBA8_GET_A(c2);

        vertc[2].pos = pos_3d(x3, y3, z3);
        vertc[2].r = RGBA8_GET_R(c3);
        vertc[2].g = RGBA8_GET_G(c3);
        vertc[2].b = RGBA8_GET_B(c3);
        vertc[2].a = RGBA8_GET_A(c3);
      }

      /*****************************************/
      /*!
      \brief
      Constructor
      
      \param x1
      X position of first vertex
      
      \param y1
      Y position of first vertex
      
      \param r1
      Red of first vertex
      
      \param g1
      Green of first vertex
      
      \param b1
      Blue of first vertex
      
      \param a1
      Alpha of first vertex
      
      \param x2
      X position of second vertex
      
      \param y2
      Y position of second vertex
      
      \param r2
      Red of second vertex
      
      \param g2
      Green of second vertex
      
      \param b2
      Blue of second vertex
      
      \param a2
      Alpha of second vertex
      
      \param x3
      X position of third vertex
      
      \param y3
      Y position of third vertex
      
      \param r3
      Red of third vertex
      
      \param g3
      Green of third vertex
      
      \param b3
      Blue of third vertex
      
      \param a3
      Alpha of third vertex
      */
      /*****************************************/
      Triangle(
          float x1, float y1, float r1, float g1, float b1, float a1,
          float x2, float y2, float r2, float g2, float b2, float a2,
          float x3, float y3, float r3, float g3, float b3, float a3) : Shape(3)
      {
        vertc[0].pos = pos_3d(x1, y1);
        vertc[0].r = r1;
        vertc[0].g = g1;
        vertc[0].b = b1;
        vertc[0].a = a1;

        vertc[1].pos = pos_3d(x2, y2);
        vertc[1].r = r2;
        vertc[1].g = g2;
        vertc[1].b = b2;
        vertc[1].a = a2;

        vertc[2].pos = pos_3d(x3, y3);
        vertc[2].r = r3;
        vertc[2].g = g3;
        vertc[2].b = b3;
        vertc[2].a = a3;
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
      
      \param r1
      Red of first vertex
      
      \param g1
      Green of first vertex
      
      \param b1
      Blue of first vertex
      
      \param a1
      Alpha of first vertex
      
      \param x2
      X position of second vertex
      
      \param y2
      Y position of second vertex
      
      \param z2
      Z position of second vertex
      
      \param r2
      Red of second vertex
      
      \param g2
      Green of second vertex
      
      \param b2
      Blue of second vertex
      
      \param a2
      Alpha of second vertex
      
      \param x3
      X position of third vertex
      
      \param y3
      Y position of third vertex
      
      \param z3
      Z position of third vertex
      
      \param r3
      Red of third vertex
      
      \param g3
      Green of third vertex
      
      \param b3
      Blue of third vertex
      
      \param a3
      Alpha of third vertex
      */
      /*****************************************/
      Triangle(
          float x1, float y1, float z1, float r1, float g1, float b1, float a1,
          float x2, float y2, float z2, float r2, float g2, float b2, float a2,
          float x3, float y3, float z3, float r3, float g3, float b3, float a3)
          : Shape(3)
      {
        vertc[0].pos = pos_3d(x1, y1, z1);
        vertc[0].r = r1;
        vertc[0].g = g1;
        vertc[0].b = b1;
        vertc[0].a = a1;

        vertc[1].pos = pos_3d(x2, y2, z2);
        vertc[1].r = r2;
        vertc[1].g = g2;
        vertc[1].b = b2;
        vertc[1].a = a2;

        vertc[2].pos = pos_3d(x3, y3, z3);
        vertc[2].r = r3;
        vertc[2].g = g3;
        vertc[2].b = b3;
        vertc[2].a = a3;
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
      Quad() : Shape(4) {}
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
    Creates an RGBA8 color based on given inputs
    0 = minimum
    255 = maximum

    \param r
    Red value of the color

    \param g
    Green value of the color

    \param b
    Blue value of the color

    \param a
    Alpha value of the color
    
    \return
    Created color in RGBA8 format
    */
    /*****************************************/
    static uint32_t Color(int r, int g, int b, int a)
    {
      return RGBA8(r, g, b, a);
    }
    
    /*****************************************/
    /*!
    \brief
    Creates a color based on given inputs 
    0 = minimum
    255 = maximum

    \param r
    Red value of the color

    \param g
    Green value of the color

    \param b
    Blue value of the color

    \param a
    Alpha value of the color
    
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

    \param r
    Red value of the color

    \param g
    Green value of the color

    \param b
    Blue value of the color

    \param a
    Alpha value of the color
    
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
    
    \param id
    ID of window to select.
    */
    /*****************************************/
    void SelectWindow(unsigned id);
    
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
    Selects a shader for the shape
    
    \param shaderID
    ID of the shaderprogram to set
    */
    /*****************************************/
    void SetShader(int shaderID)
    {
    #ifdef _WIN32 // The following only exists in a Windows build
      shaderProgram = shaderID;
    #elif _3DS // The following will only exist in a 3DS build
      Trace *trace = Engine::Get()->GetSystemIfExists<Trace>();
      if (trace)
        (*trace)[5]
          << "Shaders are only set with Graphics::SetShader() on Windows";
    #endif
    }

    /*****************************************/
    /*!
    \brief
    Selects a shader for the shape
    
    \param vs
    Vertex shader source code
    
    \param fs
    Fragment shader source code
    
    \return
    Shader Program ID. 0 on failure.
    */
    /*****************************************/
    int LoadShader(const char *vs = nullptr, const char *fs = nullptr);

    /*****************************************/
    /*!
    \brief
    Gets the shape's shader program
      
    \return
    Shader Program ID. -1 if none are connected.
    */
    /*****************************************/
    int GetShader()
    {
    #ifdef _WIN32 // The following only exists in a Windows build
      return shaderProgram;
    #elif _3DS // The following will only exist in a 3DS build
      Trace *trace = Engine::Get()->GetSystemIfExists<Trace>();
      if (trace)
        (*trace)[5] << "Graphics::GetShader() only works on Windows";
      return -1;
    #endif
    }
    
      
    /*****************************************/
    /*!
    \brief
    Generates buffers for OpenGL drawing
    */
    /*****************************************/
    void GenBuffers()
    {
    #ifdef _WIN32 // The following only exists in a Windows build
      if (!VAO && glGenVertexArrays) glGenVertexArrays(1, &VAO);
      if (!VBO && glGenBuffers) glGenBuffers(1, &VBO);
      if (!EBO && glGenBuffers) glGenBuffers(1, &EBO);
    #endif
    }

    /*****************************************/
    /*!
    \brief
    Gets the current VAO for OpenGL

    \return
    VAO handle
    */
    /*****************************************/
    unsigned GetVAO()
    {
    #ifdef _WIN32 // The following only exists in a Windows build
      return VAO;
    #elif _3DS // The following will only exist in a 3DS build
      Trace *trace = Engine::Get()->GetSystemIfExists<Trace>();
      if (trace)
        (*trace)[5] << "Graphics::GetVAO() only works on Windows";
      return 0;
    #endif
    }

    /*****************************************/
    /*!
    \brief
    Gets the current VBO for OpenGL

    \return
    VBO handle
    */
    /*****************************************/
    unsigned GetVBO()
    {
    #ifdef _WIN32 // The following only exists in a Windows build
      return VBO;
    #elif _3DS // The following will only exist in a 3DS build
      Trace *trace = Engine::Get()->GetSystemIfExists<Trace>();
      if (trace)
        (*trace)[5] << "Graphics::GetVBO() only works on Windows";
      return 0;
    #endif
    }

    /*****************************************/
    /*!
    \brief
    Gets the current EBO for OpenGL

    \return
    EBO handle
    */
    /*****************************************/
    unsigned GetEBO()
    {
    #ifdef _WIN32 // The following only exists in a Windows build
      return EBO;
    #elif _3DS // The following will only exist in a 3DS build
      Trace *trace = Engine::Get()->GetSystemIfExists<Trace>();
      if (trace)
        (*trace)[5] << "Graphics::GetEBO() only works on Windows";
      return 0;
    #endif
    }

    /*****************************************/
    /*!
    \brief
    Gets the current shader program for OpenGL

    \return
    Program handle
    */
    /*****************************************/
    unsigned GetProgram()
    {
    #ifdef _WIN32 // The following only exists in a Windows build
      return shaderProgram;
    #elif _3DS // The following will only exist in a 3DS build
      Trace *trace = Engine::Get()->GetSystemIfExists<Trace>();
      if (trace)
        (*trace)[5] << "Graphics::GetProgram() only works on Windows";
      return 0;
    #endif
    }

    /*****************************************/
    /*!
    \brief
    Gets the currently selected window

    \return
    Pointer to the current window
    */
    /*****************************************/
    GFXWindow *GetCurrentWindow()
    {
      return currentwindow;
    }

    /*****************************************/
    /*!
    \brief
    Initializes the 3DS Shaders
    */
    /*****************************************/
    void Init3DS();

    /*****************************************/
    /*!
    \brief
    Cleans up the 3DS shaders
    */
    /*****************************************/
    void Exit3DS();

    #ifdef _3DS // The following will only exist in a 3DS build
    int uLoc_projection;
    C3D_Mtx projection;
    #endif
  private:
    #ifdef _WIN32 // The following will only exist in a Windows build
    //! Vertex buffer, vertex array, and element buffer objects
    unsigned int VAO, VBO, EBO;
    int shaderProgram;
    #elif _3DS // The following will only exist in a 3DS build
    DVLB_s *vshader_dvlb;
    shaderProgram_s program;

    void *vbo_data;
    #endif
    std::vector<GFXWindow *> windows; //!< Vector of created GFXWindow
    GFXWindow *currentwindow;         //!< Currently selected window
    bool frameStarted; //!< Determines if a frame has been started
  };
}

#endif
