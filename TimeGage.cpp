/**
 * 타임 게이지.
 *
 * @author  무아
 * @date    2004-04-08 01:11am
 * @version 0.5
 *
 * @file    TimeGage.cpp
 */

#include "Core.h"
#include "ResLoader.h"
#include "BitmapFont.h"
#include "TimeGage.h"


/**
 * 생성자.
 */
cTimeGage::cTimeGage()
:   m_pGageIcon     ( NULL ),
    m_pTimeFont     ( NULL ),
    m_dwTickCount   ( 0 ),
    m_nCurGage      ( 0 ),
    m_nTotalTime    ( 0 )
{
}

/**
 * 소멸자.
 */
cTimeGage::~cTimeGage()
{
    SAFE_DELETE ( m_pTimeFont );
    SAFE_RELEASE( m_pGageIcon );
}

/**
 * 타임 게이지를 초기화 한다.
 */
BOOL cTimeGage::Init( cResLoader& ResLoader, int nTime )
{
    m_pGageIcon = ResLoader.LoadImage( "time_gage" );

    m_pTimeFont = new cBitmapFont;

    if( !m_pTimeFont->Load( ResLoader, "time_number" ) )
    {
        return FALSE;
    } //if

    m_nTotalTime    = nTime;
    m_dwTickCount   = timeGetTime();

    return TRUE;
}

/**
 *
 */
BOOL cTimeGage::Update()
{
    if( timeGetTime() - m_dwTickCount >= 500 )
    {
        m_dwTickCount = timeGetTime();

        if( ++m_nCurGage >= GAGE_NUM )
        {
            m_nCurGage = 0;

            if( --m_nTotalTime < 0 )
            {
                return FALSE;
            } //if
        } //if
    } //if

    return TRUE;
}

/**
 * 타임 게이지를 그린다.
 */
void cTimeGage::Draw()
{
    for( int i = 0; i <= m_nCurGage; i++ )
    {
        m_pGageIcon->Draw(
            ( 9 * i + 52 ),
            447
            );
    } //for

    m_pTimeFont->Draw(
        252, 447,
        0xFFFFFFFF,
        "%04d",
        m_nTotalTime
        );
}
