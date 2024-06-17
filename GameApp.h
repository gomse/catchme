/**
 * 게임 애플리케이션 클래스.
 *
 * @author  무아
 * @date    2004-03-10 04:04am
 * @version 1.0
 *
 * @file    GameApp.h
 */

#pragma once


class cCursor;
class cScene;

class cGameApp :    public cSingleton<cGameApp>,
                    public cSystemObject
{
// Operations
public:
    cGameApp();
    ~cGameApp();

    BOOL    OnInit( HWND hWnd );
    BOOL    OnIdle();
    void    OnDestroy();

// Implementation
private:
    BOOL    TestDevice();
    void    OnLostDevice();
    void    OnResetDevice();

    BOOL    UpdateScene();
    void    RenderScene();
    void    WaitFrame();

// Attributes
private:
    enum        { WAITFRAME = 40 };

    DWORD       m_dwWaitFrame;
    cCursor*    m_pCursor;
    cScene*     m_pScene;
}; //class cGameApp
