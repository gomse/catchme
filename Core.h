/**
 * 게임 전반적으로 쓰이는 STL 및 매크로들.
 *
 * @author  무아
 * @date    2004-03-10 03:27am
 * @version 0.1
 *
 * @file    Core.h
 */

#pragma once
#pragma warning( disable: 4786 )

#include <windows.h>

#include <string>
#include <queue>
#include <map>

#define PROJECT_NAME    "DotME"
#define SCREEN_WIDTH    640
#define SCREEN_HEIGHT   480

#define SAFE_RELEASE( p )       { if( (p) ) { (p)->Release();   (p) = NULL; } }
#define SAFE_DELETE( p )        { if( (p) ) { delete (p);       (p) = NULL; } }
#define SAFE_DELETE_ARRAY( p )  { if( (p) ) { delete [] (p);    (p) = NULL; } }

#define ASSERT( exp )   \
    if( !(exp) )        \
    {                   \
        MessageBox( NULL, #exp, "Assertation", MB_ICONSTOP );   \
        exit( -1 );     \
    }

#include "Singleton.h"
#include "SystemObject.h"
#include "Config.h"
#include "Logger.h"

