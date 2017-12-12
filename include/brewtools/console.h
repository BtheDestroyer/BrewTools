/******************************************************************************/
/*!
\file console.h
\author Bryce Dixon
\par email: realbthedestroyer\@gmail.com
\par BrewTools
\date 12/11/2017

\brief
Console class for creating and selecting different console windows or screens.
*/
/******************************************************************************/

#ifndef __BT_CONSOLE_H_
#define __BT_CONSOLE_H_

#include "brewtools/window.h" //!< Window class

#ifdef _3DS //The following only exists in a 3DS build
#include <3ds/console.h>      //!< 3DS's console
#endif //_3DS

namespace BrewTools
{
  class Trace; //!< Forward declaration

  /*****************************************/
  /*!
  \brief
  Window class for controlling windows in Windows or other PC OSs.
  for controlling screens on 3DS or other consoles.
  */
  /*****************************************/
  class Console : Window
  {
  public:
    /*****************************************/
    /*!
    \brief
    Default Constructor.

    \param screen
    Used to set which screen is being displayed on for 3DS and Wii U.
    Defauts to TOP/TV.
    */
    /*****************************************/
    Console(Window::Screen screen = TOP);

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

    #ifdef _3DS //The following only exists in a 3DS build
    /*****************************************/
    /*!
    \brief
    Updates the given Window.
    */
    /*****************************************/
    PrintConsole *GetPrintConsole();
    #endif //_3DS

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
    PrintConsole *m_printconsole; //!< 3DS's console window
    #endif //_3DS
  };
}

#endif
