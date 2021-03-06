/******************************************************************************/
/*!
\file brewtools.h
\author Bryce Dixon
\par email: realbthedestroyer\@gmail.com
\par BrewTools
\date 12/11/2017
\par Created: v1.0
\par Updated: v1.0

\brief
Main BrewTools header that includes all other BrewTools Headers.
*/
/******************************************************************************/

#ifndef __BT_BREWTOOLS_H_
#define __BT_BREWTOOLS_H_

#include "brewtools/distillery.h" // Engine singleton class

#include "brewtools/system.h" // System and ProtoSystem base classes
#include "brewtools/trace.h" // Trace system class
#include "brewtools/graphics.h" // Graphics system class

#include "brewtools/window.h" // Window class
#include "brewtools/console.h" // Console class
#include "brewtools/gfxwindow.h" // GFXWindow class
#include "brewtools/time.h" // Time class

#include "brewtools/macros.h" // Helpful macros

#endif
