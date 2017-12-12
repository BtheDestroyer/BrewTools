/******************************************************************************/
/*!
\file gfxwindow.h
\author Bryce Dixon
\par email: realbthedestroyer\@gmail.com
\par BrewTools
\date 12/11/2017

\brief
Window for displaying graphics using OpenGL.
*/
/******************************************************************************/

#include "brewtools/gfxwindow.h"
#include "brewtools/macros.h"
#ifdef _WIN32 //The following only exists in a Windows build
#include "SDL2/SDL.h"
#endif //_WIN32

namespace BrewTools
{
  /*****************************************/
  /*!
  \brief
  Default constructor.
  */
  /*****************************************/
  GFXWindow::GFXWindow(unsigned flags)
  {
    #ifdef _WIN32 //The following only exists in a Windows build
    m_sdlwindow = SDL_CreateWindow("",
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT,
      flags);
    if (!m_sdlwindow)
      return;
    SDL_GL_CreateContext(m_sdlwindow);
    #else
    UNREFERENCED_PARAMETER(flags);
    #endif
  }
  
  /*****************************************/
  /*!
  \brief
  Conversion constructor.
  
  \param name
  Name of window.
  */
  /*****************************************/
  GFXWindow::GFXWindow(std::string name, unsigned flags)
  {
    #ifdef _WIN32 //The following only exists in a Windows build
    m_sdlwindow = SDL_CreateWindow(name.c_str(),
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT,
      flags);
    if (!m_sdlwindow)
      return;
    SDL_GL_CreateContext(m_sdlwindow);
    #else
    UNREFERENCED_PARAMETER(name);
    UNREFERENCED_PARAMETER(flags);
    #endif
  }
  
  /*****************************************/
  /*!
  \brief
  Constructor.
  
  \param name
  Name of window.
  
  \param width
  Width of window.
  
  \param height
  Height of window.
  */
  /*****************************************/
  GFXWindow::GFXWindow(std::string name, unsigned width, unsigned height,
                       unsigned flags)
  {
    #ifdef _WIN32 //The following only exists in a Windows build
    m_sdlwindow = SDL_CreateWindow(name.c_str(),
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      width, height,
      flags);
    if (!m_sdlwindow)
      return;
    SDL_GL_CreateContext(m_sdlwindow);
    #else
    UNREFERENCED_PARAMETER(name);
    UNREFERENCED_PARAMETER(width);
    UNREFERENCED_PARAMETER(height);
    UNREFERENCED_PARAMETER(flags);
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
    SDL_GL_DeleteContext(m_glcontext);
    if (m_sdlwindow)
      SDL_DestroyWindow(m_sdlwindow);
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
    if (m_sdlwindow)
      SDL_GL_SwapWindow(m_sdlwindow);
    #endif
  }
}
