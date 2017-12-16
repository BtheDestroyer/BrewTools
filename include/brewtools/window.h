/******************************************************************************/
/*!
\file window.h
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

#ifndef __BT_WINDOW_H_
#define __BT_WINDOW_H_

#include <string>

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
  Window class for controlling windows in Windows or other PC OSs.
  for controlling screens on 3DS or other consoles.
  */
  /*****************************************/
  class Window
  {
  public:
    /*****************************************/
    /*!
    \brief
    Used for selecting different screens on 3DS and Wii U.
    Ignored by other platforms.
    */
    /*****************************************/
    enum Screen
    {
      UNKNOWN = -1, //!< Used for errors
      TOP,    //!< 3DS's top screen
      BOTTOM, //!< 3DS's bottom screen
      COUNT,  //!< Number of screens
      TV = TOP,         //!< Wii U's TV screen
      GAMEPAD = BOTTOM, //!< Wii U's Gamepad screen
    };
    
    /*****************************************/
    /*!
    \brief
    Default Constructor.

    \param name
    Name of window to create.

    \param screen
    Screen to display on (if on a multi-screen system).
    */
    /*****************************************/
    Window(std::string name = "BrewTools Window", Window::Screen screen = TOP);
    
    /*****************************************/
    /*!
    \brief
    Destructor.
    */
    /*****************************************/
    virtual ~Window();
    
    /*****************************************/
    /*!
    \brief
    Updates the given Window.
    */
    /*****************************************/
    virtual void Update();
  private:
    std::string name;
    Window::Screen screen;
  };
}

#endif
