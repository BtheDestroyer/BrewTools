/******************************************************************************/
/*!
\file trace.cpp
\author Bryce Dixon
\par email: realbthedestroyer\@gmail.com
\par BrewTools
\date 12/11/2017
\par Created: v1.0
\par Updated: v1.0

\brief
Empty shell of a file to be filled out. Not meant to be compiled anywhere.
*/
/******************************************************************************/
#include "brewtools/trace.h"   // Trace class
#include "brewtools/console.h" // Console class
#include <iostream>            // std::cout

#ifdef _3DS //The following only exists in a 3DS build
#include <3ds/console.h>      //!< 3DS's console
#endif //_3DS

#ifdef _WIN32 //The following only exists in a Windows build
#include <windows.h>
#include <stdio.h>
#endif //_WIN32

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
  Default Constructor.
  */
  /*****************************************/
  Trace::Trace() : m_path(), m_os(), m_level(0), m_console(NULL),
                   m_printing(false)
  {
    
  }
  
  /*****************************************/
  /*!
  \brief
  Conversion Constructor.
  
  \param path
  Path of file to trace to.
  */
  /*****************************************/
  Trace::Trace(std::string path) : m_path(), m_os(), m_level(0),
                                   m_console(NULL), m_printing(false)
  {
    OpenFile(path);
  }
  
  /*****************************************/
  /*!
  \brief
  Destructor
  */
  /*****************************************/
  Trace::~Trace()
  {
    CloseFile();
  }
  
  /*****************************************/
  /*!
  \brief
  Changes the current file being traced to.
  The path will only be changed if the file could be opened
  If a file is already open, it will be closed if the new file can be opened.
  
  \param path
  Path of file to trace to.
  
  \return
  true if the path was changed, false otherwise.
  */
  /*****************************************/
  bool Trace::OpenFile(std::string path)
  {
    CloseFile();
    std::ofstream new_os(path);
    if (new_os.is_open())
    {
      new_os.swap(m_os);
      m_path = path;
      return true;
    }
    else
    {
      new_os.close();
      return false;
    }
  }
  
  /*****************************************/
  /*!
  \brief
  Determines if there is a file being traced to.
  
  \return
  true if a file is being traced to, false otherwise.
  */
  /*****************************************/
  bool Trace::IsFileOpen() const
  {
    return m_os.is_open();
  }
  
  /*****************************************/
  /*!
  \brief
  Outputs a string to the console and file (if one is open).
  
  \return
  Reference to the original Trace.
  */
  /*****************************************/
  Trace &Trace::operator<<(const std::string output)
  {
    if (m_console && m_printing)
    {
      // This is split to prevent a const error with output
      std::cout << "[" << m_level << "] " << output;
      std::cout << std::endl;
    }
    
    if (IsFileOpen())
      m_os << "[" << m_level << "] " << output << std::endl;
    
    return *this;
  }
  
  /*****************************************/
  /*!
  \brief
  Determines current level of tracing.
  Currently only visual,
  but will be used to restrict excessive printing in the future.
  
  \return
  Reference to the original Trace.
  */
  /*****************************************/
  Trace &Trace::operator[](const unsigned level)
  {
    m_level = level;
    return *this;
  }
  
  /*****************************************/
  /*!
  \brief
  Helper function for closing the current file.
  */
  /*****************************************/
  void Trace::CloseFile()
  {
    if (IsFileOpen())
    {
      m_os.close();
      m_path.clear();
    }
  }
  
  /*****************************************/
  /*!
  \brief
  Updates Trace.
  */
  /*****************************************/
  void Trace::Update()
  {
    // TODO: Implement a buffer-flush system
  }
  
  
  /*****************************************/
  /*!
  \brief
  Selects a console to output to.
  */
  /*****************************************/
  void Trace::SelectConsole(Console *console)
  {
    if (m_console)
      m_console->m_selected = false;
    m_console = console;
    if (m_console)
      m_console->m_selected = true;
    #ifdef _3DS
    if (m_console)
      consoleSelect(m_console->GetPrintConsole());
    else
      consoleSelect(NULL);
    #endif
    if (!m_printing && m_console)
    {
      m_printing = true;
    }
    else if (!m_console)
    {
      m_printing = false;
    }
  }
}
