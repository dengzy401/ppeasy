
#ifndef _libtransbrg_h_
#define _libtransbrg_h_
	

#ifdef __cplusplus
extern "C"
{
#endif

BOOL MYAPI StartTransmitNetwork();
void MYAPI StopTransmitNetwork();


typedef enum tagTransNotifyCode
{
	TransNotifyCodeError = -1,
	TransNotifyCodeErrorConnectSource = -2 ,
	TransNotifyCodeErrorConnectServer = -3 ,
	TransNotifyCodeErrorDisconnectSource = -4 ,
	TransNotifyCodeErrorDisconnectServer = -5 ,
	TransNotifyCodeErrorIO = -6 ,
	TransNotifyCodeOk = 0,
	TransNotifyCodeMediaIdReturned  ,

}TransNotifyCode;

typedef void *TransBrigeHandle;

typedef int ( *_TransBrigeNotify)(TransBrigeHandle handle, TransNotifyCode notifyCode,const char *message, void *usrData);

TransBrigeHandle  MYAPI TransBrigeOpen(const char *srcAddr, const char *dstAddr,const char *nameUtf8, const char *szId, _TransBrigeNotify funcNotify, void *usrData);
void MYAPI TransBrigeClose( TransBrigeHandle handle);
BOOL MYAPI TransBrigeIsDisconnected( TransBrigeHandle handle);
const char* MYAPI TransBrigeGetId(TransBrigeHandle handle, char *szIdOut,int nIdLen );
const char * MYAPI TransBrigeNotifyCodeString( TransNotifyCode  code );

SOCKET MYAPI OpenTransmitServer(const char *srcAddr , const char *dstAddr , const char *nameUtf8,
									char *szIdOut,int nIdLen );
void  MYAPI TransBrigeSetDeviceId(const char *id);
int  MYAPI TransBrigeStartJob(const char *iniPath);

#ifdef __cplusplus
}
#endif



#endif






















