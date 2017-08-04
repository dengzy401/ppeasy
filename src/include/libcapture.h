
#ifndef _libcapture_h_
#define _libcapture_h_

#include "gps_util.h"



#ifndef _CPP_CAPTURE_EXPORT
#ifdef WIN32
#ifdef _MSC_VER
#define _CPP_CAPTURE_EXPORT __declspec(dllimport)
#else
#define _CPP_CAPTURE_EXPORT
#endif
#else
#define _CPP_CAPTURE_EXPORT
#endif
#endif

class CObjEncoderAudio;
class CObjEncoderVideo;
class _CPP_CAPTURE_EXPORT CCapture 
{
public:
	typedef enum tagConvertFlags
	{
		ConvertFlagSwapTopBottom = 0x01,
		ConvertFlagSwapLeftRight = 0x02,

	}ConvertFlags;
	typedef enum tagNetworkEvent
	{
        NetworkEventUnknown,
		NetworkEventConnecting,
		NetworkEventConnected,
		NetworkEventConnectFailed,
		NetworkEventLogining,
		NetworkEventLogined,
		NetworkEventLoginFailed,
		NetworkEventTransfering,
		NetworkEventDisconnected,
		NetworkEventRedirected,
		NetworkEventClosed,
		NetworkEventNetError,


		NetworkEventRTMPConnecting,
		NetworkEventRTMPConnected,
		NetworkEventRTMPConnectFailed,
		NetworkEventRTMPConnectingStream,
		NetworkEventRTMPConnectingStreamFailed,
		NetworkEventRTMPConnectedStream,
		NetworkEventRTMPTransfering,
		NetworkEventRTMPDisconnected,
		NetworkEventRTMPRedirected,
		NetworkEventRTMPClosed,
		NetworkEventRTMPNetError,
	}NetworkEvent;

    typedef enum tagRecordEv
    {
        RecordEvUnknown,
        RecordEvTSStart,
        RecordEvTSStop,
        RecordEvTsPause,

        RecordEvMp4Start,
        RecordEvMp4Stop,
        RecordEvMp4Pause,


		RecordEvUdpStart,
		RecordEvUdpStop,
		RecordEvUdpPause,

    }RecordEv;
public:
	CCapture();
	virtual ~CCapture();
public:
	static const char * NetworkEvent2Text(CCapture::NetworkEvent ev);
    static TIME_T OSTime();
	static void Exit();
    
    int Convert( const LibCamFrame *fromImg,  LibCamFrame *toImg , int flags);
	int Convert(const LibCamFrame *fromImg, LibCamDMAFrame *toImg, int flags);
    
	void SetVideoDev(const char *dev);
	void SetAudioDev(const char *dev);

	HCAM GetVideoHandle();
	void SetV4LInput(int index);
	void SetId(const char *szId);

	void SetParameter(const char *szPar);
	void SetPreviewRect( const LibCamRect *rt);

    void SetPreviewOnly(BOOL bPreviewOnly);
    
    
    void AppleAddVideoPreviewLayer(  void *layer);
    void AppleRemoveVideoPreviewLayer();
    

	void UseAudioInVideoCard( BOOL bUse);
	BOOL UseAudioInVideoCard();

	// record ts file
	void SetRecordPath(const char *path);
	void SetRecordDevicePath(const char *path);
	void SetRecordFileSplitTime(int minutes);
	BOOL StartRecord();
	void StopRecord();
	BOOL IsRecording();
    void SetRecordSingleFile(const char *szFile );
	void SuspendRecord(BOOL bSuspend);
	BOOL IsRecordSuspend();
	void RecordEnablePCR(BOOL bEnable);

    
	// record mp4 file
	void SetRecordPathMp4(const char *path);
	void SetRecordFileSplitTimeMp4(int minutes);
    void SetRecordSingleFileMp4( const char *szFile );
    BOOL StartRecordMp4();
    void StopRecordMp4( );
    BOOL IsRecordingMp4( );




	void CaptureSuspend(BOOL bSuspend, BOOL bClose);
	BOOL StartCapture();
	void StopCapture();
	BOOL IsCapturing();
	void EnableSound(BOOL bEnable);
	void EnableVideo(BOOL bEnable);
	void Mute(BOOL bMute);
	void SetVideoQuality(LibCamQuality  quality);
	void SetVideoSize(int width,int height);

	void SetNetworkKeepAlive(BOOL bKeepAlive);


	void SetServerAddress(const char *ip);
    BOOL Connect2Server( );
	void Disconnect();
	BOOL IsConnected();
	BOOL IsConnecting();

	void SetUdpAddress(const char *ip);
	BOOL StartUdp();
	void StopUdp();
	BOOL IsUdpRunning();
	int  GetUdpPort();
	void  SetUdpPort(int nPort);


	void SetRTMPServerAddress(const char *ip);
    BOOL Connect2RTMPServer( );
	void DisconnectRTMP();
	BOOL IsConnectedRTMP();
    void SetRTMPApplication(const char *app);

    int  DirectSendVideoFrame(LibCamFrame *frame , TIME_T tm);
    int  DirectSendAudioFrame(LibAudioFrame *frame , TIME_T tm);
	int  DirectSendText(const char *szText,int nLen, XCodec codec,TIME_T tm = -1);



	void SetUser(const char *szUsr);
	void SetPassword(const char *szPwd);

	void SetSessionId(const char *szId);
	const char *GetSessionId();

	BOOL  VideoIoCtl( int id , void *value);
	int  TakePicture(const char *szFile);
	void  SetNetworkUseSecondaryVideoChannel(BOOL bEnable);
	void  SetSendInQueue(BOOL bEnable);
public:
	void SetAlarm(BOOL bAlarm);
	BOOL GetAlarm();
	void SetAlarmData(const char *szData);
	
	BOOL StartGps(const char *dev, const char *bandrate);
	BOOL IsGpsRunning();
	TIME_T GetGpsInfo(GPS_INFO *gpsInfo);
	void   StopGps();
public:
	virtual int  OnError(int no , const char *szText);
	virtual int  OnNetworkEvent(CCapture::NetworkEvent ev);
	virtual void OnVideoFrame(LibCamFrame *videoFrame);
	virtual BOOL OnGetNextRecordFile(char *szPath ,int nLen);
	virtual BOOL OnGetNextRecordFileMp4(char *szPath, int nLen);
    virtual void OnRecordEvent(CCapture::RecordEv ev);
	virtual void OnGpsData(GPS_INFO *gps,const char *szHead);
	virtual void OnTakePictureCallback(LibCamFrame *pathFrame);
	virtual void OnAudioEncoderCreated(CObjEncoderAudio *encoder);
	virtual void OnVideoEncoderCreated(CObjEncoderVideo *encoder);

private:
	void *m_obj;
};













#endif





