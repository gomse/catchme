/**
 * Script.
 *
 * @author  무아
 * @date    2003-11-10 11:56pm
 * @version 1.0
 *
 * @file    Orange.h
 */

#ifndef __Orange_Library_Header__
#define __Orange_Library_Header__


/**
 * Script Class.
 */
class cScript
{
public:
    typedef bool        (*CMD_FUNC)( const char* szArg );

public:
    virtual bool        SetScript( const char* szName ) = 0;

    virtual bool        Step() = 0;

    virtual void        AddFunc( const char* szName, CMD_FUNC Func ) = 0;

    virtual const char* GetVariable( const char* szName ) = 0;
    virtual void        SetVariable( const char* szName, const char* szValue ) = 0;
    virtual void        SetVariable( const char* szName, int nValue ) = 0;

    virtual void        Release() = 0;
}; //class cScript


#ifndef BUILDING_DLL
    #define ORANGE_API extern "C" __declspec( dllimport )
#else
    #define ORANGE_API extern "C" __declspec( dllexport )
#endif //#ifndef BUILDING_DLL


namespace Orange
{
    ORANGE_API cScript* LoadScript( const char* szPackage );
}; //namespace Orange


#endif //#ifndef __Orange_Library_Header__
