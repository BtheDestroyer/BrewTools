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
    UNREFERENCED_PARAMETER(vertices);
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
  
  /*****************************************/
  /*!
  \brief
  Generates the vertices with colors
  */
  /*****************************************/
  bool Graphics::Shape::GenerateColorVertices()
  {
    if (vc) SAFE_DELETE(vc);
    if (vc_isdirty)
    {
      vc = new vertex_col[vertexcount];
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
    if (vt) SAFE_DELETE(vt);
    if (vt_isdirty)
    {
      vt = new vertex_tex[vertexcount];
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
  Creates and returns a pointer to an array of color vertices
  
  \return
  Pointer to allocated vertex_col
  */
  /*****************************************/
  bool Graphics::Triangle::GenerateColorVertices()
  {
    if (Shape::GenerateColorVertices())
    {
      for (unsigned i = 0; i < vertexcount; ++i)
      {
        vc[i].color = color[i];
        vc[i].pos = vertex[i];
      }
      return true;
    }
    return false;
  }
  
  /*****************************************/
  /*!
  \brief
  Creates and returns a pointer to an array of texture vertices
  */
  /*****************************************/
  bool Graphics::Triangle::GenerateTextureVertices()
  {
    if (Shape::GenerateColorVertices())
    {
      for (unsigned i = 0; i < vertexcount; ++i)
      {
        vc[i].color = color[i];
        vc[i].pos = vertex[i];
      }
      return true;
    }
    return false;
  }
  
  
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
