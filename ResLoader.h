/**
 * Resource Loader.
 *
 * @author  무아
 * @date    2004-03-10 03:44am
 * @version 1.0
 *
 * @file    ResLoader.h
 */

#pragma once


class cResLoader : public cSystemObject
{
public:
    cResLoader();
    ~cResLoader();

    BOOL    Init( const std::string& strFile );
    BOOL    Exists( const std::string& strName );

    cTexture*       LoadImage( const std::string& strName );
    cWavePlayer*    LoadSound( const std::string& strName );

private:
    cTexture*   ReadTexture( const std::string& strFile, int nPoint );
    int         GetPoint( const std::string& strFile, const std::string& strName );

    std::map<std::string, std::string>  m_mapResource;
}; //class cResLoader
