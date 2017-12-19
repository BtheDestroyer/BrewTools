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

#ifndef __BT_GFXWINDOW_H_
#define __BT_GFXWINDOW_H_

#include "brewtools/window.h"
#include <string>

#ifdef _3DS
#include <citro3d.h>

#define TOP_SCREEN_WIDTH  400
#define TOP_SCREEN_HEIGHT 240
#define BOTTOM_SCREEN_WIDTH  320
#define BOTTOM_SCREEN_HEIGHT 240
#define DEFAULT_WINDOW_WIDTH TOP_SCREEN_WIDTH
#define DEFAULT_WINDOW_HEIGHT TOP_SCREEN_HEIGHT
#elif _WIN32
#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720
#endif

#ifdef _WIN32 //The following only exists in a Windows build
struct GLFWwindow;
#endif

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
  Graphics window for drawing with OpenGL.
  */
  /*****************************************/
  class GFXWindow : public Window
  {
  public:
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
    GFXWindow(std::string name = "BrewTools GFXWindow", Window::Screen screen = TOP);
    
    /*****************************************/
    /*!
    \brief
    Conversion constructor.
    
    \param name
    Name of window.
    
    \param width
    Width of window.
    
    \param height
    Height of window.
    
    \param screen
    Which screen to display on if on a multi-screen system.
    */
    /*****************************************/
    GFXWindow(std::string name, int width, int height, Window::Screen screen = TOP);
    
    /*****************************************/
    /*!
    \brief
    Destructor.
    */
    /*****************************************/
    ~GFXWindow();
    
    /*****************************************/
    /*!
    \brief
    Updates the window.
    */
    /*****************************************/
    void Update();
    
    /*****************************************/
    /*!
    \brief
    Clears the window.
    */
    /*****************************************/
    void Clear();
    
    /*****************************************/
    /*!
    \brief
    Swaps the buffers of the window.
    */
    /*****************************************/
    void SwapBuffers();
    
    /*****************************************/
    /*!
    \brief
    Updates the window's DT
    */
    /*****************************************/
    void UpdateDT();
    
    /*****************************************/
    /*!
    \brief
    Gets the window's DT
    
    \return
    Delta time (time to draw last frame)
    */
    /*****************************************/
    float GetDT()
    {
      return dt;
    }
    
    /*****************************************/
    /*!
    \brief
    Gets the window's FPS
    
    \return
    Frames per second (based on the time to draw last frame)
    */
    /*****************************************/
    float GetFPS()
    {
      return currentfps;
    }
    
    #ifdef _WIN32 //The following only exists in a Windows build
    /*****************************************/
    /*!
    \brief
    Gets the GLFWWindow
    
    \return
    GLFWWindow of GFXWindow
    */
    /*****************************************/
    GLFWwindow* GetGLFWWindow()
    {
      return glfwwindow;
    }
    #endif
    
  private:
    uint64_t lasttime; //!< Last time dt was calculated
    float dt; //!< Average delta time to draw a frame
    float currentfps; //!< Average delta time to draw a frame
    #ifdef _3DS //The following only exists in a 3DS build
    C3D_RenderTarget* target; //!< Render target for 3DS
    #elif _WIN32 //The following only exists in a Windows build
    GLFWwindow* glfwwindow; //!< Window to draw to for OpenGL
    #endif
  };
}

#endif
