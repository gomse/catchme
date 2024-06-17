/**
 * Media Library Melon.
 *
 * @author  무아
 * @date    2003-11-06 06:34pm
 * @version 0.1
 *
 * @file    Melon.h
 */

#ifndef __Melon_Library_Header__
#define __Melon_Library_Header__


class cMp3Player
{
public:
    enum
    {
        STOPED = 0,
        PAUSED,
        PLAYING
    }; //enum

public:
    virtual bool    Play() = 0;
    virtual void    Stop() = 0;
    virtual void    Pause() = 0;
    virtual void    Rewind() = 0;
    virtual bool    IsCompleted() = 0;
    virtual void    SetVolume( long lVolume ) = 0;
    virtual int     GetState();
    virtual void    Release() = 0;
}; //class cMp3Player


class cWavePlayer
{
public:
    virtual bool    Play( bool bLoop ) = 0;
    virtual void    Stop() = 0;
    virtual void    SetVolume( long lVolume ) = 0;
    virtual bool    IsPlaying() = 0;
    virtual void    Release() = 0;
}; //class cWavePlayer


class cMedia
{
public:
    virtual cMp3Player*  LoadMp3( const char* szFileName ) = 0;
    virtual cWavePlayer* LoadWave( const char* szFileName, int nPoint = 0 ) = 0;

    virtual void         Release() = 0;
}; //class cMedia


#ifndef BUILDING_DLL
    #define MELON_API extern "C" __declspec( dllimport )
#else
    #define MELON_API extern "C" __declspec( dllexport )
#endif //#ifndef BUILDING_DLL


namespace Melon
{
    MELON_API cMedia* InitMedia( HWND hWnd );
}; //namespace Lemon


#endif //#ifndef __Melon_Library_Header__
