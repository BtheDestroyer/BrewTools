/******************************************************************************/
/*!
\file distillery.h
\author Bryce Dixon
\par email: realbthedestroyer\@gmail.com
\par BrewTools
\date 12/11/2017
\par Created: v1.0
\par Updated: v1.0

\brief
Core of the engine. Holds pointers to all other major systems.
*/
/******************************************************************************/

#ifndef __BT_DISTILLERY_H_
#define __BT_DISTILLERY_H_
#include "brewtools/system.h"
#include <map>

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
  Engine singleton class.
  The Engine class holds a pointer to all major systems. 
  */
  /*****************************************/
  class Engine
  {
  private:
    std::map<SysID, ProtoSystem*> systems; //!< Map of IDs to system pointers
    
    /*****************************************/
    /*!
    \brief
    Default constructor. Called by Get.
    */
    /*****************************************/
    Engine();
    /*****************************************/
    /*!
    \brief
    Destructor. Called on Engine shutdown.
    */
    /*****************************************/
    ~Engine();
    
  public:
    /*****************************************/
    /*!
    \brief
    Used for obtaining the Engine singleton pointer.
    
    \return
    Engine singleton pointer if successful, nullptr otherwise.
    */
    /*****************************************/
    static Engine *Get();
    
    /*****************************************/
    /*!
    \brief
    Initializes all systems.
    */
    /*****************************************/
    void InitializeAll();
    
    /*****************************************/
    /*!
    \brief
    Safely shuts down the Engine.
    */
    /*****************************************/
    void Shutdown();
    
    /*****************************************/
    /*!
    \brief
    Updates all living systems.
    */
    /*****************************************/
    bool Update();
    
    /*****************************************/
    /*!
    \brief
    Gets a system from the engine.
    If the system has not yet been created, it will be created.

    \tparam T
    System to get.

    \return
    Pointer to the requested system.
    */
    /*****************************************/
    template <typename T>
    T* GetSystem()
    {
      if (systems.size() && systems.find(T::id) != systems.end())
        return (T*)(systems[T::id]);
      systems[T::id] = new T;
      return (T*)(systems[T::id]);
    }
    
    /*****************************************/
    /*!
    \brief
    Gets a system from the engine if it exists.

    \tparam T
    System to get.

    \return
    Pointer to the requested system if it exists, nullptr otherwise.
    */
    /*****************************************/
    template <typename T>
    T* GetSystemIfExists()
    {
      if (systems.size() && systems.find(T::id) != systems.end())
        return (T*)(systems[T::id]);
      return nullptr;
    }
  };
}

#endif
