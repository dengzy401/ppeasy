

#ifndef _libwebmsgsrv_h_
#define _libwebmsgsrv_h_


typedef enum tagWebMsgLoginMode
{
    WebMsgLoginModeUnknown,
    WebMsgLoginModeWebsocket,
    WebMsgLoginModeRTMP,
    WebMsgLoginModePKG,

}WebMsgLoginMode;



class    IObjWebMsgSrvPlugin:
    public CObj
{

public:
    virtual void OnIdle( ) = 0;
    virtual BOOL OnLogin( const char *szID, const char *szPwd, const char *szLoginIp, WebMsgLoginMode  mode, SYSTEMTIME *sysTime ) = 0;
    virtual BOOL OnAuth( const char *szID, const char *szPwd, const char *szLoginIp, WebMsgLoginMode  mode, SYSTEMTIME *sysTime ) = 0;
    virtual BOOL OnGuestLogin( const char *szID, const char *szLoginIp, WebMsgLoginMode  mode, SYSTEMTIME *sysTime ) = 0;
    virtual BOOL OnOffline( const char *szID, SYSTEMTIME *sysTime ) = 0;
    virtual void OnSendPeerMessage( const char *szID, const char *szIdPeer, const char *szText, SYSTEMTIME *sysTime ) = 0;
    virtual void OnSendRoomMessage( const char *szID, const char *szIdRoom, const char *szText, SYSTEMTIME *sysTime ) = 0;
    virtual void OnSendPeerNotify( const char *szID, const char *szIdPeer, const char *szText, SYSTEMTIME *sysTime ) = 0;
    virtual BOOL OnEnterRoom( const char *szID, const char *szIdRoom, const char *szPwdRoom, SYSTEMTIME *sysTime ) = 0;
    virtual BOOL OnLeaveRoom( const char *szID, const char *szIdRoom, const char *szReason, SYSTEMTIME *sysTime ) = 0;

};

typedef IObjWebMsgSrvPlugin * (  *_WebMsgSrvCreatePlugin)(const char *configFile) ;
typedef void( *_WebMsgSrvInitPlugin )( const char *configFile );

#endif



























