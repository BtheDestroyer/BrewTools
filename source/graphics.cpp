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

#ifdef _3DS //The following only exists in a 3DS build
#include <3ds.h>
#elif _WIN32 //The following only exists in a Windows build
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
