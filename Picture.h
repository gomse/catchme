/**
 *
 *
 * @author  무아
 * @date    2004-03-12 09:33pm
 * @version 0.1
 *
 * @file    Picture.h
 */

#pragma once


class cPicture :    public cSystemObject
{
public:
    cPicture();
    ~cPicture();

    BOOL    Load( int nID );
    void    Draw( int nAlpha );

private:
    enum
    {
        WIDTH   = 290,
        HEIGHT  = 400,
    }; //enum

    cTexture*   m_pImage;
}; //class cPicture
