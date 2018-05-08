/******************************************************************************/
/*!
\file console.cpp
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
#define _CRT_SECURE_NO_WARNINGS
#include "brewtools/console.h" // Console class
#include "brewtools/distillery.h" // Engine class
#include "brewtools/trace.h" // Trace class
#ifdef _WIN32
#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif
#define _WIN32_WINNT 0x0603
#include <windows.h>
#endif

/*****************************************/
/*!
\brief
Brewtools namespace.
*/
/*****************************************/
namespace BrewTools
{
  #ifdef _WIN32 //The following only exists in a Windows build
  static unsigned m_consolecount; //!< Number of Windows consoles currently open
  #endif //_WIN32
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
  Console::Console(std::string name, Window::Screen screen) :
  Window(name, screen)
  {
    #ifdef _3DS //The following only exists in a 3DS build
    consoleInit((screen == TOP) ? GFX_TOP : GFX_BOTTOM, &m_printconsole);
    #elif _WIN32 //The following only exists in a Windows build
    if (!GetConsoleWindow())
    {
      AllocConsole();
      AttachConsole(GetCurrentProcessId());
      freopen("CON", "w", stdout);
      m_consolecount = 1;
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
      Trace *trace = Engine::Get()->GetSystemIfExists<Trace>();
      (*trace)[0] << "Currently selected console is being deleted...";
      trace->SelectConsole(nullptr);
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
  
  /*****************************************/
  /*!
  \brief
  Gets the 3DS print console
  */
  /*****************************************/
  #ifdef _3DS //The following only exists in a 3DS build
  PrintConsole *Console::GetPrintConsole()
  #else
  void *Console::GetPrintConsole()
  #endif
  {
  #ifdef _3DS //The following only exists in a 3DS build
    return &m_printconsole;
  #else
    Trace *trace = Engine::Get()->GetSystemIfExists<Trace>();
    if (trace)
    {
      (*trace)[5] << "GFXWindow::GetTarget() only works on 3DS";
      (*trace)[1] << "WARNING: *SEVERE* problems are caused "
                     "if your code depends on GFXWindow::GetTarget().";
    }
    return nullptr;
  #endif
  }
  
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
