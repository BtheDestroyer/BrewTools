/******************************************************************************/
/*!
\file console.h
\author Bryce Dixon
\par email: realbthedestroyer\@gmail.com
\par BrewTools
\date 12/11/2017
\par Created: v1.0
\par Updated: v1.0

\brief
Console class for creating and selecting different console windows or screens.
*/
/******************************************************************************/

#ifndef __BT_CONSOLE_H_
#define __BT_CONSOLE_H_

#include "brewtools/window.h" // Window class

#ifdef _3DS //The following only exists in a 3DS build
#include <3ds/console.h>      //  3DS's console
#endif //_3DS

/*****************************************/
/*!
\brief
Brewtools namespace.
*/
/*****************************************/
namespace BrewTools
{
  class Trace; //  Forward declaration

  /*****************************************/
  /*!
  \brief
  Window class for controlling windows in Windows or other PC OSs.
  for controlling screens on 3DS or other consoles.
  */
  /*****************************************/
  class Console : public Window
  {
  public:
    /*****************************************/
    /*!
    \brief
    Default Constructor.

    \param name
    Name of window.

    \param screen
    Which screen to display on if on a multi-screen system.
    */
    /*****************************************/
    Console(std::string name = "BrewTools GFX Window", Window::Screen screen = TOP);

    /*****************************************/
    /*!
    \brief
    Destructor.
    */
    /*****************************************/
    ~Console();

    /*****************************************/
    /*!
    \brief
    Updates the given Window.
    */
    /*****************************************/
    void Update();

    /*****************************************/
    /*!
    \brief
    Returns the 3DS's print console
    */
    /*****************************************/
    #ifdef _3DS //The following only exists in a 3DS build
    PrintConsole *GetPrintConsole();
    #else
    void *GetPrintConsole();
    #endif

    /*****************************************/
    /*!
    \brief
    Returns if the console is selected.
    */
    /*****************************************/
    bool IsSelected();

  private:
    friend Trace; //!< This allows the Trace system to modify consoles
    bool m_selected; //!< Determines if the console is currently selected

    #ifdef _3DS //The following only exists in a 3DS build
    PrintConsole m_printconsole; //!< 3DS's console window
    #endif //_3DS
  };
}

#endif
