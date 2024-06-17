/**
 * 마우스 커서.
 *
 * @author  무아
 * @date    2004-03-11 04:50am
 * @version 0.9
 *
 * @file    Cursor.cpp
 */

#include "Core.h"
#include "Animation.h"
#include "Cursor.h"


/**
 * 생성자.
 */
cCursor::cCursor()
:   m_pImage    ( NULL ),
    m_bHidden   ( FALSE )
{
}

/**
 * 소멸자.
 */
cCursor::~cCursor()
{
    SAFE_RELEASE( m_pImage );
}

/**
 * 커서를 초기화 한다.
 */
BOOL cCursor::Init()
{
    m_pImage = new cAnimation;

    if( m_pImage->Load( "cursor" ) )
    {
        return TRUE;
    } //if

    g_pLogger->Write( FALSE, "Cursor animation load failed.\n" );

    return FALSE;
}

/**
 * 커서를 업데이트 한다.
 */
void cCursor::Update()
{
    GetCursorPos( &m_ptPosition );
    ScreenToClient( m_hWnd, &m_ptPosition );
}

/**
 * 커서를 그린다.
 */
void cCursor::Draw()
{
    if( m_bHidden ) return;

    m_ptPosition.x  -=  ( m_pImage->GetWidth() / 2 );
    m_ptPosition.y  -=  ( m_pImage->GetHeight() / 2 );

    m_pImage->Draw( m_ptPosition.x, m_ptPosition.y, 0xFFFFFFFF, TRUE );
}

/**
 *
 */
BOOL cCursor::IsInRect( RECT rcRect )
{
    if( m_ptPosition.x >= rcRect.left &&
        m_ptPosition.x <= rcRect.right &&
        m_ptPosition.y >= rcRect.top &&
        m_ptPosition.y <= rcRect.bottom )
    {
        return TRUE;
    } //if

    return FALSE;
}
