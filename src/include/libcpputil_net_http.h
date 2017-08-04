

#ifndef _libcpputil_net_http_h_
#define _libcpputil_net_http_h_


#ifndef _libcpputil_var_h_
#include "libcpputil_var.h"
#endif

#ifndef _LIBCPPUTIL_NET_H_
#include "libcpputil_net.h"
#endif





class CHTTPNetAsync;
class CHttpResponseHeader;

class  _CPP_UTIL_EXPORT  CHttpConnContext :
    public CObjConnContext
{
    friend class CHTTPNetAsync;
public:
    typedef enum tagHttpMethod
    {
        HttpMethodUnknown,
        HttpMethodGet,
        HttpMethodPost,
        HttpMethodHead,
        HttpMethodPut,
        HttpMethodDelete,
        HttpMethodOptions,
        HttpMethodConnect,
    }HttpMethod;

    typedef enum tagHttpVer
    {
        HttpVerUnknown,
        HttpVer10,
        HttpVer11,
    }HttpVer;
public:
    _CPP_UTIL_DYNAMIC_DECLARE( CHttpConnContext );
    _CPP_UTIL_CLASSNAME_DECLARE( CHttpConnContext );
    _CPP_UTIL_QUERYOBJ_DECLARE( CHttpConnContext );
    CHttpConnContext( );
    virtual ~CHttpConnContext( );

public:
    BOOL SendResponseHeader( CHttpResponseHeader *header );
    int  GetHttpHeaderVar(const char *name , char *szVar , int nLen );
	int  GetUserAgent(char *szVar, int nLen);
public:
    CObjVar m_strHeader;
    HttpMethod m_method;
    CObjVar m_strUri;
    CObjVar m_strQuery;
    HttpVer m_clientVer;
    BOOL    m_bKeepalive;
    int     m_nContentLength;
    int     m_nCurrentContentLength;


    int     m_nMaxHttpHeaderSize;
private:
    CObjBuffer m_buf;
    int     m_state;
    
};


class  _CPP_UTIL_EXPORT  CHttpResponseHeader :
    public CObjNetIOBuffer
{
public:
    typedef enum tagHttpStatus
    {
        HttpStatusOK = 200 ,
		HttpStatusPartialContent = 206,
		HttpStatusNotModified = 304,
		HttpStatusUnauthorized = 401,
        HttpStatusForbidden = 403,
        HttpStatusNotFound = 404,
        HttpStatusServerError = 500,
        HttpStatusServiceUnavailable = 503,

    }HttpStatus;
public:
    _CPP_UTIL_CLASSNAME_DECLARE( CHttpResponseHeader );
    _CPP_UTIL_QUERYOBJ_DECLARE( CHttpResponseHeader );

    static CHttpResponseHeader * CreateObj( int status = HttpStatusOK, CHttpConnContext::HttpVer ver = CHttpConnContext::HttpVer11, const char *describe = NULL );

    
    static const char *HttpStatus2Describe( int status );
	CHttpResponseHeader(int status = HttpStatusOK, CHttpConnContext::HttpVer ver = CHttpConnContext::HttpVer11, const char *describe = NULL);
    virtual ~CHttpResponseHeader( );
public:
    void SetContentType( const char *szData );
    void SetContentLength( INT64 length );
    void SetKeepAlive( BOOL bKeepalive );
    void SetAcceptRanges();
    void SetContentRange(INT64 begin, INT64 end, INT64 total);
    void SetLastModified( SYSTEMTIME *systime);
	void SetHeader(const char *name,const char *szData);
	void AddCookie(const char *name, const char *value, const char *path = NULL, const char *domain = NULL, int expiresSeconds = 0);
    
    void Write( const char *szData, int nLen = -1, int align = 1024 );
    void EndWrite( );
    
public:
    CObjBuffer m_buf;
};


class   _CPP_UTIL_EXPORT CHTTPNetAsync :
    public CObjNetAsync
{

public:
    CHTTPNetAsync( int nWaitTimeoutSeconds = -1,
                   int nStackSize = 0, int nMaxConnections = 2000,
                   NetAsyncType netType = NetAsyncTypeDefault
                   );
    virtual ~CHTTPNetAsync( );
	static void SetHttpServerInfo(const char *szInfo);

    // if you override it please inherit from CHttpConnContext
	virtual CObjConnContext  * AllocConnContext(CObj *par);
    virtual CObjNetIOBuffer *  CreateHTTPIoBuffer( int Size );
public:
    virtual int OnHttpRequest( CHttpConnContext *pContext);
    virtual int OnHttpContentData( CHttpConnContext *pContext,  CObjNetIOBuffer *pBuffer );
public:
    virtual int OnReadCompleted( CObjConnContext *pContext, CObjNetIOBuffer *pBuffer );


};










#endif




















