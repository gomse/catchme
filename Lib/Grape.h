/**
 * Graphics Library Grape.
 *
 * @author  무아
 * @date    2003-10-28 07:30am
 * @version 0.6
 *
 * @file    Grape.h
 */

#ifndef __Grape_Library_Header__
#define __Grape_Library_Header__


/**
 * Texture의 Render State.
 */
struct sRenderState
{
    enum
    {
        INIT     = 0,
        SCALE    = 1,
        SCALE_W  = 2,
        SCALE_H  = 3,
        ROTATE   = 4,
        WIDTH    = 5,
        HEIGHT   = 6,
    }; //enum

    float   fScaleWidth;
    float   fScaleHeight;
    float   fAngle;
    int     nWidth;
    int     nHeight;
}; //struct sRenderState


/**
 * 2D Sprite.
 * cTexture로부터 생성된다.
 */
class cSprite
{
public:
    virtual void    Draw( int nX, int nY, DWORD dwColor ) = 0;

    virtual int     GetWidth() = 0;
    virtual int     GetHeight() = 0;

    virtual void    Release() = 0;
}; //class cSprite


/**
 * 2D Texture.
 */
class cTexture
{
public:
    virtual void    Draw( int nX, int nY, DWORD dwColor=0xFFFFFFFF, const RECT* pRect=NULL, bool bRevision=false ) = 0;

    virtual void    SetRenderState( DWORD dwState, float fValue ) = 0;
    virtual void    SetRenderState( sRenderState RenderState ) = 0;
    virtual void    GetRenderState( sRenderState* pRenderState ) = 0;

    virtual int     GetWidth() = 0;
    virtual int     GetHeight() = 0;

    virtual bool    OnLostDevice() = 0;
    virtual bool    OnResetDevice() = 0;

    virtual int     AddRef() = 0;
    virtual void    Release() = 0;

    virtual cSprite*    CreateSprite( RECT Rect ) = 0;
}; //class cTexture


/**
 * Font.
 * 문자열의 속성 설정 및 출력한다.
 */
class cFont
{
public:
    enum
    {
        BOLD        = 1,
        ITALIC      = 2,
        UNDERLINE   = 4,
        STRIKEOUT   = 8,
    }; //enum - Style

    enum
    {
        NONE    = 0,
        RIGHT   = 1,
        BOTTOM  = 2,
        CENTER  = 4,
        VCENTER = 8,
    }; //enum - Align

public:
    virtual int     DrawText( int nX, int nY, const char* szText, DWORD dwColor ) = 0;
    virtual int     DrawText( RECT rcText, const char* szText, DWORD dwAlign, DWORD dwColor ) = 0;

    virtual RECT    GetRect( const char* strText ) = 0;
    virtual bool    SetStyle( DWORD dwStyle, bool bEnable ) = 0;

    virtual bool    OnLostDevice() = 0;
    virtual bool    OnResetDevice() = 0;

    virtual void    Release() = 0;
}; //class cFont


/**
 * RenderBuffer
 */
class cRenderBuffer
{
public:
    virtual bool    BeginScene() = 0;
    virtual void    EndScene() = 0;

    virtual void    Clear( DWORD dwColor ) = 0;
    virtual void    Draw( int nX, int nY, DWORD dwColor=0xFFFFFFFF, const RECT* pRect=NULL, bool bRevision=false ) = 0;

    virtual void    SetRenderState( DWORD dwState, float fValue ) = 0;
    virtual void    SetRenderState( sRenderState RenderState ) = 0;
    virtual void    GetRenderState( sRenderState* pRenderState ) = 0;

    virtual int     GetWidth() = 0;
    virtual int     GetHeight() = 0;

    virtual bool    OnLostDevice() = 0;
    virtual bool    OnResetDevice() = 0;

    virtual int     AddRef() = 0;
    virtual void    Release() = 0;
}; //class cRenderBuffer


/**
 * Graphics
 */
class cGraphics
{
public:
    enum
    {
        OK = 0,
        DEVICE_LOST = -1,
        DEVICE_NOT_RESET = -2
    }; //enum

public:
    virtual bool    BeginScene() = 0;
    virtual void    EndScene() = 0;

    virtual void    Clear( DWORD dwColor ) = 0;
    virtual bool    SwapBuffer() = 0;

    virtual void    Fade( DWORD dwColor ) = 0;
    virtual void    RenderFade() = 0;

    virtual int     TestDevice() = 0;
    virtual bool    OnLostDevice() = 0;
    virtual bool    OnResetDevice() = 0;

    virtual void    Release() = 0;

    virtual cRenderBuffer*  CreateRenderBuffer( int nWidth, int nHeight ) = 0;
    virtual cTexture*       CreateTexture( const DWORD* pData, int nWidth, int nHeight ) = 0;
    virtual cFont*          CreateFont( const char* szFaceName, int nWidth ) = 0;
}; //class cGraphics


#ifndef BUILDING_DLL
    #define GRAPE_API extern "C" __declspec( dllimport )
#else
    #define GRAPE_API extern "C" __declspec( dllexport )
#endif //#ifndef BUILDING_DLL


namespace Grape
{
    GRAPE_API cGraphics* InitGraphics(
        HWND    hWnd,
        int     nWidth,
        int     nHeight,
        bool    bFullScreen
        );
}; //namespace Grape


#endif //#ifndef __Grape_Library_Header__
