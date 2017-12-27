/******************************************************************************/
/*!
\file gfxwindow.h
\author Bryce Dixon
\par email: realbthedestroyer\@gmail.com
\par BrewTools
\date 12/11/2017
\par Created: v1.0
\par Updated: v1.0

\brief
Window for displaying graphics using OpenGL.
*/
/******************************************************************************/

#include "brewtools/gfxwindow.h"
#include "brewtools/macros.h"
#include "brewtools/distillery.h"
#include "brewtools/trace.h"
#include "brewtools/graphics.h"
#include "brewtools/time.h"
#ifdef _WIN32 //The following only exists in a Windows build
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#elif _3DS //The following only exists in a 3DS build
#include <3ds.h>
#include <citro3d.h>
#include "vshader_shbin.h"
#endif

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

#ifdef _WIN32 //The following only exists in a Windows build
/*****************************************/
/*!
\brief
Framebuffer size callback for GLFW.

\param window
Window pointer.

\param width
Width of viewport.

\param height
Height of viewport.
*/
/*****************************************/
void windows_fbsc(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}
#endif //_WIN32

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
  Default constructor.
  
  \param name
  Name of window.
  
  \param screen
  Which screen to display on if on a multi-screen system.
  */
  /*****************************************/
  GFXWindow::GFXWindow(std::string name, Window::Screen screen)
  : Window(name, screen)
  {
    #ifdef _WIN32 //The following only exists in a Windows build
    glfwwindow = glfwCreateWindow
    (DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, name.c_str(), NULL, NULL);
    if (glfwwindow)
    {
      glfwSetFramebufferSizeCallback(glfwwindow, windows_fbsc);
      
      Trace *trace = Engine::Get()->GetSystemIfExists<Trace>();
      Graphics *g = Engine::Get()->GetSystem<Graphics>();
      g->SelectWindow(this);
      
      if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
      {
        if (trace) (*trace)[0] << "Failed to initialize GLAD";
      }
    }
    #elif _3DS //The following only exists in a 3DS build
    // //Setup the shader
    // vshader_dvlb = DVLB_ParseFile((u32 *)shader_shbin, shader_shbin_size);
    // shaderProgramInit(&shader);
    // shaderProgramSetVsh(&shader, &dvlb->DVLE[0]);
    // C3D_BindProgram(&shader);
    
    // //Get shader uniform descriptors
    // int projection_desc =
    // shaderInstanceGetUniformLocation(shader.vertexShader, "projection");
    // int transform_desc =
    // shaderInstanceGetUniformLocation(shader.vertexShader, "transform");
    // int useTransform_desc =
    // shaderInstanceGetUniformLocation(shader.vertexShader, "useTransform");
    #endif
  }
  
  /*****************************************/
  /*!
  \brief
  Destructor.
  */
  /*****************************************/
  GFXWindow::~GFXWindow()
  {
    #ifdef _3DS //The following only exists in a 3DS build
    C3D_RenderTargetDelete(target);
    #elif _WIN32 //The following only exists in a Windows build
    glfwDestroyWindow(glfwwindow);
    #endif
  }
  
  /*****************************************/
  /*!
  \brief
  Constructor.
  
  \param name
  Name of window to create.
  
  \param width
  Width of window.
  
  \param height
  Height of window.
  
  \param screen
  Which screen to display on if on a multi-screen system.
  */
  /*****************************************/
  GFXWindow::GFXWindow
  (std::string name, int width, int height, Window::Screen screen) :
  Window(name, screen), width(width), height(height)
  {
    #ifdef _3DS //The following only exists in a 3DS build
    target = C3D_RenderTargetCreate(
      height, width, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8
    );
    Mtx_OrthoTilt(
      &projection, -width, width, -height, height, 0.0f, 1.0f, true
    );
    C3D_RenderTargetSetOutput(
      target,
      screen == Window::Screen::TOP ? GFX_TOP : GFX_BOTTOM,
      GFX_LEFT,
      0x1000
    );
    #elif _WIN32 //The following only exists in a Windows build
    glfwwindow = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
    if (glfwwindow)
    {
      glfwSetFramebufferSizeCallback(glfwwindow, windows_fbsc);
      
      Trace *trace = Engine::Get()->GetSystemIfExists<Trace>();
      Graphics *g = Engine::Get()->GetSystem<Graphics>();
      g->SelectWindow(this);
      
      if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
      {
        if (trace) (*trace)[0] << "Failed to initialize GLAD";
      }
    }
    #endif
  }
  
  /*****************************************/
  /*!
  \brief
  Updates the window by swapping buffers.
  */
  /*****************************************/
  void GFXWindow::Update()
  {
    SwapBuffers();
    Clear();
    UpdateDT();
  }
  
  /*****************************************/
  /*!
  \brief
  Clears the window.
  */
  /*****************************************/
  void GFXWindow::Clear()
  {
    #ifdef _3DS
    uint64_t color =
    ((bg>>24)&0x000000FF) |
    ((bg>>8)&0x0000FF00) |
    ((bg<<8)&0x00FF0000) |
    ((bg<<24)&0xFF000000);
    
    C3D_RenderTargetSetClear(target, C3D_CLEAR_ALL, color, 0);
    #elif _WIN32
    glClearColor(
      RGBA8_GET_R(bg) / 255.0f,
      RGBA8_GET_G(bg) / 255.0f,
      RGBA8_GET_B(bg) / 255.0f,
      1.0f
    );
    glClear(GL_COLOR_BUFFER_BIT);
    #endif
  }
  
  /*****************************************/
  /*!
  \brief
  Swaps the buffers of the window.
  */
  /*****************************************/
  void GFXWindow::SwapBuffers()
  {
    #ifdef _3DS
    C3D_FrameEnd(0);
    #elif _WIN32
    glfwSwapBuffers(glfwwindow);
    glfwPollEvents();
    #endif
  }
  
  /*****************************************/
  /*!
  \brief
  Updates the window's DT
  */
  /*****************************************/
  void GFXWindow::UpdateDT()
  {
    Time *t;
    if (!(t = Engine::Get()->GetSystemIfExists<Time>())) return;
    dt = float(t->Current() - lasttime) / 1000.0f;
    currentfps = 1.0f/dt;
    lasttime = t->Current();
  }
}
