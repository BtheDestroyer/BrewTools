/******************************************************************************/
/*!
\file time.h
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

#ifndef __BT_TIME_H_
#define __BT_TIME_H_

#include "brewtools/system.h"
#include <cstdint>
#ifdef _WIN32 //The following only exists in a Windows build
#include <chrono>
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
  Time management system.
  */
  /*****************************************/
  class Time : public System<Time>
  {
  public:
    /*****************************************/
    /*!
    \brief
    Default Constructor
    */
    /*****************************************/
    Time();
    
    /*****************************************/
    /*!
    \brief
    Sleeps for a given amount of time in seconds.
    
    \param time
    Time in ms to sleep for.
    */
    /*****************************************/
    static void Sleep(uint64_t time);
    
    /*****************************************/
    /*!
    \brief
    Gets the current time.
    
    \return
    Current time in ms since January 1st 1970
    */
    /*****************************************/
    static uint64_t Current();
    
    /*****************************************/
    /*!
    \brief
    Gets the start time of the system.
    
    \return
    Time that the Time system was started in ms since January 1st 1970
    */
    /*****************************************/
    uint64_t Start();
    
    /*****************************************/
    /*!
    \brief
    Gets the last time the system was updated.
    
    \return
    Time that the Time system was started in ms since January 1st 1970
    */
    /*****************************************/
    uint64_t LastUpdate();
    
    /*****************************************/
    /*!
    \brief
    Updates the system
    */
    /*****************************************/
    void Update() {}
    
  private:
    uint64_t start_time; //!< Time that the Time system was started in ms
    uint64_t last_update; //!< Time of last update in ms
  };
}

#endif
