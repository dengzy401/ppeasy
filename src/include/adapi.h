

/* this is advanced  cross-platform  API  ,support 		*/
/* normal File ,	ini file read and write				*/
/* string ,Queue mutex ,thread pool, memory file ,		*/
/* BFS file(is very large Support TB) ,					*/
/* auto io(integrate with normal File, memory file and  */
/* BFS file), hardware infomation(MAC address           */
/* ,harddisk serial number), and some encrypt methods   */
/* sunch as MD5 base64 ....								*/
/********************************************************/
/************* windows/wince/unix/linux	*****************/
/**************author : f117cdh**************************/
/**************e-mail: f117cdh@gmail.com ****************/
/***********bugs report: f117cdh@gmail.com **************/
/********************************************************/
#ifndef _ADAPI_H_
#define _ADAPI_H_



#if  defined(_WIN32_WCE) /* win32 ce */
    #include <windows.h>
    #define snprintf (_snprintf)
    #define FILE_IO_ERR  INVALID_HANDLE_VALUE
    #define FILE_HANDLE_INVALID  INVALID_HANDLE_VALUE
    typedef HANDLE    FILE_HANDLE;
	typedef __int64    INT_FILE;
	typedef HINSTANCE DLL_HANDLE;
	typedef DWORD INT_THREADID;
	typedef const unsigned short *PAUTOCHAR;
#elif defined(WIN32) /* windows */
	#include <windows.h>
#ifndef snprintf
	#define snprintf (_snprintf)
#endif
    #define FILE_IO_ERR  INVALID_HANDLE_VALUE
    #define FILE_HANDLE_INVALID  INVALID_HANDLE_VALUE
    typedef HANDLE    FILE_HANDLE;
	typedef __int64    INT_FILE;
	typedef const char *PAUTOCHAR;
	typedef HINSTANCE DLL_HANDLE;
	typedef UINT64 INT_THREADID;
#else

	typedef const char *PAUTOCHAR;
    #define FILE_IO_ERR  -1
    #define FILE_HANDLE_INVALID -1
    typedef int    FILE_HANDLE;
	typedef long long    INT_FILE;
	typedef void * DLL_HANDLE;
	typedef UINT64 INT_THREADID;
#endif

#ifndef _ADTYPES_H_
#include "adtypes.h"
#endif

#ifndef _BFS_TYPE
#define _BFS_TYPE
    typedef void * BFS_HANDLE;
	#if defined(WIN32)
		typedef __int64 BFS_DSK_INT;
		typedef unsigned __int64 BFS_DSK_UINT;
	#else
		typedef long long BFS_DSK_INT;
		typedef unsigned  long long BFS_DSK_UINT;
	#endif
#define BFS_INVALID_DSK_PTR ((BFS_DSK_INT)-1)

#define BFS_OPERATOR_UNLOCK		0
#define BFS_OPERATOR_WRITING	1
#define BFS_OPERATOR_READING	2
#define BFS_OPERATOR_SEEKING	3
#define BFS_ERROR_OPENFILE		-1
#define BFS_ERROR_WRITE			-2
#define BFS_ERROR_READ			-3
#define BFS_ERROR_SEEK			-4
#define BFS_ERROR_NOT_SUPPORT	-5

#endif

#if !defined(_MF_TYPE)
#define _MF_TYPE
		typedef void * MF_HANDLE;
#endif


#if !defined(_AUTO_IO)
#define _AUTO_IO
typedef void * IO_HANDLE;
#define IO_TYPE_FILE			0
#define IO_TYPE_BFS				1
#define IO_TYPE_MF				2
#define IO_TYPE_FILE_CACHE		3

#define IO_OPT_LINE_CACHE(x)        ((void *)x)
#define IO_OPT_MF_HANDLE(hMf)        ((void *)hMf)
#define IO_OPT_BFS_BLK(blksize)        ((void *)blksize)
#define IO_HANDLE_COPY(hIo,nType)     (IoHandelCopy(((IO_HANDLE)alloca( IoHandleSize((hIo)) )),(hIo),(nType)))

#endif



#ifndef OX_RDONLY
#define OX_RDONLY       0x0000  /* open for reading only */
#define OX_WRONLY       0x0001  /* open for writing only */
#define OX_RDWR         0x0002  /* open for reading and writing */
#define OX_APPEND       0x0008  /* writes done at eof */

#define OX_CREAT        0x0100  /* create and open file */
#define OX_TRUNC        0x0200  /* open and truncate */
#define OX_EXCL         0x0400  /* open only if file doesn't already exist */
#endif

#if !defined(_INT_IO)
#define _INT_IO
#if defined(WIN32)
	typedef __int64 INT_IO;
	typedef unsigned __int64 UINT_IO;
#else
	typedef long long INT_IO;
	typedef unsigned  long long UINT_IO;
#endif
#endif

#if !defined(_INI_ERROR)
#define _INI_ERROR
#define INI_ERROR_VARNOTFIND -1
#define INI_ERROR_SECTION_NOTFIND -2
#define INI_ERROR_FILEOPEN	-3

#endif

#if !defined(_QUEUE_TYPE)
#define _QUEUE_TYPE
typedef void * QUEUE_HANDLE;
#define QUEUE_ERROR_OK	0
#define QUEUE_ERROR_INVALID_PARAMETER	-1
#define QUEUE_ERROR_TIMEOUT	-2
#define QUEUE_ERROR_FULL	-3
#define QUEUE_ERROR_CANCEL_BYUSER	-4
#define QUEUE_ERROR_USED	-5
#define _WAIT_TIMEOUT	-1
#define _WAIT_ERROR		-2
#define _WAIT_CANCEL	-3
#define _WAIT_OK		0
#endif

#if !defined(_OS_TYPE_UNKNOWN)
#define _OS_TYPE_UNKNOWN	0
#define _OS_TYPE_WINCE		10
#define _OS_TYPE_WINDOWS	20
#define _OS_TYPE_UNIX		50
#endif



#if !defined(_LOG_LEVEL_FATAL)
    #define _LOG_LEVEL_BACKTRACE	-1
	#define _LOG_LEVEL_FATAL		0
	#define _LOG_LEVEL_ERROR		1
	#define _LOG_LEVEL_WARNING		2
	#define _LOG_LEVEL_INFO			3
	#define _LOG_LEVEL_DEBUG		4
	#define _LOG_LEVEL_DETAIL	    5
	typedef void   ( *_LogLevel)(int nLevel,const char *fmt, ...);
#endif

#if !defined(_TH_POOL_)
#define   _TH_POOL_      1
	#define _THPOOL_ERROR		-1
	#define _THPOOL_EMPTY		-2
	#define _THPOOL_FULL		-3
	#define _THPOOL_EXIT		-4
	#define _THPOOL_OK			0

	typedef void * THPOOL_HANDLE;

	#define  _THPOOL_OPT_USEPOOLONLY	0x00000001

#endif

#if !defined(_LOGIN_OK_)
#define _LOGIN_SYS_ERROR_		-1
#define _LOGIN_OK_				0
#define _LOGIN_NO_USER_			1
#define _LOGIN_PWD_ERROR_		2
#endif


#if !defined(_TIME_TYPES_)
#define _TIME_TYPES_		1
typedef   INT64    TIME_T;
#endif


#ifndef _DB_EXT_
#define _DB_EXT_
#define LEN_DB_HOST    80
#define LEN_DB_USER        40
#define LEN_DB_PASS    40
#define LEN_DB_DATABASE    100
#define LEN_DB_EXTRA    100
typedef struct tagDATABASE_INI
{
	char        szHost[LEN_DB_HOST];
	char        szUser[LEN_DB_USER];
	char        szPass[LEN_DB_PASS];
	char        szDatabase[LEN_DB_DATABASE];
	char		szExtra[LEN_DB_EXTRA];
	int         nPort;
	unsigned int nTimeOut;
}DATABASE_INI,*PDATABASE_INI;
#endif


#ifndef _BMPFILE_HEADER_LEN
#define _BMPFILE_HEADER_LEN 54
#endif
#ifndef _BMPINFOHEADER_
#define _BMPINFOHEADER_

typedef enum tagRetBmpZoom
{
    BmpZoomOK,
    BmpZoomNoRequire ,
    BmpZoomErrorIOSrc ,
    BmpZoomErrorIODest ,
    BmpZoomErrorFail ,
    BmpZoomErrorNoMem ,
}RetBmpZoom;

typedef struct tagBMPINFOHEADER {
    char    bfType[4];
    DWORD   bfSize;
    DWORD   bfReserved1;
    DWORD   bfOffBits;

    DWORD  biSize;
    LONG   biWidth;
    LONG   biHeight;
    WORD   biPlanes;
    WORD   biBitCount;
    DWORD  biCompression;
    DWORD  biSizeImage;
    LONG   biXPelsPerMeter;
    LONG   biYPelsPerMeter;
    DWORD  biClrUsed;
    DWORD  biClrImportant;
    int   nPaletteCount;

} BMPINFOHEADER;

#pragma pack(1)
typedef struct tagBMPINFOHEADER_RAW {
    char    bfType[2];
    DWORD   bfSize;
    DWORD   bfReserved1;
    DWORD   bfOffBits;

    DWORD  biSize;
    LONG   biWidth;
    LONG   biHeight;
    WORD   biPlanes;
    WORD   biBitCount;
    DWORD  biCompression;
    DWORD  biSizeImage;
    LONG   biXPelsPerMeter;
    LONG   biYPelsPerMeter;
    DWORD  biClrUsed;
    DWORD  biClrImportant;
} BMPINFOHEADER_RAW;
#pragma pack()
#endif

#ifndef _RGB_COLOR_
#define _RGB_COLOR_
typedef struct tagRGB_COLOR {
    BYTE    rgbRed;
    BYTE    rgbGreen;
    BYTE    rgbBlue;
    BYTE    rgbReserved;
} RGB_COLOR,*PRGB_COLOR;
#endif

#ifndef _FILE_STATXX_
#define _FILE_STATXX_
typedef struct tagFILE_STATX
{
    SYSTEMTIME	tLstModify;
    INT_FILE	nFileLength;
}FILE_STATX,*PFILE_STATX;
#endif


#ifndef _LIST_ITEM_
#define _LIST_ITEM_
typedef struct tagLIST_ITEM
{
    struct tagLIST_ITEM *next;
    struct tagLIST_ITEM *prev;

}LIST_ITEM,*PLIST_ITEM;
#endif

#ifndef _Convert2TxtItem_
    #define _Convert2TxtItem_(ptr) ((TXT_ITEM *)((char *)(ptr)-(unsigned long)(&((TXT_ITEM *)0)->item)))

    typedef struct tagTXT_ITEM
    {
        LIST_ITEM item;
        char *szTxt;
        int nLen ;
    }TXT_ITEM;

#endif

#ifndef _MTX_OBJ_
#define _MTX_OBJ_

#ifdef WIN32
	typedef CRITICAL_SECTION MTX_OBJ;
	#define   _MTX_OBJ_DEF
#else
    #if defined(_PTHREAD_H) || defined(_PTHREAD_H_)
    typedef pthread_mutex_t  MTX_OBJ;
    #define   _MTX_OBJ_DEF
    #endif
#endif


#define  _MTX_OPT_FAST          0x01
#define  _MTX_OPT_RECURSIVE     0x02
#define  _MTX_OPT_ERRORCHECK    0x04

typedef void *HEVWAIT;

typedef enum tagEvWaitResult
{
	EvWaitResultError = -1,
	EvWaitResultOk,
	EvWaitResultTimeout,
	

}EvWaitResult;


typedef void * MemoryBuffer2Handle;

#endif

/********************structs define*******************************************/
#ifndef _AUTH_PLS_
#define _AUTH_PLS_
#define LEN_AUTH_NAME 50

typedef int ( *_UserInit)();
typedef int ( *_UserLogin)(const char *szUser,const char *szPass,int nUserType,void *ExtData);
typedef struct tagAUTH_PLUGIN
{
	DLL_HANDLE hPlugin;
	_UserLogin UserLogin;
	struct tagAUTH_PLUGIN *next;
	char szPluginName[LEN_AUTH_NAME];
}AUTH_PLUGIN,*PAUTH_PLUGIN;


typedef struct tagAUTH_USER
{
	const char *szUser;
	const char *szPwd;
	struct tagAUTH_USER *next;
}AUTH_USER, *PAUTH_USER;
#endif

#if !defined(TAG_FILE_SEARCH)
#define TAG_FILE_SEARCH
typedef struct tagFILE_SEARCH
{
    char    *szFileName;
    INT_FILE     nDataFindedPointer;//out
    int     nLow;
    int     nHigh;
    int     nBlockSize;
    void    *DataWillFind;
    int     nDataWillFindOffset;
    void    *UserData;
    void    *FuncCmp;
    void    *ReadBuf;
    int     nReadBufSize;

}FILE_SEARCH;
typedef int (MYAPI *_FileSearchCallBack)(FILE_SEARCH *pSC);
#endif

#define _PROGRESS_STATUS_START		0
#define _PROGRESS_STATUS_ING		1
#define _PROGRESS_STATUS_END		2
typedef int (MYAPI * _QsortExComp)(  void *a,  void * b,void *vUserData);
typedef int (MYAPI * _DeleteFileNotifyCallBack)( const char *szPathFull,const char *szName,int IsFile,unsigned int ExtWinUnix, void *UserData);
typedef int (MYAPI *_ServiceEventCall)(int nEvent ,const char *szInfo);
typedef unsigned int (MYAPI *_ThreadProc)(void *vData);
typedef int (MYAPI *_FileCopyProgress)(INT_FILE nCurPos,INT_FILE nLength,int nStatus,void *vData);

typedef void* (MYAPI *_ThreadCreateJavaCtx)(const char *threadName);
typedef void  (MYAPI *_ThreadDestroyJavaCtx)(void * ctx);
#define WaitCondition(condition)  while( !(condition) ){SleepMilli(10);}
/************MYAPI.h Copyright cdh 2005*****************/
#ifdef __cplusplus
extern "C"
{
#endif

typedef int ( *__LogPrintFunc)( int prio, const char *tag,const char *fmt, va_list ap );
typedef void* (*__malloc)( size_t size );
typedef void (*__free)( void *memblock );

void MYAPI SetLogPrint( __LogPrintFunc func );
int  LogPrint(int prio, const char *tag,  const char *fmt, ...);
int  VLogPrint(int prio, const char *tag,  const char *fmt, va_list ap );

const char * MYAPI LogLevelStr(int nLevel);
char * MYAPI GetAdapiError();
int MYAPI ClearAdapiError();
int MYAPI OS_Type();

void   MYAPI ThreadSetJavaCtxFunc(_ThreadCreateJavaCtx createJavaCtx , _ThreadDestroyJavaCtx destroyJavaCtx);
void * MYAPI ThreadCreateJavaCtx(const char *threadName);
void   MYAPI ThreadDestroyJavaCtx(void * ctx);
    
BOOL MYAPI CpuId(char *szId, int nLen);
int MYAPI CpuCoreNumber();
BOOL MYAPI IsBigEndian();
int MYAPI AlignLength( int Size ,int Align  );
INT16 MYAPI htole_16( INT16 s16 );
INT16 MYAPI letoh_16( INT16 s16 );
INT32 MYAPI htole_32( INT32 s32 );
INT32 MYAPI letoh_32( INT32 s32 );
INT64 MYAPI letoh_64( INT64 s64 );
INT64 MYAPI htole_64( INT64 s64 );

int MYAPI CharPosInStr(char Sig,const char *Str);
char MYAPI CharIsInRange(char cValue,char cStart,char cEnd);
int MYAPI ChopPathFileName(const char *inout);
char * MYAPI UpLevelPath(const char *szPath);
char*   MYAPI  StrTrimLeft(char *str);
char*   MYAPI StrTrimRight(char *szBuf);
char*   MYAPI  StrTrimX(const char *str);
int MYAPI PathAddSlash(const  char *inout);
int MYAPI PathAddSlashEx(const char *szDir,int nOsType);
const char *MYAPI FileNameExt(const char *szFileName);
const char *MYAPI FileNameFromPath(const char *szFilePathName);

void MYAPI RemoveStr(char *szSrc,int iStart,int iEnd);
int MYAPI HttpReplyCode(const char *szHead);
int MYAPI TruncateStringRight(char *in,int n);
char * MYAPI WeekToStr(    int week,char *out);
char * MYAPI MonthToStr(int month,char *out);
int MYAPI StrMonthToNumber(const char *month);
int MYAPI atoix(const char *szValue);
INT64 MYAPI atoi64x(const char *szValue);
int MYAPI atoin( const char *szValue ,int nCount);
int MYAPI GetIpPort(const char *szAddr,char *szIPOut,int nIpSize,int *nPortOut);
char * MYAPI StrUpper(const char *buf);
char * MYAPI StrLower(const char *buf);
int MYAPI RandomEx(int Start,int End);
int MYAPI strcatn(char *src,const char *dest,int lensrc);
int MYAPI GetHostFromUrl(char *szHost,int Size,const char *szUrl,int *portOut);
int MYAPI SwapByteOrder(void *pData,int Size);
int MYAPI ExeProg(const char *szApplacation,const char *szCmdLine);
int MYAPI strncmpix(const char *szSource,const char *szDest,int nSize);
int MYAPI strcmpix(const char *szSource,const char *szDest);
int MYAPI strcmpifind(const char *szSource,const char *szDest);
int MYAPI strcmpifind_from_end(const char *szSource,const char *szDest,
							   const void *pHeadPoint);
int MYAPI strcmpipre(const char *szSourceLong,const char *szDestShort);
int MYAPI strcmppre(const char *szSourceLong, const char *szDestShort);
char * MYAPI strcpyn(char *szDest,const char *szSource,int nSize);
char *  MYAPI strcpyx(char * szDest,const char *szSource);
int MYAPI strlenx(const char *s);
int MYAPI strlenxW(const WCHAR *s);
WCHAR * MYAPI strcpyFromChar(WCHAR *buf ,const char * szA, int nLen);
char * MYAPI strcpyFromWChar(char *buf ,const WCHAR * szW, int nLen);
int MYAPI strlenex(const char *s,const char *szStop);
int MYAPI strcmpi_stop(const char *szSource,
                        const char *szDest,
                        char *szStop);
int MYAPI strcmpi_endrange(const char *szSource,
                        const char *szDest,
                        char cStart,
                        char cEnd);
int MYAPI strcpyn_stop(char * szDest, const char *szSource,int nDestSize,const char *szStop);
int MYAPI strcpyn_visual(char *szDest,int nDestSize,
                         const char *szSource,const char *szStop,
                         int    *pCmped);
int MYAPI strcpyn_number(char * szDest,const char *szSource,int nLen);
int MYAPI strcmpipre_ncmped(const char *szSource,const char *szDest,int *pnCmped);
int MYAPI strcmpipre_skipunvisual(const char *szSource,const char *szDest);
void MYAPI InsertStr(char *szSrc,int nLenSrc,int iWhereInsert,const char *szInsertStr);
int MYAPI ReplaceChar(char *src,const char *szCharList,char cValue);
int MYAPI ReplaceStrToChar(char *szSrc,  const char *szWillReplace,char cValue);
int MYAPI wstrlenx(const wchar_t *szBuf);
int MYAPI UnicodeToUTF8(const wchar_t *wszIn, char *szUTF8Out,int vLen);
int MYAPI UTF8ToUnicode(const char *szUtf8, wchar_t * szUnicode,int nLen);
int MYAPI UrlEncode(const char *szUrl,char *szUrlOut,int nLen);
BOOL  MYAPI IsTextUTF8(const char* str,int length) ;


int MYAPI BinSearchFromFile( FILE_SEARCH *pSC, _FileSearchCallBack BinFindCallBack );
double MYAPI ExpressionResult(const char *szExp,char *szErrOut,int nErrSize);
int MYAPI GetValueFromString(const char *szSource, const char *szVarName,
							 char *szVarValue,int  nVarValueSize,
							 const char *szEqual,const char *szStopSig);
BOOL MYAPI Str2Bool(const char *szValue);


#ifndef _ADAPI_NO_THREAD_FUNC_
void * MYAPI Thread2CreateEx(void *RoutineProc, void *vParameter,   void *vThreadId,unsigned int nStackSize,
    int nSchedType,int nPriority);
void * MYAPI Thread2Create(void *RoutineProc, void *vParameter,   INT_THREADID *vThreadId,unsigned int nStackSize ,BOOL bJoin);
void MYAPI Thread2Exit(void * nExitCode);
BOOL MYAPI Thread2IsValid(void * handle);
void MYAPI Thread2Close(void * handle);
INT_THREADID MYAPI Thread2GetID();
unsigned int MYAPI Thread2GetIdNumber();
void MYAPI Thread2WaitForExit( void *handle );
#endif


int MYAPI EnumLogicalDrives(_DeleteFileNotifyCallBack DeleteFileNotifyCallBack,
							void *UserData,int *pIsStop);
unsigned char MYAPI Swap4Bit(unsigned char cValue);
BOOL MYAPI RemoveFileX(const char *szFilePath);
int MYAPI RemoveDirX(const char *szFolderPath);
int MYAPI RemoveDirRecur(const char *szFolderPath,
						 _DeleteFileNotifyCallBack DeleteFileNotifyCallBack,
						 void *UserData,int *pIsStop);
BOOL MYAPI MakeDirX(const char *szFolderPath);
int MYAPI MakeDirRecur(const char *szFolderPath, char *szNewPathOut);
int MYAPI LogFileX(const char *Path,const char *fmt, ...);

INT_FILE MYAPI FileLength(const char *szFile);
int MYAPI FileReadEx(const char *szFile,INT_FILE nSeek,void *buf,unsigned int nBufSize);
int MYAPI FileWriteEx(const char *szFile,INT_FILE nSeek,const void *buf,unsigned int nBufSize);
int MYAPI FileOverWriteX(const char *szFile,const void *buf,int nBufSize);
char MYAPI FileGetChar(FILE_HANDLE hFile,BOOL *IsFileEnd);
FILE_HANDLE MYAPI FileOpenXX(const char *szFile,int nMode);
FILE_HANDLE  MYAPI FileOpenXX2(const char *szFile,int nMode);
int MYAPI FileReadXX(FILE_HANDLE hFile,void *Buf,unsigned int nBufSize);
int MYAPI FileReadXXLoop(FILE_HANDLE hFile,void *Buf,unsigned int nBufSize);
int MYAPI FileReadLineXX(FILE_HANDLE hFile,void *Buf,int nBufSize,BOOL *pIsEnd,BOOL *pIsLineEnd);
int MYAPI FileWriteXX(FILE_HANDLE hFile,const void *Buf,unsigned int nBufSize);
int MYAPI FileWriteXXLoop(FILE_HANDLE hFile,const void *Buf, unsigned int nBufSize);
INT_FILE MYAPI FileSeekXX(FILE_HANDLE hFile,INT_FILE nOffSet,int nSet);
int MYAPI FileCloseXX(FILE_HANDLE hFile);
BOOL MYAPI FileTruncateXX(FILE_HANDLE hFile,INT_FILE length );
BOOL MYAPI FileSyncXX( FILE_HANDLE hFile );
void MYAPI FileSetAutoSync(BOOL bAutoSync);
BOOL MYAPI PathIsDirectoryX(const char *szPath);
int MYAPI PathIsDirOrFileX(const char *szFile);
BOOL MYAPI PathIsFileX(const char *szFile);
BOOL MYAPI FileSatusUTC(const char *szFile,PFILE_STATX pStatusFile);
BOOL MYAPI FileSetLstModifyTime(const char *szFile,const SYSTEMTIME *pSysTime,BOOL bLocalTime);
BOOL MYAPI FileMoveX(const char *szFileSrc,const char *szFileDest);
BOOL MYAPI FileCopyXX(const char *szFileSrc,const char *szFileDest,_FileCopyProgress funcCall,void *vUserData);

void MYAPI SleepMicro(unsigned int us);
void  MYAPI SleepMilli(unsigned int nTime);
char MYAPI GetBase64Char(int index);
signed char  MYAPI GetBase64Index( unsigned char ch);
int MYAPI Base64Encode(const void * vData, int nDataLen,char * szB64Out, int nB64BufLen);
int MYAPI Base64Encode72PerLine(const void * vData, int nDataLen,
                        char * szB64Out, int nB64BufLen) ;
int MYAPI Base64Decode(const char * szCode, void * vDataOut, int nDataBufLen);
int MYAPI Base64DecodeEx(const char * szCode,char *szStopCharList,
                        void * vDataOut, int nDataBufLen) ;

int MYAPI  Base64ExEncode(const void * vData, int nDataLen,
						  char * szB64Out, int nB64BufLen);
int  MYAPI Base64ExDecode(const char * szCode, void * vDataOut, int nDataBufLen);
int  MYAPI Base64ExDecodeEx(const char * szCode,char *szStopCharList,
							 void * vDataOut, int nDataBufLen);



int MYAPI GetIDESerialNumber(char *szOut ,int nSize,int index);
int  MYAPI GetMacAddress(char *szMacOut , int nSize ,const char *szSplit,const char *szEthName );


int MYAPI DateGetMonthDays(int nMonth,int nYear);
int MYAPI DateSubMonth(int *pYear,int *pMonth,int *pDay,int nSubMonth);
int MYAPI DateAddMonth(int *pYear,int *pMonth,int *pDay,int nAddMonth);
int MYAPI DateSubDay(int *pYear,int *pMonth,int *pDay,int nSubDay);
int MYAPI DateAddDay(int *pYear,int *pMonth,int *pDay,int nAddDay);
char * MYAPI DateTimeNowStr(char *out22len,BOOL bUTC,BOOL IsSplit);
char * MYAPI Systime2Str(const SYSTEMTIME *systime, char *out22len,BOOL IsSplit);
char * MYAPI Systime2HttpDate( const SYSTEMTIME *systime, char *out30len );
char * MYAPI Systime2HttpCookieDate(const SYSTEMTIME *systime, char *out30len);

SYSTEMTIME *MYAPI HttpDate2Systime( const char *szDate, SYSTEMTIME *systime );
SYSTEMTIME *MYAPI SystemTime( SYSTEMTIME *pSysTime, BOOL bUTC );
int MYAPI StrWeekToNumber( const char *week );
TIME_T MYAPI OSUptime();
TIME_T MYAPI OSUptimeMilli();
TIME_T MYAPI OSTickCount();
TIME_T MYAPI OSUptimeMilliEx();
int MYAPI WeekDay();
int MYAPI SecondsFromMidNight();

#if defined( _INC_TIME ) || defined(_LINUX_TIME_H) ||  defined(_TIME_H) ||  defined(_TIME_H_)
SYSTEMTIME * MYAPI time_t2SystemTime(time_t tm1, SYSTEMTIME *pSysTime);
SYSTEMTIME * MYAPI tm2SystemTime(const struct tm *pTm,SYSTEMTIME *pSysTime);
struct tm * MYAPI SystemTime2tm(const SYSTEMTIME *pSysTime,struct tm *pTm);
SYSTEMTIME * MYAPI SystemTimeAddWeek(SYSTEMTIME *pSysTime);
time_t MYAPI SystemTime2time_t(const SYSTEMTIME *pSysTime);
time_t MYAPI time_t2Local(time_t tSysTime);
char * MYAPI time_t2Str(time_t tToday,char *out22len,BOOL bUTC,BOOL IsSplit);

#endif
int MYAPI TimeStr2Seconds(const char *szTime);
const char * MYAPI Seconds2TimeStr(int nSecondsIn,char *szBuf,int nLen,BOOL bSplit);
BOOL MYAPI SystemTimeSet( const SYSTEMTIME *pSysTime, BOOL bUTC );
SYSTEMTIME * MYAPI DateTimeStr2SystemTime(const char *szTime, SYSTEMTIME *pSysTime,BOOL *pbSuccess);
int MYAPI SystemTimeCompare(const SYSTEMTIME *pSysTime,const SYSTEMTIME *pSysTime2);

int MYAPI IniWriteMapValue(const char *section,const char *var,
                          char **pMapStr,int nCount,const int *pMapValue,int nValue,
                          const char * iniFile);
int MYAPI IniReadMapValue(const char *section,const char *var,
                          char **pMapStr,int nCount,const int *pMapValue,
                          const char * iniFile);
int MYAPI IniWriteInt(const char *section,const char *var,int nValue,const char * iniFile);
int MYAPI IniWriteIndex(const char *section,int index,const char *szValue,const char * iniFile);
int MYAPI IniReadIndex(const char *section,int nIndex,char *outValue,int size,const char * iniFile);
double MYAPI IniReadFloat(const char *section,const char *var,const char * iniFile,double nDefaultValue);
int MYAPI IniReadStr(const char *section,const char *var,char *outValue,int size,const char * iniFile);
BOOL  MYAPI IniReadBool(const char *section,const char *var,const char * iniFile,int nDefaultValue);
int MYAPI IniReadInt(const char *section,const char *var,const char * iniFile,int nDefaultValue);
int MYAPI IniWrite(const char *section,const char *var,const char *szValue,const char * iniFile);
int MYAPI IniRead(const char *section,const char *var,char *outValue,int size,const char * iniFile);
BOOL MYAPI IniReadRgbColor(const char *section,const char *var,PRGB_COLOR pRgb,const char * iniFile);
void  MYAPI QsortEx(void *base,unsigned int  num,unsigned int  width,void *userData,void * pfuncCmp/*_QsortExComp*/);
int MYAPI GetSHA1(const void *pData ,int nDataLen,unsigned char *szSHA1Out,int nSHA1OutLen20);
int MYAPI GetMD5(const void *pData ,int nDataLen,char *szMd5Out,int nMd5OutLen);
int MYAPI GetMD5File(const char *szFile,char *szMd5Out,int nMd5OutLen);
INT64 MYAPI GetDiskFreeSpaceX(const char *szPath, INT64 * pnTotal );
/*******************************************/
int  MYAPI TransHex2Data(const char * szData,void *vData,int nLen);
int MYAPI TransData2Hex(const void *vData ,int nDataLen,
							 char *szCodeOut ,int nOutLen);
UINT64  MYAPI HexToUINT64(const char *dest);
UINT32  MYAPI HexToUINT32(const char *dest);
UINT16  MYAPI HexToUINT16(const char *szDest);
UINT8  MYAPI HexToUINT8(const char *szDest);

BFS_HANDLE  MYAPI BFSOpen(const char *szDir,int nMode);
BFS_HANDLE  MYAPI BFSOpenEx(const char *szDir,int nMode,unsigned int nBlockSize);
int MYAPI BFSCloseEx(BFS_HANDLE *phBfs);
int MYAPI BFSClose(BFS_HANDLE hBfs);
int MYAPI BFSRead(BFS_HANDLE hBfs,void *Buf,unsigned int nBufSize);
int MYAPI BFSWrite(BFS_HANDLE hBfs,const void *Buf,unsigned int nBufSize);
BFS_DSK_INT MYAPI BFSSeek(BFS_HANDLE hBfs,BFS_DSK_INT nOffSet,int nSet);
FILE_HANDLE  MYAPI BFSOpenBlock(BFS_HANDLE hBfs,unsigned int nBlock,int nMode);


QUEUE_HANDLE MYAPI QueueAlloc(const unsigned int nMaxQueue, BOOL bNoQueue);
int MYAPI QueueFree(QUEUE_HANDLE pQueueHandle,int IsForce);
void * MYAPI QueueGetUserData(QUEUE_HANDLE pQueue);
void MYAPI QueueSetUserData(QUEUE_HANDLE pQueue,void *UserData);
unsigned int MYAPI QueueCurLength(QUEUE_HANDLE pQueue);
const char * MYAPI QueueErrorTxt(QUEUE_HANDLE pQueueHandle);
int MYAPI QueueErrorCode(QUEUE_HANDLE pQueueHandle);
int MYAPI QueueWaitLock(QUEUE_HANDLE pQueueHandle,unsigned int nWaitTime);
int MYAPI QueueWaitLockEx(QUEUE_HANDLE pQueueHandle,unsigned int nWaitTime,int *pIsStop);
void MYAPI QueueUnlock(QUEUE_HANDLE pQueueHandle);
int MYAPI QueueHandleSize();
QUEUE_HANDLE MYAPI QueueInit(void *pHandleMem,const unsigned int nMaxQueue, BOOL bNoQueue);
const char * MYAPI QueueErrStr(int nErrorCode);
int MYAPI QueueLogFileX(QUEUE_HANDLE pQueueHandle,unsigned int nWaitTime,
						const char *Path,const char *fmt,...);
int MYAPI WaitConditionEqual(int *pCondition,int nValue,unsigned int nWaitTime,int *IsStop);
int MYAPI WaitConditionNoEqual(int *pCondition,int nValue,unsigned int nWaitTime,int *IsStop);
IO_HANDLE MYAPI IoOpen(const char *szFile,int nFileOpenMode,int nIoType,void * vOption);
int MYAPI IoCloseEx(IO_HANDLE *phIo);
int MYAPI IoClose(IO_HANDLE hIo);
void * MYAPI IoGetUserData(IO_HANDLE hIo);
void MYAPI IoSetUserData(IO_HANDLE hIo,void *UserData);
int MYAPI IoRead(IO_HANDLE hIo,void *Buf,unsigned int nBufSize);
int MYAPI IoReadLine(IO_HANDLE hIo,void *Buf,unsigned int nBufSize,BOOL *pIsLineEnd);
int MYAPI IoReadLineEx(IO_HANDLE hIo,void *Buf,unsigned int nBufSize);
int MYAPI  IoWrite(IO_HANDLE hIo,const void *Buf,unsigned int nBufSize);
INT_IO MYAPI IoSeek(IO_HANDLE hIo, INT_IO nOffSet,int nSet);
void * MYAPI IoTypeHandle(IO_HANDLE hIo);
int MYAPI IoType(IO_HANDLE hIo);
int MYAPI IoHandleSize(IO_HANDLE hIo);
int MYAPI IoShutdown( IO_HANDLE hIo );
IO_HANDLE MYAPI IoHandelCopy(void * hIoMem,IO_HANDLE hIoSrc,int nFileOpenMode);


int MYAPI GetCurrentAppPath(char *szPath, int nLen);
int MYAPI GetCurrentAppDir(char *szPath, int nLen);
void MYAPI AddDllSearchPath(const char *path);
void MYAPI AddSearchPath(const char *path);

DLL_HANDLE MYAPI DllOpen(const char *szFile,int nOption);
DLL_HANDLE MYAPI DllOpenW(const wchar_t *szFile,int nOption);
DLL_HANDLE MYAPI DllHandle(const char *szFile);
int MYAPI DllClose(DLL_HANDLE DlHandle);
void * MYAPI DllSymbol(DLL_HANDLE DlHandle,const char *szSymbol);
void * MYAPI DllSymbolEx(const char *szLibraryPath,const char *szSymbol);
char * MYAPI DllError();
/************************mem file functions**********************************************/

int MYAPI MFSupportLength();
MF_HANDLE MYAPI MFOpen2(const char *szPath,int blocks, int blockSize, __malloc funcMalloc , __free funcFree );
MF_HANDLE MYAPI MFOpen(const char *szPath,MF_HANDLE hMfPre);
int MYAPI MFSeek(MF_HANDLE hMf, int nOffSet,int nSet);
int MYAPI MFRead(MF_HANDLE hMf,void *Buf,int nBufSize);
int MYAPI MFWrite(MF_HANDLE hMf,const void *Buf,int nBufSize);
int MYAPI MFClose(MF_HANDLE hMf);
int MYAPI MFCloseX(MF_HANDLE *phMf);
int MYAPI MF2File(MF_HANDLE hMf,FILE_HANDLE hFile,int nPosStart,int nPosEnd);
int MYAPI MFFromFile(MF_HANDLE hMf,FILE_HANDLE hFile,int nPosStart,int nCount);
const char *MYAPI MFPath(MF_HANDLE hMf);
MF_HANDLE MYAPI MFOpenFromFile(const char *szFile);
int MYAPI MFSize( MF_HANDLE hMf );
int MYAPI MFIniRead(const char *section,const char *var,
                    char *outValue,int size,MF_HANDLE hMf);
int MYAPI MFIniReadStr(const char *section,const char *var,
                       char *outValue,int size,MF_HANDLE hMf);
int MYAPI MFIniReadInt(const char *section,const char *var,
                       MF_HANDLE hMf,int nDefaultValue);
BOOL MYAPI MFIniReadBool(const char *section,const char *var,
                         MF_HANDLE hMf,int nDefaultValue);
BOOL MYAPI MFIniReadRgbColor(const char *section,const char *var,
                             PRGB_COLOR pRgb,MF_HANDLE hMf);

int MYAPI ThPoolHandleSize(int nPoolLen);
THPOOL_HANDLE MYAPI  ThPoolInit(void *pHandleMem,void *pfuncThreadProc,unsigned int nStackSize,int nPoolLen);
THPOOL_HANDLE MYAPI  ThPoolAlloc(void *pfuncThreadProc,unsigned int nStackSize,int nPoolLen);
int MYAPI ThPoolCountAll(THPOOL_HANDLE hPool);
int MYAPI ThPoolCountWaiting(THPOOL_HANDLE hPool);
int MYAPI ThPoolCountWorking(THPOOL_HANDLE hPool);
int MYAPI ThPoolRunTask(THPOOL_HANDLE hPool,void *ThreadParameter,void *pfuncThreadProc);
int MYAPI ThPoolWaitTask(THPOOL_HANDLE hPool ,void **ppThreadParameterOut);
int MYAPI ThPoolCancelAll(THPOOL_HANDLE hPool);
void MYAPI ThPoolFree(THPOOL_HANDLE hPool);
UINT32 MYAPI ThPoolSetOption(THPOOL_HANDLE hPool,UINT32 NewOption);//return old option
UINT32 MYAPI ThPoolOption(THPOOL_HANDLE hPool);

UINT32 MYAPI CalCRC32(void *buf, int len);
UINT16 MYAPI CalCRC16(void *puchMsg, int usDataLen);
BYTE MYAPI LRC(BYTE *auchMsg,UINT16 usDataLen);


int MYAPI MinInt(int a,int b);
int MYAPI MaxInt(int a,int b);


PAUTH_USER MYAPI AuthUserAlloc(const char *szUser,const char *szPwd);
void MYAPI AuthUserFree(PAUTH_USER *ppUser);
void MYAPI AuthUserFreeList(PAUTH_USER pUser);
int MYAPI AuthUserLogin(PAUTH_USER pUserList,const char *szUser,const char *szPwd,int nUserType);
void MYAPI AuthUsersInitFromIni(PAUTH_USER *ppUserHead,const char *szIniSec,const char *szIniFile);


int MYAPI AuthPluginLogin(PAUTH_PLUGIN pPluginList,const char *szUser,const char *szPwd,int nUserType,void *ExtData);
int MYAPI AuthPluginLoad(PAUTH_PLUGIN pPlugin,const char *szPathPlugin,const char *szLoginFunction);

///////////////////////////////database extension//////////////////////////////////////////
int IniReadDatabase(const char *szIniFile,const char *szSection,PDATABASE_INI pDblIni);
int IniWriteDatabase(const char *szIniFile,const char *szSection,const PDATABASE_INI pDblIni);

RGB_COLOR * MYAPI Str2RgbColor(const char *szStr,RGB_COLOR *pRgbColor);
BOOL MYAPI ReadBmpInfoHeader(const char *szFile,const BMPINFOHEADER *pHeaderIn);
BOOL MYAPI IsBmpHeader(const void *pBuf);
int MYAPI ReadBmpPalette(const char *szFile,const BMPINFOHEADER *pHeader,PRGB_COLOR pPalt,int nCount);
FILE_HANDLE MYAPI FileOpenBmpBitData(const char *szFile,const BMPINFOHEADER *pHeader);
void MYAPI BmpZoom(const UINT32 *pBitArSrc,int nWidthSrc,int nHeightSrc,
                   UINT32 *pBitArDest,int nWidthDest,int nHeightDest,
                   BYTE diaphaneity);
RetBmpZoom MYAPI BmpFileZoom(const char *szFileSrc,const char *szFileDest ,int nWidth , int nHeight );
///////////////////////////////////////////////////////////////////////////////////////
void MYAPI ListInit(LIST_ITEM *newItem);
void MYAPI _ListAdd(LIST_ITEM *newItem,LIST_ITEM *prev, LIST_ITEM *next);
void MYAPI ListAddHead(LIST_ITEM *newItem, LIST_ITEM *head);
void MYAPI ListAddTail(LIST_ITEM *newItem, LIST_ITEM *head);
void MYAPI _ListDel(LIST_ITEM *prev, LIST_ITEM *next);
void MYAPI ListDel(LIST_ITEM *entry);
void MYAPI ListMoveHead(LIST_ITEM *listMv, LIST_ITEM *head);
void MYAPI ListMoveTail(LIST_ITEM *listMv,LIST_ITEM *head);
BOOL MYAPI ListIsEmpty(LIST_ITEM *head);

void MYAPI TxtItemFreeList(LIST_ITEM *  pHead);
void MYAPI TxtItemFree( LIST_ITEM *pItemTmp );
TXT_ITEM * MYAPI TxtItemAlloc(char *szhead ,int nLen);

#if defined(WIN32) || defined(_PTHREAD_H) || defined(_PTHREAD_H_)

BOOL MYAPI MtxInitEx( MTX_OBJ * pMtxObj,int nSpinCount,int nMtxOpt);
BOOL MYAPI MtxInit( MTX_OBJ * pMtxObj,int nMtxOpt);
BOOL MYAPI MtxTryLock( MTX_OBJ * pMtxObj);
BOOL MYAPI MtxLock( MTX_OBJ * pMtxObj);
BOOL MYAPI MtxUnLock( MTX_OBJ * pMtxObj);
BOOL MYAPI MtxDestroy( MTX_OBJ * pMtxObj);

#endif

void MYAPI AdAPIInit_Mtx();
void MYAPI MtxInternalLock();
void MYAPI MtxInternalUnlock();
INT32 MYAPI MtxInterlockedInc(INT32 volatile *pCount);
INT32 MYAPI MtxInterlockedDec(INT32 volatile *pCount);
INT32 MYAPI MtxInterlockedExchange(INT32 volatile *pCount,INT32 nNewValue);

INT64 MYAPI MtxInterlockedInc64(INT64 volatile *pCount);
INT64 MYAPI MtxInterlockedDec64(INT64 volatile *pCount);


void  MYAPI   MemoryBufferFree(void *hMem);
void *  MYAPI MemoryBufferAlloc( int nBufSize,BOOL bAutoClear);
int MYAPI MemoryBufferLength( void *hMem );
int MYAPI MemoryBufferWrite(void *hMem,const void *buf,int nSize,BOOL bCopyFromUser);
int MYAPI MemoryBufferRead(void *hMem,void *buf,int nSize,BOOL bCopyToUser);
void MYAPI MemoryBufferReset( void *hMem );

#if !defined(WIN32)
BOOL is_path_match_device(const char *path,const char *szDevPath);
BOOL find_block_device(const char *path,char *szDevPath,int nLen) ;
BOOL Serial_Conf(int fd,int speed,int databits,int stopbits,int parity,int binMode,int flow) ;
#endif

FILE_HANDLE MYAPI  SerialOpen(const char *szDev,int mode,const char *szOpt /*19200-8-1-N*/,BOOL bNoBlock );

typedef void * SERIAL_HANDLE;
SERIAL_HANDLE MYAPI Serial_Open( const char *szDev,int mode,const char *szOpt /*19200-8-1-N*/ );
int			  MYAPI Serial_Read( SERIAL_HANDLE handle, void *buf , int nLen, int timeout); // return -1 error, -2 time out , -3 write event 
int			  MYAPI Serial_Write( SERIAL_HANDLE handle, const void *buf , int nLen, int timeout);
void		  MYAPI Serial_Shutdown( SERIAL_HANDLE handle );
void		  MYAPI Serial_Close( SERIAL_HANDLE handle );
int			  MYAPI Serial_EnableBin(SERIAL_HANDLE handle, BOOL bEnable);

#if defined(WIN32) && !defined(_WIN32_WCE)

const char * MYAPI Win32UserAppData(char *szPathOut,int nLen);
const char * MYAPI Win32AllUserAppData(char *szPathOut,int nLen);
const char * MYAPI Win32UserSettingAppData(char *szPathOut,int nLen);
const char * MYAPI Win32UserDocuments(char *szPathOut,int nLen);
const char * MYAPI Win32AllUserDocuments(char *szPathOut,int nLen);
BOOL MYAPI Win32RegGetString(const char *szRegPath, const char *szValueName,
							 char *outvalue,int cb);
BOOL MYAPI Win32RegSetString(const  char *szRegPath, const char *szValueName,  
							 const char *szValue);
BOOL MYAPI Win32RegDelKey(const char *szRegPath, const char *szSubKey);
BOOL MYAPI Win32RegDelValue(const char *szRegPath, const char *szValueName);
#ifdef __IUnknown_INTERFACE_DEFINED__
HRESULT  WINAPI Win32CoCreateInstanceFromDLLW(__in     REFCLSID rclsid, 
										 __in_opt LPUNKNOWN pUnkOuter,
										 __in     DWORD dwClsContext, 
										 __in     REFIID riid, 
										 __deref_out LPVOID FAR* ppv,
										 const WCHAR *szDllPath);
HRESULT  WINAPI Win32CoCreateInstanceFromDLLA(__in     REFCLSID rclsid, 
										 __in_opt LPUNKNOWN pUnkOuter,
										 __in     DWORD dwClsContext, 
										 __in     REFIID riid, 
										 __deref_out LPVOID FAR* ppv,
										 const char *szDllPath);
int MYAPI GetIDESerialNumberWIN7(char *szOut ,int nSize,int index);
#endif

#ifdef UNICODE
#define Win32CoCreateInstanceFromDLL  Win32CoCreateInstanceFromDLLW
#else
#define Win32CoCreateInstanceFromDLL  Win32CoCreateInstanceFromDLLA
#endif // !UNICODE

#endif

HEVWAIT MYAPI EvWaitCreate( BOOL  bManualReset );
void    MYAPI EvWaitClose( HEVWAIT hWait );
EvWaitResult     MYAPI EvWaitForEvent(HEVWAIT hWait , int nMilliseconds);
void    MYAPI EvWaitSetEvent( HEVWAIT hWait );
BOOL    MYAPI EvWaitResetEvent( HEVWAIT hWait );


typedef struct tagMemoryBuffer2Ref
{
	char *Data;
	int   DataLen;

	int Begin;
	int Length;
	
	struct tagMemoryBuffer2Ref* Next;

} MemoryBuffer2Ref;
MemoryBuffer2Ref * MYAPI  MemoryBuffer2AllocRef();
void MYAPI  MemoryBuffer2FreeRef(MemoryBuffer2Ref *ref);
MemoryBuffer2Handle MYAPI MemoryBuffer2Open(int blocksize);
MemoryBuffer2Handle MYAPI MemoryBuffer2Open2(int blocksize,int nSeekLength, int nMaxFreeBlocks , BOOL bShareData );
void MYAPI MemoryBuffer2Close( MemoryBuffer2Handle handle );
int  MYAPI MemoryBuffer2Length( MemoryBuffer2Handle handle  );
int MYAPI MemoryBuffer2Seek(MemoryBuffer2Handle handle ,int pos,int origin );
int MYAPI MemoryBuffer2Read( MemoryBuffer2Handle handle ,void *buf,int nSize);
int MYAPI MemoryBuffer2ReadRef( MemoryBuffer2Handle handle ,MemoryBuffer2Ref **refPtr ,int nSize  ,MemoryBuffer2Ref **refTail );
int MYAPI MemoryBuffer2Write(MemoryBuffer2Handle handle ,const void *buf,int nSize);
void MYAPI MemoryBuffer2Reset(MemoryBuffer2Handle handle);

    
typedef void ( *__Destory )(void *p);
void *  MYAPI  MemoryCreate( size_t cb,__Destory destroy );
void *  MYAPI  MemoryAlloc( size_t cb );
void *  MYAPI  MemoryRealloc( void *p,size_t cb );
char *  MYAPI  MemoryEmptyString( );
char *  MYAPI  MemoryString( const char *str, int nLen, int align );
int     MYAPI  MemoryStringLen(const char *str);
size_t  MYAPI  MemorySize( void *p );
INT32    MYAPI  MemoryAddRef( void *p   );
INT32    MYAPI  MemoryRelease( void *p   );



typedef int ( *__LrcItemCallback )( int timeTag , const char *txt,void *usrdata );
void *	MYAPI LrcOpen(const char *fileOrContent,BOOL bFile,int nContentLength);
void	MYAPI LrcClose(void *lrc);
const char *	MYAPI LrcTxtByTime(void *lrc,int timeTagMilliSeconds);
const char *	MYAPI LrcTxtByTimeTag(void *lrc,const char * timeTag);
const char *	MYAPI LrcTagTi(void *lrc);
const char *	MYAPI LrcTagAr(void *lrc);
const char *	MYAPI LrcTagAl(void *lrc);
const char *	MYAPI LrcTagBy(void *lrc);
int MYAPI LrcItems(void *lrc, __LrcItemCallback callback,void *usrdata );

void * MYAPI CreateMemoryPool();
void MYAPI ReleaseMemoryPool(void *p);

void MYAPI PrintBacktrace();
int MYAPI GetMachineId(char *szOut, int nSize,const char *szEth);

#ifdef __cplusplus
}
#endif

#endif




















