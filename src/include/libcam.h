

#ifndef _LIBCAM_H_
#define _LIBCAM_H_

#include "libaudio.h"

#ifndef FOURCCBE
#define FOURCCBE(a,b,c,d) \
	(((UINT8)(a) << 24) | ((UINT8)(b) << 16) | \
	((UINT8)(c) << 8) | ((UINT8)(d) << 0))
#endif

#ifndef FOURCCLE
#define FOURCCLE(a,b,c,d) \
	(((UINT8)(a) << 0) | ((UINT8)(b) << 8) | \
	((UINT8)(c) << 16) | ((UINT8)(d)<< 24))
#endif

#ifndef FOURCC
#ifdef IS_BIG_ENDIAN
#define FOURCC(a,b,c,d) FOURCCBE(a,b,c,d)
#else
#define FOURCC(a,b,c,d) FOURCCLE(a,b,c,d)
#endif
#endif


typedef void *HCAM ;


#define _CAM_DIRECTION_SWAP_TopBottom 0x01
#define _CAM_DIRECTION_SWAP_LeftRight 0x02
#define _CAM_CALLBACK_TYPE_VIDEO 0x01
#define _CAM_CALLBACK_TYPE_AUDIO 0x02

typedef enum tagCamPixelFormat
{
        CamPixelFormatNONE = 0,
        CamPixelFormatYUV420P ,
        CamPixelFormatYUY2 ,
        CamPixelFormatRGB24,
        CamPixelFormatBGR24 ,
        CamPixelFormatUYVY,
        CamPixelFormatJPEG,
        CamPixelFormatNV12,
        CamPixelFormatNV12T,
        CamPixelFormatUYVY422,
        CamPixelFormatRGB32,
        CamPixelFormatBGR32,
        CamPixelFormat32ARGB,
        CamPixelFormatNV21,
        CamPixelFormatRGB565,
        CamPixelFormatYV12,
		CamPixelFormatRGB8,


		CamPixelFormatH264  = 500 ,
		CamPixelFormatH263,
		CamPixelFormatH265,
		CamPixelFormatMJPG,
		CamPixelFormatMPEG4,

        CamPixelFormatAudioPCM = 1000 ,

		CamPixelFormatJpegFile = 2000 ,
		CamPixelFormatFilePath,
	
	

}CamPixelFormat;

typedef enum tagXCodec
{
	XCodecUnknown ,
	XCodecMPEG1 = FOURCC('M','P','G','1') ,
	XCodecMP4V_ES = FOURCC('M','P','4','V') ,
	XCodecH263 = FOURCC('H','2','6','3'),
	XCodecH264 = FOURCC('H','2','6','4'),
	XCodecH265 = FOURCC('H','2','6','5'),
	XCodecJPEG = FOURCC('J','P','E','G'),
	XCodecMJPG = FOURCC('M','J','P','G'),
	XCodecAudioAAC = FOURCC('A','A','C','1') ,
	XCodecAudioAMRNB= FOURCC('A','M','R','N')  ,

	XCodecText = 2000 ,
	XCodecGPS ,

}XCodec ;


#define _H64_NONE_KEY_FRAME  2
#define _H64_KEY_FRAME  4
#define _H64_KEY_FRAME_NO_PATCH  5

typedef enum tagLibCamOption
{
        LibCamOptionUnknown,
        LibCamOptionVFW,
        LibCamOptionDShow,
        LibCamOptionDShow2,
        LibCamOptionIOS,
        LibCamOptionOSX,
        LibCamOptionSocket,
        LibCamOptionDesktop,
        LibCamOptionWindow,
        LibCamOptionV4L2,
        LibCamOptionCallback,
		LibCamOptionDShowAudio,

}LibCamOption;


typedef enum tagLibCamCallbackEvent
{
	LibCamCallbackFrame,
	LibCamCallbackError,
	LibCamCallbackStatus,
	LibCamCallbackControl,
	LibCamCallbackStreamVideo,
	LibCamCallbackStreamAudio,
	LibCamCallbackGetAudioBufferSize,
	LibCamCallbackTakePicture = 1000,

}LibCamCallbackEvent;

typedef enum tagLibCamPosition
{
	LibCamPositionUnknown ,
	LibCamPositionBack   ,
	LibCamPositionFront  
}LibCamPosition;

typedef enum tagLibCamQuality
{
	LibCamQualityUnknown ,
	LibCamQualityLow   ,
	LibCamQualityMid ,
	LibCamQualityHigh ,  
	LibCamQualityPhoto ,
}LibCamQuality;

typedef enum tagLibCamPhyConnType
{
	LibCamPhyConnTypeDefault ,
	LibCamPhyConnTypeVideoTuner,
	LibCamPhyConnTypeVideoComposite   ,
	LibCamPhyConnTypeVideoSVideo ,
	LibCamPhyConnTypeAudioTuner ,  
	LibCamPhyConnTypeAudioLine , 
	LibCamPhyConnTypeAudioMic 
}LibCamPhyConnType;

typedef struct tagLibCamFrame
{
	void *usrData;
	unsigned int flags;
	int width ;
	int height ;
	int bitCount ;
	int bytesPerline ;
	int imageSize;
	int imageActualSize;
	unsigned int sequence ;
	int frameType;
	CamPixelFormat format;
	unsigned char * imageData;
}LibCamFrame;


typedef struct tagCbCrYFrame
{
	void *CbCr;
	void *Y;
	int CbCrLength;
	int YLength;
}CbCrYFrame;

typedef struct tagPlaneFrame
{
	void *Data;
	int DataLength;
}PlaneFrame;

typedef struct tagPlanesFrame
{
	void *Data[4];
}PlanesFrame;

typedef enum tagDMAFrameType
{
	DMAFrameTypeNone,
	DMAFrameTypeCbCrY,
	DMAFrameTypePlane,
	DMAFrameTypePlanes,

}DMAFrameType;

typedef enum tagLibCamWait
{
	LibCamWaitError = -1 ,
	LibCamWaitNoData = 0 ,
	LibCamWaitOk = 1 ,
	LibCamWaitNotSupport ,
}LibCamWait;


typedef struct tagLibCamDMAFrame
{
	DMAFrameType type;
	void *usrData;
	int width ;
	int height ;
	CamPixelFormat format;
	
	union
	{
		CbCrYFrame CbCrY;
		PlaneFrame Plane ;
		PlanesFrame Planes;

	}Frame;

}LibCamDMAFrame;


typedef struct tagLibCamCallbackData
{
	LibCamCallbackEvent ev ;
	void *vUsrData;
    TIME_T tm ;
	union
	{
		LibCamFrame *videoFrame;
		LibAudioFrame *audioFrame;
		LibAudioConfig *audioConfig;

	}data;

}LibCamCallbackData;


typedef int ( MYAPI *_LibCamCallback)( LibCamCallbackData *pData);



typedef struct tagLibCamRect
{
	int x;
	int y;
	int width;
	int height;
}LibCamRect;

typedef struct tagLibCamSize
{
	int width;
	int height;
}LibCamSize;

#define _MAX_SECONDARY_   8
typedef struct tagLibCamPar
{
	unsigned int callbackType;
	_LibCamCallback funcCallback ;
	void *vUsrData;



	int width;
	int height;
	CamPixelFormat pixFormat;
	LibCamRect previewRect;

    

	BOOL haveMsgLoop;
	BOOL bDisplayProperties;
    unsigned int direction;
	int fps;
	LibCamQuality quality;
	LibCamPhyConnType phyConnType;
    int V4L2Input;
	

	LibCamSize secondarySizes[_MAX_SECONDARY_];
	int		   secondaryCount;
	
}LibCamPar;



typedef enum tagLibCamNotify
{
	LibCamNotifyTypeOpen,
	LibCamNotifyTypeClose
}LibCamNotifyType;

typedef void   ( MYAPI *_OnLibCamNotify)(LibCamNotifyType ntType,const char *szDevicePath , HCAM hCam );


#ifdef __cplusplus
extern "C"
{
#endif

CamPixelFormat MYAPI String2CamPixelFormat( const char *strFormat);

void MYAPI LibCamCopy2Frame(LibCamFrame *frame , unsigned char *buf , unsigned int direction );
LibCamFrame *  MYAPI LibCamFrameCreate(int nWidth ,int nHeight,int bitCount);
LibCamFrame *  MYAPI LibCamFrameCreateWithLength(int nWidth, int nHeight, int imgSize);
LibCamFrame *  MYAPI LibCamFrameCopy(const LibCamFrame *hImg);
LibCamFrame * MYAPI LibCamFrameAddRef( LibCamFrame *  hImg);
long MYAPI LibCamFrameRelease( LibCamFrame *  hImg);
void *   MYAPI SharedMemCreate24BMP(const LibCamFrame *hImg, BOOL bBottomUp );
BOOL MYAPI LibCamFrameIsCompatible(const LibCamFrame *hImg1, const LibCamFrame *hImg2);
	
	

BOOL MYAPI  LibCamIsV4LDev(const char *szDev);
int MYAPI  LibCamCemeraCount();
BOOL MYAPI  LibCamCameraName(int index, char* sName, int nBufferSize,char* devPath ,int devPathLen);
BOOL MYAPI  LibCamCameraNamePhone(int index, 
								  char* sName, int nBufferSize,
								  char* devPath ,int devPathLen,
								  LibCamPosition *position);


void MYAPI LibCamSetNotify(_OnLibCamNotify funcNotify );
void MYAPI LibCamSetCameraOrientation(int ori);
    
HCAM MYAPI LibCamOpen(const char *szDevicePath , LibCamOption opt,LibCamPar *par);
const char * MYAPI LibCamDevPath( HCAM hCam );
CamPixelFormat MYAPI LibCamPixFormat( HCAM hCam ,int *width,int *height );
BOOL MYAPI LibCamReadFrame(HCAM hCam,LibCamFrame **imgOut );
BOOL MYAPI LibCamReadDMAFrame(HCAM hCam,LibCamDMAFrame *dmaFrame );
int MYAPI LibCamReadFrames(HCAM hCam,LibCamFrame *frames[], int nCount );
int MYAPI LibCamIoctl(HCAM hCam, int code , void *arg);
int MYAPI  LibCamSetCtl(HCAM hCam, int id , void *value);
int MYAPI LibCamSendFrame(HCAM hCam, LibCamFrame *frame , TIME_T tm);
    
    
int MYAPI LibCamTakePicture(HCAM hCam,const char *szFile);

LibCamWait MYAPI LibCamWaitForFrame(HCAM hCam , int millisecond);

void MYAPI LibCamClose( HCAM hCam );
BOOL MYAPI LibCamHaveAudio( HCAM hCam );
BOOL MYAPI LibCamGetAudioConfig(HCAM hCam,LibAudioConfig *config);


void MYAPI LibCamShowDlgVideoSource( HCAM hCam );
void MYAPI LibCamShowDlgVideoFormat( HCAM hCam );
void MYAPI LibCamShowDlgVideoDisplay( HCAM hCam );
void MYAPI Win32LibCamCoInit();
void MYAPI Win32LibCamCoUnInit();

    
void LibCamAddAVCaptureVideoPreviewLayer( HCAM hCam , void *layer);
void LibCamRemoveAVCaptureVideoPreviewLayer( HCAM hCam );
void LibCamV4L2EnablePreview(BOOL bEnable);

const char * LibCamGetIOSPreset();
void LibCamSetIOSPreset(const char *preset);
    
void  LibCamPrintf(void *handle, const char *fmt, ...);
    





int    MYAPI  DShowAudioCount();
BOOL   MYAPI  DShowAudioName(int index, char* sName, int nBufferSize, char* devPath, int devPathLen);
HAUDIO MYAPI  DShowAudioOpen(const char *szDevPath, LibAudioOption opt, LibAudioPar *par);
BOOL   MYAPI  DShowAudioStartRecord(HAUDIO hAudio);
void   MYAPI  DShowAudioStopRecord(HAUDIO hAudio);
void   MYAPI  DShowAudioClose(HAUDIO hAudio);
BOOL   MYAPI  DShowAudioGetConfig(HAUDIO hAudio, LibAudioConfig *config);
int    MYAPI  DShowAudioGetMaxBufferSize(HAUDIO hAudio);

#if defined(WIN32) && defined(_USE_CAMAUDIO)
#define LibAudioCount DShowAudioCount
#define LibAudioName DShowAudioName
#define LibAudioOpen DShowAudioOpen
#define LibAudioStartRecord DShowAudioStartRecord
#define LibAudioStopRecord DShowAudioStopRecord
#define LibAudioClose DShowAudioClose
#define LibAudioGetConfig DShowAudioGetConfig
#define LibAudioGetMaxBufferSize DShowAudioGetMaxBufferSize

#endif

#ifdef __cplusplus
}
#endif






#endif




