
#ifndef _LIBCPPUTIL_NET_H_
#define _LIBCPPUTIL_NET_H_

#ifndef _LIBCPPUTIL_H_
#include "libcpputil.h"
#endif



class CObjNetAsync;

class  _CPP_UTIL_EXPORT  CObjNetIOBuffer :
    public CObj 
{

public:
    _CPP_UTIL_DYNAMIC_DECLARE(CObjNetIOBuffer)  ;
    _CPP_UTIL_CLASSNAME_DECLARE(CObjNetIOBuffer) ;
    _CPP_UTIL_QUERYOBJ_DECLARE(CObjNetIOBuffer) ;

    typedef enum tagIOOpType
    {
        IOOpTypeUnkown,
        IOOpTypeAccept,
        IOOpTypeRead,
        IOOpTypeWrite,
        IOOpTypeConnect,

    }IOOpType;

public:
    void * operator new( size_t cb );
    void operator delete( void* p );

    CObjNetIOBuffer();
    virtual ~CObjNetIOBuffer();
    CObjNetIOBuffer(const CObjNetIOBuffer &src);
    CObjNetIOBuffer & operator =(  const CObjNetIOBuffer& src );
    static const char *IOOpType2Str(CObjNetIOBuffer::IOOpType ioType);
	static int ObjCount();





public:
    char *m_pBuf;
    int  m_nBufLen;
    int  m_nDataLen;
    int  m_nLenTrans;
    IOOpType m_opType;
    

public:

#ifdef WIN32
    WSAOVERLAPPED m_ol;
    SOCKET m_socAccept_Connect;
    unsigned int  m_nSequenceNumber;
	BOOL   m_bV6;
#else
#endif

};

class _CPP_UTIL_EXPORT CObjNetError
{
public:
	CObjNetError();
	virtual ~CObjNetError();
	operator const char *() const; 
    operator int () const;
private:
	const char *m_error;
	int    m_errno;
};

class  _CPP_UTIL_EXPORT  CObjConnContext :
    public CObj 
{
public:
    _CPP_UTIL_DYNAMIC_DECLARE(CObjConnContext)  ;
    _CPP_UTIL_CLASSNAME_DECLARE(CObjConnContext) ;
    _CPP_UTIL_QUERYOBJ_DECLARE(CObjConnContext) ;
public:
    void * operator new( size_t cb );
    void operator delete( void* p );

	static TIME_T UpSeconds();
	static int ObjCount();
    CObjConnContext();
    virtual ~CObjConnContext();
    virtual BOOL InitLater();
    virtual BOOL Send(CObjNetIOBuffer *pBuf);
    virtual void OnClose();
    CObjConnContext(const CObjConnContext &src);
    CObjConnContext & operator =(  const CObjConnContext& src );

    CObj * AttachUserObj( CObj * objUsr, BOOL bAutoRelease = FALSE ) ;
    CObj * ClearUserObj();
    CObj * GetUserObj();

    void Lock();
    void Unlock();

	int PendingBuffers();
	void ClearPendingBuffers();

public:
    /* in your code don't modify the flowing variable, read only */
    SOCKET m_soc;
    INET_ADDR_STR m_AddrLocal;
    INET_ADDR_STR m_AddrRemote;

	int m_nWrittingBytes;

	BOOL m_bConnecting;
    BOOL m_bBadConntext;
    BOOL m_bClosing ;
    TIME_T m_tmConnected;
    TIME_T m_tmLastRead;
    TIME_T m_tmLastWrite;
    TIME_T m_tmLastActive;
    BOOL m_bTriggeredClosedEvent ;
    CObjNetAsync *m_net;

#ifdef WIN32
    unsigned int m_nReadSequence;
    unsigned int m_nCurrentReadSequence;
    CObj m_listOutOfOrderReads;		
    int m_nOutstandingSend;
#else
    BOOL m_bEvent;
#endif
	CObj m_listSendBufs;

private:
    CObj *m_ObjUser;
    BOOL m_bAutoReleaseUserObj;
    MTX_OBJ m_mtx;
    BOOL m_bInited;
};
class  _CPP_UTIL_EXPORT  CObjNetIOBuffer4KB :
	public CObjNetIOBuffer
{
public:
	_CPP_UTIL_DYNAMIC_DECLARE(CObjNetIOBuffer4KB)  ;
	_CPP_UTIL_CLASSNAME_DECLARE(CObjNetIOBuffer4KB) ;
	_CPP_UTIL_QUERYOBJ_DECLARE(CObjNetIOBuffer4KB) ;

	CObjNetIOBuffer4KB();
	virtual ~CObjNetIOBuffer4KB();
private:
	char m_szBuf[4096];
};

class  _CPP_UTIL_EXPORT  CObjNetIOBufferDefault :
    public CObjNetIOBuffer
{
public:
    _CPP_UTIL_DYNAMIC_DECLARE(CObjNetIOBufferDefault)  ;
    _CPP_UTIL_CLASSNAME_DECLARE(CObjNetIOBufferDefault) ;
    _CPP_UTIL_QUERYOBJ_DECLARE(CObjNetIOBufferDefault) ;

    CObjNetIOBufferDefault();
    virtual ~CObjNetIOBufferDefault();
private:
    char m_szBuf[2176];
};

class  _CPP_UTIL_EXPORT  CObjNetIOBufferUDP :
	public CObjNetIOBuffer
{
public:
	_CPP_UTIL_DYNAMIC_DECLARE(CObjNetIOBufferUDP)  ;
	_CPP_UTIL_CLASSNAME_DECLARE(CObjNetIOBufferUDP) ;
	_CPP_UTIL_QUERYOBJ_DECLARE(CObjNetIOBufferUDP) ;

	CObjNetIOBufferUDP();
	virtual ~CObjNetIOBufferUDP();

public:
	INET_ADDR_STR m_AddrRemote;

};

class  _CPP_UTIL_EXPORT  CObjNetIOBufferUDPDefault :
	public CObjNetIOBufferUDP
{
public:
	_CPP_UTIL_DYNAMIC_DECLARE(CObjNetIOBufferUDPDefault)  ;
	_CPP_UTIL_CLASSNAME_DECLARE(CObjNetIOBufferUDPDefault) ;
	_CPP_UTIL_QUERYOBJ_DECLARE(CObjNetIOBufferUDPDefault) ;

	CObjNetIOBufferUDPDefault();
	virtual ~CObjNetIOBufferUDPDefault();
private:
	char m_szBuf[SIZE_2KB];
};

class  _CPP_UTIL_EXPORT  CObjNetIOBufferDynamic :
	public CObjNetIOBuffer
{
public:
	static CObjNetIOBufferDynamic * CreateObj(int bufferSize,int Align = 1024 );
	_CPP_UTIL_CLASSNAME_DECLARE(CObjNetIOBufferDynamic) ;
	_CPP_UTIL_QUERYOBJ_DECLARE(CObjNetIOBufferDynamic) ;

	CObjNetIOBufferDynamic(int bufferSize,int Align = 1024 );
	virtual ~CObjNetIOBufferDynamic();
private:
	char *m_BufAlloced;
};

class  _CPP_UTIL_EXPORT  CObjNetIOBufferSharedMemory:
	public CObjNetIOBuffer
{
public:
	static CObjNetIOBufferSharedMemory * CreateObj(void *memShared,int memSize,BOOL bMalloc2 = TRUE);
	_CPP_UTIL_CLASSNAME_DECLARE(CObjNetIOBufferSharedMemory) ;
	_CPP_UTIL_QUERYOBJ_DECLARE(CObjNetIOBufferSharedMemory) ;

	CObjNetIOBufferSharedMemory(void *memShared,int memSize,BOOL bMalloc2 = TRUE);
	virtual ~CObjNetIOBufferSharedMemory();
	CObjNetIOBufferSharedMemory *Copy();
	CObjNetIOBufferSharedMemory *CopyNoShare();

public:
	char *m_BufShared;
	BOOL m_bMalloc2;
};

class  _CPP_UTIL_EXPORT  CObjNetAsync 
{
public:
	typedef enum tagNetAsyncType
	{
		NetAsyncTypeDefault ,
		NetAsyncTypeSelect ,

	}NetAsyncType;

	typedef enum tagSessionTimeoutType
	{
		SessionTimeoutRead,
		SessionTimeoutWrite,
		SessionTimeoutAll,

	}SessionTimeoutType;
public:


    CObjNetAsync(	int nWaitTimeoutSeconds = -1,
					int nStackSize = 0,int nMaxConnections = 2000,
					NetAsyncType netType = NetAsyncTypeDefault );
    virtual ~CObjNetAsync();
       
    
    void SetSessionTimeout(int nSeconds = -1);
    void SetMaxConnections(int nCount = 2000);
    BOOL BindAddr(int nPort = 80,const char * szBindAddr = NULL, BOOL bIpV6 = FALSE);
    BOOL Start();
    void Shutdown();
	int  GetBindPort(BOOL bIpV6 = FALSE);
    int  GetConnections();

    BOOL Send(CObjConnContext *pContext, CObjNetIOBuffer *pBuffer);
    virtual BOOL Send(CObjConnContext *pContext, const char *szBuffer,int nLen);


    const CObj  *  GetConetxtListHead();
    void LockContextList();
    void UnlockContextList();
    
     

    void CloseConnection(CObjConnContext *pContext);
    void CloseAllConnections();
	void SetName(const char *szName);

    

public: 
    // the follow methods for client use .
    static SOCKET ConnectSocket(char *szAddr,int nPort,unsigned int timeout = 10 );
    static SOCKET ConnectAgentHttps(const char *szAgentUrl,const char *szIP,int nPort,unsigned int timeout = 10);
    static SOCKET ConnectAgentSks4(const char *szAgentUrl,const char *szIP,int nPort,unsigned int timeout = 10);
    static SOCKET ConnectAgentSks5(const char *szAgentUrl,const char *szIP,int nPort,unsigned int timeout = 10);
    BOOL AddSocket2Asyn(CObjConnContext *pSocketConnectByYourself);
	BOOL AddSocket2Asyn(SOCKET soc, INET_ADDR_STR *remoteAddr = NULL, INET_ADDR_STR *localAddr = NULL);

	BOOL Connect(const char *addr ,int port, CObj *par = NULL);

public:
	virtual CObjConnContext  * AllocConnContext(CObj *par);
    virtual CObjNetIOBuffer  * AllocReadIOBuffer();
	virtual CObj * CreateThreadContext();
    CObj *GetThreadContext();

    // return -1 , if you want block the connection
    virtual int OnNewConnectionIncoming(CObjConnContext *pContext);  
    virtual int OnNewConnectionOutgoing(CObjConnContext *pContext);

	virtual int OnConnected(CObjConnContext *pContext);
    virtual int OnConnectionClosed(CObjConnContext *pContext);


    virtual int OnReadCompleted(CObjConnContext *pContext, CObjNetIOBuffer *pBuffer);
    virtual int OnWriteCompleted(CObjConnContext *pContext, CObjNetIOBuffer *pBuffer);
    virtual int OnEventWaitTimeout(int nSeconds);
    // return -1 , if you no want  close the session
    virtual int OnSessionTimeout(CObjConnContext *pContext); 
    virtual int OnMaxConnectionsLimited(CObjConnContext *pContext); 
    virtual int OnEvent();
	virtual int OnError(CObjConnContext *pContext, const char * szTxt);

private:
    CObjNetAsync(const CObjNetAsync &src);
    CObjNetAsync & operator =(  const CObjNetAsync& src );
public:
    SessionTimeoutType m_SessionTimeoutType;
    int m_nMaxConnections ;
    int m_nMaxSends ;
	int m_nMaxWrittingBytes;
    int m_nWaitTimeoutSeconds;
    int m_nSessionTimeoutSeconds;

private:
	NetAsyncType m_netType;
    CObj *m_pNetObj;
};




class  _CPP_UTIL_EXPORT  CObjTcpServer
{
public:
	typedef enum tagBlanceMode
	{
		BlanceModeFast,
		BlanceModeMinimum

	}BlanceMode;
public:
	CObjTcpServer(int nMaxInstance = -1, BlanceMode mode = BlanceModeMinimum, CObjNetAsync::NetAsyncType type = CObjNetAsync::NetAsyncTypeDefault);
    virtual ~CObjTcpServer();
    
	BOOL BindAddr(int nPort = 80, const char * szBindAddr = NULL, BOOL bIpV6 = FALSE);
    BOOL Start();
    void Shutdown();
    int  GetBindPort();
	void SetBlanceMode(BlanceMode mode);
	int  GetConnections();
	void SetMaxInstance(int nMaxInstance);
	void SetSessionTimeout(int timeout);
	CObjNetAsync *GetIdleNet();
public:
	virtual CObjNetAsync *CreateNetInstance();
	virtual int OnNewConnectionIncoming(CObjConnContext *pContext);
    virtual BOOL OnDeleteInstance(CObjNetAsync *ins);
private:
	CObj *m_pNetObj;
};





class  _CPP_UTIL_EXPORT  CObjNetUDP :
	public CObj 
{

public:
	_CPP_UTIL_DYNAMIC_DECLARE(CObjNetUDP)  ;
	_CPP_UTIL_CLASSNAME_DECLARE(CObjNetUDP) ;
	_CPP_UTIL_QUERYOBJ_DECLARE(CObjNetUDP) ;
	CObjNetUDP();
	~CObjNetUDP();

	BOOL BindAddr(int nPort = 80,const char * szBindAddr = NULL);
	BOOL Start();
	void Shutdown();
	int  GetBindPort();
	BOOL Send(CObjNetIOBufferUDP *pBuffer);


	virtual CObjNetIOBufferUDP  * AllocReadIOBuffer();
	virtual int OnReadCompleted(CObjNetIOBufferUDP *pBuffer);


private:
	CObjNetUDP(const CObjNetUDP &src);
	CObjNetUDP & operator =(  const CObjNetUDP& src );
private:
	CObj *m_pNetObj;
};






#endif


