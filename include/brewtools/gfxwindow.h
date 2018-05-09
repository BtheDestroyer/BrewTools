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

#include "brewtools/distillery.h"
#include "brewtools/trace.h"
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

//! Flags for C3D
#define DISPLAY_TRANSFER_FLAGS                                              \
  (GX_TRANSFER_FLIP_VERT(0) | GX_TRANSFER_OUT_TILED(0) |                    \
   GX_TRANSFER_RAW_COPY(0) | GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8) | \
   GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGB8) |                           \
   GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_NO))
#elif _WIN32
#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720
#endif

#ifdef _WIN32 //The following only exists in a Windows build
#include <glad/glad.h>
#include <GLFW/glfw3.h>
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
    
    /*****************************************/
    /*!
    \brief
    Gets the background color
    
    \return
    Background color
    */
    /*****************************************/
    uint64_t GetBG()
    {
      return bg;
    }
    
    /*****************************************/
    /*!
    \brief
    Sets the background color
    */
    /*****************************************/
    void SetBG(uint64_t col)
    {
      bg = col;
    #ifdef _3DS //The following only exists in a 3DS build
      C3D_RenderTargetSetClear(target, C3D_CLEAR_ALL, bg, 0);
    #endif
      Clear();
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
    
    /*****************************************/
    /*!
    \brief
    Sets the window's name

    \param newname
    New name
    */
    /*****************************************/
    void SetName(std::string newname)
    {
      name = newname;
    #ifdef _WIN32 //The following only exists in a Windows build
      glfwSetWindowTitle(glfwwindow, name.c_str());
    #endif
    }

    /*****************************************/
    /*!
    \brief
    Sets the window's screen

    \param newscreen
    New screen
    */
    /*****************************************/
    void SetScreen(Window::Screen newscreen)
    {
      screen = newscreen;
    #ifdef _3DS //The following only exists in a 3DS build
      // If screen is bottom, use the bottom screen. Otherwise, default to top
      C3D_RenderTargetSetOutput(
        target,
        (screen == BOTTOM) ? GFX_BOTTOM : GFX_TOP, GFX_LEFT,
        DISPLAY_TRANSFER_FLAGS
      );
    #endif
    }

    /*****************************************/
    /*!
    \brief
    Gets the 3DS Render Target

    \return
    C3D Render Target pointer
    */
    /*****************************************/
    #ifdef _3DS //The following only exists in a 3DS build
    C3D_RenderTarget *GetTarget()
    #else
    void *GetTarget()
    #endif
    {
    #ifdef _3DS //The following only exists in a 3DS build
      return target;
    #else
      Trace *trace = Engine::Get()->GetSystemIfExists<Trace>();
      if (trace)
        (*trace)[5] << "GFXWindow::GetTarget() only works on 3DS";
      return nullptr;
    #endif
    }

    /*****************************************/
    /*!
    \brief
    Starts a new frame

    \return
    Success. This will be false if there is already a frame in progress.
    */
    /*****************************************/
    bool StartFrame();

    /*****************************************/
    /*!
    \brief
    Ends the current frame

    \return
    Success. This will be false if there is no frame in progress.
    */
    /*****************************************/
    bool EndFrame();

  private:
    uint64_t bg; //!< Background color of the window
    uint64_t lasttime; //!< Last time dt was calculated
    float dt; //!< Average delta time to draw a frame
    float currentfps; //!< Average delta time to draw a frame
    int width; //!< Width of the window
    int height; //!< Height of the window
     //! Determines if a frame has been started on this window
    bool frameStarted;
    #ifdef _3DS //The following only exists in a 3DS build
    DVLB_s* vshader_dvlb;
    shaderProgram_s program;
    int uLoc_projection;
    C3D_RenderTarget* target; //!< Render target for 3DS
    C3D_Mtx projection; //!< Projection matrix
    #elif _WIN32 //The following only exists in a Windows build
    GLFWwindow* glfwwindow; //!< Window to draw to for OpenGL
    #endif
  };
}

#endif
