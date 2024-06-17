/**
 * 게임 애플리케이션 클래스.
 *
 * @author  무아
 * @date    2004-03-10 04:10am
 * @version 0.9
 *
 * @file    GameApp.cpp
 */

#include "Core.h"
#include "GameApp.h"
#include "Cursor.h"
#include "Scene.h"


/**
 * 생성자.
 */
cGameApp::cGameApp()
:   m_pCursor       ( NULL ),
    m_pScene        ( NULL ),
    m_dwWaitFrame   ( 0 )
{
    ASSERT( NULL == m_pInput );
    ASSERT( NULL == m_pGraphic );
    ASSERT( NULL == m_pMedia );

    ShowCursor( FALSE );
}

/**
 * 소멸자.
 */
cGameApp::~cGameApp()
{
    ShowCursor( TRUE );

    ASSERT( NULL == m_pInput );
    ASSERT( NULL == m_pGraphic );
    ASSERT( NULL == m_pMedia );
}

/**
 * 게임 애플리케이션 초기화.
 */
BOOL cGameApp::OnInit( HWND hWnd )
{
    // cSystemObject의 변수들을 초기화 한다.
    m_hWnd      = hWnd;
    m_pInput    = Lemon::InitInput( m_hWnd );
    m_pMedia    = Melon::InitMedia( m_hWnd );

    m_pGraphic  = Grape::InitGraphics(
        m_hWnd,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        false
        );

    // 커서를 초기화 한다.
    m_pCursor = new cCursor;

    if( !m_pCursor->Init() )
    {
        g_pLogger->Write( FALSE, "Init cursor failed.\n" );

        return FALSE;
    } //if

    // 장면을 초기화 한다.
    m_pScene = cSceneFactory::Logo();

    if( !m_pScene->Init() )
    {
        g_pLogger->Write( FALSE, "Init scene failed.\n" );

        return FALSE;
    } //if

    return TRUE;
}

/**
 * 게임 애플리케이션 종료.
 */
void cGameApp::OnDestroy()
{
    SAFE_RELEASE( m_pScene );
    SAFE_DELETE( m_pCursor );

    SAFE_RELEASE( m_pMedia );
    SAFE_RELEASE( m_pGraphic );
    SAFE_RELEASE( m_pInput );
}

/**
 *
 */
BOOL cGameApp::OnIdle()
{
    m_pInput->Update();

    if( TestDevice() )
    {
        m_pCursor->Update();

        if( !UpdateScene() )
        {
            return FALSE;
        } //if

        RenderScene();
        WaitFrame();
    } //if

    return TRUE;
}

/**
 *
 */
BOOL cGameApp::UpdateScene()
{
    cScene* pScene = m_pScene->Update();

    if( NULL == pScene )
    {
        return false;
    }
    else if( m_pScene != pScene )
    {
        m_pScene->Release();
        m_pScene = pScene;

        if( !m_pScene->Init() )
        {
            return false;
        } //if
    } //if..else if

    return TRUE;
}

/**
 *
 */
void cGameApp::RenderScene()
{
    if( m_pGraphic->BeginScene() )
    {
        m_pScene->Render();
        m_pCursor->Draw();

        m_pGraphic->EndScene();
        m_pGraphic->SwapBuffer();
    } //if
}

/**
 *
 */
BOOL cGameApp::TestDevice()
{
    int nErr = m_pGraphic->TestDevice();

    switch( nErr )
    {
    case cGraphics::DEVICE_LOST:
        OnLostDevice();
        return FALSE;

    case cGraphics::DEVICE_NOT_RESET:
        OnResetDevice();
        return FALSE;
    } //switch

    return TRUE;
}

/**
 *
 */
void cGameApp::OnLostDevice()
{
    m_pGraphic->OnLostDevice();
    m_pScene->OnLostDevice();
}

/**
 *
 */
void cGameApp::OnResetDevice()
{
    m_pGraphic->OnResetDevice();
    m_pScene->OnResetDevice();
}

/**
 *
 */
void cGameApp::WaitFrame()
{
    while( timeGetTime() - m_dwWaitFrame < WAITFRAME )
    {
        Sleep( 1 );
    } //while

    m_dwWaitFrame = timeGetTime();
}
