/**
 * 환경 설정.
 *
 * @author  무아
 * @date    2004-03-15 08:43am
 * @version 0.1
 *
 * @file    Config.h
 */

#pragma once


class cConfig : public cSingleton<cConfig>
{
public:
    cConfig();
    ~cConfig();

    BOOL        Init();

public:
    std::string     m_strNick;
    std::string     m_strGamePath;
    std::string     m_strMP3Path;
    BOOL            m_bUploadRank;
    BOOL            m_bMusic;
    BOOL            m_bSound;
    int             m_nMusicVolume;
    int             m_nSoundVolume;
    float           m_fVersion;

private:
    const char*     GetValue( HKEY hKey, const char* szName );
}; //class cConfig
