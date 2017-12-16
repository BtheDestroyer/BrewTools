/******************************************************************************/
/*!
\file distillery.cpp
\author Bryce Dixon
\par email: realbthedestroyer\@gmail.com
\par BrewTools
\par Created: v1.0
\par Updated: v1.0
\date 12/11/2017

\brief
Core of the engine. Holds pointers to all other major systems.
*/
/******************************************************************************/
#include "brewtools/distillery.h" // Engine class
#include "brewtools/trace.h"      // Trace class
#include "brewtools/graphics.h"   // Graphics class

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
  Default constructor. Called by Get.
  */
  /*****************************************/
  Engine::Engine() {}
  
  /*****************************************/
  /*!
  \brief
  Destructor. Called on Engine shutdown.
  */
  /*****************************************/
  Engine::~Engine()
  {
    for (auto it : systems)
      delete it.second;
  }
  
  /*****************************************/
  /*!
  \brief
  Used for obtaining the Engine singleton pointer.
  
  \return
  Engine singleton pointer if successful, NULL otherwise.
  */
  /*****************************************/
  Engine *Engine::Get()
  {
    static Engine *engine = new Engine;
    return engine;
  }
  
  /*****************************************/
  /*!
  \brief
  Initializes all systems.
  */
  /*****************************************/
  void Engine::InitializeAll()
  {
    GetSystem<Trace>();
    GetSystem<Graphics>();
  }
  
  /*****************************************/
  /*!
  \brief
  Safely shuts down the Engine.
  */
  /*****************************************/
  void Engine::Shutdown()
  {
    Update();
    delete this;
  }
  
  /*****************************************/
  /*!
  \brief
  Updates all living systems.
  */
  /*****************************************/
  void Engine::Update()
  {
    for (auto it : systems)
      it.second->Update();
  }
}
