/******************************************************************************/
/*!
\file graphics.h
\author Bryce Dixon
\par email: realbthedestroyer\@gmail.com
\par BrewTools
\date 12/11/2017
\par Created: v1.0
\par Updated: v1.0

\brief
Graphics management and implementation.
*/
/******************************************************************************/

#ifndef __BT_GRAPHICS_H_
#define __BT_GRAPHICS_H_
#include "brewtools/window.h"
#include <vector>

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
  Graphics system class.
  Used for creating, managing, and updating Windows
  */
  /*****************************************/
  class Graphics
  {
  public:
    /*****************************************/
    /*!
    \brief
    Default Constructor
    */
    /*****************************************/
    Graphics();
    
    /*****************************************/
    /*!
    \brief
    Destructor
    */
    /*****************************************/
    ~Graphics();

    /*****************************************/
    /*!
    \brief
    Updates graphics by flushing and swapping the buffers.
    */
    /*****************************************/
    void Update();

  private:
    std::vector<Window *> m_windows;
  };
}

#endif
