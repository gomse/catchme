/**
 * 로그를 남긴다.
 *
 * @author  무아
 * @date    2004-03-28 02:34pm
 * @version 1.0
 *
 * @file    Logger.cpp
 */

#include "Core.h"
#include "Logger.h"
#include <time.h>

const char  g_szLogFile[] = "catchme_log.txt";


/**
 * 로그를 시작한다.
 */
BOOL cLogger::Begin()
{
    cConfig* pConfig = cConfig::GetSingletonPtr();

    FILE* fp = fopen( g_szLogFile, "wt" );

    fprintf( fp, "CatchMe Version %0.2f\n",     pConfig->m_fVersion );
    fprintf( fp, "Date/Time : %s\n",            GetCurTime() );
    fprintf( fp, "OS : \"%s\".\n",              GetPlatform() );
    fprintf( fp, "Game directory is \"%s\".\n", pConfig->m_strGamePath.c_str() );

    fclose( fp );

    return TRUE;
}

/**
 * 로그를 끝낸다.
 */
void cLogger::End()
{
    FILE* fp = fopen( g_szLogFile, "a" );
    fprintf( fp, "Cleanup.\n" );
    fclose( fp );
}

/**
 * 로그를 남긴다.
 */
BOOL cLogger::Write( BOOL bTime, const char* szText, ... )
{
    char szBuffer[255];

    va_list va;
    va_start( va, szText );
    vsprintf( szBuffer, szText, va );
    va_end( va );

    FILE* fp = fopen( g_szLogFile, "a" );

    if( fp != NULL )
    {
        Write( fp, bTime, szBuffer );
        fclose( fp );

        return TRUE;
    } //if

    return FALSE;
}

/**
 *
 */
void cLogger::Write( FILE* fp, BOOL bTime, const char* szText )
{
    std::string strText = szText;

    if( bTime )
    {
        strText += " [";
        strText += GetCurTime();
        strText += "]";
    } //if

    fprintf( fp, " %s", strText.c_str() );
}

/**
 * 현재 날짜와 시간을 얻는다.
 */
const char* cLogger::GetCurTime()
{
    static char result[255];
    struct tm   when;
    time_t      now;

    time( &now );

    when = *localtime( &now );

    sprintf(
        result,
        "%04d/%02d/%02d, %02d:%02d:%02d",
        ( when.tm_year + 1900 ),
        ( when.tm_mon + 1 ),
        when.tm_mday,
        when.tm_hour,
        when.tm_min,
        when.tm_sec
        );

    return result;
}

/**
 * OS의 버젼을 얻는다.
 */
const char* cLogger::GetPlatform()
{
    static std::string  strPlatform = "Unknown";
    OSVERSIONINFOEX     osvi;

    ZeroMemory( &osvi, sizeof( OSVERSIONINFOEX ) );

    osvi.dwOSVersionInfoSize = sizeof( OSVERSIONINFOEX );

    if( !GetVersionEx( (OSVERSIONINFO*)&osvi ) )
    {
        osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);

        if( !GetVersionEx( (OSVERSIONINFO*)&osvi ) )
        {
            return strPlatform.c_str();
        } //if
    } //if

    switch( osvi.dwPlatformId )
    {
    // Test for the Windows NT product family.
    case VER_PLATFORM_WIN32_NT:
        if( osvi.dwMajorVersion == 5 )
        {
            switch( osvi.dwMinorVersion )
            {
            case 2:
                strPlatform = "Microsoft Windows Server 2003 family";
                break;
            case 1:
                strPlatform = "Microsoft Windows XP";
                break;
            case 0:
                strPlatform = "Microsoft Windows 2000";
                break;
            } //switch
        }
        else if( osvi.dwMajorVersion <= 4 )
        {
            strPlatform = "Microsoft Windows NT";
        } //if..else if
        break;

    // Test for the Windows 95 product family.
    case VER_PLATFORM_WIN32_WINDOWS:
        if( osvi.dwMajorVersion == 4 )
        {
            switch( osvi.dwMinorVersion )
            {
            case 0:
                strPlatform = "Microsoft Windows 95";

                if( osvi.szCSDVersion[1] == 'C' || osvi.szCSDVersion[1] == 'B' )
                {
                    strPlatform += " OSR2";
                } //if
                break;

            case 10:
                strPlatform = "Microsoft Windows 98";

                if( osvi.szCSDVersion[1] == 'A' )
                {
                    strPlatform += " SE";
                } //if
                break;

            case 90:
                strPlatform = "Microsoft Windows Millennium Edition";
                break;
            } //switch
        } //if
        break;

    case VER_PLATFORM_WIN32s:
        strPlatform = "Microsoft Win32s";
        break;

    default:
        strPlatform = "Unknown";
        break;
    } //switch

    return strPlatform.c_str();
}
