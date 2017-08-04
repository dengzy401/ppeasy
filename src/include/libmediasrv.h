

#ifndef _libmediasrv_h_
#define _libmediasrv_h_
	


#if defined(_NO_MEDIASRV_EXPORT)
#define _MEDIASRV_EXPORT
#elif !defined(_MEDIASRV_EXPORT)
#ifdef WIN32
#ifdef _MSC_VER
#define _MEDIASRV_EXPORT __declspec(dllimport)
#else
#define _MEDIASRV_EXPORT
#endif
#else
#define _MEDIASRV_EXPORT
#endif
#endif



#ifdef __cplusplus
extern "C"
{
#endif

#ifndef MYAPI

	#if defined(WIN32) || defined(_WIN32_WCE)

	#define MYAPI WINAPI

	#else

	#define MYAPI

	#endif

#endif






	BOOL MYAPI MediaSrvStart();
	void MYAPI MediaSrvStop();

	
	typedef int     (MYAPI *_MediaInitCallback)(const char *configFile, const char *appPath); //return TRUE success
	typedef void *  (MYAPI *_MediaOpenCallback)(const char *configFile, const char *appPath);
	typedef void    (MYAPI *_MediaCloseCallback)(void *handle);

	_MEDIASRV_EXPORT const char * CtxType2String(int type);

#ifdef __cplusplus
}
#endif	
	
class CObjVar;
class CCtx;
class _MEDIASRV_EXPORT CMediasrvCallback
{
public:
	CMediasrvCallback();
	virtual ~CMediasrvCallback();

public:
	virtual int OnStreamWillPublish(CCtx *ctx);
	virtual int OnStreamPublished(CCtx *ctx);
	virtual int OnStreamPublishClosed(CCtx *ctx);

	virtual int OnStreamWillPlay(CCtx *ctx);
    virtual int OnStreamPlayStarted(CCtx *ctx);
	virtual int OnStreamPlayClosed(CCtx *ctx);

	virtual int OnInvalidRequestClosed(CCtx *ctx);


    virtual int OnStreamRecordFinished(CCtx *ctx, const char *szFileName, const char *szFilePath, double dur,
        const char *szBeginTime, const char *szEndTime, const char *szType);
    virtual int OnStreamRecordFlush(CCtx *ctx);

    virtual int OnStreamHLSRecordFinished(CCtx *ctx, const char *szFileName, const char *szFilePath, double dur,
        const char *szBeginTime, const char *szEndTime);

    virtual int OnStreamHLSFlush(CCtx *ctx);
    virtual int OnStreamHLSReOpen(CCtx *ctx);

    virtual int IsInLocalNetwork(const char *reqDevId, CObjVar *outAddress);
	virtual int OnGetSourceStreamURL(const char *szApp ,const char *szStream, CObjVar *outAddress); //  for cdn support


};

_MEDIASRV_EXPORT int CtxAddRef(CCtx *ctx);
_MEDIASRV_EXPORT int CtxRelease(CCtx *ctx);
_MEDIASRV_EXPORT int CtxClose(CCtx *ctx);
_MEDIASRV_EXPORT int CtxGetConnections(CCtx *ctx);

_MEDIASRV_EXPORT int GetStreamConnections(const char *szApp ,const char *szStream);
_MEDIASRV_EXPORT int CtxSendCall(CCtx *ctx,const char *szMethod,CObjVar *value);

_MEDIASRV_EXPORT int GetDevId(CRefString *value);
_MEDIASRV_EXPORT int GetNodeName(CRefString *value);



_MEDIASRV_EXPORT int ConfigSetRecordType(const char *type);
_MEDIASRV_EXPORT int ConfigSetRecordDuration(int seconds);
_MEDIASRV_EXPORT int ConfigSetRecordFormat(const char *format);

_MEDIASRV_EXPORT int ConfigSetRecordTsPath(const char *path);
_MEDIASRV_EXPORT int ConfigSetRecordMp4Path(const char *path);
_MEDIASRV_EXPORT int ConfigSetRecordFlvPath(const char *path);

_MEDIASRV_EXPORT int ConfigSetRecordTsEnable(BOOL enable);
_MEDIASRV_EXPORT int ConfigSetRecordMp4Enable(BOOL enable);
_MEDIASRV_EXPORT int ConfigSetRecordFlvEnable(BOOL enable);

#endif





