/**
 * 비트맵 폰트.
 *
 * @author  무아
 * @date    2004-03-14 07:19pm
 * @version 1.0
 *
 * @file    BitmapFont.h
 */

#pragma once


class cResLoader;

class cBitmapFont
{
public:
    cBitmapFont();
    ~cBitmapFont();

    BOOL    Load( cResLoader& ResLoader, const std::string& strName );
    void    Draw( int nX, int nY, DWORD dwColor, const char* szCount, ... );

private:
    cTexture*   m_pImage;
    int         m_nWidth;
}; //class cBitmapFont
