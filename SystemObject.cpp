/**
 * System Object Base Class.
 *
 * @author  무아
 * @date    2003-03-10 03:40am
 * @version 1.0
 *
 * @file    SystemObject.cpp
 */

#include "Core.h"

#pragma comment( lib, "Src/Lib/Grape.lib" )
#pragma comment( lib, "Src/Lib/Melon.lib" )
#pragma comment( lib, "Src/Lib/Lemon.lib" )


HWND        cSystemObject::m_hWnd       = NULL;
cInput*     cSystemObject::m_pInput     = NULL;
cGraphics*  cSystemObject::m_pGraphic   = NULL;
cMedia*     cSystemObject::m_pMedia     = NULL;
