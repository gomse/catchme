/**
 * 애플리케이션 메인 소스.
 *
 * @author  무아
 * @date    2004-03-10 03:21am
 * @version 0.1
 *
 * @file    WinMain.cpp
 */

#include "Core.h"
#include "GameApp.h"

#pragma comment( lib, "winmm.lib" )


/**
 * 윈도우 메세지를 처리한다.
 *
 * @param   hWnd    [IN] 윈도우 핸들
 * @param   uMsg    [IN] 메세지
 * @param   wParam  [IN] 파라미터 #1
 * @param   lParam  [IN] 파라미터 #2
 * @return  메세지 처리 결과.
 */
LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    switch( uMsg )
    {
    case WM_DESTROY:
        PostQuitMessage( 0 );
        break;
    } //switch

    return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

/**
 * 윈도우 클래스를 등록한다.
 *
 * @param   hInstance   [IN] 인스턴스 핸들
 * @return  성공 여부.
 */
BOOL RegisterWindowClass( HINSTANCE hInstance )
{
    WNDCLASSEX wcEx;

    wcEx.cbSize         = sizeof( WNDCLASSEX );
    wcEx.cbClsExtra     = 0;
    wcEx.cbWndExtra     = 0;
    wcEx.hbrBackground  = (HBRUSH)GetStockObject( GRAY_BRUSH );
    wcEx.hCursor        = LoadCursor( NULL, IDC_ARROW );
    wcEx.hIcon          = NULL;
    wcEx.hIconSm        = NULL;
    wcEx.hInstance      = hInstance;
    wcEx.lpfnWndProc    = MsgProc;
    wcEx.lpszMenuName   = NULL;
    wcEx.lpszClassName  = PROJECT_NAME;
    wcEx.style          = CS_HREDRAW | CS_VREDRAW;

    if( !RegisterClassEx( &wcEx ) )
    {
        return FALSE;
    } //if

    return TRUE;
}

/**
 * 윈도우를 초기화 한다.
 */
HWND InitWindow( HINSTANCE hInstance )
{
    DWORD dwStyle = WS_VISIBLE | WS_CAPTION | WS_SYSMENU;
//  DWORD dwStyle = WS_POPUP;

    RECT rcWindow = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    AdjustWindowRect( &rcWindow, dwStyle, 0 );

    DWORD dwWidth   = rcWindow.right - rcWindow.left;
    DWORD dwHeight  = rcWindow.bottom - rcWindow.top;

    int nWndPosX    = ( GetSystemMetrics( SM_CXSCREEN ) - dwWidth ) / 2;
    int nWndPosY    = ( GetSystemMetrics( SM_CYSCREEN ) - dwHeight ) / 2;

    HWND hWnd = CreateWindow(
        PROJECT_NAME, PROJECT_NAME,
        dwStyle,
        nWndPosX, nWndPosY,
        dwWidth, dwHeight,
        NULL, NULL,
        hInstance,
        NULL
        );

    return hWnd;
}

/**
 * 파라미터를 체크한다.
 */
BOOL CheckCmdParam( LPSTR szCmdParam )
{
    if( !strcmp( szCmdParam, "/excute" ) )
    {
        return TRUE;
    } //if

    return FALSE;
}

/**
 * 애플리케이션 메인 함수.
 */
int WINAPI WinMain(
    HINSTANCE   hInstance,
    HINSTANCE   hPrevInstance,
    LPSTR       szCmdParam,
    int         nCmdShow
    )
{
    cConfig     Config;
    cLogger     Logger;
    cGameApp    GameApp;
    HANDLE      hMutex  = NULL;
    HWND        hWnd    = NULL;
    MSG         Msg     = { 0, };

    // 파라미터가 제대로 되어있는지 체크한다.
    if( !CheckCmdParam( szCmdParam ) )  return 0;

    // 뮤텍스를 생성한다.
    hMutex = CreateMutex( NULL, FALSE, "CatchMe" );

    // 게임이 실행중인지 체크한다.
    if( GetLastError() == ERROR_ALREADY_EXISTS )
    {
        MessageBox( NULL, "게임이 이미 실행 중입니다.", "ERROR", MB_OK | MB_ICONEXCLAMATION );
        return 0;
    } //if

    // 환경설정 로드 및 로그를 초기화 한다.
    if( !Config.Init() )                return 0;
    if( !Logger.Begin() )               return 0;

    // 윈도우 클래스를 등록 및 윈도우 초기화.
    RegisterWindowClass( hInstance );
    hWnd = InitWindow( hInstance );

    // 게임을 초기화 한다.
    if( GameApp.OnInit( hWnd ) )
    {
        ShowWindow( hWnd, SW_SHOWDEFAULT );
        UpdateWindow( hWnd );

        while( Msg.message != WM_QUIT )
        {
            if( PeekMessage( &Msg, NULL, 0, 0, PM_REMOVE ) )
            {
                TranslateMessage( &Msg );
                DispatchMessage( &Msg );
            }
            else if( GameApp.OnIdle() != TRUE )
            {
                SendMessage( hWnd, WM_CLOSE, 0, 0 );
                break;
            } //if..else if
        } //while
    } //if

    // 게임 및 로그 종료.
    GameApp.OnDestroy();
    Logger.End();

    // 윈도우 클래스 해제 및 뮤텍스 해제.
    UnregisterClass( PROJECT_NAME, hInstance );
    ReleaseMutex( hMutex );

    return Msg.wParam;
}
