/******************************************************************************/
/*!
\file STUB.h
\author Bryce Dixon
\par email: realbthedestroyer\@gmail.com
\par BrewTools
\date 12/11/2017

\brief
Trace system
*/
/******************************************************************************/

#ifndef __BT_TRACE_H_
#define __BT_TRACE_H_

#include <string>  //!< std::string
#include <fstream> //!< std::ofstream

#ifdef _3DS //The following only exists in a 3DS build
#include <3ds.h>
#endif //_3DS

namespace BrewTools
{
  class Console; //<! Forward declaration

  /*****************************************/
  /*!
  \brief
  Trace system class.
  Used for printing to a console and file.
  */
  /*****************************************/
  class Trace
  {
  public:
    /*****************************************/
    /*!
    \brief
    Default Constructor.
    */
    /*****************************************/
    Trace();
    
    /*****************************************/
    /*!
    \brief
    Conversion Constructor.
    
    \param path
    Path of file to trace to.
    */
    /*****************************************/
    Trace(std::string path);
    
    /*****************************************/
    /*!
    \brief
    Destructor
    */
    /*****************************************/
    ~Trace();
    
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
    bool OpenFile(std::string path);
    
    /*****************************************/
    /*!
    \brief
    Determines if there is a file being traced to.
    
    \return
    true if a file is being traced to, false otherwise.
    */
    /*****************************************/
    bool IsFileOpen() const;
    
    /*****************************************/
    /*!
    \brief
    Outputs a string to the console and file (if one is open).
    
    \return
    Reference to the original Trace.
    */
    /*****************************************/
    Trace &operator<<(std::string output);
    
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
    Trace &operator[](const unsigned level);
    
    /*****************************************/
    /*!
    \brief
    Updates Trace.
    */
    /*****************************************/
    void Update();

    /*****************************************/
    /*!
    \brief
    Selects a console to output to.
    */
    /*****************************************/
    void SelectConsole(Console *console);

  private:
    /*****************************************/
    /*!
    \brief
    Helper function for closing the current file.
    */
    /*****************************************/
    void CloseFile();
    
    std::string m_path; //!< Path of file
    std::ofstream m_os; //!< File out stream
    unsigned   m_level; //!< Current level of trace
    Console *m_console; //!< Currently selected console
  };
}

#endif
