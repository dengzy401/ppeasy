
#ifndef _libxencoder_h_
#define _libxencoder_h_




#ifndef _XENCODER_EXPORT
	#if defined(WIN32) && !defined(_XENCODER_STATIC)
		#ifdef _MSC_VER
		#define _XENCODER_EXPORT __declspec(dllimport)
		#else
		#define _XENCODER_EXPORT
		#endif
	#else
		#define _XENCODER_EXPORT
	#endif
#endif

#include "libcam.h"
#include "libaudio.h"
#include "libcpputil.h"
#include "libcpputil_var.h"


#define  ENCODER_PRI_DEFAULD  3000

#define PROP_DMAFrameType "DMAFrameType"
#define PROP_AddrY "AddrY"
#define PROP_AddrCbCr "AddrCbCr"
#define PROP_AddrPlane "AddrPlane"
#define PROP_GopSize "gopsize"
#define PROP_CBR "cbr"
#define PROP_VBR "vbr"
#define PROP_FPS "fps"
#define PROP_DeInterlace "DeInterlace"
#define PROP_NoDelay "nodelay"
#define PROP_NaluSplitLen "nalusplitlen"


#define PROP_quality "quality"
#define PROP_vbrflag "vbrflag" 
#define PROP_bitrate "bitrate" 
#define PROP_speed_level "speed_level" 
#define PROP_band_width "band_width" 


#define  _AMR_BLOCK_ 320
#define  _AMR_MAGIC_NUMBER "#!AMR\n"
#define  _AMR_MAGIC_LEN     6


#ifndef _H264_TYPE_
#define _H264_TYPE_



typedef enum tagNaluType
{
	NALU_TYPE_SLICE    = 1,
	NALU_TYPE_DPA      = 2,
	NALU_TYPE_DPB      = 3,
	NALU_TYPE_DPC      = 4,
	NALU_TYPE_IDR      = 5,
	NALU_TYPE_SEI      = 6,
	NALU_TYPE_SPS      = 7,
	NALU_TYPE_PPS      = 8,
	NALU_TYPE_AUD      = 9,
	NALU_TYPE_EOSEQ    = 10,
	NALU_TYPE_EOSTREAM = 11,
	NALU_TYPE_FILL     = 12,
#if (MVC_EXTENSION_ENABLE)
	NALU_TYPE_PREFIX   = 14,
	NALU_TYPE_SUB_SPS  = 15,
	NALU_TYPE_SLC_EXT  = 20,
	NALU_TYPE_VDRD     = 24  // View and Dependency Representation Delimiter NAL Unit
#endif
} NaluType;


#define _I_FRAME 1
#define _P_FRAME 2
#define _B_FRAME 3

typedef struct {
	//byte 0
	unsigned char TYPE:5;
	unsigned char NRI:2;
	unsigned char F:1;    

} NALU_HEADER; /**//* 1 BYTES */

typedef struct {
	//byte 0
	unsigned char TYPE:5;
	unsigned char NRI:2; 
	unsigned char F:1;    


} FU_INDICATOR; /**//* 1 BYTES */

typedef struct {
	//byte 0
	unsigned char TYPE:5;
	unsigned char R:1;
	unsigned char E:1;
	unsigned char S:1;    
} FU_HEADER; /**//* 1 BYTES */

typedef struct
{
	int startcodeprefix_len;      //! 4 for parameter sets and first slice in picture, 3 for everything else (suggested)
	int len;                 //! Length of the NAL unit (Excluding the start code, which does not belong to the NALU)
	//	unsigned max_size;            //! Nal Unit Buffer size
	int forbidden_bit;            //! should be always FALSE
	int nal_reference_idc;        //! NALU_PRIORITY_xxxx
	int nal_unit_type;            //! NALU_TYPE_xxxx   
	int frame_type;
	unsigned char *buf;                    //! contains the first byte followed by the EBSP
	unsigned short lost_packets;  //! true, if packet loss is detected
} NALU_T;

#endif

typedef struct tagEncodedFrame
{
    
	unsigned char *data;
	int datalen;
	int type;
    int width;
    int height;
	XCodec codec;

}EncodedFrame;

class _XENCODER_EXPORT CEncodedFrame:
	public EncodedFrame
{
public:
	CEncodedFrame(unsigned char *dat = NULL,int len = 0 );
	virtual ~CEncodedFrame();
};

typedef struct tagCEncoderInfo
{
	UINT32 Id;
	const char* Name;
	const char* ContentType;

} CEncoderInfo;

class _XENCODER_EXPORT CObjEncoder:
	public CObj
{
	_CPP_UTIL_DYNAMIC_DECLARE(CObjEncoder)  ;
	_CPP_UTIL_CLASSNAME_DECLARE(CObjEncoder)  ;
	_CPP_UTIL_QUERYOBJ_DECLARE(CObjEncoder)  ;
public:
	CObjEncoder();
	virtual ~CObjEncoder();
public:

	static void Init();
	static BOOL Register(const char *szPath);
	static BOOL Register(const char* className, CEncoderInfo *codecInfo, int pri, void *pfuncCreate );
	static CObjEncoder *CreateEncoderById(UINT32 Id);
	static CObjEncoder *CreateEncoderByContentType(const char * ContentType);

	static unsigned char PT(XCodec codec);
	const char *GetRtspSDP(XCodec codec,int trackId,char *buffer,int len,int samplesRate = 0);
	const char *GetRtspSDP(int trackId,char *buffer,int len);

	void  SetCodec(XCodec codec);
	XCodec GetCodec();
	unsigned char PT();
	const char *GetEncoderName();

	virtual int GetSamplesRate();
	virtual BOOL Set(const char *name, const CObjVar  &Val);
	virtual BOOL Get(const char *name, CObjVar  &Val);

public:
	XCodec m_codec;
protected:
	const CEncoderInfo *m_CodecInfo;

};


class _XENCODER_EXPORT CObjEncoderVideo:
	public CObjEncoder
{
	_CPP_UTIL_DYNAMIC_DECLARE(CObjEncoderVideo)  ;
	_CPP_UTIL_CLASSNAME_DECLARE(CObjEncoderVideo)  ;
	_CPP_UTIL_QUERYOBJ_DECLARE(CObjEncoderVideo)  ;
public:
	CObjEncoderVideo();
	virtual ~CObjEncoderVideo();
public:
	virtual BOOL Init( CamPixelFormat pixFormat ,int width ,int height,int bitrate);
	virtual int  EncodeVideoFrame( LibCamFrame *image, EncodedFrame *encodedFrame ,TIME_T twNow);
	virtual void UnInit();

public:

	int m_width;
	int m_height;
	int m_bitrate;
	CamPixelFormat m_pixFormat;


};

class _XENCODER_EXPORT CObjEncoderAudio:
	public CObjEncoder
{
	_CPP_UTIL_DYNAMIC_DECLARE(CObjEncoderAudio)  ;
	_CPP_UTIL_CLASSNAME_DECLARE(CObjEncoderAudio)  ;
	_CPP_UTIL_QUERYOBJ_DECLARE(CObjEncoderAudio)  ;
public:
	CObjEncoderAudio();
	virtual ~CObjEncoderAudio();
public:
	virtual BOOL Init( LibAudioConfig *config );
	virtual int  EncodeAudio( void *data, int nDataLen, unsigned char *buffer ,int bufferLen ,TIME_T twNow);
	virtual void UnInit();
	virtual int GetSamplesRate();
	virtual BOOL Get(const char *name, CObjVar  &Val);

public:

	LibAudioConfig m_audioConfig;


};















#endif





















































