
#ifndef _libcpputil_rtmp_h_
#define _libcpputil_rtmp_h_

#ifndef _libcpputil_var_h_
#include "libcpputil_var.h"
#endif

#ifndef _libcpputil_amf_h_
#include "libcpputil_amf.h"
#endif

#define RTMP_PORT 1935
#define _RTMP_MAX_CHANNELS  125


typedef enum tagRTMPCtrl
{
	RTMPCtrl_StreamBegin = 0 ,
	RTMPCtrl_StreamEOF = 1 ,
	RTMPCtrl_StreamDry = 2 ,
	RTMPCtrl_SetBufferLength = 3 ,
	RTMPCtrl_StreamIsRecorded = 4 ,
	RTMPCtrl_Ping = 6 ,
	RTMPCtrl_Pong = 7 ,
	RTMPCtrl_StreamBufferEmpty = 31 ,
	RTMPCtrl_StreamBufferReady = 32 ,
}RTMPCtrl;



class CRTMPNetAsync;
class CRTMPConnContext ;
class CRTMPCtx ;







class _CPP_UTIL_EXPORT CRTMPHeader
{
public:
    typedef enum tagTimmerType
    {
        TimmerTypeUnknown,
        TimmerTypeRelative,
        TimmerTypeABS,
        TimmerTypeExt,

    }TimmerType;
public:
	CRTMPHeader();
	virtual ~CRTMPHeader();

    CRTMPHeader( const CRTMPHeader& _this );
    CRTMPHeader& operator = ( const CRTMPHeader& _this );

	void Clear();
	BOOL IsValid();
public:
	UINT8	HeadType;
	int		HeadSize;
	int     ExtHeadSize;
	int		ChannelId;
	INT32  Timmer;
    TimmerType Timmer_Type;
	UINT32  PacketSize;
	RTMPPacketType	PacketType;
	UINT32  StreamId;
};
class _CPP_UTIL_EXPORT CRTMPState
{
public:
	typedef struct tagRTMPHandshake
	{
		BOOL m_bHandShaked;
		BOOL m_bF9;
		BOOL m_bEncrypted;
		UINT8 m_type;
	}RTMPHandshake;
public:
	CRTMPState();
	virtual ~CRTMPState();
	void Clear();

	RTMPHandshake m_handshake;
	
	CRTMPHeader prevHeaders[_RTMP_MAX_CHANNELS];
	CObjNetIOBuffer *m_PktIoBufs[_RTMP_MAX_CHANNELS];

	CRTMPHeader header;
	int state;
	int  m_ChunkSizeIn;
	int  m_ChunkSizeOut;
	int  m_nBWCheckCounter;
	int m_nClientBandWidth ;
	int m_nClientLimitType ;
	int m_nWindowAck ;

	

};

class  _CPP_UTIL_EXPORT  CObjNetIOBufferRTMP :
	public CObjNetIOBuffer
{
public:
	_CPP_UTIL_DYNAMIC_DECLARE(CObjNetIOBufferRTMP)  ;
	_CPP_UTIL_CLASSNAME_DECLARE(CObjNetIOBufferRTMP) ;
	_CPP_UTIL_QUERYOBJ_DECLARE(CObjNetIOBufferRTMP) ;

	CObjNetIOBufferRTMP();
	virtual ~CObjNetIOBufferRTMP();
	void EndWrite();
public:
	CAMFBuffer m_buf;
};

class  _CPP_UTIL_EXPORT  CObjNetIOBufferSharedMemoryRTMP :
	public CObjNetIOBufferSharedMemory
{
public:
	static CObjNetIOBufferSharedMemoryRTMP * CreateObj(void *memShared,int memSize,BOOL bMalloc2 = TRUE);
	_CPP_UTIL_CLASSNAME_DECLARE(CObjNetIOBufferSharedMemoryRTMP) ;
	_CPP_UTIL_QUERYOBJ_DECLARE(CObjNetIOBufferSharedMemoryRTMP) ;

	CObjNetIOBufferSharedMemoryRTMP(void *memShared,int memSize,BOOL bMalloc2 = TRUE);
	virtual ~CObjNetIOBufferSharedMemoryRTMP();
	int Write( const void* Ptr, int Length );
	int WriteUINT8( UINT8 bv);
public:
	int m_chunksize;
	int m_amfsize;
	UINT8 m_channelId;
};

class   _CPP_UTIL_EXPORT CRTMPHttpIoBuffers :
	public CObj
{
public:
	static CRTMPHttpIoBuffers * CreateObj( CObjNetIOBuffer * ioBuf = NULL  );
	_CPP_UTIL_CLASSNAME_DECLARE(CRTMPHttpIoBuffers) ;
	_CPP_UTIL_QUERYOBJ_DECLARE(CRTMPHttpIoBuffers) ;
public:
	CRTMPHttpIoBuffers( CObjNetIOBuffer * ioBuf = NULL );
	virtual ~CRTMPHttpIoBuffers();
	CObjNetIOBuffer *RemoveHead();
	void AddTail( CObjNetIOBuffer * ioBuf );
public:
	void * operator new( size_t cb );
	void operator delete( void* p );
public:
	CObj m_ioBufs;
	int  m_nDataLen;
};

class   _CPP_UTIL_EXPORT CRTMPCtx:
	public CObj 
{
public:
	friend class CRTMPNetAsync;
	friend class CRTMPConnContext;
	typedef enum tagConnType
	{
		ConnTypeUnknown,
		ConnTypeRTMP,
		ConnTypeRTMPT,

	}ConnType;
public:
	void * operator new( size_t cb );
	void operator delete( void* p );
public:
	static void RTMPServerName(const char *szName);
	static const char * RTMPServerName();
public:
	_CPP_UTIL_DYNAMIC_DECLARE(CRTMPCtx)  ;
	_CPP_UTIL_CLASSNAME_DECLARE(CRTMPCtx) ;
	_CPP_UTIL_QUERYOBJ_DECLARE(CRTMPCtx) ;

	CRTMPCtx();
	virtual ~CRTMPCtx();
	virtual void CloseByRTMPT();
	BOOL Send(CObjNetIOBuffer *pBuf);
	BOOL Sync();

    CRTMPConnContext *GetConnCtx();  // must be release it after use
	BOOL AddHttpIoBuffer( CObjNetIOBuffer *pBuf );
	CRTMPHttpIoBuffers *GetHttpIoBuffers();

	int RTMPConnCtxAdd(CRTMPConnContext *ctx);
	int RTMPConnCtxRemove(CRTMPConnContext *ctx);
	int RTMPConnCtxCount();
	void RTMPConnCtxCloseAll();
	void RTMPConnCtxRemoveAll();

public:
	ConnType m_type;
	int m_nMaxHttpHeaderSize;
	int m_nMaxRTMPPacketSize;
	CObjBuffer m_buf;

	CRTMPState m_state;
	UINT8 m_nChannelOfSend;
	BOOL m_bPlaying ;
	BOOL m_bPlayCalled;
	int  m_objectEncoding;
	char m_szClientId[80];

public:
	CRTMPHttpIoBuffers *m_httpIoBufs;
	MTX_OBJ m_mtxhttpIoBufs;
private:
	CObj m_listCtxs;
	MTX_OBJ m_mtxListCtxs;
};
class   _CPP_UTIL_EXPORT CRTMPConnContext :
	public CObjConnContext 
{

	
public:
	friend class CRTMPNetAsync;
	friend class CRTMPCtx;
public:
	_CPP_UTIL_DYNAMIC_DECLARE(CRTMPConnContext)  ;
	_CPP_UTIL_CLASSNAME_DECLARE(CRTMPConnContext) ;
	_CPP_UTIL_QUERYOBJ_DECLARE(CRTMPConnContext) ;
	CRTMPConnContext();
	virtual ~CRTMPConnContext();
	virtual BOOL InitLater();
	virtual CRTMPCtx *CreateRTMPCtx();



	virtual BOOL Send(CObjNetIOBuffer *pBuf);
	virtual BOOL SendIoBuffer(CObjNetIOBuffer *pBuf);
    
    
    CObjNetIOBufferRTMP *CreateRTMPIoBuffer();


	BOOL SendHttpIoBuffers(CRTMPHttpIoBuffers *ioBufs);
	BOOL SyncIoBuffer();
	
    BOOL SendInvoke(const char *method, const CObjVar &value, double txn = 0);
	BOOL SendInvokeConnectResult(double txn);
	BOOL SendInvokeResultNumber(double txn , CObjVar *var);
	BOOL SendInvokePong(double txn);
    BOOL SendInvokePing(double txn);
	BOOL SendInvokeCheckBWResult(double txn);
	BOOL SendInvokeCallFailed(double txn , const char * method);
	BOOL SendOnBWDone(double txn);
	BOOL SendOnFCPublish(const char *szDesc);


	BOOL SendChunkSize(int chunksize  );
	BOOL SendCtrl(INT16 nType,UINT32 nObject = 0 ,UINT32 nTime = 0 );
    BOOL SendWindowAck(int size); // Window Acknowledgement Size 
    BOOL SendSetPeerBandwidth(int bw1, UINT8 LimitType);
    BOOL SendBytesReceived(UINT32 bytes);



	BOOL SendPlayReset(const char *details = NULL, const char *clientid = NULL);
	BOOL SendPlayStart(const char *details = NULL, const char *clientid = NULL);
	BOOL SendPlayNotFound();
	BOOL SendPublishStart(const char * clientId , const char *szDesc);
    BOOL SendUnPublishSuccess(const char * clientId, const char *szDesc);
	BOOL SendRtmpSampleAccess();
	BOOL SendHttpNotFound();
	CObjNetIOBuffer *SendHttpContentLength(int ContentLength);
	

	void IncHttpRequests();
	void DecHttpRequests();
public:
	CRTMPCtx::ConnType m_type;
	CRTMPCtx *m_ctxRtmp;
	CObj *m_objEncrypt;
	

	BOOL		m_bHttpOpened;
	int			m_nTimeoutHttpRequest;
	TIME_T		m_tmHttpRequest;
	CObjBuffer	m_bufHttp;
	INT32		m_nHttpRequests;
	int			m_nHttpIdleCount;
	int			m_HttpDelayIndex;
private:
	MTX_OBJ		m_mtxhttpRequests;
	CObj		m_ctxItem;
	


};


class   _CPP_UTIL_EXPORT CRTMPNetAsync :
	public CObjNetAsync 
{
public:
	typedef enum tagRTMPProtocol
	{
		RTMPProtocolRTMP = 0x01 ,
		RTMPProtocolRTMPT = 0x02 ,

	}RTMPProtocol;
public:
	unsigned int m_Protocol;

	CRTMPNetAsync(	int nWaitTimeoutSeconds = -1,
		int nStackSize = 0,int nMaxConnections = 2000,
		NetAsyncType netType = NetAsyncTypeDefault 
		);
	virtual ~CRTMPNetAsync();

	
	// if you override it please inherit from CRTMPConnContext
	virtual CObjConnContext  * AllocConnContext(CObj *par);
	virtual CObjNetIOBuffer *  CreateRTMPIoBuffer( int Size );
public:
	virtual int OnReceivedHandshake1(CRTMPConnContext *pContext ,const unsigned char * data, int length);
	virtual int OnReceivedHandshake2(CRTMPConnContext *pContext ,const unsigned char * data, int length);
	virtual int OnRTMPReadCompleted(CRTMPConnContext *pContext, CRTMPHeader *header,CObjNetIOBuffer *pBuffer);
	virtual int OnReadCompleted(CObjConnContext *pContext, CObjNetIOBuffer *pBuffer);
	virtual int OnInvalidRTMPIOBuffer(CObjConnContext *pContext, CObjNetIOBuffer *pBuffer,const char *szMsg);

	virtual int OnHttpOpen(CRTMPConnContext *pContext);
	virtual int OnHttpClose(CRTMPConnContext *pContext);
	virtual int OnHttpIdle(CRTMPConnContext *pContext, const char *Id, const char *sequence);
	virtual int OnHttpSend(CRTMPConnContext *pContext, const char *Id, const char *sequence);
private:

};








































#endif



