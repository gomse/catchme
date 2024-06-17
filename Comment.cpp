/**
 * 코멘트 클래스.
 *
 * @author  무아
 * @date    2004-03-13 07:18am
 * @version 1.0
 *
 * @file    Comment.cpp
 */

#include "Core.h"
#include "Comment.h"
#include "ResLoader.h"

using std::string;
using std::vector;


/**
 * 생성자.
 */
cComment::cComment()
:   m_pFont         ( NULL ),
    m_bScroll       ( FALSE ),
    m_nScrollPos    ( 0 ),
    m_nCurLine      ( 0 )
{
    ASSERT( m_pGraphic != NULL );

    m_aLines.clear();
}

/**
 * 소멸자.
 */
cComment::~cComment()
{
    m_aLines.clear();

    SAFE_RELEASE( m_pFont );
}

/**
 * 코멘트를 초기화 한다.
 */
BOOL cComment::Init()
{
    m_pFont = m_pGraphic->CreateFont( "굴림", 12 );

    return TRUE;
}

/**
 * 코멘트를 설정한다.
 */
void cComment::Set( const string& strText )
{
    int nLine       = 0;

    m_dwShowTime    = timeGetTime();
    m_bScroll       = FALSE;
    m_nScrollPos    = 0;
    m_nCurLine      = 0;

    m_aLines.clear();
    m_aLines.resize( 1 );

    for( int i = 0; i < strText.size(); i++ )
    {
        // 한글 체크.
        if( strText.c_str()[i] & 0x80 )
        {
            if( m_aLines[nLine].size() + 2 > COLS )
            {
                m_aLines.push_back( "" );
                nLine++;
            } //if

            m_aLines[nLine] += strText.c_str()[i++];
            m_aLines[nLine] += strText.c_str()[i];
        }
        else if( strText.c_str()[i] == '\\' )
        {
            if( strText.c_str()[i + 1] == 'n' )
            {
                i++;

                if( i + 1 < strText.size() )
                {
                    m_aLines.push_back( "" );
                    nLine++;
                }
                else
                {
                    m_aLines[nLine] += ' ';
                } //if..else
            } //if
        }
        else
        {
            if( m_aLines[nLine].size() + 1 > COLS )
            {
                m_aLines.push_back( "" );
                nLine++;
            } //if

            m_aLines[nLine] += strText.c_str()[i];
        } //if..else
    } //for
}

/**
 * 코멘트를 업데이트 한다.
 */
void cComment::Update()
{
    if( m_aLines.size() < 2 ) return;

    if( m_bScroll )
    {
        if( --m_nScrollPos < -20 )
        {
            m_nCurLine      = m_nNextLine;
            m_bScroll       = FALSE;
            m_nScrollPos    = 0;
        } //if
    }
    else
    {
        if( timeGetTime() - m_dwShowTime >= SHOWTIME )
        {
            m_dwShowTime    = timeGetTime();
            m_bScroll       = TRUE;
            m_nNextLine     = m_nCurLine + 1;

            if( m_nNextLine >= m_aLines.size() )
            {
                m_nNextLine = 0;
            } //if
        } //if
    } //if..else
}

/**
 * 코멘트를 출력한다.
 */
void cComment::Draw( int nX, int nY, DWORD dwColor )
{
    if( m_aLines.empty() ) return;

    string strComment = m_aLines[m_nCurLine];

    m_pFont->DrawText(
        nX,
        nY + m_nScrollPos,
        strComment.c_str(),
        dwColor
        );

    if( m_bScroll )
    {
        strComment = m_aLines[m_nNextLine];

        m_pFont->DrawText(
            nX,
            nY + m_nScrollPos + 20,
            strComment.c_str(),
            dwColor
            );
    } //if
}
