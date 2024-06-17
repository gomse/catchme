/**
 * BGM 플레이어.
 *
 * @author  무아
 * @date    2004-03-14 12:18am
 * @version 1.0
 *
 * @file    BGMPlayer.h
 */

#pragma once


class cBGMPlayer :  public cSystemObject
{
public:
    cBGMPlayer();
    ~cBGMPlayer();

    BOOL    Init();
    void    Update();

    void    Next();
    void    Prev();

    const   std::string GetName();

private:
    void    Load();

    cMp3Player*                 m_pMp3;
    cWavePlayer*                m_pChangeSnd;
    std::map<int, std::string>  m_mapFiles;
    BOOL                        m_bEnable;
    int                         m_nBGM;
}; //class cBGMPlayer
