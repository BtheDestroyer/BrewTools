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
    Position in 3d space.
    */
    /*****************************************/
    class pos_3d
    {
    public:
      float x; //!< X Position
      float y; //!< Y Position
      float z; //!< Z Position
    };
    
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
      
      /*****************************************/
      /*!
      \brief
      Default Constructor

      \param count
      Number of vertices in the shape
      */
      /*****************************************/
      Shape(unsigned count = 0) : vc(NULL), vt(NULL),
      vc_isdirty(true), vt_isdirty(true), vertexcount(count) {}
      
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
    };
    
    /*****************************************/
    /*!
    \brief
    Triangle
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
      Triangle() : Shape(3)
      {
        vertex = new pos_3d[vertexcount];
        color = new uint32_t[vertexcount];
      }

      pos_3d *vertex; //!< position of each vertex
      uint32_t *color; //!< Color of each vertex
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
