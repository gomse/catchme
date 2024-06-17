/**
 * 로그를 남긴다.
 *
 * @author  무아
 * @date    2004-03-28 02:33pm
 * @version 1.0
 *
 * @file    Logger.h
 */

#pragma once


class cLogger : public cSingleton<cLogger>,
                public cSystemObject
{
public:
    BOOL    Begin();
    BOOL    Write( BOOL bTime, const char* szText, ... );
    void    End();

private:
    void        Write( FILE* fp, BOOL bTime, const char* szText );
    const char* GetPlatform();
    const char* GetCurTime();
}; //class cLogger


#define g_pLogger   cLogger::GetSingletonPtr()
