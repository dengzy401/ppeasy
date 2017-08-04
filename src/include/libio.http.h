

#ifndef _LIBIO_HTTP_H_
#define _LIBIO_HTTP_H_

typedef void *HHTTP;

#ifdef __cplusplus
extern "C"
{
#endif

int   MYAPI LibIO_HttpHandleSize();
HHTTP MYAPI LibIO_HttpCreate(void *pBuffer /* may be NULL */);
void  MYAPI LibIO_HttpDestroy(HHTTP hHttp);
void  MYAPI LibIO_HttpClear(HHTTP hHttp);
void  MYAPI LibIO_HttpAddRawHead(HHTTP hHttp,const char *szHead,int nLen);
void  MYAPI LibIO_HttpSetPostData(HHTTP hHttp,const void *vDataPost,int nLen);
void  MYAPI LibIO_HttpSetDefaultUserAgent(const char *szDefUserAgent);
void  MYAPI LibIO_HttpSetUserAgent(HHTTP hHttp,const char *szUserAgent);
void  MYAPI LibIO_HttpSetSeekPosition(HHTTP hHttp,int seekPosition);
const char *  MYAPI LibIO_HttpGetReturnHead(HHTTP hHttp);
int  MYAPI LibIO_HttpGetReturnContentLength(HHTTP hHttp);
int  MYAPI LibIO_HttpReturnCode(HHTTP hHttp);

BOOL  MYAPI LibIO_HttpOpen(HHTTP hHttp,SOCKET soc,const char *szUrl);
int   MYAPI LibIO_HttpRead(HHTTP hHttp,SOCKET soc,char *szBuf,int nLen);
int   MYAPI LibIO_HttpWrite(HHTTP hHttp,SOCKET soc,const char *szBuf,int nLen);
void  MYAPI LibIO_HttpClose( HHTTP hHttp );
int   MYAPI LibIO_HttpDataAvailable(HHTTP hHttp,SOCKET soc);

#ifdef __cplusplus
}
#endif



#endif

