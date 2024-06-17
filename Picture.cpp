/**
 *
 *
 * @author  무아
 * @date    2004-03-12 09:35pm
 * @version 0.1
 *
 * @file    Picture.cpp
 */

#include "Core.h"
#include "Picture.h"
#include "ResLoader.h"


/**
 * 생성자.
 */
cPicture::cPicture()
:   m_pImage    ( NULL )
{
}

/**
 * 소멸자.
 */
cPicture::~cPicture()
{
    SAFE_RELEASE( m_pImage );
}

/**
 * 그림을 로드한다.
 */
BOOL cPicture::Load( int nID )
{
    cResLoader ResLoader;

    if( !ResLoader.Init( "package/picture.list" ) )
    {
        g_pLogger->Write( FALSE, "Loaded... \"package/picture.list\" fail.\n" );

        return FALSE;
    } //if

    char szName[255];
    sprintf( szName, "picture-%d", nID );

    m_pImage = ResLoader.LoadImage( szName );

    return ( m_pImage != NULL );
}

/**
 * 그림을 그린다.
 */
void cPicture::Draw( int nAlpha )
{
    RECT    rcRect[2];

    DWORD   dwColor  = 0x00FFFFFF;
    dwColor         |= ( nAlpha * 255 / 100 ) << 24;

    for( int i = 0; i < 2; i++ )
    {
        SetRect( &rcRect[i], i * WIDTH, 0, i * WIDTH + WIDTH, HEIGHT );
    } //for

    m_pImage->Draw( 20, 30, dwColor, &rcRect[0] );
    m_pImage->Draw( 20 + WIDTH + 20, 30, dwColor, &rcRect[1] );
}
