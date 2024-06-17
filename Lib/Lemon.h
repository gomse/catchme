/**
 * Input Library Lemon.
 *
 * @author  무아
 * @date    2003-11-04 11:27pm
 * @version 1.0
 *
 * @file    Lemon.h
 */

#ifndef __Lemon_Library_Header__
#define __Lemon_Library_Header__


class cInput
{
public:
    enum
    {
        NONE = 0,
        RELEASE,
        PRESS,
        REPEAT,
    }; //enum

public:
    virtual void    Update() = 0;
    virtual void    SetState( BYTE nKeyID, BYTE nState ) = 0;
    virtual BYTE    GetState( BYTE nKeyID ) = 0;
    virtual void    Release() = 0;
}; //class cInput


#ifndef BUILDING_DLL
    #define LEMON_API extern "C" __declspec( dllimport )
#else
    #define LEMON_API extern "C" __declspec( dllexport )
#endif //#ifndef BUILDING_DLL


namespace Lemon
{
    LEMON_API cInput* InitInput( HWND hWnd );
}; //namespace Lemon


#endif //#ifndef __Lemon_Library_Header__
