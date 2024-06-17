/**
 * 애니메이션.
 *
 * @author  무아
 * @date    2004-03-11 03:49am
 * @version 1.0
 *
 * @file    Animation.cpp
 */

#include "Core.h"
#include "Animation.h"
#include "ResLoader.h"

using std::string;


/**
 * 생성자.
 */
cAnimation::cAnimation()
:   m_pImage    ( NULL ),
    m_nCurFrame ( 0 ),
    m_nRefCount ( 1 )
{
}

/**
 * 소멸자.
 */
cAnimation::~cAnimation()
{
    ASSERT( NULL == m_pImage );
}

/**
 * 참조 카운트를 증가시킨다.
 */
void cAnimation::AddRef()
{
    m_nRefCount++;
}

/**
 * 참조 카운트를 감소시키며, 객체를 소멸한다.
 */
void cAnimation::Release()
{
    if( --m_nRefCount <= 0 )
    {
        SAFE_RELEASE( m_pImage );

        delete this;
    } //if
}

/**
 * 애니메이션을 로드한다.
 */
BOOL cAnimation::Load( const string& strName )
{
    FILE*   fp      = fopen( "data/animation.dat", "rt" );
    int     nCount  = 0;

    fread( &nCount, 4, 1, fp );

    for( int i = 0; i < nCount; i++ )
    {
        char szName[255] = { 0, };

        fread( szName, 30, 1, fp );
        fread( &m_Info.nWidth, 4, 1, fp );
        fread( &m_Info.nHeight, 4, 1, fp );
        fread( &m_Info.dwDelay, 4, 1, fp );
        fread( &m_Info.bLoop, 4, 1, fp );

        if( !strcmp( szName, strName.c_str() ) )
        {
            cResLoader ResLoader;

            if( ResLoader.Init( "package/animation.list" ) )
            {
                m_pImage = ResLoader.LoadImage( strName );

                if( m_pImage != NULL )
                {
                    m_Info.nFrames = m_pImage->GetWidth() / m_Info.nWidth;

                    return TRUE;
                } //if
            } //if
        } //if
    } //while

    fclose( fp );

    return FALSE;
}

/**
 * 애니메이션을 그린다.
 */
BOOL cAnimation::Draw( int nX, int nY, DWORD dwColor, BOOL bPlay )
{
    // 프레임을 그린다.
    RECT rcFrame =
    {
        m_Info.nWidth * m_nCurFrame,
        0,
        m_Info.nWidth * m_nCurFrame + m_Info.nWidth,
        m_Info.nHeight
    };

    m_pImage->Draw( nX, nY, dwColor, &rcFrame );

    // 프레임 재생.
    if( bPlay )
    {
        return Play();
    } //if

    return FALSE;
}

/**
 * 애니메이션을 재생한다.
 */
BOOL cAnimation::Play()
{
    if( timeGetTime() - m_dwDelay >= m_Info.dwDelay )
    {
        m_dwDelay = timeGetTime();

        if( ++m_nCurFrame >= m_Info.nFrames )
        {
            if( m_Info.bLoop != TRUE )
            {
                m_nCurFrame = m_Info.nFrames - 1;
            }
            else
            {
                m_nCurFrame = 0;
            } //if..else

            return FALSE;
        } //if
    } //if

    return TRUE;
}

/**
 *
 */
void cAnimation::Reset()
{
    m_nCurFrame = 0;
    m_dwDelay   = timeGetTime();
}
