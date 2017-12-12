/******************************************************************************/
/*!
\file distillery.h
\author Bryce Dixon
\par email: realbthedestroyer\@gmail.com
\par BrewTools
\date 12/11/2017

\brief
Core of the engine. Holds pointers to all other major systems.
*/
/******************************************************************************/
#include "brewtools/distillery.h" //!< Engine class
#include "brewtools/trace.h"      //!< Trace class
#include "brewtools/graphics.h"   //!< Graphics class

namespace BrewTools
{
  /*****************************************/
  /*!
  \brief
  Default constructor. Called by Get.
  */
  /*****************************************/
  Engine::Engine() : m_trace(NULL), m_graphics(NULL) {}
  
  /*****************************************/
  /*!
  \brief
  Destructor. Called on Engine shutdown.
  */
  /*****************************************/
  Engine::~Engine()
  {
    if (m_trace)
    delete m_trace;
    if (m_graphics)
    delete m_graphics;
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
    GetTrace();
    GetGraphics();
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
  Returns pointer to the Trace system.
  
  \return
  Pointer to the Trace system if successful, NULL otherwise.
  */
  /*****************************************/
  Trace *Engine::GetTrace()
  {
    if (!m_trace)
      m_trace = new Trace;
    return m_trace;
  }
  
  /*****************************************/
  /*!
  \brief
  Returns pointer to the Graphics system.
  
  \return
  Pointer to the Graphics system if successful, NULL otherwise.
  */
  /*****************************************/
  Graphics *Engine::GetGraphics()
  {
    if (!m_graphics)
    m_graphics = new Graphics;
    return m_graphics;
  }
  
  /*****************************************/
  /*!
  \brief
  Updates all living systems.
  */
  /*****************************************/
  void Engine::Update()
  {
    if (m_trace)
    m_trace->Update();
    if (m_graphics)
    m_graphics->Update();
  }
}
