/**
 * Singleton Module.
 *
 * @author  무아
 * @date    2004-03-10 04:08am
 * @version 1.0
 *
 * @file    Singleton.h
 */

#pragma once


/**
 * Singleton Base Class.
 * Singleton 객체를 만들고 싶으면 이 클래스를 상속 받으면 된다.
 */
template <typename T>
class cSingleton
{
public:
    /**
     * 생성자.
     */
    cSingleton()
    {
        ASSERT( NULL == ms_pSingleton );

        int nOffset     = (int)(T*)1 - (int)(cSingleton<T>*)(T*)1;
        ms_pSingleton   = (T*)( (int)this + nOffset );
    } //cSingleton

    /**
     * 소멸자.
     */
    ~cSingleton()
    {
        ASSERT( ms_pSingleton );

        ms_pSingleton = NULL;
    } //~cSingleton

    /**
     * Singleton 객체를 얻는다.
     */
    static T& GetSingleton()
    {
        ASSERT( ms_pSingleton );

        return *ms_pSingleton;
    } //GetSingleton

    /**
     * Singleton 객체의 포인터를 얻는다.
     */
    static T* GetSingletonPtr()
    {
        ASSERT( ms_pSingleton );

        return ms_pSingleton;
    } //GetSingletonPtr

private:
    static T*   ms_pSingleton;  ///< Singleton 객체.
}; //class cSingleton


template <typename T>
T* cSingleton<T>::ms_pSingleton = NULL;
