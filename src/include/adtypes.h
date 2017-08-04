/*********************************************************/
#ifndef _ADTYPES_H_
#define _ADTYPES_H_

#ifdef WIN32
#include <windows.h>
#endif

#ifndef SIZE_512B
#define SIZE_512B 512
#define SIZE_1KB 1024
#define SIZE_2KB 2048
#define SIZE_4KB 4096
#define SIZE_6KB 6144
#define SIZE_8KB 8192
#define SIZE_10KB 10240
#define SIZE_16KB 16384
#define SIZE_32KB 32768
#define SIZE_64KB 65536
#define SIZE_96KB 98304
#define SIZE_128KB 131072
#define SIZE_256KB 262144
#define SIZE_512KB 524288
#define SIZE_1M   1048576
#define SIZE_4M   4194304
#define SIZE_10M  10485760
#define SIZE_20M  20971520
#define SIZE_1GB 1073741824LL //1GB
#define SIZE_2GB  2147483648LL //2GB
#endif


#ifndef LEN_MAX_PATH
#define LEN_MAX_PATH 280
#endif

#ifndef LEN_MAX_URL
#define LEN_MAX_URL 280
#endif

#ifndef LEN_DOMAIN
#define LEN_DOMAIN      72
#endif
/*********************************************************/

#define ISVALID_PTR(p) ( ( (p) != 0 ) && ( (void *)p != (void *)-1 ) )
/*********************************************************/
#if defined(WIN32) || defined(_WIN32_WCE)

	#ifndef S_IRWALL
	#define S_IRWALL 0x0
	#endif
	#define MYAPI WINAPI

#else

	#ifndef S_IRWALL
	#define S_IRWALL S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH
	#endif
	#define MYAPI

#endif

#define _SIZE_OF(x)  ((int)sizeof(x))
/*********************** NOMINMAX **********************************/
#ifndef NOMINMAX

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#endif  /* NOMINMAX */

#define ROTATE32_LEFT(x,n) ((x << n)|(x >> (32-n)))
#define ROTATE32_RIGHT(x,n) ((x << (32-n))|(x >> n))
/**************************TYPE*******************************/




#if !defined(WIN32) && !defined(_WIN32_WCE)


#ifndef WIN32_TYPE
#define WIN32_TYPE

#ifndef ___TYPE_BOOL__
#define ___TYPE_BOOL__
	
    #if  !defined(__DARWIN_UNIX03) 
    
	#if !defined(_BOOL_)
        typedef int BOOL;
        #define _BOOL_ 
	#endif
    #else

        #include <objc/objc.h>

        #if !defined(OBJC_BOOL_DEFINED)
            /// Type to represent a boolean value.
            #if !defined(OBJC_HIDE_64) && TARGET_OS_IPHONE && __LP64__
            typedef bool BOOL;
            #else
            typedef signed char BOOL;
            // BOOL is explicitly signed so @encode(BOOL) == "c" rather than "C"
            // even if -funsigned-char is used.
            #endif

        #endif

    #define _BOOL_ 

    #endif
	
#endif
	
typedef unsigned int DWORD;

#ifndef ___TYPE_WORD__
#define ___TYPE_WORD__
typedef unsigned short int WORD;
#endif

#ifndef ___TYPE_BYTE__
#define ___TYPE_BYTE__
typedef unsigned char BYTE;
#endif
typedef unsigned long ULONG;
typedef unsigned int UINT;
typedef long LONG;
typedef unsigned short WCHAR;
typedef DWORD COLORREF;


#ifndef TRUE
#define TRUE   1
#endif

#ifndef FALSE
#define FALSE   0
#endif

#ifndef NULL
#define NULL   0
#endif


#endif

#ifndef MAKEWORD

#define MAKEWORD(a, b)      ((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)(a)) | ((DWORD)((WORD)(b))) << 16))
#define LOWORD(l)           ((WORD)(l))
#define HIWORD(l)           ((WORD)(((DWORD)(l) >> 16) & 0xFFFF))
#define LOBYTE(w)           ((BYTE)(w))
#define HIBYTE(w)           ((BYTE)(((WORD)(w) >> 8) & 0xFF))

#endif  /* no MAKEWORD*/

#endif  /* no win32*/



#ifndef NUM_TYPE
#define NUM_TYPE




#if defined(WIN32)  || defined(_WIN32_WCE)
typedef signed char INT8;
typedef unsigned char UINT8;
typedef signed short int INT16;
typedef unsigned short int UINT16;
typedef signed int INT32;
typedef unsigned int UINT32;

#ifndef _SSIZE_T_
#define _SSIZE_T_
typedef long _ssize_t;

#ifndef	_NO_OLDNAMES
typedef _ssize_t ssize_t;
#endif
#endif /* Not _SSIZE_T_ */





#else



#ifndef _NO_I8
typedef signed char INT8;
#endif
#ifndef _NO_U8
typedef unsigned char UINT8;
#endif
#ifndef _NO_I16
typedef signed short int INT16;
#endif
#ifndef _NO_U16
typedef unsigned short int UINT16;
#endif
#ifndef _NO_I32
typedef signed int INT32;
#endif
#ifndef _NO_U32
typedef unsigned int UINT32;
#endif






typedef signed long long INT64;
typedef unsigned long long UINT64;

#endif

#ifdef WIN32
	#if defined(_WIN64)
	typedef UINT64  UINTPTR;
	typedef INT64   INTPTR;
	#else
	typedef UINT32   UINTPTR;
	typedef INT32   INTPTR;
	#endif
#else
    #if defined(__LP64__)
	typedef UINT64  UINTPTR;
	typedef INT64   INTPTR;
	#else
	typedef UINT32   UINTPTR;
	typedef INT32   INTPTR;
	#endif
#endif



#if !defined(_TIME_TYPES_)
#define _TIME_TYPES_		1
typedef   INT64    TIME_T;
#endif


#endif

#if !defined(WIN32) && !defined(_WIN32_WCE)
#if !defined(_SYSTEMTIME_)
#define _SYSTEMTIME_
typedef struct _SYSTEMTIME {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;
#endif
#endif


typedef struct tagAPP_KEY
{
	SYSTEMTIME	tmCreate;
	SYSTEMTIME	tmOutOfDate;
	INT32		nConnectNumber;
	char		szMachineID[40];
	char		szAppID[40];
}APP_KEY, *PAPP_KEY;

/*********************************************************/

#define INVALID_PTR(p) if(!(p))return;
#define INVALID_PTR_RETURN(p,ret) if(!(p))return (ret);
/*******************************************************/

#ifndef RGB_EM86XX
#define RGB_EM86XX(r,g,b)          ((COLORREF)(((BYTE)(b)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(r))<<16)))
#endif

#ifndef RGB
#ifdef EM86XX_CHIP
#define RGB(r,g,b)          ((COLORREF)(((BYTE)(b)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(r))<<16)))
#else
#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#endif
#endif

#ifndef PALETTERGB
#define PALETTERGB(r,g,b)   (0x02000000 | RGB(r,g,b))
#endif

#ifndef PALETTEINDEX
#define PALETTEINDEX(i)     ((COLORREF)(0x01000000 | (DWORD)(WORD)(i)))
#endif

/* constants for the biCompression field */
#ifndef BI_RGB
#define BI_RGB        0L
#endif
#ifndef BI_RLE8
#define BI_RLE8       1L
#endif
#ifndef BI_RLE4
#define BI_RLE4       2L
#endif
#ifndef BI_BITFIELDS
#define BI_BITFIELDS  3L
#endif
#ifndef BI_JPEG
#define BI_JPEG       4L
#endif
#ifndef BI_PNG
#define BI_PNG        5L
#endif

#ifdef WIN32
typedef unsigned ( __stdcall *_thread_proc )( void * ) ;
#endif

#endif






















