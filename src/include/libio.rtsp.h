

#ifndef _LIBIO_RTSP_H_
#define _LIBIO_RTSP_H_

typedef void *HRTSP_MGR;
typedef void *HRTSP_IO;

typedef struct tagRTSPRTPMAP
{
	int pt;
	char method[40];
	int rate;
	int channels;
	char fmtp[40];

}RTSPRTPMAP;


typedef struct tagRTSPSTREAM
{
	char m[40];
	char control[40];
	RTSPRTPMAP rtpmap;
	char mimetype[40];
	int  AvgBitRate;
	int  MaxBitRate;
	char pixel[12];
	double length;
	void *vUsrData;
}RTSPSTREAM;

typedef int (MYAPI *_CallBackRtpData)(RTSPSTREAM *stream,unsigned char *szBuf,int nLen , void *usrData); /* return the data you have read , -1 abort */

#ifdef __cplusplus
extern "C"
{
#endif

int   MYAPI LibIO_RtspHandleSize();
HRTSP_MGR MYAPI LibIO_RtspCreate(void *pBuffer /* may be NULL */);
void  MYAPI LibIO_RtspDestroy(HRTSP_MGR hRtsp);
void  MYAPI LibIO_RtspClear(HRTSP_MGR hRtsp);
void  MYAPI LibIO_RtspAddRawHead(HRTSP_MGR hRtsp,const char *szHead,int nLen);
void  MYAPI LibIO_RtspSetDefaultUserAgent(const char *szDefUserAgent);
void  MYAPI LibIO_RtspSetUserAgent(HRTSP_MGR hRtsp,const char *szUserAgent);

int MYAPI LibIo_RtspCalculateRequestSize(HRTSP_MGR hRtsp);
int  MYAPI LibIO_RtspGetReturnContentLength(HRTSP_MGR hRtsp);
const char *  MYAPI LibIO_RtspGetReturnHead(HRTSP_MGR hRtsp);
BOOL  MYAPI LibIO_RtspSendRequest(HRTSP_MGR hRtsp,SOCKET soc ,BOOL bGetResult);
BOOL  MYAPI LibIO_RtspReadResult(HRTSP_MGR hRtsp,SOCKET soc ,char *szInBuffer,int nLen);

int   MYAPI LibIO_RtspRead(HRTSP_MGR hRtsp,SOCKET soc,char *szBuf,int nLen);
int   MYAPI LibIO_RtspReadLoop(HRTSP_MGR hRtsp,SOCKET soc,char *szBuf,int nLen);
BOOL    MYAPI LibRtspOn_RTSPCmdRTCP( HRTSP_IO hIo,UINT8 Channel , int nLength);
BOOL    MYAPI LibRtspOn_RTSPCmdRecv( HRTSP_IO hIo);

const RTSPSTREAM *  MYAPI LibRtspStream(HRTSP_IO hIo,int streamIndex);
int         MYAPI LibRtspReturnCode(const char *szHead);
HRTSP_MGR		MYAPI LibRtspMgrHandle( HRTSP_IO hIo );
SOCKET		MYAPI LibRtspSocket( HRTSP_IO hIo );
HRTSP_IO    MYAPI LibRtspOpen(const char *szURL,SOCKET soc);
HRTSP_IO    MYAPI LibRtspOpenSdp(const char *szURL,SOCKET soc,char *szSdpRet,int *nSdpBufLenInOut, const char *szSetupExtHeader);
void        MYAPI LibRtspClose( HRTSP_IO hIo);

int         MYAPI LibRtspSeek( HRTSP_IO hIo,int nPosition );

int			MYAPI LibRtspCacheDataAvailable( HRTSP_IO hIo);
int         MYAPI LibRtspDataAvailable( HRTSP_IO hIo);
int         MYAPI LibRtspReadRTP( HRTSP_IO hIo,void * buffer , int nLen);
void		MYAPI LibRtspSetReadRTPHead ( HRTSP_IO hIo , BOOL bRead);
int         MYAPI LibRtspRead( HRTSP_IO hIo,void * buffer , int nLen);
int			MYAPI LibRtspReadCache( HRTSP_IO hIo,void * buffer , int nLen);
int         MYAPI LibRtspReadEx( HRTSP_IO hIo,_CallBackRtpData funcRtpData , void *vData);
int			MYAPI LibRtspNoop( HRTSP_IO hIo );


#ifdef __cplusplus
}
#endif



#endif

