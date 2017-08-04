
#ifndef _LIBCPPUTIL_NET_PKG_H_
#define _LIBCPPUTIL_NET_PKG_H_

#ifndef _LIBCPPUTIL_NET_H_
#include "libcpputil_net.h"
#endif

class CPkgNetAsync;
class  _CPP_UTIL_EXPORT  CPkgConnContext :
    public CObjConnContext 
{
    friend class CPkgNetAsync;
public:
    _CPP_UTIL_DYNAMIC_DECLARE(CPkgConnContext)  ;
    _CPP_UTIL_CLASSNAME_DECLARE(CPkgConnContext) ;
    _CPP_UTIL_QUERYOBJ_DECLARE(CPkgConnContext) ;
    CPkgConnContext();
    virtual ~CPkgConnContext();
    virtual BOOL InitLater();

public:
	unsigned char *m_szHeaderBuffer;
	int  m_nHeaderLength;
private:
    CObjNetIOBuffer *m_pIoBuf;
	int m_nPkgHeaderLen;
    BOOL m_bPkg ;
	BOOL m_bAllocedHeaderBuffer;
};

class  _CPP_UTIL_EXPORT  CPkgNetAsync :
    public CObjNetAsync 
{
public:

	CPkgNetAsync(	int nWaitTimeoutSeconds = -1,
					int nStackSize = 0,int nMaxConnections = 2000,
					NetAsyncType netType = NetAsyncTypeDefault 
				);
    virtual ~CPkgNetAsync();
	void SetMaxPkgbuffer(int MaxPkgbuffer );


	virtual BOOL  IsPkgHead(CPkgConnContext *pContext, void  *pBufHead);
	virtual int   GetPkgLen(CPkgConnContext *pContext, void  *pBufHead);

    // if you override it please inherit from CPkgConnContext
	virtual CObjConnContext  * AllocConnContext(CObj *par);
	virtual CObjNetIOBuffer *  CreatePkgBuffer( int Size );
public:
    virtual int OnPkgReadCompleted(CPkgConnContext *pContext, CObjNetIOBuffer *pBuffer);
    virtual int OnReadCompleted(CObjConnContext *pContext, CObjNetIOBuffer *pBuffer);
    virtual int OnInvalidPkgIOBuffer(CObjConnContext *pContext, CObjNetIOBuffer *pBuffer,const char *szMsg);
public:
	BOOL m_bIoBufferIncludeHeader;
private:
	int m_nMaxPkgbuffer;
};



















#endif




