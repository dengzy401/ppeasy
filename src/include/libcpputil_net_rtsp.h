
#ifndef _LIBCPPUTIL_NET_RTSP_H_
#define _LIBCPPUTIL_NET_RTSP_H_

#ifndef _LIBCPPUTIL_NET_H_
#include "libcpputil_net.h"
#endif



typedef enum tagRtspStatus
{
	RtspStatusUnknown ,
	RtspStatusClose ,
	RtspStatusPlaying ,
	RtspStatusPause ,
	RtspStatusTeardown ,
	RtspStatusJoin ,
	RtspStatusGetSdp ,
	RtspStatusSetup ,
	RtspStatusPlay ,

}RtspStatus;


class CRTSPNetAsync;
class  _CPP_UTIL_EXPORT  CRTSPConnContext :
	public CObjConnContext 
{
	friend class CRTSPNetAsync;
public:
	_CPP_UTIL_DYNAMIC_DECLARE(CRTSPConnContext)  ;
	_CPP_UTIL_CLASSNAME_DECLARE(CRTSPConnContext) ;
	_CPP_UTIL_QUERYOBJ_DECLARE(CRTSPConnContext) ;
	CRTSPConnContext();
	virtual ~CRTSPConnContext();
	virtual BOOL InitLater();
	RtspStatus m_status;
	
protected:
	int  m_nMaxBuffer;
private:
	CObjBuffer	m_ioBuf;


	
};

class  _CPP_UTIL_EXPORT  CRTSPNetAsync :
	public CObjNetAsync 
{
public:
	CRTSPNetAsync(	int nWaitTimeoutSeconds = -1,
		int nStackSize = 0,int nMaxConnections = 2000,
		NetAsyncType netType = NetAsyncTypeDefault );
	virtual ~CRTSPNetAsync();

	// if you override it please inherit from CRTSPConnContext
	virtual CObjConnContext  * AllocConnContext(CObj *par);
	virtual CObjNetIOBuffer  * AllocRTSPIOBuffer(int nLen = -1);
	virtual int OnRTSPCommandReadCompleted(CRTSPConnContext *pContext, CObjNetIOBuffer *pBuffer);
	virtual int OnRTSPDataReadCompleted(CRTSPConnContext *pContext, CObjNetIOBuffer *pBuffer);
public:
	virtual int OnReadCompleted(CObjConnContext *pContext, CObjNetIOBuffer *pBuffer);




};








	
	
	
	
	
#endif






