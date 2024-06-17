/**
 * 게임 클래스.
 *
 * @author  무아
 * @date    2004-03-13 02:50am
 * @version 0.1
 *
 * @file    Game.h
 */

#pragma once


class cGame :   public cScene
{
public:
    cGame();

    BOOL        Init();
    cScene*     Update();
    void        Render();
    void        Release();

private:
    int         CheckMark();
    void        ClickPicture( const POINT& ptCursor );
    void        ResetGameData();
    void        UpdateBGM();
    void        ScrollCopyright();
    void        DrawInterface();

private:
    enum GAME_STATE
    {
        PLAYING = 0,
        CLEAR,
        ENDING,
    }; //enum GAME_STATE

    struct sMark
    {
        BOOL    bCheck;
        POINT   ptPosition;

        sMark()
        {
            bCheck          = FALSE;
            ptPosition.x    = 0;
            ptPosition.y    = 0;
        } //sMark
    }; //struct sMark

    cBGMPlayer*     m_pBGM;
    cTexture*       m_pInterface;
    cTexture*       m_pCopyright;
    int             m_nCopyrightPos;

    cPictureMgr*    m_pPictureMgr;
    cPicture*       m_pPicture[2];
    BYTE            m_nPictureAlpha;

    cAnimation*     m_pMark[6];
    sMark           m_Mark[6];
    int             m_nMarks;

    cTimeGage*      m_pTimeGage;
    cComment*       m_pComment;
    cFont*          m_pFont;

    cBitmapFont*    m_pScoreFont;
    cBitmapFont*    m_pStageFont;
    cTexture*       m_pClearWindow;

    GAME_STATE      m_nGameState;
    int             m_nStage;
}; //class cGame
