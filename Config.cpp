/**
 * 환경 설정.
 *
 * @author  무아
 * @date    2004-03-15 08:45am
 * @version 0.1
 *
 * @file    Config.cpp
 */

#include "Core.h"
#include "Config.h"


/**
 * 생성자.
 */
cConfig::cConfig()
:   m_strNick       ( "NICK" ),
    m_strGamePath   ( "PATH" ),
    m_strMP3Path    ( "MP3" ),
    m_bMusic        ( TRUE ),
    m_bSound        ( TRUE ),
    m_bUploadRank   ( TRUE ),
    m_nMusicVolume  ( -300 ),
    m_nSoundVolume  ( -300 ),
    m_fVersion      ( 0.00 )
{
}

/**
 * 소멸자.
 */
cConfig::~cConfig()
{
}

/**
 * 환경설정을 초기화 한다.
 */
BOOL cConfig::Init()
{
    HKEY    hKey;
    LONG    lResult;

    lResult = RegOpenKeyEx(
        HKEY_CURRENT_USER,
        "Software\\DotME\\CatchMe",
        0,
        KEY_QUERY_VALUE,
        &hKey
        );

    if( lResult != ERROR_SUCCESS )
    {
        return FALSE;
    } //if

    m_strNick       = GetValue( hKey, "Nick" );
    m_strGamePath   = GetValue( hKey, "GamePath" );
    m_strMP3Path    = GetValue( hKey, "MP3Path" );
    m_bUploadRank   = (BOOL)atoi( GetValue( hKey, "UploadRank" ) );
    m_nMusicVolume  = atoi( GetValue( hKey, "MusicVolume" ) );
    m_nSoundVolume  = atoi( GetValue( hKey, "SoundVolume" ) );
    m_bMusic        = (BOOL)atoi( GetValue( hKey, "Music" ) );
    m_bSound        = (BOOL)atoi( GetValue( hKey, "Sound" ) );

    RegCloseKey( hKey );

    FILE* fp = fopen( "data/version.dat", "rt" );

    if( fp != NULL )
    {
        fscanf( fp, "%f", &m_fVersion );
        fclose( fp );

        return TRUE;
    } //if

    return FALSE;
}

/**
 * 키 값을 얻어온다.
 */
const char* cConfig::GetValue( HKEY hKey, const char* szName )
{
    static char szValue[255];
    DWORD dwLength = 255;

    memset( szValue, 0, 255 );
    RegQueryValueEx( hKey, szName, NULL, NULL, (LPBYTE)szValue, &dwLength );

    return szValue;
}
