/**
 * 게임 화면.
 *
 * @author  무아
 * @date    2004-03-10 05:04am
 * @version 0.1
 *
 * @file    Game.cpp
 */

#include "Core.h"
#include "Scene.h"
#include "ResLoader.h"
#include "Animation.h"
#include "BitmapFont.h"
#include "Cursor.h"
#include "PictureMgr.h"
#include "Picture.h"
#include "Comment.h"
#include "BGMPlayer.h"
#include "TimeGage.h"
#include "Game.h"


/**
 * 게임 클래스를 생성한다.
 */
cScene* cSceneFactory::Game()
{
    return new cGame;
}

/**
 * 생성자.
 */
cGame::cGame()
:   m_pBGM          ( NULL ),
    m_pInterface    ( NULL ),
    m_pCopyright    ( NULL ),
    m_nCopyrightPos ( 360 ),
    m_pPictureMgr   ( NULL ),
    m_nPictureAlpha ( 0 ),
    m_pComment      ( NULL ),
    m_pScoreFont    ( NULL ),
    m_pStageFont    ( NULL ),
    m_pClearWindow  ( NULL ),
    m_pTimeGage     ( NULL ),
    m_nGameState    ( PLAYING ),
    m_nStage        ( 0 )
{
    m_pPicture[0]   = NULL;
    m_pPicture[1]   = NULL;

    for( int i = 0; i < 6; i++ )
    {
        m_pMark[i] = NULL;
    } //for
}

/**
 * 게임을 초기화 한다.
 */
BOOL cGame::Init()
{
    cResLoader ResLoader;

    if( !ResLoader.Init( "package/game.list" ) )
    {
        g_pLogger->Write( FALSE, "Loaded... \"package/game.list\" fail.\n" );

        return FALSE;
    } //if

    // BGM 플레이어를 초기화 한다.
    m_pBGM = new cBGMPlayer;
    m_pBGM->Init();

    if( !m_pBGM->Init() )
    {
        g_pLogger->Write( FALSE, "BGM is not found!\n" );
    } //if

    // 인터페이스 로드 및 틀린 그림 관리자를 초기화 한다.
    m_pFont         = m_pGraphic->CreateFont( "굴림", 12 );
    m_pInterface    = ResLoader.LoadImage( "interface" );
    m_pCopyright    = ResLoader.LoadImage( "copyright" );
    m_pPictureMgr   = new cPictureMgr;

    if( !m_pPictureMgr->Init() )
    {
        g_pLogger->Write( FALSE, "Init Picture manager failed.\n" );

        return FALSE;
    } //if

    // 그림을 로드한다.
    m_pPicture[0]   = new cPicture;
    m_pPicture[1]   = new cPicture;

    m_pPicture[0]->Load( m_pPictureMgr->GetImageNum() );
    m_pPicture[1]->Load( m_pPictureMgr->GetNextImageNum() );

    // 마크 애니메이션을 로드한다.
    for( int i = 0; i < 5; i++ )
    {
        m_pMark[i] = new cAnimation;
        m_pMark[i]->Load( "o_mark" );
    } //for

    m_pMark[5]  = new cAnimation;
    m_pMark[5]->Load( "x_mark" );

    // 코멘트를 초기화 한다.
    m_pComment  = new cComment;
    m_pComment->Init();
    m_pComment->Set( m_pPictureMgr->GetComment() );

    // 숫자 폰트들을 로드한다.
    m_pStageFont    = new cBitmapFont;
    m_pScoreFont    = new cBitmapFont;

    m_pStageFont->Load( ResLoader, "stage_number" );
    m_pScoreFont->Load( ResLoader, "score_number" );

    // 스테이지 클리어 윈도우를 로드한다.
    m_pClearWindow  = ResLoader.LoadImage( "clear_window" );

    // 타임 게이지를 초기화 한다.
    m_pTimeGage     = new cTimeGage;
    m_pTimeGage->Init( ResLoader, ( m_pPictureMgr->GetTotalNum() * 30 ) );

    // 게임 데이터를 초기화 한다.
    ResetGameData();

    return TRUE;
}

/**
 * 게임 데이터를 리셋 시킨다.
 */
void cGame::ResetGameData()
{
    for( int i = 0; i < 6; i++ )
    {
        m_Mark[i].bCheck = FALSE;
        m_pMark[i]->Reset();
    } //for

    m_nPictureAlpha = 0;
    m_nMarks        = 5;
}

/**
 * 객체를 소멸시킨다.
 */
void cGame::Release()
{
    SAFE_DELETE( m_pTimeGage );

    SAFE_RELEASE( m_pClearWindow );

    SAFE_DELETE( m_pBGM );
    SAFE_DELETE( m_pComment );

    SAFE_DELETE( m_pScoreFont );
    SAFE_DELETE( m_pStageFont );

    SAFE_DELETE( m_pPicture[1] );
    SAFE_DELETE( m_pPicture[0] );
    SAFE_DELETE( m_pPictureMgr );

    for( int i = 0; i < 6; i++ )
    {
        SAFE_RELEASE( m_pMark[i] );
    } //for

    SAFE_RELEASE( m_pCopyright );
    SAFE_RELEASE( m_pInterface );
    SAFE_RELEASE( m_pFont );

    delete this;
}

/**
 * 게임을 업데이트 한다.
 */
cScene* cGame::Update()
{
    if( m_pInput->GetState( KEY_ESC ) == cInput::PRESS )
    {
        return NULL;
    } //if

    switch( m_nGameState )
    {
    case PLAYING:
        {
            m_pTimeGage->Update();

            if( m_pInput->GetState( MOUSE_LBUTTON ) == cInput::PRESS )
            {
                RECT rcPicture[2];

                SetRect( &rcPicture[0], 20, 30, 310, 430 );     // 왼쪽 사진.
                SetRect( &rcPicture[1], 330, 30, 620, 430 );    // 오른쪽 사진.

                if( cCursor::GetSingletonPtr()->IsInRect( rcPicture[0] ) ||
                    cCursor::GetSingletonPtr()->IsInRect( rcPicture[1] ) )
                {
                    ClickPicture( cCursor::GetSingletonPtr()->GetPosition() );
                } //if
            }
            else if( m_pInput->GetState( MOUSE_RBUTTON ) == cInput::PRESS )
            {
            } //if..else if

            // 틀린 그림을 모두 찾음.
            if( m_nMarks <= 0 )
            {
                m_nGameState = CLEAR;

                if( m_nStage + 1 >= m_pPictureMgr->GetTotalNum() )
                {
                    m_nGameState = ENDING;
                } //if
            } //if
        }
        break;

    case CLEAR:
        {
            if( ++m_nPictureAlpha > 100 )
            {
                m_pPictureMgr->Next();

                SAFE_DELETE( m_pPicture[0] );
                m_pPicture[0] = m_pPicture[1];

                m_pPicture[1]   = new cPicture;
                m_pPicture[1]->Load( m_pPictureMgr->GetNextImageNum() );

                m_pComment->Set( m_pPictureMgr->GetComment() );

                ResetGameData();

                m_nStage++;
                m_nGameState = PLAYING;
            } //if
        }
        break;

    case ENDING:
        ResetGameData();
        m_pComment->Set( "모두 클리어!!!" );
        break;
    }; //switch

    m_pComment->Update();

    ScrollCopyright();
    UpdateBGM();

    return this;
}

/**
 * BGM을 업데이트 한다.
 */
void cGame::UpdateBGM()
{
    m_pBGM->Update();

    if( m_pInput->GetState( KEY_LEFT ) == cInput::PRESS )
    {
        m_pBGM->Prev();
    }
    else if( m_pInput->GetState( KEY_RIGHT ) == cInput::PRESS )
    {
        m_pBGM->Next();
    } //if..else if
}

/**
 * 그림을 클릭한다.
 */
void cGame::ClickPicture( const POINT& ptCursor )
{
    int nMark = CheckMark();

    if( nMark != -1 )
    {
        m_pMark[nMark]->Reset();

        if( !m_Mark[nMark].bCheck )
        {
            m_Mark[nMark].bCheck        = TRUE;
            m_Mark[nMark].ptPosition.x  = ptCursor.x - ( m_pMark[nMark]->GetWidth() / 2 );
            m_Mark[nMark].ptPosition.y  = ptCursor.y - ( m_pMark[nMark]->GetHeight() / 2 );
            m_nMarks--;
        } //if
    }
    else
    {
        m_pMark[5]->Reset();

        m_Mark[5].bCheck        = TRUE;
        m_Mark[5].ptPosition.x  = ptCursor.x - ( m_pMark[5]->GetWidth() / 2 );
        m_Mark[5].ptPosition.y  = ptCursor.y - ( m_pMark[5]->GetHeight() / 2 );
    } //if..else
}

/**
 * 저작권을 스크롤 시킨다.
 */
void cGame::ScrollCopyright()
{
    RECT rcRect = { 4, 306, 15, 360 };

    if( !cCursor::GetSingletonPtr()->IsInRect( rcRect ) )
    {
        m_nCopyrightPos--;

        if( abs( m_nCopyrightPos - rcRect.top ) >= m_pCopyright->GetHeight() )
        {
            m_nCopyrightPos = rcRect.bottom;
        } //if
    } //if
}

/**
 * 게임 화면을 그린다.
 */
void cGame::Render()
{
    // 인터페이스를 그린다.
    DrawInterface();

    // 틀린 그림을 그린다.
    m_pPicture[0]->Draw( 100 );

    if( CLEAR == m_nGameState )
    {
        m_pPicture[1]->Draw( m_nPictureAlpha );
    } //if

    // 타임 게이지를 그린다.
    m_pTimeGage->Draw();

    // 체크 표시들을 그린다.
    for( int i = 0; i < 6; i++ )
    {
        DWORD dwColor = 0xAAFFFFFF;

        if( CLEAR == m_nGameState )
        {
            dwColor      = 0x00FFFFFF;
            dwColor     |= ( abs( m_nPictureAlpha - 100 ) * 255 / 100 ) << 24;

            // 체크 표시 투명도 보정.
            if( dwColor > 0xAAFFFFFF )
            {
                dwColor = 0xAAFFFFFF;
            } //if
        } //if

        if( m_Mark[i].bCheck )
        {
            m_pMark[i]->Draw(
                m_Mark[i].ptPosition.x,
                m_Mark[i].ptPosition.y,
                dwColor,
                TRUE
                );
        } //if
    } //for

    // 스테이지 클리어 창을 띄운다.
    if( CLEAR == m_nGameState )
    {
        int nX  = ( SCREEN_WIDTH / 2 ) - ( m_pClearWindow->GetWidth() / 2 );
        int nY  = ( SCREEN_HEIGHT / 2 ) - ( m_pClearWindow->GetHeight() / 2 );

        m_pClearWindow->Draw( nX, nY );
    } //if
}

/**
 * 인터페이스를 그린다.
 */
void cGame::DrawInterface()
{
    RECT rcRect;

    // 인터페이스 전체.
    SetRect( &rcRect, 0, 0, 640, 480 );
    m_pInterface->Draw( 0, 0, 0xFFFFFFFF, &rcRect );

    // 저작권 출력.
    SetRect( &rcRect, 640, 0, 660, 480 );

    m_pCopyright->Draw( 4, m_nCopyrightPos );
    m_pInterface->Draw( 0, 0, 0xFFFFFFFF, &rcRect );

    // 코멘트 출력.
    SetRect( &rcRect, 0, 480, 640, 525 );
    m_pComment->Draw( 25, 466, 0xFFE6E6E6 );
    m_pInterface->Draw( 0, 435, 0xFFFFFFFF, &rcRect );

    // 스테이지 출력.
    m_pStageFont->Draw( 185, 6, 0xFFFFFFFF, "%03d", ( m_nStage + 1 ) );

    // BGM 이름 출력.
    m_pFont->DrawText( 385, 8, m_pBGM->GetName().c_str(), 0xFFE6E6E6 );

    // 점수 출력.
    m_pScoreFont->Draw( 400, 440, 0xFFFFFFFF, "123456" );
}

/**
 * 커서가 틀린 그림에 있는지 체크한다.
 *
 * @return  -1:없음, 0~4:틀린 그림 번호.
 */
int cGame::CheckMark()
{
    for( int i = 0; i < 5; i++ )
    {
        RECT rcRect     = m_pPictureMgr->GetRect( i );
        RECT rcMark[2]  =
        {
            // 왼쪽 그림.
            {
                rcRect.left + 20,
                rcRect.top + 30,
                rcRect.right + 30,
                rcRect.bottom + 30
            },
            // 오른쪽 그림.
            {
                rcRect.left + 330,
                rcRect.top + 30,
                rcRect.right + 330,
                rcRect.bottom + 30
            }
        };

        if( cCursor::GetSingletonPtr()->IsInRect( rcMark[0] ) ||
            cCursor::GetSingletonPtr()->IsInRect( rcMark[1] ) )
        {
            return i;
        } //if
    } //for

    return -1;
}
