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
#include "brewtools/trace.h" //!< Trace class

#ifdef _3DS //The following only exists in a 3DS build
#include <3ds.h>
#endif //_3DS

namespace BrewTools
{
  /*****************************************/
  /*!
  \brief
  Default constructor. Called by Get.
  */
  /*****************************************/
  Engine::Engine()
  {
    m_trace = NULL;
    #ifdef _3DS //The following only exists in a 3DS build
    gfxInitDefault(); // TODO: Replace with actual graphics implementation
    consoleInit(GFX_TOP, NULL);
    #endif //_3DS
  }
  
  /*****************************************/
  /*!
  \brief
  Destructor. Called on Engine shutdown.
  */
  /*****************************************/
  Engine::~Engine()
  {
    delete m_trace;
    #ifdef _3DS //The following only exists in a 3DS build
    gfxExit(); // TODO: Replace with actual graphics implementation
    #endif //_3DS
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
  Safely shuts down the Engine.
  */
  /*****************************************/
  void Engine::Shutdown()
  {
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
  Updates all living systems.
  */
  /*****************************************/
  void Engine::Update()
  {
    if (m_trace)
      m_trace->Update();
    #ifdef _3DS //The following only exists in a 3DS build
    gfxFlushBuffers();
    gfxSwapBuffers();
    gspWaitForVBlank();
    #endif //_3DS
  }
}
