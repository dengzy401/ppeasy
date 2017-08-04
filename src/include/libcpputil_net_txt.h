
#ifndef _LIBCPPUTIL_NET_TXT_H_
#define _LIBCPPUTIL_NET_TXT_H_

#ifndef _LIBCPPUTIL_NET_H_
#include "libcpputil_net.h"
#endif

class CTxtNetAsync;
class  _CPP_UTIL_EXPORT  CTxtConnContext :
    public CObjConnContext 
{
    friend class CTxtNetAsync;
public:
    _CPP_UTIL_DYNAMIC_DECLARE(CTxtConnContext)  ;
    _CPP_UTIL_CLASSNAME_DECLARE(CTxtConnContext) ;
    _CPP_UTIL_QUERYOBJ_DECLARE(CTxtConnContext) ;
    CTxtConnContext();
    virtual ~CTxtConnContext();
    virtual BOOL InitLater();
    void CleanTxtBuffer();
private:
    CObjNetIOBuffer *m_pIoBuf;
};

class  _CPP_UTIL_EXPORT  CTxtNetAsync :
    public CObjNetAsync 
{
public:

    CTxtNetAsync(	int nWaitTimeoutSeconds = -1,
					int nStackSize = 0,int nMaxConnections = 2000,
					NetAsyncType netType = NetAsyncTypeDefault );
    virtual ~CTxtNetAsync();

    // if you override it please inherit from CTxtConnContext
	virtual CObjConnContext  * AllocConnContext(CObj *par);
    virtual CObjNetIOBuffer  * AllocTxtIOBuffer();
public:
    virtual int OnTxtReadCompleted(CTxtConnContext *pContext, CObjNetIOBuffer *pBuffer);
    virtual int OnReadCompleted(CObjConnContext *pContext, CObjNetIOBuffer *pBuffer);
    virtual int OnInvalidTxtIOBuffer(CObjConnContext *pContext, CObjNetIOBuffer *pBuffer,const char *szMsg);
};



















#endif




