/**
 * System Object Base Class.
 *
 * @author  무아
 * @date    2003-03-10 03:40am
 * @version 1.0
 *
 * @file    SystemObject.h
 */

#pragma once

#include "Lib/KeyCode.h"
#include "Lib/Grape.h"
#include "Lib/Melon.h"
#include "Lib/Lemon.h"


/**
 * System Object Base Class.
 * Library를 사용하는 객체는 이 클래스를 상속받으면 된다.
 */
class cSystemObject
{
public:
    cSystemObject()     {}
    ~cSystemObject()    {}

protected:
    static  HWND        m_hWnd;
    static  cInput*     m_pInput;
    static  cMedia*     m_pMedia;
    static  cGraphics*  m_pGraphic;
}; //class cSystemObject
