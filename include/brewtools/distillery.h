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
#include "brewtools/trace.h"
#include "brewtools/graphics.h"

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
    Engine singleton pointer if successful, NULL otherwise.
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
    Returns pointer to the Trace system.
    
    \return
    Pointer to the Trace system if successful, NULL otherwise.
    */
    /*****************************************/
    Trace *GetTrace();
    
    /*****************************************/
    /*!
    \brief
    Returns pointer to the Graphics system.
    
    \return
    Pointer to the Graphics system if successful, NULL otherwise.
    */
    /*****************************************/
    Graphics *GetGraphics();
    
    /*****************************************/
    /*!
    \brief
    Updates all living systems.
    */
    /*****************************************/
    void Update();
    
  private:
    Trace    *m_trace;    //!< Pointer to the Trace system
    Graphics *m_graphics; //!< Pointer to the Graphics system
  };
}

#endif
