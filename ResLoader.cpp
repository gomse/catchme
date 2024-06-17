/**
 * Resource Loader.
 *
 * @author  무아
 * @date    2004-03-10 03:44am
 * @version 1.0
 *
 * @file    ResLoader.cpp
 */

#include "Core.h"
#include "ResLoader.h"

using std::string;
using std::make_pair;


/**
 * 생성자.
 */
cResLoader::cResLoader()
{
    ASSERT( m_pGraphic );
    ASSERT( m_pMedia );

    m_mapResource.clear();
}

/**
 * 소멸자.
 */
cResLoader::~cResLoader()
{
    m_mapResource.clear();
}

/**
 *
 */
BOOL cResLoader::Init( const string& strFile )
{
    m_mapResource.clear();

    FILE* fp = fopen( strFile.c_str(), "rb" );

    if( NULL == fp )
    {
        return FALSE;
    } //if

    int nTotalPackage = 0;

    fread( &nTotalPackage, 4, 1, fp );

    for( int i = 0; i < nTotalPackage; i++ )
    {
        char    szPackage[255]  = { 0, };
        int     nLength         = 0;
        int     nData           = 0;

        fread( &nLength, 4, 1, fp );
        fread( szPackage, nLength, 1, fp );
        fread( &nData, 4, 1, fp );

        string strPackage = szPackage;

        for( int j = 0; j < nData; j++ )
        {
            char szName[255] = { 0, };

            fread( &nLength, 4, 1, fp );
            fread( szName, nLength, 1, fp );

            string strName = szName;

            m_mapResource.insert( make_pair( strName, strPackage ) );
        } //for
    } //for

    fclose( fp );

    return TRUE;
}

/**
 *
 */
int cResLoader::GetPoint( const string& strFile, const string& strName )
{
    FILE* fp = fopen( strFile.c_str(), "rb" );

    if( NULL == fp )
    {
        return -1;
    } //if

    fseek( fp, 0, SEEK_END );
    fseek( fp, ftell( fp ) - 8, SEEK_SET );

    int nHeadPoint  = 0;
    int nHeadCount  = 0;

    fread( &nHeadPoint, 4, 1, fp );
    fread( &nHeadCount, 4, 1, fp );

    fseek( fp, nHeadPoint, SEEK_SET );

    for( int i = 0; i < nHeadCount; i++ )
    {
        char    szName[255] = { 0, };
        int     nLength     = 0;
        int     nPoint      = 0;

        fread( &nLength, 4, 1, fp );
        fread( szName, nLength, 1, fp );
        fread( &nPoint, 4, 1, fp );

        if( !strcmp( strName.c_str(), szName ) )
        {
            fclose( fp );
            return nPoint;
        } //if
    } //for

    fclose( fp );

    return -1;
}

/**
 *
 */
cTexture* cResLoader::ReadTexture( const string& strFile, int nPoint )
{
    FILE* fp = fopen( strFile.c_str(), "rb" );

    if( NULL == fp )
    {
        g_pLogger->Write( FALSE, "Read Texture from... \"%s\", %d.\n", strFile.c_str(), nPoint );

        return FALSE;
    } //if

    fseek( fp, nPoint, SEEK_SET );

    int nWidth  = 0;
    int nHeight = 0;

    fread( &nWidth, 4, 1, fp );
    fread( &nHeight, 4, 1, fp );

    DWORD* pData = new DWORD[ nWidth * nHeight ];

    fread( pData, nWidth * nHeight * 4 , 1, fp );
    fclose( fp );

    cTexture* pTexture = m_pGraphic->CreateTexture( pData, nWidth, nHeight );

    SAFE_DELETE_ARRAY( pData );

    return pTexture;
}

/**
 *
 */
BOOL cResLoader::Exists( const string& strName )
{
    if( m_mapResource.find( strName ) != m_mapResource.end() )
    {
        return TRUE;
    } //if

    return FALSE;
}

/**
 *
 */
cTexture* cResLoader::LoadImage( const string& strName )
{
    if( Exists( strName ) )
    {
        string  strFile = "package/" + m_mapResource[ strName ];
        int     nPoint  = GetPoint( strFile, strName );

        return ReadTexture( strFile, nPoint );
    } //if

    g_pLogger->Write( FALSE, "Loaded Image... \"%s\" fail.\n", strName.c_str() );

    return NULL;
}

/**
 *
 */
cWavePlayer* cResLoader::LoadSound( const string& strName )
{
    if( Exists( strName ) )
    {
        string  strFile = "package/" + m_mapResource[ strName ];
        int     nPoint  = GetPoint( strFile, strName );

        return m_pMedia->LoadWave( strFile.c_str(), nPoint );
    } //if

    g_pLogger->Write( FALSE, "Loaded Sound... \"%s\" fail.\n", strName.c_str() );

    return NULL;
}
