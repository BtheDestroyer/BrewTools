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
#include "brewtools/distillery.h" //!< Engine class
#include "brewtools/trace.h" //!< Trace class
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
  Console::Console(Window::Screen screen)
  {
    #ifdef _3DS //The following only exists in a 3DS build
    m_printconsole = consoleInit((screen == TOP) ? GFX_TOP : GFX_BOTTOM, NULL);
    #elif _WIN32 //The following only exists in a Windows build
    UNREFERENCED_PARAMETER(screen);
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
    if (m_selected)
    {
      Trace *trace = Engine::Get()->GetTrace();
      (*trace)[0] << "Currently selected console is being deleted...";
      trace->SelectConsole(NULL);
    }
    #ifdef _WIN32 //The following only exists in a Windows build
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
  
  /*****************************************/
  /*!
  \brief
  Returns if the console is selected.
  */
  /*****************************************/
  bool Console::IsSelected()
  {
    return m_selected;
  }
}
