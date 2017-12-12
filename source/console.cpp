/******************************************************************************/
/*!
\file console.cpp
\author Bryce Dixon
\par email: realbthedestroyer\@gmail.com
\par BrewTools
\date 12/11/2017

\brief
Console class for creating and selecting different console windows or screens.
*/
/******************************************************************************/

#include "brewtools/console.h" //!< Console class
#ifdef _WIN32
#include <windows.h>
#include <stdio.h>
#endif

namespace BrewTools
{
  #ifdef _WIN32 //The following only exists in a Windows build
  static unsigned m_consolecount; //!< Number of Windows consoles currently open
  #endif //_WIN32
  /*****************************************/
  /*!
  \brief
  Default Constructor.
  */
  /*****************************************/
  Console::Console()
  {
    #ifdef _3DS //The following only exists in a 3DS build
    m_printconsole = consoleInit(GFX_TOP, NULL);
    #elif _WIN32 //The following only exists in a Windows build
    if (!GetConsoleWindow())
    {
      AllocConsole();
      AttachConsole(GetCurrentProcessId());
      freopen("CON", "w", stdout);
      m_consolecount = 0;
    }
    else
      ++m_consolecount;
    #endif
  }
  
  /*****************************************/
  /*!
  \brief
  Destructor.
  */
  /*****************************************/
  Console::~Console()
  {
    #ifdef _3DS //The following only exists in a 3DS build
    m_printconsole = consoleInit(GFX_TOP, NULL);
    #elif _WIN32 //The following only exists in a Windows build
    if (m_consolecount == 0 || --m_consolecount == 0)
      FreeConsole();
    #endif
  }
  
  /*****************************************/
  /*!
  \brief
  Updates the given Window.
  */
  /*****************************************/
  void Console::Update()
  {
    
  }
  
  #ifdef _3DS //The following only exists in a 3DS build
  /*****************************************/
  /*!
  \brief
  Updates the given Window.
  */
  /*****************************************/
  PrintConsole *Console::GetPrintConsole()
  {
    return m_printconsole;
  }
  #endif //_3DS
}
