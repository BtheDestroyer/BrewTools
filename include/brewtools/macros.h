/******************************************************************************/
/*!
\file macros.h
\author Bryce Dixon
\par email: realbthedestroyer\@gmail.com
\par BrewTools
\date 12/11/2017

\brief
Macros to make code more readable.
*/
/******************************************************************************/

#ifndef __BT_MACROS_H_
#define __BT_MACROS_H_

/*****************************************/
/*!
\brief
Safely deletes and sets a pointer to NULL.
*/
/*****************************************/
#define SAFE_DELETE(x) {delete x; x = NULL;}

/*****************************************/
/*!
\brief
Prevents warnings from unreferenced parameters.
Usually used for ensuring functions work across platforms.
*/
/*****************************************/
#define UNREFERENCED_PARAMETER(x) if (x) {}

#endif
