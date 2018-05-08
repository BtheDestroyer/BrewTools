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
    : Window(name, screen), bg(DEFAULT_BG_COLOR), dt(0), currentfps(0),
      width(DEFAULT_WINDOW_WIDTH), height(DEFAULT_WINDOW_HEIGHT)
  {
    Trace *trace = Engine::Get()->GetSystemIfExists<Trace>();
    if (trace)
      (*trace)[6] << "  Creating GFXWindow...";
    Time *t;
    if ((t = Engine::Get()->GetSystemIfExists<Time>()))
      lasttime = t->Current();
    else
      lasttime = 0;
    Graphics *gfx = Engine::Get()->GetSystemIfExists<Graphics>();
    GFXWindow *cwin = nullptr;
    if (gfx)
      cwin = gfx->GetCurrentWindow();
    #ifdef _WIN32 //The following only exists in a Windows build
    if (trace)
      (*trace)[7] << "    Creating glfw window...";
    glfwwindow = glfwCreateWindow(
      DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT,
      name.c_str(),
      nullptr, nullptr
    );
    if (!glfwwindow)
    {
      if (trace)
        (*trace)[6] << "  Failed to create glfw window";
      return;
    }

    if (trace)
      (*trace)[7] << "    Setting FBSC...";
    glfwMakeContextCurrent(glfwwindow);
    glfwSetFramebufferSizeCallback(glfwwindow, windows_fbsc);

    if (trace)
      (*trace)[7] << "    Loading GLAD...";
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      if (trace)
        (*trace)[6] << "  Failed to initialize GLAD";
      return;
    }
    if (cwin)
      glfwMakeContextCurrent(cwin->glfwwindow);
    #elif _3DS //The following only exists in a 3DS build
    target = C3D_RenderTargetCreate(
      height, width,
      GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8
    );
    C3D_RenderTargetSetClear(target, C3D_CLEAR_ALL, bg, 0);
    Mtx_OrthoTilt(
      &projection, -width, width, -height, height, 0.0f, 1.0f, true
    );
    // If screen is bottom, use the bottom screen. Otherwise, default to top
    C3D_RenderTargetSetOutput(
      target,
      (screen == BOTTOM) ? GFX_BOTTOM : GFX_TOP, GFX_LEFT,
      DISPLAY_TRANSFER_FLAGS
    );
    if (cwin)
      C3D_FrameDrawOn(cwin->GetTarget());
    #endif
    Clear();
    if (trace)
      (*trace)[6] << "  Created GFXWindow!";
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
  (std::string name, int width, int height, Window::Screen screen)
    : Window(name, screen), bg(DEFAULT_BG_COLOR), dt(0), currentfps(0),
      width(width), height(height)
  {
    #ifdef _3DS //The following only exists in a 3DS build
    target = C3D_RenderTargetCreate(
      height, width,
      GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8
    );
    Mtx_OrthoTilt(
      &projection, -width, width, -height, height, 0.0f, 1.0f, true
    );
    // If screen is bottom, use the bottom screen. Otherwise, default to top
    C3D_RenderTargetSetOutput(
      target,
      (screen == BOTTOM) ? GFX_BOTTOM : GFX_TOP, GFX_LEFT,
      DISPLAY_TRANSFER_FLAGS
    );
    #elif _WIN32 //The following only exists in a Windows build
    glfwwindow = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
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
  void GFXWindow::Update(bool swap)
  {
    if (swap)
    {
      SwapBuffers();
      Clear();
    }
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
    C3D_RenderTargetSetClear(target, C3D_CLEAR_ALL, bg, 0);
    #elif _WIN32
    glClearColor(
      RGBA8_GET_R(bg) / 255.0f,
      RGBA8_GET_G(bg) / 255.0f,
      RGBA8_GET_B(bg) / 255.0f,
      RGBA8_GET_A(bg) / 255.0f
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
