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

#ifdef _3DS //The following only exists in a 3DS build
#include <3ds.h>
#endif //_3DS

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
    #endif //_3DS
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
    #endif //_3DS
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