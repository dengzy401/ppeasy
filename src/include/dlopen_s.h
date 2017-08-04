


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if !defined(_FreeBSD_) && !defined(__DARWIN_UNIX03)
#include "malloc.h"
#endif

#if !defined(WIN32) 
#include <sys/wait.h> 
#include <dlfcn.h>
#include <sys/types.h>
#include <unistd.h>
#endif

#if defined(__DARWIN_UNIX03)
#include <CoreFoundation/CoreFoundation.h>
#ifdef __OBJC__
#include <Foundation/Foundation.h>
#endif
#endif

#include "adtypes.h"

#ifndef WIN32
#define strcmpi strcasecmp
#else

#if !defined(snprintf)
#define snprintf _snprintf
#endif
#define chdir SetCurrentDirectoryA
#endif
typedef void * DLL_HANDLE ;

static char _szErrorDLL[100];
static DLL_HANDLE  DllOpen(const char *szFile,int nOption)
{

#if defined(WIN32) || defined(_WIN32_WCE)

    DLL_HANDLE hDll = NULL ;
	#if defined(_UNICODE) || defined(UNICODE)
		LPTSTR pszTmp=0;
		int nLenWideChar;
		if(!szFile||!szFile[0])return (DLL_HANDLE)0;
		nLenWideChar=MultiByteToWideChar(CP_ACP,MB_COMPOSITE,(char*)szFile,-1,0,0);
		pszTmp=(LPTSTR)alloca((nLenWideChar+1)*2);
		if(!pszTmp)return (DLL_HANDLE)0;
		pszTmp[nLenWideChar]=0;
		MultiByteToWideChar(CP_ACP,MB_COMPOSITE,(char*)szFile,-1,pszTmp,nLenWideChar);
		hDll =  LoadLibraryEx(pszTmp,NULL,nOption);
	#else
		if(!szFile||!szFile[0])
        {
            strncpy( _szErrorDLL ,"empty file name",sizeof(_szErrorDLL));
            return (DLL_HANDLE)0;
        }
		hDll = LoadLibraryEx(szFile,NULL,nOption);
	#endif
        if( hDll == NULL )
        {
            FormatMessageA( 
                FORMAT_MESSAGE_FROM_SYSTEM | 
                FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                GetLastError(),
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                _szErrorDLL,
                sizeof(_szErrorDLL)-1,
                NULL 
                );
        }
        return  hDll ;

#else

#ifndef _NO_DLOPEN_
	if(!szFile||!szFile[0])
    {
        return (DLL_HANDLE)0;
    }
	if(nOption==0)
    {
        nOption=RTLD_NOW;
    }
	return dlopen(szFile,nOption);
#else
	return NULL;
#endif

#endif


	
}
static DLL_HANDLE  DllHandle(const char *szFile)
{
#if defined(WIN32) || defined(_WIN32_WCE)
	#if defined(_UNICODE) || defined(UNICODE)
		LPTSTR pszTmp=0;
		int nLenWideChar;
		if(!szFile||!szFile[0])return (DLL_HANDLE)0;
		nLenWideChar=MultiByteToWideChar(CP_ACP,MB_COMPOSITE,(char*)szFile,-1,0,0);
		pszTmp=(LPTSTR)alloca((nLenWideChar+1)*2);
		pszTmp[nLenWideChar]=0;
		MultiByteToWideChar(CP_ACP,MB_COMPOSITE,(char*)szFile,-1,pszTmp,nLenWideChar);
	#else
		if(!szFile||!szFile[0])return (DLL_HANDLE)0;
	#endif

	#if defined(_UNICODE) || defined(UNICODE)
			return (DLL_HANDLE)GetModuleHandle(pszTmp);
	#else
			return (DLL_HANDLE)GetModuleHandle(szFile);
	#endif

	
#else

#ifndef _NO_DLOPEN_
	if(!szFile||!szFile[0])return (DLL_HANDLE)0;
	#ifdef RTLD_NOLOAD
	return (DLL_HANDLE)dlopen(szFile,RTLD_NOLOAD);
	#else
	return (DLL_HANDLE)dlopen(szFile,RTLD_NOW);
	#endif
#else
	return 0;
#endif

#endif
}
static int   DllClose(DLL_HANDLE DlHandle)
{
	if(!DlHandle)return 0;
#if defined(WIN32) || defined(_WIN32_WCE)
	return FreeLibrary((HMODULE)DlHandle);
#else
#ifndef _NO_DLOPEN_
	return dlclose(DlHandle);
#else
	return 0;
#endif
#endif
}

static void *  DllSymbol(DLL_HANDLE DlHandle,const char *szSymbol)
{
#if defined(WIN32)

	#if defined(_WIN32_WCE) 
		LPTSTR szSymbolWide;
		int nLenWideChar;
		if(!DlHandle||!szSymbol||!szSymbol[0])return 0;
		nLenWideChar=MultiByteToWideChar(CP_ACP,MB_COMPOSITE,(char*)szSymbol,-1,0,0);
		szSymbolWide=alloca((nLenWideChar+1)*2);
		if(!szSymbolWide)return 0;
		szSymbolWide[nLenWideChar]=0;
		MultiByteToWideChar(CP_ACP,MB_COMPOSITE,(char*)szSymbol,-1,szSymbolWide,nLenWideChar);
		return GetProcAddress(DlHandle,szSymbolWide);
	#else
		if(!DlHandle||!szSymbol||!szSymbol[0])return 0;
		return GetProcAddress((HMODULE)DlHandle,szSymbol);
	#endif

	
#else

#ifndef _NO_DLOPEN_
	if(!DlHandle||!szSymbol || !szSymbol[0]) 
    {
        return 0;
    }
	return dlsym(DlHandle,szSymbol);
#else
	return 0;
#endif

#endif
	
}

static char *  DllError()
{
	static char STRNULL[]="\0";
	
#if defined(WIN32) || defined(_WIN32_WCE)

	return _szErrorDLL;
#else
#ifndef _NO_DLOPEN_
	char *szError;
	szError=(char *)dlerror();
	if(szError==0)
	{
		return STRNULL;
	}
	else
	{
		return szError;
	}
#else
	return STRNULL;
#endif

#endif

}


static const char * FileNameFromPath(const char *szFilePathName)
{
	int nLen,i;
	if(!szFilePathName||!szFilePathName[0])
	{
            return 0;
	}
	nLen=strlen(szFilePathName);
	i=nLen-1;

	for(;i>=0;i--)
	{
		if(szFilePathName[i]=='/'||szFilePathName[i]=='\\')
		{
			return szFilePathName+i+1;
		}
	}
	return szFilePathName;

}



static int  GetCurrentAppPath(char *szPath, int nLen)
{

#if defined(WIN32)
	return GetModuleFileNameA(NULL, szPath, nLen - 1);
#elif defined(__DARWIN_UNIX03)

    CFURLRef refPath = 0 ;

	if (nLen < 2)
	{
		szPath[0] = 0;
		return 0;
	}
	refPath = CFBundleCopyExecutableURL(CFBundleGetMainBundle());
	CFURLGetFileSystemRepresentation(refPath,1, (UInt8*)szPath, nLen-1 );
	CFRelease(refPath);
	
	return strlen(szPath);
#else
	char link[100];
	int nReaden = 0;
	sprintf(link, "/proc/%d/exe", getpid());/////////////
	nReaden = readlink(link, szPath, nLen - 1);//////////////
	if (nReaden < 0)
	{
		return 0;
	}
	szPath[nReaden] = 0;
	return nReaden;
#endif
}

static void  AddDllSearchPath(const char *path)
{
#if defined(WIN32)
	char DlVar[]="PATH";
#elif defined(__DARWIN_UNIX03)
	char DlVar[]="DYLD_LIBRARY_PATH";
#else
	char DlVar[] = "LD_LIBRARY_PATH";
#endif
	char szBuf[4096];
	szBuf[sizeof(szBuf)-1] = 0;
	char *envOld = getenv(DlVar);
#if defined(WIN32)
	if( envOld == NULL || envOld[0] == 0 )
	{
		snprintf(szBuf, sizeof(szBuf) - 1, "%s=%s", DlVar, path);
	}
	else
	{
		snprintf(szBuf, sizeof(szBuf) - 1, "%s=%s;%s", DlVar, path, envOld);
	}
	
#else
	if (envOld == NULL || envOld[0] == 0)
	{
		snprintf(szBuf, sizeof(szBuf) - 1, "%s=%s", DlVar, path);
	}
	else
	{
		snprintf(szBuf, sizeof(szBuf) - 1, "%s=%s:%s", DlVar, path, envOld);
	}
#endif
	putenv(szBuf);
	
}

static void  AddSearchPath(const char *path)
{
	char DlVar[] = "PATH";
	char szBuf[4096];
	szBuf[sizeof(szBuf) - 1] = 0;
	char *envOld = getenv(DlVar);
#if defined(WIN32)
	if( envOld == NULL || envOld[0] == 0 )
	{
		snprintf(szBuf, sizeof(szBuf) - 1, "%s=%s", DlVar, path);
	}
	else
	{
		snprintf(szBuf, sizeof(szBuf) - 1, "%s=%s;%s", DlVar, path, envOld);
	}
	
#else
	if (envOld == NULL || envOld[0] == 0)
	{
		snprintf(szBuf, sizeof(szBuf) - 1, "%s=%s", DlVar, path);
	}
	else
	{
		snprintf(szBuf, sizeof(szBuf) - 1, "%s=%s:%s", DlVar, path, envOld);
	}
#endif
	putenv(szBuf);
}

static int  ChopPathFileName(const char *szPath)
{
    int i;
	char *inout=(char *)szPath;
    if(!inout)return 0;
    i=strlen(inout);
    if(inout[i-1]=='\\'||inout[i-1]=='/')return 1L;
    i--;
    for(;i>-1;i--)
    {
        if(inout[i]=='\\'||inout[i]=='/')
        {
        //    ::ShowString(inout);
            inout[i+1]=0;
            return 1L;
        }
    }
    return 1L;
}

