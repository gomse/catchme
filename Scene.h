/**
 * Scene
 *
 * @author  무아
 * @date    2004-03-10 04:20am
 * @version 1.0
 *
 * @file    Scene.h
 */

#pragma once


class cScene :  public cSystemObject
{
public:
    cScene()            {}
    virtual ~cScene()   {}

    virtual BOOL    Init() = 0;
    virtual cScene* Update() = 0;
    virtual void    Render() = 0;
    virtual void    Release() = 0;

    virtual void    OnLostDevice()  {}
    virtual void    OnResetDevice() {}
}; //class cScene


class cSceneFactory
{
public:
    static  cScene* Logo();
    static  cScene* Title();
    static  cScene* Game();
}; //class cSceneFactory
