/******************************************************************************/
/*!
\file graphics.cpp
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
#include "brewtools/distillery.h"
#include "brewtools/trace.h"
#include "brewtools/graphics.h"
#include "brewtools/window.h"
#include "brewtools/macros.h"

#ifdef _3DS //The following only exists in a 3DS build
#include <3ds.h>
#endif

/*****************************************/
/*!
\brief
Brewtools namespace.
*/
/*****************************************/
namespace BrewTools
{
  #ifdef _3DS //The following only exists in a 3DS build
  /*****************************************/
  /*!
  \brief
  Brewtools namespace.
  */
  /*****************************************/
  void c3d_setup_env_internal(const Graphics::vertex_col* vertices) {
    C3D_TexEnv* env = C3D_GetTexEnv(0);
    C3D_TexEnvSrc(env, C3D_Both, GPU_PRIMARY_COLOR, 0, 0);
    C3D_TexEnvOp(env, C3D_Both, 0, 0, 0);
    C3D_TexEnvFunc(env, C3D_Both, GPU_REPLACE);
    
    C3D_AttrInfo* attrInfo = C3D_GetAttrInfo();
    AttrInfo_Init(attrInfo);
    AttrInfo_AddLoader(attrInfo, 0, GPU_FLOAT, 3);
    AttrInfo_AddLoader(attrInfo, 1, GPU_UNSIGNED_BYTE, 4);
    
    C3D_BufInfo* bufInfo = C3D_GetBufInfo();
    BufInfo_Init(bufInfo);
    BufInfo_Add(bufInfo, vertices, sizeof(Graphics::vertex_col), 2, 0x10);
  }
  #endif
  
  /****************************************************************************/
  /*
  BASIC GEOMETRY
  */
  /****************************************************************************/
  
  /*****************************************/
  /*!
  \brief
  Assignment operator
  
  \param rhs
  Object to the right of the =
  */
  /*****************************************/
  Graphics::pos_2d& Graphics::pos_2d::operator=(pos_2d rhs)
  {
    x = rhs.x;
    y = rhs.y;
    return *this;
  }
  
  /*****************************************/
  /*!
  \brief
  Index operator
  
  \param rhs
  Object to the right of the =
  */
  /*****************************************/
  float& Graphics::pos_2d::operator[](unsigned rhs)
  {
    switch (rhs)
    {
      case 0:
      return x;
      
      case 1:
      default:
      return y;
    }
  }
  
  /*****************************************/
  /*!
  \brief
  Assignment operator
  
  \param rhs
  Object to the right of the =
  */
  /*****************************************/
  Graphics::pos_3d& Graphics::pos_3d::operator=(pos_3d rhs)
  {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
  }
  
  /*****************************************/
  /*!
  \brief
  Assignment operator
  
  \param rhs
  Object to the right of the =
  */
  /*****************************************/
  Graphics::pos_3d& Graphics::pos_3d::operator=(pos_2d rhs)
  {
    x = rhs.x;
    y = rhs.y;
    return *this;
  }
  
  /*****************************************/
  /*!
  \brief
  Index operator
  
  \param rhs
  Object to the right of the =
  */
  /*****************************************/
  float& Graphics::pos_3d::operator[](unsigned rhs)
  {
    switch (rhs)
    {
      case 0:
      return x;
      
      case 1:
      return y;
      
      case 2:
      default:
      return z;
    }
  }
  
  /*****************************************/
  /*!
  \brief
  Assignment operator
  
  \param rhs
  Object to the right of the =
  */
  /*****************************************/
  Graphics::pos_4d& Graphics::pos_4d::operator=(pos_4d rhs)
  {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    w = rhs.w;
    return *this;
  }
  
  /*****************************************/
  /*!
  \brief
  Assignment operator
  
  \param rhs
  Object to the right of the =
  */
  /*****************************************/
  Graphics::pos_4d& Graphics::pos_4d::operator=(pos_3d rhs)
  {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
  }
  
  /*****************************************/
  /*!
  \brief
  Assignment operator
  
  \param rhs
  Object to the right of the =
  */
  /*****************************************/
  Graphics::pos_4d& Graphics::pos_4d::operator=(pos_2d rhs)
  {
    x = rhs.x;
    y = rhs.y;
    return *this;
  }
  
  /*****************************************/
  /*!
  \brief
  Index operator
  
  \param rhs
  Object to the right of the =
  */
  /*****************************************/
  float& Graphics::pos_4d::operator[](unsigned rhs)
  {
    switch (rhs)
    {
      case 0:
      return x;
      
      case 1:
      return y;
      
      case 2:
      return z;
      
      case 3:
      default:
      return w;
    }
  }
  
  /*****************************************/
  /*!
  \brief
  Default constructor (Identity Matrix)
  
  \param scalar
  What to scale the matrix by
  */
  /*****************************************/
  Graphics::mat_3d::mat_3d(float scalar)
  {
    for (unsigned i = 0; i < 3; ++i) index[i][i] = scalar;
  }
  
  /*****************************************/
  /*!
  \brief
  Copy constructor
  */
  /*****************************************/
  Graphics::mat_3d::mat_3d(const mat_3d& mat)
  {
    for (unsigned i = 0; i < 3; ++i)
    index[i] = mat[i];
  }
  
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
  Graphics::mat_3d::mat_3d(
    float x1, float y1, float z1,
    float x2, float y2, float z2,
    float x3, float y3, float z3
  )
  {
    index[0][0] = x1;
    index[0][1] = x2;
    index[0][2] = x3;
    
    index[1][0] = y1;
    index[1][1] = y2;
    index[1][2] = y3;
    
    index[2][0] = z1;
    index[2][1] = z2;
    index[2][2] = z3;
  }
  
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
  Graphics::mat_3d::mat_3d(pos_3d c1, pos_3d c2, pos_3d c3)
  {
    index[0] = c1;
    index[1] = c2;
    index[2] = c3;
  }
  
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
  Graphics::pos_2d operator*(Graphics::pos_2d lhs, Graphics::mat_3d rhs)
  {
    Graphics::pos_2d newpos(rhs[2][0], rhs[2][1]);
    for (unsigned i = 0; i < 2; ++i)
    {
      for (unsigned j = 0; j < 2; ++j)
      {
        newpos[i] += lhs[j] * rhs[j][i];
      }
    }
    return newpos;
  }
  
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
  Graphics::mat_3d Graphics::mat_3d::operator*(mat_3d rhs)
  {
    mat_3d newmat(0);
    for(unsigned i = 0; i < 3; ++i)
    {
      for (unsigned j = 0; j < 3; ++j)
      {
        for (unsigned k = 0; k < 3; ++k)
        {
          newmat[i][j] += index[i][k] * rhs[k][j];
        }
      }
    }
    return newmat;
  }
  
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
  Graphics::pos_3d& Graphics::mat_3d::operator[](unsigned rhs)
  {
    return index[rhs];
  }
  
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
  Graphics::pos_3d Graphics::mat_3d::operator[](unsigned rhs) const
  {
    return index[rhs];
  }
  
  /*****************************************/
  /*!
  \brief
  Assignment operator
  
  \param rhs
  Object to the right of the =
  
  \return
  Reference to modified vertex
  */
  /*****************************************/
  Graphics::vertex_col& Graphics::vertex_col::operator=(vertex_col rhs)
  {
    pos = rhs.pos;
    color = rhs.color;
    return *this;
  }
  
  /*****************************************/
  /*!
  \brief
  Assignment operator
  
  \param rhs
  Object to the right of the =
  
  \return
  Reference to modified vertex
  */
  /*****************************************/
  Graphics::vertex_tex& Graphics::vertex_tex::operator=(vertex_tex rhs)
  {
    pos = rhs.pos;
    uv = rhs.uv;
    return *this;
  }
  
  /*****************************************/
  /*!
  \brief
  Assignment operator
  
  \param rhs
  Object to the right of the =
  
  \return
  Reference to modified texture
  */
  /*****************************************/
  Graphics::texture& Graphics::texture::operator=(texture rhs)
  {
    #ifdef _3DS //The following only exists in a 3DS build
    C3D_TexInit(&tex, rhs.width, rhs.height, rhs.tex.fmt);
    #elif _WIN32 //The following only exists in a Windows build
    //TODO: Figure out windows equivalent
    #endif
    tile = rhs.tile;
    width = rhs.width;
    height = rhs.height;
    return *this;
  }
  
  /****************************************************************************/
  /*
  GENERIC SHAPE
  */
  /****************************************************************************/
  
  /*****************************************/
  /*!
  \brief
  Assignment operator
  
  \param rhs
  Object to the right of the =
  */
  /*****************************************/
  Graphics::Shape& Graphics::Shape::operator=(Shape rhs)
  {
    position = rhs.position;
    rotation = rhs.rotation;
    scale = rhs.scale;
    if (!tex) tex = new texture;
    *tex = *(rhs.tex);
    vc_isdirty = true;
    vt_isdirty = true;
    return *this;
  }
  
  /*****************************************/
  /*!
  \brief
  Generates the vertices with colors
  */
  /*****************************************/
  bool Graphics::Shape::GenerateColorVertices()
  {
    SAFE_DELETE(vc);
    if (vc_isdirty && vertexcount)
    {
      vc = new vertex_col[vertexcount];
      mat_3d mat;
      for (unsigned i = 0; i < vertexcount; ++i)
      {
        vc[i].color = color[i];
        vc[i].pos = vertex[indice[i]];
      }
      return true;
    }
    return false;
  }
  
  /*****************************************/
  /*!
  \brief
  Generates the vertices with texture coordinates
  */
  /*****************************************/
  bool Graphics::Shape::GenerateTextureVertices()
  {
    SAFE_DELETE(vt);
    if (vt_isdirty && vertexcount && tex)
    {
      vt = new vertex_tex[vertexcount];
      for (unsigned i = 0; i < vertexcount; ++i)
      {
        vt[i].uv = uv[i];
        vt[i].pos = vertex[i];
      }
      return true;
    }
    return false;
  }
  
  /*****************************************/
  /*!
  \brief
  Creates and returns a pointer to an array of color vertices
  
  \return
  Pointer to allocated vertex_col
  */
  /*****************************************/
  const Graphics::vertex_col* Graphics::Shape::GetColorVertices()
  {
    GenerateColorVertices();
    return vc;
  }
  
  /*****************************************/
  /*!
  \brief
  Creates and returns a pointer to an array of texture vertices
  */
  /*****************************************/
  const Graphics::vertex_tex* Graphics::Shape::GetTextureVertices()
  {
    GenerateTextureVertices();
    return vt;
  }
  
  /*****************************************/
  /*!
  \brief
  Draws the shape to the screen at its current location
  */
  /*****************************************/
  void Graphics::Shape::Draw()
  {
    const vertex_tex *texdraw;
    const vertex_col *coldraw;
    if ((texdraw = GetTextureVertices()) != NULL)
    {
      
    }
    else if ((coldraw = GetColorVertices()) != NULL)
    {
      #ifdef _3DS //The following only exists in a 3DS build
      c3d_setup_env_internal(coldraw);
      C3D_DrawArrays(GPU_TRIANGLES, 0, vertexcount);
      #elif _WIN32 //The following only exists in a Windows build
      
      #endif
    }
  }
  
  /****************************************************************************/
  /*
  GRAPHICS SYSTEM
  */
  /****************************************************************************/
  
  /*****************************************/
  /*!
  \brief
  Default Constructor
  */
  /*****************************************/
  Graphics::Graphics()
  {
    #ifdef _3DS //The following only exists in a 3DS build
    gfxInitDefault();
    
    
    #elif _WIN32 //The following only exists in a Windows build
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      Trace *trace = Engine::Get()->GetSystemIfExists<Trace>();
      if (trace)
      (*trace)[0] << "Failed to initialize GLAD";
    }
    #endif
  }
  
  /*****************************************/
  /*!
  \brief
  Destructor
  */
  /*****************************************/
  Graphics::~Graphics()
  {
    for (auto it : windows)
    delete it;
    #ifdef _3DS //The following only exists in a 3DS build
    gfxExit();
    #elif _WIN32
    glfwTerminate();
    #endif
  }
  
  /*****************************************/
  /*!
  \brief
  Updates graphics by flushing and swapping the buffers.
  */
  /*****************************************/
  void Graphics::Update()
  {
    for (auto it : windows)
    it->Update();
    #ifdef _3DS //The following only exists in a 3DS build
    gfxFlushBuffers();
    gfxSwapBuffers();
    gspWaitForVBlank();
    #elif _WIN32 //The following only exists in a Windows build
    
    #endif
  }
  
  /*****************************************/
  /*!
  \brief
  Adds a created window to the list of windows.
  
  \param window
  Pointer to window to add.
  */
  /*****************************************/
  void Graphics::AddWindow(Window *window)
  {
    if (window->parent)
    ((Graphics*)(window->parent))->RemoveWindow(window);
    window->parent = this;
    windows.push_back(window);
  }
  
  /*****************************************/
  /*!
  \brief
  Removes a created window from the list of windows.
  
  \param window
  Pointer to window to remove.
  */
  /*****************************************/
  void Graphics::RemoveWindow(Window *window)
  {
    auto it = windows.begin();
    for (auto prev = it; it != windows.end(); prev = it++)
    {
      if (*it == window)
      {
        window->parent = NULL;
        windows.erase(it);
        it = prev;
      }
    }
  }
}
