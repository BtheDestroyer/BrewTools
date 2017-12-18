/******************************************************************************/
/*!
\file system.h
\author Bryce Dixon
\par email: realbthedestroyer\@gmail.com
\par BrewTools
\date 12/15/2017
\par Created: v1.0
\par Updated: v1.0

\brief
Base class for systems.
*/
/******************************************************************************/

#ifndef __BT_SYSTEM_H_
#define __BT_SYSTEM_H_

/*****************************************/
/*!
\brief
Brewtools namespace.
*/
/*****************************************/
namespace BrewTools
{
  typedef unsigned SysID; //!< ID of a given system
  
  /*****************************************/
  /*!
  \brief
  ProtoSystem base class.
  Basically used as a templateless System
  */
  /*****************************************/
  class ProtoSystem
  {
  public:
    /*****************************************/
    /*!
    \brief
    Destructor
    */
    /*****************************************/
    virtual ~ProtoSystem();
    
    /*****************************************/
    /*!
    \brief
    Updates the system
    */
    /*****************************************/
    virtual void Update() = 0;
    
    /*****************************************/
    /*!
    \brief
    Gets the number of SysIDs
    */
    /*****************************************/
    static SysID& GetSysIDCount();
  };
  
  /*****************************************/
  /*!
  \brief
  System base class.
  */
  /*****************************************/
  template<typename T>
  class System : public ProtoSystem
  {
  public:
    /*****************************************/
    /*!
    \brief
    Default constructor.
    */
    /*****************************************/
    System() {}
    
    /*****************************************/
    /*!
    \brief
    Destructor
    */
    /*****************************************/
    ~System() {}
    
    /*****************************************/
    /*!
    \brief
    Gets the ID of the system.
    
    \return
    SysID of the system.
    */
    /*****************************************/
    SysID GetID() const
    {
      return id;
    }
    
    static const SysID id; //!< ID of the system
  };
  
  /*****************************************/
  /*!
  \brief
  Creates a unique id for each derived system.
  
  \tparam T
  System to set the id of.
  */
  /*****************************************/
  template<typename T>
  const SysID System<T>::id = ++ProtoSystem::GetSysIDCount();
}

#endif
