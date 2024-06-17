/**
 * 틀린그림 관리자.
 *
 * @author  무아
 * @date    2004-03-11 07:15am
 * @version 1.0
 *
 * @file    PictureMgr.cpp
 */

#include "Core.h"
#include "PictureMgr.h"

using std::string;
using std::map;
using std::make_pair;
using std::vector;


/**
 * 생성자.
 */
cPictureMgr::cPictureMgr()
:   m_nTotal    ( 0 ),
    m_nCurrent  ( 0 )
{
    m_mapPicture.clear();

    srand( timeGetTime() );
}

/**
 * 소멸자.
 */
cPictureMgr::~cPictureMgr()
{
    m_mapPicture.clear();
}

/**
 * 틀린그림 관리자를 초기화 한다.
 */
BOOL cPictureMgr::Init()
{
    vector<sPicture>    aPictures;
    map<int, int>       mapSort;
    int                 nCount = 0;

    // 그림의 정보 데이터 파일을 연다.
    FILE* fp = fopen( "data/picture.info", "rb" );

    if( NULL == fp )
    {
        g_pLogger->Write( FALSE, "Loaded... \"data/picture.info\" fail.\n" );

        return FALSE;
    } //if

    // 그림의 총 갯수를 읽는다.
    fread( &m_nTotal, 4, 1, fp );

    // 틀린 그림의 영역들과 코멘트를 읽는다.
    for( int i = 0; i < m_nTotal; i++ )
    {
        sPicture    Picture;
        int         nCommentLen;

        Picture.nImage = i;

        fread( Picture.rcRect, sizeof( RECT ), 5, fp );
        fread( &nCommentLen, 4, 1, fp );

        for( int j = 0; j < nCommentLen; j++ )
        {
            char ch;
            fread( &ch, 1, 1, fp );

            Picture.strComment += ( ch ^ 0x19841223 );
        } //for

        aPictures.push_back( Picture );
    } //for

    fclose( fp );

    // 그림들을 무작위로 정렬한다.
    while( nCount < m_nTotal )
    {
        int nPicture = rand() % m_nTotal;

        if( mapSort.find( nPicture ) == mapSort.end() )
        {
            mapSort.insert( make_pair( nPicture, nCount ) );
            m_mapPicture.insert( make_pair( nCount, aPictures[nPicture] ) );

            ++nCount;
        } //if
    } //while

    mapSort.clear();
    aPictures.clear();

    return TRUE;
}

/**
 * 다음 그림으로 넘어간다.
 */
int cPictureMgr::Next()
{
    if( ++m_nCurrent >= m_nTotal )
    {
        m_nCurrent = m_nTotal - 1;
    } //if

    return m_nCurrent;
}

/**
 * 그림의 총 갯수를 얻는다.
 */
int cPictureMgr::GetTotalNum()
{
    return m_nTotal;
}

/**
 * 현재 그림의 번호를 얻는다.
 */
int cPictureMgr::GetImageNum()
{
    return m_mapPicture[m_nCurrent].nImage;
}

/**
 * 다음 그림의 번호를 얻는다.
 */
int cPictureMgr::GetNextImageNum()
{
    int nNext = m_nCurrent + 1;

    if( nNext >= m_nTotal )
    {
        nNext = m_nTotal - 1;
    } //if

    return m_mapPicture[nNext].nImage;
}

/**
 * 코멘트를 얻는다.
 */
const string& cPictureMgr::GetComment()
{
    return m_mapPicture[m_nCurrent].strComment;
}

/**
 * 틀린 부분의 RECT를 얻는다.
 */
const RECT& cPictureMgr::GetRect( int nID )
{
    return m_mapPicture[m_nCurrent].rcRect[nID];
}
