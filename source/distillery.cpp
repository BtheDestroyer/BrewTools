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
#include "brewtools/time.h"   // Time class

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
  Engine singleton pointer if successful, nullptr otherwise.
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
    GetSystem<Time>();
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
  bool Engine::Update()
  {
    BrewTools::Trace *trace = GetSystemIfExists<BrewTools::Trace>();
    if (trace)
      (*trace)[5] << "Updating the engine...";
    for (auto it : systems)
      it.second->Update();
    if (trace)
      (*trace)[5] << "Engine updated!";
    return true;
  }
}
