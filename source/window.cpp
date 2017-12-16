/******************************************************************************/
/*!
\file window.cpp
\author Bryce Dixon
\par email: realbthedestroyer\@gmail.com
\par BrewTools
\date 12/11/2017
\par Created: v1.0
\par Updated: v1.0

\brief
Window class for creating and selecting different windows or screens.
*/
/******************************************************************************/

#include "brewtools/window.h"

namespace BrewTools
{
  /*****************************************/
  /*!
  \brief
  Default Constructor.
  
  \param name
  Name of window to create.
  */
  /*****************************************/
  Window::Window(std::string name, Window::Screen screen)
  {
    this->name = name;
    this->screen = screen;
  }
  
  /*****************************************/
  /*!
  \brief
  Destructor.
  */
  /*****************************************/
  Window::~Window()
  {
    
  }
  
  /*****************************************/
  /*!
  \brief
  Update function.
  */
  /*****************************************/
  void Window::Update()
  {
    
  }
}
