/******************************************************************************/
/*!
\file graphics.cpp
\author Bryce Dixon
\par email: realbthedestroyer\@gmail.com
\par BrewTools
\date 12/11/2017

\brief
Graphics management and implementation.
*/
/******************************************************************************/
#include "brewtools/graphics.h"
#include "brewtools/window.h"

#ifdef _3DS //The following only exists in a 3DS build
#include <3ds.h>
#elif _WIN32 //The following only exists in a Windows build
#include "SDL2/SDL.h"
#endif

namespace BrewTools
{
  /*****************************************/
  /*!
  \brief
  Default Constructor
  */
  /*****************************************/
  Graphics::Graphics() : m_windows()
  {
    #ifdef _3DS //The following only exists in a 3DS build
    gfxInitDefault();
    #elif _WIN32 //The following only exists in a Windows build
    SDL_Init(SDL_INIT_VIDEO);
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
    #ifdef _3DS //The following only exists in a 3DS build
    gfxExit();
    #elif _WIN32
    SDL_Quit();
    #endif
    for (unsigned i = 0; i < m_windows.size(); ++i)
      delete m_windows[i];
  }
  
  /*****************************************/
  /*!
  \brief
  Updates graphics by flushing and swapping the buffers.
  */
  /*****************************************/
  void Graphics::Update()
  {
    #ifdef _3DS //The following only exists in a 3DS build
    gfxFlushBuffers();
    gfxSwapBuffers();
    gspWaitForVBlank();
    #endif //_3DS
  }
}
