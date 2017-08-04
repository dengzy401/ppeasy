
/* this is a cross-platform network operation API. 		*/
/* use functions PKG_*** can build transaction safe		*/
/* network application. support proxy SOCKS5/4 HTTPS,	*/
/* DNS lookup,NTP time									*/
/********************************************************/
/************* windows/wince/unix/linux	*****************/
/**************author : f117cdh**************************/
/**************e-mail: f117cdh@gmail.com ****************/
/***********bugs report: f117cdh@gmail.com **************/
/********************************************************/

#ifndef _RDE_H_
#define _RDE_H_


#if defined(_WIN32_WCE)
    #define INVALID_RDE  INVALID_SOCKET
	//typedef SYSTEMTIME *  PSYSTEMTIME;

#elif  defined(WIN32)

	#ifndef _WINSOCK2API_
	//#include<winsock2.h>
	#endif

    #define INVALID_RDE  INVALID_SOCKET
#else
    typedef int SOCKET;
    #define INVALID_RDE -1
    #define INVALID_SOCKET -1
#endif


#if !defined(_DNS_TYPE_)

#define _DNS_TYPE_
#ifndef DNS_TYPE_A

#define DNS_TYPE_A 1
#define DNS_TYPE_NS 2
#define DNS_TYPE_CNAME 5
#define DNS_TYPE_SOA 6
#define DNS_TYPE_MX 15
#define DNS_TYPE_ANY 255
#endif

#endif

#ifndef _ADTYPES_H_
#include "adtypes.h"
#endif

#ifndef DEF_TYPE_INT_IP
#define DEF_TYPE_INT_IP
typedef UINT32 INT_IP ;
#endif

#ifndef DEF_TYPE_INT_IPV4
#define DEF_TYPE_INT_IPV4
typedef UINT32 INT_IPV4 ;
#endif

#define PKG_ERROR_SOCKET	-1
#define PKG_ERROR_PKGHEAD	-2
#define PKG_ERROR_READBUF_SMALL	-3


#ifndef DEF_TYPE_INET_ADDR
#define DEF_TYPE_INET_ADDR
typedef struct tagINET_ADDR
{
    INT_IP  addr;
    INT32   port;
}INET_ADDR,*PINET_ADDR;
#endif

#ifndef DEF_TYPE_PKG_HEAD
#define DEF_TYPE_PKG_HEAD

#define _PKG_0 0xBA
#define _PKG_1 0xCE
#define _PKG_2 0xEF
#define _PKG_3 0xAB

typedef struct tagPKG_HEAD
{
    unsigned char  Marker[4];
    INT32 nLenPkg;
}PKG_HEAD,*PPKG_HEAD;
#endif


#ifdef __cplusplus
extern "C"
{
#endif

/*************************************/
const char * MYAPI GetRdeError();
int MYAPI ClearRdeError();
UINT16 MYAPI h2ns(UINT16 nValue);
UINT16 MYAPI n2hs(UINT16 nValue);
/////////////////unix socket///////////////////////////////////
SOCKET MYAPI RDE_Connect2UnixSocket(const char *unix_path , int len_path , int timeout );
SOCKET MYAPI RDE_OpenUnixSocket( const char *unix_path , int len_path );
SOCKET MYAPI RDE_WaitConnectUnixSocket(SOCKET h_rde);
SOCKET MYAPI RDE_OpenLinuxHotplug();
////////////////////////////////////////////////////
const char *MYAPI RDE_Error();
void MYAPI RDE_ErrorFree(const void *p);
void MYAPI RdeTest();
int MYAPI RDE_Init();
int MYAPI RDE_Shutdown(SOCKET h_rde);

SOCKET MYAPI RDE_Open( const char *lpstrIP,int port);
SOCKET MYAPI RDE_WaitConnect(SOCKET h_rde,char *szOutIP,int *nOutPort);
SOCKET MYAPI RDE_Connect(const char *IpAddr,int port,unsigned int timeout);
SOCKET MYAPI RDE_Connect2(const char *IpAddr,int port,unsigned int timeout, SOCKET *pSocConnecting);

SOCKET MYAPI RDE_Socks5Auth(const char *szAgentUrl,unsigned int timeout);
int MYAPI RDE_Socks5Connect(SOCKET hRde,const char *szDomain,INT_IP nIp,int nPort);
void MYAPI UrlParseUPDP(const char *szAgentUrlIn,
						 char *szAgentUser,int nUserLen,char *szAgentPass,int nPassLen,
						 char *szDomain,int nDomainLen,int *pnPort);
SOCKET MYAPI RDE_ConnectWithAgent(const char *szAgentUrl,const char *IpAddr,int port,unsigned int timeout);
SOCKET MYAPI RDE_ConnectAgentSks5(const char *szAgentUrl,const char *szIP,int nPort,unsigned int timeout);
SOCKET MYAPI RDE_ConnectAgentSks4(const char *szAgentUrl,const char *szIP,int nPort,unsigned int timeout);
SOCKET MYAPI RDE_ConnectAgentHttps(const char *szAgentUrl,const char *szIP,int nPort,unsigned int timeout);

SOCKET MYAPI RDE_ConnectEx(INT_IP nIp,int port,unsigned int timeout , SOCKET *pSocConnecting, BOOL bAsync);
BOOL  MYAPI RDE_ConnectX(SOCKET hRdeClient,const char *IpAddr,int port);
BOOL  MYAPI RDE_ConnectXX(SOCKET hRdeClient,INT_IP nIp,int port);
int MYAPI RDE_SetReadTimeout(SOCKET h_rde,int timeout);
int MYAPI RDE_SetWriteTimeout(SOCKET h_rde,int timeout);
int MYAPI RDE_SetReadTimeoutSec(SOCKET h_rde,int timeoutSec);
int MYAPI RDE_SetWriteTimeoutSec(SOCKET h_rde,int timeoutSec);
int MYAPI RDE_Close( SOCKET h_rde);
int MYAPI RDE_CloseEx( SOCKET *phRde);
int MYAPI RDE_WriteStr(SOCKET h_rde,const char *buffer);
int MYAPI RDE_WriteStr0(SOCKET h_rde,const char *buffer);
int MYAPI RDE_Write(SOCKET h_rde,const void *buffer,int size);
int MYAPI RDE_DataAvailable( SOCKET  h_rde );
int MYAPI RDE_Read(SOCKET  h_rde,void *buffer,int size);
int MYAPI RDE_ReadLoop(SOCKET  h_rde,void *buffer,int size);
int MYAPI RDE_ReadLoopNetHead(SOCKET  h_rde,void *buffer,int size);
int MYAPI RDE_ReadLoopNetHead2(SOCKET  h_rde,void *buffer,int size);
int MYAPI RDE_SendRead(SOCKET h_rde,
               const void *vSend ,int nSendSize,
               void *vRec,int nRecSize);
int MYAPI RDE_SendReadLine(SOCKET h_rde,
const void *vSend ,int nSendSize,
void *vRec,int nRecSize);
int MYAPI RDE_ReadLine(SOCKET  h_rde,void *buffer,int size,int *pIsLineEnd);
int MYAPI RDE_GetBindName(SOCKET h_rde,INT_IP *BindIp,int *BindPort,char *szBindIP);
int MYAPI RDE_GetPeerName(SOCKET h_rde,INT_IP *PeerIp,int *PeerPort,char *szPeerIP);
int MYAPI RDE_SoError(SOCKET h_rde);
int MYAPI RDE_ErrorCode(SOCKET h_rde);
BOOL MYAPI RDE_IsTimeout(SOCKET h_rde);
int MYAPI RDE_CancelIO(SOCKET h_rde);
int MYAPI RDE_SetSendBuf(SOCKET h_rde,int bufsize);
int MYAPI RDE_SetRecvBuf(SOCKET h_rde,int bufsize);
///////////////////////////////////////udp function//////////////////////////////////////////////////////////////////////
SOCKET MYAPI RDEU_Open(const  char *lpstrIP,int port);
SOCKET MYAPI RDEU_OpenEx(INT_IP nBindAddr,int nPort);
int MYAPI RDEU_Close( SOCKET h_rde);
int MYAPI RDEU_Write(SOCKET h_rde,const void *buf,int nBufSize,const char *szIp,int nPort);
int MYAPI RDEU_WriteEx(SOCKET h_rde,const void *buf,int nBufSize,INT_IP nDestIp,int nPort);
int MYAPI RDEU_Read(SOCKET h_rde,void *buf,int nBufSize,char *szOutIp, int *nOutPort);
int MYAPI RDEU_ReadEx(SOCKET h_rde,void *buf,int nBufSize,INT_IP *nOutSrcIp,int *nOutPort);
int MYAPI RDEU_WriteXX(SOCKET h_rde,const void *buf,int nBufSize,PINET_ADDR pAddr);
int MYAPI RDEU_ReadXX(SOCKET h_rde,void *buf,int nBufSize,PINET_ADDR pAddr);
///////////////////////////////////////////////////////////////////
const char *MYAPI RDE_GetHostName(char *szHost,int nHostLen);
INT_IP MYAPI RDE_GetIPByName(const char *szHost,char *szIP,int nLen);
#define HAVE_RDE_IP_PORT_
int MYAPI RDE_IP_PORT(const char *szAddr,char *szIPOut,int nIpSize, int *nPortOut);
BOOL MYAPI RDE_GetNtpTime(SYSTEMTIME *pSysTime,SOCKET hRdeU,const char *szTimeHost);
BOOL MYAPI RDE_GetTime(SYSTEMTIME *pSysTime,SOCKET hRdeU,const char *szTimeHost);
//////////////////////////DNS function////////////////////////////////////////////////////
int MYAPI DNS_GetMXAddr(const char *szDNSIP,const char*szHost, char *szMXOut,int nLenOut);
char * MYAPI DNS_GetOSDnsAddr(char *szOutDnsAddr,int nLen);
int MYAPI DNS_GetInfoWithType(const char *szDNSIP,const char*szHost, const UINT16 nDnsType,char *szInfoOut,int nLen);
//////////////////////////pkg function//////////////////////////////////////////////////////////////////
void *MYAPI PKG_Alloc(int size);
void MYAPI PKG_Free(void *p);
int MYAPI  PKG_Write(SOCKET h_rde,const void *buffer,int size);
int MYAPI  PKG_Read(SOCKET h_rde,void *buffer,int size ,int *pnPkgLen);
int MYAPI  PKG_ReadPkgLen(SOCKET h_rde);
int MYAPI  PKG_ReadAlloc(SOCKET h_rde,void **pBuffer);
void MYAPI PKG_Fill(void  *pBuf,int nLenPkg);
int MYAPI IsPkgHead(void  *pBuf);
int MYAPI PKG_GetHeadLen();
int MYAPI PKG_GetPkgLen(void  *pBuf);
BOOL MYAPI RDE_SetSocketBlocking(SOCKET soc ,BOOL bBlock);
/*********************************************************************/
char *MYAPI INT_IP2Str(INT_IP ip,char *szOut ,int nLen);
char *MYAPI INET_ADDR2Str(INET_ADDR *pAddr,char *szOut ,int nLen);
/******************************************************************************/

typedef int (MYAPI * _OnNetworkTimeUpdated)(BOOL bSuccess);
void MYAPI SetNetworkTimeUpdatedFunc(_OnNetworkTimeUpdated _func);
SYSTEMTIME *MYAPI NetworkTime( SYSTEMTIME *pSysTime );
BOOL MYAPI NetworkTimeUpdate();
void MYAPI StartTimeGuard();
void MYAPI StopTimeGuard();
/*************************************************/

UINT64 MYAPI hton_ll(UINT64 n) ;
UINT64 MYAPI ntoh_ll(UINT64 n) ;
double MYAPI ntoh_double(double net_double) ;
double MYAPI hton_double(double host_double) ;


#ifdef __cplusplus
}
#endif



#endif


