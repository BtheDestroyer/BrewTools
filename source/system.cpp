/******************************************************************************/
/*!
\file system.cpp
\author Bryce Dixon
\par email: realbthedestroyer\@gmail.com
\par BrewTools
\date 12/11/2017
\par Created: v1.0
\par Updated: v1.0

\brief
Base class for systems.
*/
/******************************************************************************/
#include "brewtools/system.h"

/*****************************************/
/*!
\brief
Brewtools namespace.
*/
/*****************************************/
namespace BrewTools
{
  static SysID systemidcount; //!< Total number of SysIDs.
  
    /*****************************************/
    /*!
    \brief
    Destructor
    */
    /*****************************************/
    ProtoSystem::~ProtoSystem() {}
    
    /*****************************************/
    /*!
    \brief
    Updates the system
    */
    /*****************************************/
    void ProtoSystem::Update() {}
    
    /*****************************************/
    /*!
    \brief
    Gets the number of SysIDs
    */
    /*****************************************/
    SysID& ProtoSystem::GetSysIDCount()
    {
      return systemidcount;
    }
}
