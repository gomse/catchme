/**
 * 로고 화면.
 *
 * @author  무아
 * @date    2004-03-10 04:29am
 * @version 1.0
 *
 * @file    Logo.cpp
 */

#include "Core.h"
#include "Scene.h"
#include "ResLoader.h"


class cLogo :   public cScene
{
public:
    cLogo();

    BOOL        Init();
    cScene*     Update();
    void        Render();
    void        Release();

private:
    enum
    {
        TEAMDTR = 0,
        OVERLAP = 1,
        DOTME   = 2,
        FADEOUT = 3,
    }; //enum

    cTexture*   m_pDtrLogo;     ///< 도트락 로고.
    cTexture*   m_pDotMeLogo;   ///< 닷미 로고.
    BYTE        m_nState;       ///< 현재 상태.
    int         m_nAlpha;       ///< 알파값 변수.
    DWORD       m_dwShowTime;   ///< 로고를 보여주는 시간.
}; //class cLogo


/**
 *
 */
cScene* cSceneFactory::Logo()
{
    return new cLogo;
}

/**
 * 생성자.
 */
cLogo::cLogo()
:   m_pDtrLogo  ( NULL ),
    m_pDotMeLogo( NULL ),
    m_nState    ( TEAMDTR ),
    m_nAlpha    ( 0 ),
    m_dwShowTime( 0 )
{
}

/**
 * 로고 화면을 초기화 한다.
 */
BOOL cLogo::Init()
{
    cResLoader ResLoader;

    if( !ResLoader.Init( "package/logo.list" ) )
    {
        g_pLogger->Write( FALSE, "Loaded... \"package/logo.list\" fail.\n" );

        return FALSE;
    } //if

    m_pDtrLogo      = ResLoader.LoadImage( "teamdtr" );
    m_pDotMeLogo    = ResLoader.LoadImage( "dotme" );
    m_dwShowTime    = timeGetTime();

    return TRUE;
}

/**
 * 객체를 소멸시킨다.
 */
void cLogo::Release()
{
    SAFE_RELEASE( m_pDotMeLogo );
    SAFE_RELEASE( m_pDtrLogo );

    delete this;
}

/**
 * 로고 화면을 업데이트 한다.
 */
cScene* cLogo::Update()
{
    BOOL bSkip = (BOOL)( m_pInput->GetState( MOUSE_LBUTTON ) == cInput::PRESS );

    switch( m_nState )
    {
    case TEAMDTR:
        if( timeGetTime() - m_dwShowTime >= 1800 || bSkip )
        {
            m_nState = OVERLAP;
        } //if
        break;

    case OVERLAP:
        if( ( m_nAlpha += 5 ) >= 100 )
        {
            m_nAlpha        = 100;
            m_dwShowTime    = timeGetTime();
            m_nState        = DOTME;
        } //if
        break;

    case DOTME:
        if( timeGetTime() - m_dwShowTime >= 1500 || bSkip )
        {
            m_nAlpha = 100;
            m_nState = FADEOUT;
        } //if
        break;

    case FADEOUT:
        if( ( m_nAlpha -= 5 ) <= 0 )
        {
            return cSceneFactory::Game();
        } //if
        break;
    } //switch

    return this;
}

/**
 * 로고 화면을 그린다.
 */
void cLogo::Render()
{
    switch( m_nState )
    {
    case TEAMDTR:
        m_pDtrLogo->Draw( 0, 0, 0xFFFFFFFF, NULL );
        break;

    case OVERLAP:
        {
            DWORD dwColor    = 0x00FFFFFF;
            dwColor         |= ( m_nAlpha * 255 / 100 ) << 24;

            m_pDtrLogo->Draw( 0, 0, 0xFFFFFFFF );
            m_pDotMeLogo->Draw( 0, 0, dwColor );
        }
        break;

    case DOTME:
        m_pDotMeLogo->Draw( 0, 0 );
        break;

    case FADEOUT:
        {
            DWORD dwColor    = 0x00FFFFFF;
            dwColor         |= ( m_nAlpha * 255 / 100 ) << 24;

            m_pGraphic->Clear( 0xFF000000 );
            m_pDotMeLogo->Draw( 0, 0, dwColor );
        }
        break;
    } //switch
}
