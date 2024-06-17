/**
 * 코멘트 클래스.
 *
 * @author  무아
 * @date    2004-03-13 07:14am
 * @version 1.0
 *
 * @file    Comment.h
 */

#pragma once


class cComment :    public cSystemObject
{
public:
    cComment();
    ~cComment();

    BOOL    Init();
    void    Set( const std::string& strText );
    void    Update();
    void    Draw( int nX, int nY, DWORD dwColor );

private:
    enum
    {
        COLS        = 80,
        SHOWTIME    = 2000,
    }; //enum

    cFont*      m_pFont;

    BOOL        m_bScroll;
    int         m_nScrollPos;
    int         m_nCurLine;
    int         m_nNextLine;
    DWORD       m_dwShowTime;

    std::vector<std::string>    m_aLines;
}; //class cComment
