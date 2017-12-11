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
    #elif _WIN32
    AllocConsole();
    AttachConsole(GetCurrentProcessId());
    freopen("CON", "w", stdout);
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
