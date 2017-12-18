/******************************************************************************/
/*!
\file time.cpp
\author Bryce Dixon
\par email: realbthedestroyer\@gmail.com
\par BrewTools
\date 12/16/2017
\par Created: v1.0
\par Updated: v1.0

\brief
Time management system.
*/
/******************************************************************************/
#include "brewtools/time.h"
#include "brewtools/distillery.h"

#ifdef _3DS //The following only exists in a 3DS build
#include <3ds.h>
#elif _WIN32 //The following only exists in a Windows build
#endif

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
  Default Constructor
  */
  /*****************************************/
  Time::Time()
  {
    start_time = Current();
  }
  
  /*****************************************/
  /*!
  \brief
  Sleeps for a given amount of time in seconds.
  
  \param time
  Time in ms to sleep for.
  */
  /*****************************************/
  void Time::Sleep(uint64_t time)
  {
    uint64_t start = Current();
    uint64_t current = start;
    uint64_t end = start + time;
    Engine::Get()->Update(); // TODO: Remove. This is just for testing.
    while (current < end)
    {
      current = Current();
    }
  }
  
  /*****************************************/
  /*!
  \brief
  Gets the current time.
  
  \return
  Current time in ms since January 1st 1970
  */
  /*****************************************/
  uint64_t Time::Current()
  {
    #ifdef _3DS //The following only exists in a 3DS build
    return osGetTime();
    #elif _WIN32 //The following only exists in a Windows build
    return std::chrono::duration_cast< std::chrono::milliseconds >
    (std::chrono::system_clock::now().time_since_epoch()).count();
    #endif
  }
  
  /*****************************************/
  /*!
  \brief
  Gets the start time of the system.
  
  \return
  Time that the Time system was started in ms since January 1st 1970
  */
  /*****************************************/
  uint64_t Time::Start()
  {
    return start_time;
  }
}
