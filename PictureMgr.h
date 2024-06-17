/**
 * 스테이지 관리자.
 *
 * @author  무아
 * @date    2004-03-11 07:12am
 * @version 1.0
 *
 * @file    PictureMgr.h
 */

#pragma once

#include "Singleton.h"


class cPictureMgr : public cSingleton<cPictureMgr>
{
public:
    cPictureMgr();
    ~cPictureMgr();

    BOOL    Init();

    int     Next();
    int     GetTotalNum();
    int     GetImageNum();
    int     GetNextImageNum();

    const std::string&  GetComment();
    const RECT&         GetRect( int nID );

private:
    struct sPicture
    {
        int         nImage;
        RECT        rcRect[5];
        std::string strComment;
    }; //struct sPicture

    std::map<int, sPicture> m_mapPicture;
    int                     m_nTotal;
    int                     m_nCurrent;
}; //class cPictureMgr
