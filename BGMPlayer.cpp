/**
 * BGM 플레이어.
 *
 * @author  무아
 * @date    2004-03-14 12:18am
 * @version 1.0
 *
 * @file    BGMPlayer.cpp
 */

#include "Core.h"
#include "BGMPlayer.h"
#include "ResLoader.h"
#include <io.h>

using std::string;
using std::map;
using std::make_pair;


/**
 * 생성자.
 */
cBGMPlayer::cBGMPlayer()
:   m_pMp3      ( NULL ),
    m_pChangeSnd( NULL ),
    m_bEnable   ( FALSE ),
    m_nBGM      ( 0 )
{
    ASSERT( m_pMedia );

    srand( timeGetTime() );
    m_mapFiles.clear();
}

/**
 * 소멸자.
 */
cBGMPlayer::~cBGMPlayer()
{
    m_mapFiles.clear();

    SAFE_RELEASE( m_pChangeSnd );
    SAFE_RELEASE( m_pMp3 );
}

/**
 * BGM 플레이어를 업데이트 한다.
 */
BOOL cBGMPlayer::Init()
{
    struct _finddata_t  FindData;
    long                hFile       = -1L;
    int                 nCount      = 0;

    string strExts = cConfig::GetSingletonPtr()->m_strMP3Path + "/*.mp3";

    if( ( hFile = _findfirst( strExts.c_str(), &FindData ) ) == -1L )
    {
        return FALSE;
    }
    else
    {
        string strFile = FindData.name;

        m_mapFiles.insert( make_pair( nCount++, strFile ) );

        while( _findnext( hFile, &FindData ) == 0 )
        {
            strFile = FindData.name;

            m_mapFiles.insert( make_pair( nCount++, strFile ) );
        } //while

        _findclose( hFile );
    } //if..else

    m_nBGM = rand() % m_mapFiles.size();

    cResLoader ResLoader;
    ResLoader.Init( "package/sound.list" );

    m_pChangeSnd = ResLoader.LoadSound( "change_bgm" );
    m_pChangeSnd->SetVolume( cConfig::GetSingletonPtr()->m_nSoundVolume );

    return TRUE;
}

/**
 * BGM을 업데이트 한다.
 */
void cBGMPlayer::Update()
{
    if( m_mapFiles.empty() ) return;

    if( m_pMp3 != NULL )
    {
        if( m_pMp3->IsCompleted() )
        {
            if( m_mapFiles.size() <= 1 )
            {
                m_pMp3->Pause();
                m_pMp3->Rewind();
                m_pMp3->Play();
            }
            else
            { 
                while( 1 )
                {
                    int nBGM = rand() % m_mapFiles.size();

                    if( m_nBGM != nBGM )
                    {
                        m_nBGM = nBGM;
                        break;
                    } //if
                } //while

                SAFE_RELEASE( m_pMp3 );
            } //if..else
        } //if
    } //if

    if( NULL == m_pMp3 ) Load();
}

/**
 *
 */
void cBGMPlayer::Load()
{
    if( m_mapFiles.empty() ) return;

    SAFE_RELEASE( m_pMp3 );

    string strFile  = cConfig::GetSingletonPtr()->m_strMP3Path + "/" + m_mapFiles[ m_nBGM ];
    m_pMp3          = m_pMedia->LoadMp3( strFile.c_str() );

    if( m_pMp3 != NULL )
    {
        m_pMp3->Play();
        m_pMp3->SetVolume( cConfig::GetSingletonPtr()->m_nMusicVolume );
    } //if
}

/**
 *
 */
const string cBGMPlayer::GetName()
{
    string strName = "NONE";

    if( !m_mapFiles.empty() )
    {
        char    szCount[255];
        sprintf( szCount, "%d. ", ( m_nBGM + 1 ) );

        strName = szCount + m_mapFiles[m_nBGM];
        strName = strName.substr( 0, strName.size() - 4 );
    } //if

    return strName;
}

/**
 *
 */
void cBGMPlayer::Next()
{
    if( m_mapFiles.size() <= 1 ) return;

    if( ++m_nBGM >= m_mapFiles.size() )
    {
        m_nBGM = 0;
    } //if

    m_pChangeSnd->Play( false );
    Load();
}

/**
 *
 */
void cBGMPlayer::Prev()
{
    if( m_mapFiles.size() <= 1 ) return;

    if( --m_nBGM < 0 )
    {
        m_nBGM = m_mapFiles.size() - 1;
    } //if

    m_pChangeSnd->Play( false );
    Load();
}