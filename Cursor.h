/**
 * 마우스 커서.
 *
 * @author  무아
 * @date    2004-03-11 04:48am
 * @version 0.1
 *
 * @file    Cursor.h
 */

#pragma once


class cAnimation;
class cCursor : public cSingleton<cCursor>,
                public cSystemObject
{
public:
    cCursor();
    ~cCursor();

    BOOL    Init();
    void    Update();
    void    Draw();
    BOOL    IsInRect( RECT rcRect );

    const   POINT&  GetPosition()
    {
        return m_ptPosition;
    } //GetPosition

private:
    cAnimation*     m_pImage;
    POINT           m_ptPosition;
    BOOL            m_bHidden;
}; //class cCursor
