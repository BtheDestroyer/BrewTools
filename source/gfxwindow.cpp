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
#include <citro3d.h>
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
  GFXWindow::GFXWindow(std::string name, Window::Screen screen) : Window(name, screen)
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
    #else
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
    #ifdef _WIN32 //The following only exists in a Windows build
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
  Window(name, screen)
  {
    #ifdef _WIN32 //The following only exists in a Windows build
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
    #else
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
    #elif _WIN32
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
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
    glClearColor(0.5f, 0.3f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
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
