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
    */
    /*****************************************/
    Console();

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

  private:
    #ifdef _3DS //The following only exists in a 3DS build
    PrintConsole *m_printconsole; //!< 3DS's console window
    #endif //_3DS
    #ifdef _WIN32 //The following only exists in a Windows build
    static unsigned m_consolecount; //!< Number of Windows consoles currently open
    #endif //_WIN32
  };
}

#endif
