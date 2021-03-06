/******************************************************************************/
/*!
\file macros.h
\author Bryce Dixon
\par email: realbthedestroyer\@gmail.com
\par BrewTools
\date 12/11/2017
\par Created: v1.0
\par Updated: v1.0

\brief
Macros to make code more readable.
*/
/******************************************************************************/

#ifndef __BT_MACROS_H_
#define __BT_MACROS_H_

/*****************************************/
/*!
\brief
Safely deletes and sets a pointer to nullptr.
*/
/*****************************************/
#define SAFE_DELETE(x) {if (x) {delete (x); (x) = nullptr;}}

/*****************************************/
/*!
\brief
Safely deletes and sets a pointer to an array to nullptr.
*/
/*****************************************/
#define SAFE_DELETE_ARR(x) {if (x) {delete[] (x); (x) = nullptr;}}

#endif
