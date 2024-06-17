/**
 * 타임 게이지.
 *
 * @author  무아
 * @date    2004-04-08 01:11am
 * @version 0.5
 *
 * @file    TimeGage.h
 */

#pragma once


class cTimeGage
{
public:
    cTimeGage();
    ~cTimeGage();

    BOOL    Init( cResLoader& ResLoader, int nTime );
    BOOL    Update();
    void    Draw();

private:
    enum
    {
        GAGE_NUM    = 20,
    }; //enum

    cTexture*       m_pGageIcon;
    cBitmapFont*    m_pTimeFont;

    DWORD           m_dwTickCount;
    DWORD           m_nCurGage;
    int             m_nTotalTime;
}; //class cTimeGage
