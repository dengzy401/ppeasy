
#ifndef _libcpputil_net_websocket_h_
#define _libcpputil_net_websocket_h_

#ifndef _LIBCPPUTIL_NET_H_
#include "libcpputil_net.h"
#endif
class _CPP_UTIL_EXPORT CWebSocketState
{
public:
	typedef enum tagMessageType
	{
		MessageTypeUnknown ,
		MessageTypeBinary ,
		MessageTypeText ,
		MessageTypeCustom,

	}MessageType;
public:
	CWebSocketState();
	void Clear();
	BOOL fin;
	int rsv ;
	UINT8 mask[4];
	int maskIndex;
	int opCode;
	int state;
	int payloadLength ;
	int payloadWritten ;
	MessageType messageType;
	BOOL continuationExpected;
	BOOL bMask;
};
class CWebSocketNetAsync;
class  _CPP_UTIL_EXPORT  CWebSocketConnContext :
    public CObjConnContext 
{
    friend class CWebSocketNetAsync;

public:
    _CPP_UTIL_DYNAMIC_DECLARE(CWebSocketConnContext)  ;
    _CPP_UTIL_CLASSNAME_DECLARE(CWebSocketConnContext) ;
    _CPP_UTIL_QUERYOBJ_DECLARE(CWebSocketConnContext) ;
    CWebSocketConnContext();
    virtual ~CWebSocketConnContext();
    virtual BOOL InitLater();
	BOOL Send(const  char * data , int nDataLen = -1 , CWebSocketState::MessageType type = CWebSocketState::MessageTypeText );
	BOOL SendPing();
	BOOL SendPong();
	BOOL SendClose();
public:
	int  m_MaxHttpHeaderSize;
	int  m_MaxMessageSize;
public:
	TIME_T m_tmLastSend;
	BOOL m_bSendWithMask;
	char m_szMethod[8];
	char m_szURI[ 2048 ];
	char m_szHost[80];
	BOOL m_bWebSocket;
	CObjBuffer m_buf;
	CObjBuffer m_bufMessage;
	BOOL m_bConnected;
	CWebSocketState m_state;
	

};

class  _CPP_UTIL_EXPORT  CWebSocketNetAsync :
    public CObjNetAsync 
{
public:

	CWebSocketNetAsync(	int nWaitTimeoutSeconds = -1,
					int nStackSize = 0,int nMaxConnections = 2000,
					NetAsyncType netType = NetAsyncTypeDefault 
				);
    virtual ~CWebSocketNetAsync();

    // if you override it please inherit from CWebSocketConnContext
	virtual CObjConnContext  * AllocConnContext(CObj *par);
public:
	virtual int  OnWebSocketConnectionIncoming(CWebSocketConnContext *pContext);
	virtual int  OnWebSocketReadCompleted(CWebSocketConnContext *pContext, const unsigned char *szMessage, int nMessageLen , CWebSocketState::MessageType type );
	virtual void OnWebSocketErrorMessage(CWebSocketConnContext *pContext, const char *szMessage);
	
public:
    virtual int OnReadCompleted(CObjConnContext *pContext, CObjNetIOBuffer *pBuffer);

private:

};



















#endif




