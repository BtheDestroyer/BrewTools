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
#ifdef _WIN32 //The following only exists in a Windows build

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
  {
    Window(name, screen);
    #ifdef _WIN32 //The following only exists in a Windows build
    glfwwindow = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT,
                                  name.c_str(), NULL, NULL);
    #else
    UNREFERENCED_PARAMETER(name);
    UNREFERENCED_PARAMETER(screen);
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
  GFXWindow::GFXWindow(std::string name, int width, int height,
                       Window::Screen screen)
  {
    Window(name, screen);
    #ifdef _WIN32 //The following only exists in a Windows build
    glfwwindow = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
    #else
    UNREFERENCED_PARAMETER(name);
    UNREFERENCED_PARAMETER(width);
    UNREFERENCED_PARAMETER(height);
    UNREFERENCED_PARAMETER(screen);
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
    #ifdef _WIN32 //The following only exists in a Windows build
    
    #endif
  }
}
