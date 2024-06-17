/**
 * 비트맵 폰트.
 *
 * @author  무아
 * @date    2004-03-14 07:19pm
 * @version 1.0
 *
 * @file    BitmapFont.cpp
 */

#include "Core.h"
#include "ResLoader.h"
#include "BitmapFont.h"


/**
 * 생성자.
 */
cBitmapFont::cBitmapFont()
:   m_pImage    ( NULL ),
    m_nWidth    ( 0 )
{
}

/**
 * 소멸자.
 */
cBitmapFont::~cBitmapFont()
{
    SAFE_RELEASE( m_pImage );
}

/**
 *
 */
BOOL cBitmapFont::Load( cResLoader& ResLoader, const std::string& strName )
{
    m_pImage = ResLoader.LoadImage( strName );

    if( m_pImage != NULL )
    {
        m_nWidth = m_pImage->GetWidth() / 10;

        return TRUE;
    } //if

    g_pLogger->Write( FALSE, "Loaded Bitmap font... \"%s\" fail.\n", strName.c_str() );

    return FALSE;
}

/**
 *
 */
void cBitmapFont::Draw( int nX, int nY, DWORD dwColor, const char* szCount, ... )
{
    char    szResult[255];
    va_list va;

    va_start( va, szCount );
    vsprintf( szResult, szCount, va );
    va_end( va );

    for( int i = 0; i < strlen( szResult ); i++ )
    {
        int nCount = szResult[i] - 0x30;

        RECT rcCount =
        {
            m_nWidth * nCount,
            0,
            m_nWidth * nCount + m_nWidth,
            m_pImage->GetHeight()
        };

        m_pImage->Draw(
            nX + ( i * m_nWidth ),
            nY,
            dwColor,
            &rcCount
            );
    } //for
}
