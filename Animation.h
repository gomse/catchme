/**
 * 애니메이션.
 *
 * @author  무아
 * @date    2004-03-11 03:45am
 * @version 1.0
 *
 * @file    Animation.h
 */

#pragma once


class cAnimation :  public cSystemObject
{
public:
    cAnimation();
    ~cAnimation();

    BOOL    Load( const std::string& strName );
    BOOL    Draw( int nX, int nY, DWORD dwColor, BOOL bPlay = TRUE );
    void    Reset();

    inline  int     GetWidth()  { return m_Info.nWidth; }
    inline  int     GetHeight() { return m_Info.nHeight; }

    void    AddRef();
    void    Release();

private:
    BOOL    Play();

    /**
     * 애니메이션 정보 구조체.
     */
    struct sInfo
    {
        int     nWidth;
        int     nHeight;
        DWORD   dwDelay;
        BOOL    bLoop;
        int     nFrames;
    }; //struct sInfo

    int         m_nRefCount;    ///< 참조 카운트.
    cTexture*   m_pImage;       ///< 텍스쳐.
    sInfo       m_Info;         ///< 애니메이션 정보.
    int         m_nCurFrame;    ///< 현재 프레임.
    DWORD       m_dwDelay;      ///< 프레임 딜레이.
}; //class cAnimation
