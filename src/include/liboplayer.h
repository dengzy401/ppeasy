
#ifndef _liboplayer_h_
#define _liboplayer_h_



#ifndef _CPP_OPLAYER_EXPORT
#ifdef WIN32
#ifdef _MSC_VER
#define _CPP_OPLAYER_EXPORT __declspec(dllimport)
#else
#define _CPP_OPLAYER_EXPORT
#endif
#else
#define _CPP_OPLAYER_EXPORT
#endif
#endif

#ifndef WIN32
	#include <pthread.h>
#endif
#include <stdlib.h>
#include "adtypes.h"
#include "adapi.h"

#ifdef __cplusplus
#include "libcpputil.h"
#endif

#define _MAX_URL_ 300

#define FOURCCBE(a,b,c,d) \
	(((UINT8)(a) << 24) | ((UINT8)(b) << 16) | \
	((UINT8)(c) << 8) | ((UINT8)(d) << 0))

#define FOURCCLE(a,b,c,d) \
	(((UINT8)(a) << 0) | ((UINT8)(b) << 8) | \
	((UINT8)(c) << 16) | ((UINT8)(d)<< 24))

#ifdef IS_BIG_ENDIAN
#define FOURCC(a,b,c,d) FOURCCBE(a,b,c,d)
#else
#define FOURCC(a,b,c,d) FOURCCLE(a,b,c,d)
#endif

#define SAFETAIL 256


///////////////////////////////////////////////////////////
#define RSHIFT_ROUND(v,n)	(((v)+(1<<(n-1)))>>(n))
#define SWAP32(a) ((((uint32_t)(a) >> 24) & 0x000000FF) | (((uint32_t)(a) >> 8)  & 0x0000FF00)|\
	(((uint32_t)(a) << 8)  & 0x00FF0000) | (((uint32_t)(a) << 24) & 0xFF000000))
#define SWAP16(a) ((uint16_t)((((uint32_t)(a) >> 8) & 0xFF) | (((uint32_t)(a) << 8) & 0xFF00)))
#define SWAP64(a) (((uint64_t)SWAP32(a) << 32) | SWAP32((uint64_t)(a)>>32))

#ifdef IS_BIG_ENDIAN
#define INT64BE(a) (a)
#define INT64LE(a) SWAP64(a)
#define INT32BE(a) (a)
#define INT32LE(a) SWAP32(a)
#define INT16BE(a) (a)
#define INT16LE(a) SWAP16(a)
#else
#define INT64LE(a) (a)
#define INT64BE(a) SWAP64(a)
#define INT32LE(a) (a)
#define INT32BE(a) SWAP32(a)
#define INT16LE(a) (a)
#define INT16BE(a) SWAP16(a)
#endif

#define CRGB(r,g,b) INT32LE((r)|((g)<<8)|((b)<<16))

//////////////////////////////////////////////////////////
//pixelformat flags
#define	PF_FOURCC		0x0001
#define	PF_PALETTE		0x0002
#define	PF_RGB			0x0004
#define	PF_YUV			0x0008
#define	PF_INVERTED		0x0020
#define PF_READONLY		0x0040
#define PF_FRAGMENTED	0x0080
#define PF_PIXELDOUBLE	0x0100
#define PF_16BITACCESS	0x0200
#define PF_16ALIGNED	0x0400
#define PF_SAFEBORDER	0x0800
#define PF_NOPREROTATE	0x4000
#define PF_GRAYSCALE	0x8000
#define PF_PTS			0x20000
#define PV_YUV_TV		0x00000
#define PF_YUV_PC		0x40000
#define PF_YUV_BT601	0x00000
#define PF_YUV_BT709	0x80000

#define	PF_YUV420		0x0010
#define	PF_YUV422		0x1000
#define	PF_YUV444		0x2000
#define	PF_YUV410		0x10000


//---------------------------------------------------------------
//private rgb fourcc
#define	FOURCC_RGB32 	FOURCC('R','3','2','_')
#define	FOURCC_RGB24 	FOURCC('R','2','4','_')
#define	FOURCC_RGB16 	FOURCC('R','1','6','_')
#define	FOURCC_RGB15 	FOURCC('R','1','5','_')

#define	FOURCC_BGR32 	FOURCC('B','3','2','_')
#define	FOURCC_BGR24 	FOURCC('B','2','4','_')
#define	FOURCC_BGR16 	FOURCC('B','1','6','_')
#define	FOURCC_BGR15 	FOURCC('B','1','5','_')

//---------------------------------------------------------------
//planar YUV420 formats
#define	FOURCC_YV12 	FOURCC('Y','V','1','2')
#define	FOURCC_IYUV 	FOURCC('I','Y','U','V')
#define	FOURCC_I420 	FOURCC('I','4','2','0')
#define	FOURCC_IMC2 	FOURCC('I','M','C','2')
#define	FOURCC_IMC4 	FOURCC('I','M','C','4')

//planar YUV422 formats
#define	FOURCC_YV16 	FOURCC('Y','V','1','6')

//planar YUV410 formats
#define	FOURCC_YVU9 	FOURCC('Y','V','U','9')
#define	FOURCC_YUV9 	FOURCC('Y','U','V','9')

//---------------------------------------------------------------
//packed YUV formats
#define	FOURCC_YUY2 	FOURCC('Y','U','Y','2')
#define	FOURCC_YUNV 	FOURCC('Y','U','N','V')
#define	FOURCC_V422 	FOURCC('V','4','2','2')
#define	FOURCC_YUYV 	FOURCC('Y','U','Y','V')
#define	FOURCC_YVYU 	FOURCC('Y','V','Y','U')
#define	FOURCC_UYVY 	FOURCC('U','Y','V','Y')
#define	FOURCC_Y422		FOURCC('Y','4','2','2')
#define	FOURCC_UYNV		FOURCC('U','Y','N','V')
#define	FOURCC_VYUY 	FOURCC('V','Y','U','Y')

//---------------------------------------------------------------
//direction flags
#define	DIR_SWAPXY			0x001
#define	DIR_MIRRORLEFTRIGHT	0x002
#define	DIR_MIRRORUPDOWN	0x004

//---------------------------------------------------------------
//vide caps
#define	VC_DITHER		0x0001
#define	VC_BRIGHTNESS	0x0002
#define	VC_CONTRAST		0x0004
#define	VC_SATURATION	0x0008
#define	VC_RGBADJUST	0x0010

#define SCALE_ONE	(1<<16)
#define ASPECT_ONE	(1<<16)
#define ASPECT_RATIO(num,den)  ((int)(((int64_t)num<<16)/den))




#define RGB_NULL	((UINT32)-1)
/***********************************************************************/
#define AUDIOFMT_PCM			0x01
#define AUDIOFMT_ADPCM_MS		0x02
#define AUDIOFMT_ALAW			0x06
#define AUDIOFMT_MULAW			0x07
#define AUDIOFMT_ADPCM_IMA		0x11
#define AUDIOFMT_ADPCM_IMA_QT	0x10011
#define AUDIOFMT_ADPCM_G726		0x45
#define AUDIOFMT_MP2			0x50
#define AUDIOFMT_MP3			0x55
#define AUDIOFMT_MSA			0x160
#define AUDIOFMT_WMA9			0x161
#define AUDIOFMT_WMA9PRO		0x162
#define AUDIOFMT_WMA9LL			0x163
#define AUDIOFMT_WMA9V			0x0A
#define AUDIOFMT_A52			0x2000
#define AUDIOFMT_AAC			0xAAC0
#define	AUDIOFMT_QDESIGN2		0x450
#define AUDIOFMT_TTA			0x77A1

// not sure about this...
#define AUDIOFMT_AMR_NB			0x57
#define AUDIOFMT_AMR_WB			0x58

#define AUDIOFMT_VORBIS_MODE1	0x674F
#define AUDIOFMT_VORBIS_MODE1P	0x676F
#define AUDIOFMT_VORBIS_MODE2	0x6750
#define AUDIOFMT_VORBIS_MODE2P	0x6770
#define AUDIOFMT_VORBIS_MODE3	0x6751
#define AUDIOFMT_VORBIS_MODE3P	0x6771
#define AUDIOFMT_VORBIS_PACKET	0x2674F
#define AUDIOFMT_VORBIS_INTERNAL_VIDEO 0x1674F
#define AUDIOFMT_VORBIS_INTERNAL_AUDIO 0x3674F

// not official! just internal usage
#define AUDIOFMT_QCELP			0xCC00
#define AUDIOFMT_SPEEX			0xCD00

#define SPEED_ONE			(1<<16)

// pcm flags
#define PCM_SWAPPEDSTEREO	0x0001
#define PCM_PLANES			0x0002
#define PCM_UNSIGNED		0x0004
#define PCM_ONLY_LEFT		0x0008
#define PCM_ONLY_RIGHT		0x0010
#define PCM_PACKET_BASED	0x0020
#define PCM_SWAPEDBYTES		0x0040
#define PCM_FLOAT			0x0080

#define PCM_LIFEDRIVE_FIX	0x1000

/************************************************************************/
#define MAXREADER	1
#define MAXSTREAM	64
#define MINBUFFER	(256*1024)
#define HEADERLOAD	(1024*1024)



/************************************************************************/

#define ALIGN64(x) (((x) + 63) & ~63)
#define ALIGN16(x) (((x) + 15) & ~15)
#define ALIGN8(x) (((x) + 7) & ~7)
#define ALIGN4(x) (((x) + 3) & ~3)

#define GET_R(x)   ((uint8_t)(((x) >> 0) & 255))
#define GET_G(x)   ((uint8_t)(((x) >> 8) & 255))
#define GET_B(x)   ((uint8_t)(((x) >> 16) & 255))
/************************************************************************/
#define ERR_NONE			0
#define ERR_BUFFER_FULL		-1
#define ERR_OUT_OF_MEMORY	-2
#define ERR_INVALID_DATA	-3
#define ERR_INVALID_PARAM	-4
#define ERR_NOT_SUPPORTED	-5
#define ERR_NEED_MORE_DATA	-6
#define ERR_FILE_NOT_FOUND	-8
#define ERR_END_OF_FILE		-9
#define ERR_DEVICE_ERROR	-10
#define ERR_SYNCED			-11
#define ERR_DATA_NOT_FOUND	-12
#define ERR_MIME_NOT_FOUND	-13
#define ERR_NOT_DIRECTORY	-14
#define ERR_NOT_COMPATIBLE	-15
#define ERR_CONNECT_FAILED	-16
#define ERR_DROPPING		-17
#define ERR_STOPPED			-18
#define ERR_UNAUTHORIZED	-19
#define ERR_LOADING_HEADER	-20

#define TIME_UNKNOWN	-1
#define TIME_RESEND		-2
#define TIME_BENCH		-3
#define TIME_SYNC		-4

// special flag for get/set format structure (packetformat)
#define PIN_FORMAT		0x10000
// special flag for get/set process function (packetprocess)
#define PIN_PROCESS		0x20000
// format not test
#define PACKET_NONE			0
// video (packet based)
#define PACKET_VIDEO		1
// audio (packet based)
#define PACKET_AUDIO		2
// subtitle (packet based)
#define PACKET_SUBTITLE		3

#define PACKET_TEXT		4

#define PACKET_MAX			5

#define STEREO_NORMAL		0
#define STEREO_SWAPPED		1
#define STEREO_JOINED		2
#define STEREO_LEFT			3
#define STEREO_RIGHT		4

// process return code 
#define CODEC_NO_DROPPING	0x200



#define  MAXPLANES 4
#define	 MAXSTREAM	64
#define  TICKSPERSEC			16384
#define  BLOCKSIZE				32768








/**************** prop ***************************/
#define  MAX_INT	0x7FFFFFFF
#define  OPLAYER_PRI_DEFAULD  500 



#define  PROP_STREAM_CONTENTTYPE   600
#define  PROP_STREAM_RTSPHANDLE   601
#define  PROP_STREAM_URL          602
#define  PROP_STREAM_SILENT			603

#define  PROP_TIMER_PLAY        700
#define  PROP_TIMER_SPEED       701
#define  PROP_TIMER_TIME        702
#define  PROP_TIMER_CLEAR       703

#define  PROP_INPUT_COPacketFormat			730

#define	 PROP_VOUT_PLAY						731
#define	 PROP_VOUT_VIEWPORT					732
#define	 PROP_VOUT_COOutVideoInterface		733
#define	 PROP_VOUT_Update		734
#define	 PROP_VOUT_BLIT_TIME		735

#define  PROP_INIT 800
#define  PROP_SEND_TEXT 801
#define  PROP_FLOW_FLUSH 802
#define  PROP_FLOW_RESEND 803
#define  PROP_NETWORK_TIMEOUT 804

#define  PROP_USER 2000
/**************** types ***************************/


typedef struct tagOBlitfx
{
	int Flags;			// combination of blitfx flags
	int ScaleX;			// 16.16 fixed point scale factor (before swapxy)
	int ScaleY;			// 16.16 fixed point scale factor (before swapxy)
	int Brightness;
	int Contrast;
	int Saturation;
	int Direction;
	int RGBAdjust[3];		// additional r,g,b brightness
} OBlitfx;

typedef enum tagOPlayStatus
{
	OPlayStatusUnknown,
	OPlayStatusPlay,
	OPlayStatusPause,
	OPlayStatusStop,
}OPlayStatus;


typedef union tagORgb
{
	struct 
	{
		UINT8 r;
		UINT8 g;
		UINT8 b;
		UINT8 a;
	} c;
	UINT8 ch[4];
	UINT32 v;

} ORgb;


typedef void* planes[MAXPLANES];
typedef const void* constplanes[MAXPLANES];
typedef struct tagCOPacket
{
	constplanes  Data;
	constplanes  LastData;	// optional (for video it may increase performance)
	int Length;			// length of data (in bytes, per planes, not filled for surfaces)
	TIME_T RefTime;			// packet time (-1 if unknown)
	BOOL Key;			

} COPacket;

typedef struct tagCOCodecInfo
{
	UINT32 Id;
	UINT32 CodecId;
	const char* Name;
	const char* ContentType;

} COCodecInfo;

typedef struct tagOAudio
{
	int Format;
	int Channels;	
	int SampleRate;
	int BlockAlign;
	int Flags;
	int Bits;		
	int FracBits;	

}OAudio;

typedef struct tagOPixel
{
	int Flags;
	UINT32 FourCC;
	int BitCount;
	UINT32 BitMask[3];
	ORgb *Palette;
}OPixel;

typedef struct tagORect
{
	int x;
	int y;
	int Width;
	int Height;
}ORect;

typedef struct tagOFraction
{
	int Num;
	int Den;
}OFraction;

typedef struct tagOPoint
{
	int x;
	int y;
}OPoint;

typedef struct tagOVideo
{
	int Direction;	// direction flags
	int Aspect;		// 16.16 fixed point
	int Width;		// phyisical width of surface
	int Height;		// phyisical height of surface
	int Pitch;
	int ForceBGR;
	OPixel Pixel;
}OVideo;

#ifdef __cplusplus



class COStream;
class COFormatReader;
class COFormatStream;
class COFormat;
class COCodec;
class COPlayer;
class CONode;
class COPacketFormat;

typedef struct tagCOFormatPacket
{
	MemoryBuffer2Ref* Data;
	TIME_T RefTime;
	TIME_T EndRefTime; // optional (only for subtitle)
	COFormatStream* Stream;
	struct tagCOFormatPacket* Next;
	BOOL Key;
} COFormatPacket;


class _CPP_OPLAYER_EXPORT COFraction
	:public OFraction
{
public:
	COFraction();
	COFraction(const COFraction &frac);
	COFraction(const OFraction &frac);


	void Clear();
	BOOL IsEq( const OFraction *b);
    void Copy( const OFraction *b);
    void CopyTo( OFraction *b);

} ;



class _CPP_OPLAYER_EXPORT COBlitfx
	:public OBlitfx
{
public:
	COBlitfx();
	void Clear();

} ;



class _CPP_OPLAYER_EXPORT  COPoint
	:public OPoint
{
public:
	COPoint();
	void Clear();
} ;


class _CPP_OPLAYER_EXPORT  CORect
	:public ORect
{
public:
	CORect();
	void Clear();
	void Copy(const ORect *New );


} ;

class _CPP_OPLAYER_EXPORT  COPixel
	:public OPixel
{
public:
	COPixel();
	void Clear();
	static void DefaultRGB(OPixel* p, int BitCount, 
		int RBits, int GBits, int BBits,
		int RGaps, int GGaps, int BGaps);
	static void DefaultBGR(OPixel* p, int BitCount, 
		int RBits, int GBits, int BBits,
		int RGaps, int GGaps, int BGaps);
	void DefaultRGB(int BitCount, 
		int RBits, int GBits, int BBits,
		int RGaps, int GGaps, int BGaps);
	int GetBPP();
	BOOL PlanarYUV420();
	BOOL PlanarYUV410();
	BOOL PlanarYUV422();
	BOOL PlanarYUV444();
	BOOL PackedYUV();
	BOOL PlanarYUV(int* x, int* y,int *s);
	BOOL AnyYUV();
	UINT32 DefFourCC();
	void FillInfo();
	BOOL Compressed();
	BOOL IsEq( const COPixel *b);
public:


} ;



class _CPP_OPLAYER_EXPORT  COVideo
	:public OVideo
{
public:
	COVideo();
	void DefaultPitch();
	BOOL IsEq(const COVideo *b);
	void Clear();



	

} ;

class _CPP_OPLAYER_EXPORT  COAudio:
	public OAudio
{
public:
	COAudio();
	void Clear();
	BOOL IsEq(const COAudio *b);
	void Copy(const OAudio *New );

} ;

class _CPP_OPLAYER_EXPORT  COSubtitle
{
public:
	COSubtitle();
	void Clear();
	BOOL IsEq(const COSubtitle *b);
	UINT32 FourCC;

} ;

class _CPP_OPLAYER_EXPORT  COText
{
public:
	COText();
	void Clear();
	BOOL IsEq(const COText *b);
	UINT32 FourCC;

} ;



class _CPP_OPLAYER_EXPORT  COProcessState
{
public:
	COProcessState();
	void Clear();
	TIME_T Time;
	BOOL Fill;
	int BufferUsedBefore;
	int BufferUsedAfter;

} ;

class _CPP_OPLAYER_EXPORT  COFlowstate
{
public:
	COFlowstate();
	void Clear();
	int DropLevel;
	TIME_T CurrTime;

};



/*********************************************/




class _CPP_OPLAYER_EXPORT COPacketFormat
{
public:
	COPacketFormat();
	~COPacketFormat();
	COPacketFormat & operator= ( COPacketFormat const &_this);
	void Clear();
	void Combine(const COPacketFormat* Src);
	void Default();
	void FormatPCM( const COPacketFormat* In, int Bits);
	BOOL FormatExtra(int Length);
	BOOL SimilarAudio( const COPacketFormat* New);
	BOOL RotatedVideo(const COPacketFormat* New,int Mask);
	BOOL IsEq(const COPacketFormat *b);
	BOOL PitchChanged(const COPacketFormat* New);
	BOOL PacketFormatRotatedVideo(const COPacketFormat* New,int Mask);
public:
	int Type;

	int ByteRate;
	COFraction PacketRate;

	void* Extra;
	int ExtraLength;

	struct
	{
		COVideo Video;
		COAudio Audio;
		COSubtitle Subtitle;
		COText Text;

	} Format;

};

/*************** COArray *************************/
typedef	int (*_COArrayCmp)(const void* a,const void* b);
template <class T>
class  COArray
{
public:
	COArray()
	{
		m_Begin = NULL ;
		m_End = NULL ;
		m_Allocated = FALSE ;
	}
	~COArray()
	{
		Clear();
	}
	void Lock(){}
	BOOL Unlock(){return 1;}
	void Clear()
	{
		if( m_Begin != NULL )
		{
			MemoryRelease( m_Begin );
			m_Begin = NULL ;
		}
		m_Begin = NULL;
		m_End = NULL;
		m_Allocated = 0;
	}
	void Drop()
	{
		m_End = m_Begin;
	}
	BOOL Alloc(int Total,int Align)
	{
		unsigned char* Data;
		--Align;
		Total = (Total + Align) & ~Align;
		Data = (unsigned char*)MemoryRealloc(m_Begin,Total);
		if (!Data)
			return FALSE;
		m_End = Data + (m_End - m_Begin);
		m_Begin = Data;
		m_Allocated = Total;
		return TRUE;
	}
	int  Find(int Count,  const T* Data, _COArrayCmp Cmp, BOOL* Found)
	{
		if( m_Begin == NULL )
		{
			*Found = 0 ;
			return -1 ;
		}
		if (Cmp)
		{
			int i;
			int Mid = 0;
			int Lower = 0;
			int Upper = Count-1;

			while (Upper >= Lower) 
			{
				Mid = (Upper + Lower) >> 1;

				i = Cmp(m_Begin+sizeof(T)*Mid,Data);
				if (i>0)
					Upper = Mid-1;	
				else if (i<0)  		
					Lower = Mid+1;	
				else 
				{			        
					*Found = 1;
					return Mid;
				}
			}

			*Found = 0;
			if (Upper == Mid - 1)
				return Mid;		
			else                 
				return Lower;    
		}
		else
		{
			int No = 0;
			const unsigned char* i;
			for (i=m_Begin;Count--;i+=sizeof(T),++No)
				if (memcmp(i,Data,sizeof(T))==0)
				{
					*Found = 1;
					return No;
				}

				*Found = 0;
				return No;
		}
	}
	
	BOOL Append( const void* Ptr, int Length, int Align)
	{
		int Total = m_End - m_Begin + Length;
		if (Total > m_Allocated && !Alloc(Total,Align))
			return FALSE;
		if (Ptr)
			memcpy(m_End,Ptr,Length);
		m_End += Length;
		return TRUE;
	}
	BOOL Add(int Count, const T* Data, _COArrayCmp Cmp,int Align)
	{
		int Pos;
		BOOL Found;

		Pos = Find(Count,Data,Cmp,&Found);
		if (!Found)
		{
			if (!Append(NULL,sizeof(T),Align))
				return 0;
			memmove(m_Begin+sizeof(T)*(Pos+1),m_Begin+sizeof(T)*Pos,(Count-Pos)*sizeof(T));
		}
		memcpy(m_Begin+sizeof(T)*Pos,Data,sizeof(T));
		return TRUE;
	}
    BOOL Remove( int Count, const T* Data, _COArrayCmp Cmp)
	{
		BOOL Found;
		int Pos = Find(Count,Data,Cmp,&Found);
		if (Found)
		{
			memmove(m_Begin+Pos*sizeof(T),m_Begin+(Pos+1)*sizeof(T),(m_End-m_Begin)-(Pos+1)*sizeof(T));
			m_End -= sizeof(T);
		}
		return Found;
	}
	void Sort( int Count, _COArrayCmp Cmp)
	{
		qsort(m_Begin,Count,sizeof(T),Cmp);
	}
	BOOL IsEmpty()
	{
		return ( m_Begin == m_End );
	}
	T* Begin()
	{
		return (T*)m_Begin;
	}
	T* End()
	{
		return (T*)m_End;
	}
	int Count()
	{
		return  ( End() - Begin() ) ;
	}
	int Allocated()
	{
		return (m_Allocated/sizeof(T)) ;
	}
public:
	unsigned char* m_Begin;
	unsigned char* m_End;
	int m_Allocated;
};
/*************** COBuffer *************************/
class _CPP_OPLAYER_EXPORT COBuffer : public CObjBuffer
{
public:
	BOOL Stream(COStream* stream);

};
/*************** COBase *************************/

class  _CPP_OPLAYER_EXPORT  COBase :
    public CObj 
{
public:
    _CPP_UTIL_DYNAMIC_DECLARE(COBase)  ;
    _CPP_UTIL_CLASSNAME_DECLARE(COBase) ;
    _CPP_UTIL_QUERYOBJ_DECLARE(COBase) ;
public:
    COBase();
    ~COBase();
	virtual int PropSet(int name ,const void* Data, int Size);
	virtual int PropGet(int name ,void* Data, int Size);
	void SetPlayerCtx(void *ctx);
	
public:
	BOOL m_bWillClose;
protected:
	void *m_ctx;
	
};

/*************** COStream *************************/
class  _CPP_OPLAYER_EXPORT  COStream :
    public COBase 
{
public:
    _CPP_UTIL_DYNAMIC_DECLARE(COStream)  ;
    _CPP_UTIL_CLASSNAME_DECLARE(COStream) ;
    _CPP_UTIL_QUERYOBJ_DECLARE(COStream) ;
public:
    static void Init();
    static BOOL Register(const char* className, const char *szProtcol, int pri, void *pfuncCreate );
    static COStream *CreateStream( const char* szURL );
	static COStream *CreateStreamByClass( const char* className );
    COStream();
    ~COStream();
	virtual BOOL IsLiveStream();
	virtual BOOL IsNetwork();
	virtual int  DataAvailable();
	virtual BOOL Open(const char *szURL, BOOL bReopen = FALSE  );
	virtual int  Read( void* data, int len );
	virtual int  Write( const void* data, int len );
	virtual int  Seek( int pos, int SeekMode );
	virtual int  FileSize();
	virtual BOOL Eof();
	virtual int  SeekByTime( int timePos );
	virtual void Close();
	virtual void SetPlayStatus(OPlayStatus status);



};

/*************** COFormatStream *************************/
class  _CPP_OPLAYER_EXPORT  COFormatStream:
	public COBase 
{
	friend class COFormat;
	friend class COFormatReader;

public:
	_CPP_UTIL_DYNAMIC_DECLARE(COFormatStream)  ;
	_CPP_UTIL_CLASSNAME_DECLARE(COFormatStream) ;
	_CPP_UTIL_QUERYOBJ_DECLARE(COFormatStream) ;
	COFormatStream();
	~COFormatStream();
    int Flush();
public:
	int m_No;
	int m_Id;
	COCodec *m_Pin;
	COFormatReader *m_Reader;
	COPacketFormat m_Format;
	int Process(const  COPacket* Data, const COFlowstate* State);
	int Update();
	int BufferTime();
	void CleanBuffer();

	BOOL m_Fragmented; //don't bother to merge buffers
	BOOL m_ForceMerge; 
	BOOL m_DisableDrop; // no dropping allowed
	int m_PacketBurst;

	// buffer for merging fragmented packets 
	// to a single continous memory
	COBuffer m_BufferMem; // faster system mem

	BOOL m_Pending; // 1:full packet 2:only first reference
	TIME_T m_LastTime; // last known refrence time (-1 out of sync)
	COPacket m_Packet;  // pending packet
	COFlowstate m_State;
	int m_DropCount;

	// buffered packets waiting for processing
	COFormatPacket* m_PacketFirst;
	COFormatPacket* m_PacketLast;

	COFormat *m_OFormat;
	COBase *m_Comment;
	int m_Priority;
	int m_Reserved[9];
};


/*************** COFormatReader *************************/
class  _CPP_OPLAYER_EXPORT  COFormatReader:
	public COBase 
{
	friend class COFormat;
	friend class COFormatStream;
public:
	_CPP_UTIL_DYNAMIC_DECLARE(COFormatReader)  ;
	_CPP_UTIL_CLASSNAME_DECLARE(COFormatReader) ;
	_CPP_UTIL_QUERYOBJ_DECLARE(COFormatReader) ;
	COFormatReader();
	~COFormatReader();

	int		Seek(int Pos,int Origin);
	int		SeekEx(int Pos,int Origin);
	BOOL	Eof();
	void	Skip(int Length);
	int		Read(void* Data,int Length0);
	int		Read8();
	int		ReadBE16();
	int		ReadLE16();
	int		ReadBE32();
	int		ReadLE32();
	INT64	ReadBE64();
	INT64	ReadLE64();
	MemoryBuffer2Ref * ReadAsRef(int Length);


	void    Backup(COFormatReader *Reader);
	void    Restore(COFormatReader *Reader);

	int     Write(const void *Data , int nLen);
    int     BufferAvailable();
	void    ClearBuffer();

    int     MaxBufferSize();

	void	SetFormat(COFormat *format);
	void	SetStream(COStream *stream);
private:
    int     ReadStream( int datasize = 0 );
public:
	COStream *m_Input;
	MemoryBuffer2Handle m_hBuf;
	COFormat *m_format;
    BOOL    m_bSeekSupport;
	MTX_OBJ m_mtxRead;
	BOOL m_NoMoreInput;
	BOOL m_OutOfSync;
	int		m_Ratio;

	int m_FilePos;


	COFormatStream* m_Current;
	int m_OffsetMin;
	int m_OffsetMax;
};

/*************** COFormat *************************/
class  _CPP_OPLAYER_EXPORT  COFormat:
    public COBase 
{
	friend class COFormatStream;
	friend class COFormatReader;
public:
    _CPP_UTIL_DYNAMIC_DECLARE(COFormat)  ;
    _CPP_UTIL_CLASSNAME_DECLARE(COFormat) ;
    _CPP_UTIL_QUERYOBJ_DECLARE(COFormat) ;
public:
	static void Init();
	static BOOL Register(const char* className, const char *szContentType, const char *szExts, int pri, void *pfuncCreate );
	static COFormat *CreateFormat(const char *szContentType, const char* szURL = NULL );

    COFormat();
    ~COFormat();
    int Flush();
	void WillClose();
	COFormatPacket *PacketAlloc();
    void PacketRelease( COFormatPacket* Packet);


    void PacketFree( COFormatPacket* Packet);
    void CleanFreePackets();

	void TimeStampRestarted(COFormatStream* Stream,TIME_T* RefTime);
	void CalcDuration();
	int ProcessCoverArt(COFormatStream* Stream);
	void ProcessSubTitle(COFormatStream* s);
	COFormatStream* AddStream();
	void RemoveStream();
	void UpdateTotalCount();
	int PrepairStream(COFormatStream* Stream);
	BOOL IsVideo();
	void FindSubtitles();
	int BufferTime();

	COFormatReader* FindReader(int Min,int Max);

	void SetStream(COStream *stream);
	int  Send(COFormatStream* Stream);
	int  Synced(COFormatStream* Stream);
	int  CheckEof(COFormatStream* Stream);
	virtual int MaxSeekLength();

	virtual COFormatStream *CreateFormatStream();


public:
	int Sync( TIME_T Time, int FilePos, BOOL PrevKey );
	int Read( int datasize = 0 );
	int Process( COProcessState *State);

	virtual int OnInit();
	virtual int OnDone();

	virtual int FillQueue(COFormatReader* Reader);
	virtual int	Process( COFormatStream* Stream);
	virtual void Sended(COFormatStream* Stream);


	virtual int ReadPacket(COFormatReader* Reader, COFormatPacket* Packet);// must implement

	virtual int Seek(TIME_T Time,int FilePos,BOOL PrevKey);
	virtual void AfterSeek();
	virtual void BackupPacketState(int Begin);
public:
	COFormatStream * DefSyncStream(  COFormatReader* Reader );
public:
	BOOL m_bFuncSeek;
	BOOL m_bFuncAfterSeek;
	BOOL m_bFuncBackupPacketState;
	BOOL m_bFuncSended;
public:
	BOOL m_AutoReadSize;
	BOOL m_TimeStamps; // CalcDuration will try to load last packets
	BOOL m_FirstSync;
	BOOL m_NeedSubtitles;
	BOOL m_DisableReader;
	BOOL m_UseBufferBlock;
	TIME_T m_Duration;
	TIME_T m_StartTime;
	int m_FileSize;
	TIME_T m_DropTolerance;
	TIME_T m_SkipTolerance;
	TIME_T m_AVOffset;
	TIME_T m_GlobalOffset;
//	notify UpdateStreams;
//	notify ReleaseStreams;
	int m_FileAlign;
	int m_MinHeaderLoad;

	int m_SeekByPacket_DataStart;
	int m_SeekByPacket_BlockAlign;

	int m_StreamCount;
	int m_ActiveStreams;
	COFormatStream* m_Streams[MAXSTREAM];
	COFormatStream* m_SubTitle;
	int m_ProcessMinBuffer;
	COBase *m_Comment;

	BOOL m_SyncMode;
	int m_SyncRead; // number of blocks the processing thread allowed to read by it's own after sync
	COFormatStream* m_SyncStream;
	TIME_T m_SyncTime;

	int m_BufferId;
	COFormatPacket* m_FreePackets;
//	format_buffer* FreeBuffers; 
	MemoryBuffer2Ref*	   m_FreeRefs;

	void* m_BufferLock; // buffer handling must be multithread safe
	int m_BufferUsed; // number of buffers allocated (referenced)
	int m_BufferSize; // number of buffers allowed
	int m_ReadSize; // BLOCKSIZE/(2^n)

//	format_reader Reader[MAXREADER];
	COFormatReader* m_LastRead;

	TIME_T m_ProcessTime;
	BOOL m_Bench;
	BOOL m_HeaderLoaded;
	BOOL m_InSeek;

	void* m_InputLock;
	int m_SumByteRate;

	BOOL m_Timing;
	int m_TotalCount;
	COFormatStream* m_CoverArt;


	
public:
	COFormatReader m_Reader[MAXREADER];
	COStream *m_stream;
public:
	static int Scale(int v,int Num,int Den);
	static int Scale64(INT64 v,INT64 Num,INT64 Den);
	static int ScaleRound(int v,int Num,int Den);
};
/*************** CONode *************************/
class  _CPP_OPLAYER_EXPORT  CONode:
	public COBase 
{
	friend class COFormatStream;
	friend class COFormatReader;
	friend class COFormat;
public:
	_CPP_UTIL_DYNAMIC_DECLARE(CONode)  ;
	_CPP_UTIL_CLASSNAME_DECLARE(CONode) ;
	_CPP_UTIL_QUERYOBJ_DECLARE(CONode) ;
public:
	CONode();
	~CONode();

	virtual int Process(const  COPacket* Packet, const COFlowstate* State);
	virtual int UpdateInput();
public:
	BOOL m_bFuncUpdateInput;
public:
	COPacketFormat m_InFormat;
	COPacketFormat m_OutFormat;
};
/*************** COTimer *************************/
class  _CPP_OPLAYER_EXPORT   COTimer :
    public CONode 
{
public:
    _CPP_UTIL_DYNAMIC_DECLARE(COTimer)  ;
    _CPP_UTIL_CLASSNAME_DECLARE(COTimer) ;
    _CPP_UTIL_QUERYOBJ_DECLARE(COTimer) ;
public:
    static int GetTimeFreq();
    static int GetTimeTick();
    static void GetTimeCycle(int* p);
public:
    COTimer();
    ~COTimer();
    void Lock();
    void UnLock();

	virtual int PropSet(int name ,const void* Data, int Size);
	virtual int PropGet(int name ,void* Data, int Size);


    void Clear();
    void SetPlay(BOOL bPlay);
    void SetSpeed(OFraction *speed);
    void SetTime(TIME_T timet);

    BOOL GetPlay();
    void GetSpeed(OFraction *speed);
    TIME_T GetTime();

    virtual int OnUpdatePlay();
    virtual int OnUpdateSpeed();
public:
    BOOL m_Play;
    COFraction m_Speed;
    COFraction m_SpeedTime;
    TIME_T m_Tick;
    int m_TimeRef;
private:
    MTX_OBJ m_mtx;
};
/*************** COOutVideoInterface*************************/
class  _CPP_OPLAYER_EXPORT  COOutVideoInterface 
{
public:
	COOutVideoInterface();
	virtual ~COOutVideoInterface();

	virtual void GetVideoFormat(OVideo *video , const OVideo *videoInput);
	virtual void GetVideoRect( ORect *rt , const ORect *rtVideo);
	virtual void OnVideoArrived(OVideo *format, int width, int height, void *data , TIME_T time);
	virtual void *LockVideoBuffer(int bufferSize);
	virtual void UnlockVideoBuffer(void *p);
	
};
/*************** COOutVideo*************************/
class  _CPP_OPLAYER_EXPORT  COOutVideo :
	public CONode 
{
public:
	_CPP_UTIL_DYNAMIC_DECLARE(COOutVideo)  ;
	_CPP_UTIL_CLASSNAME_DECLARE(COOutVideo) ;
	_CPP_UTIL_QUERYOBJ_DECLARE(COOutVideo) ;
public:
	static void * BlitCreate(const OVideo* DstFormat,const OVideo* SrcFormat, const OBlitfx* FX, int* OutCaps);
	static void BlitAlign(void *p, ORect* DstRect, ORect* SrcRect);
	static void BlitImage(void *p, const planes Dst, const constplanes Src, const constplanes SrcLast,
		int DstPicth, int SrcPitch); // video pitch can be overridden
	static void BlitRelease(void *p);

	static void ClipRectPhy(ORect* Physical, const OVideo* p);
	static void VirtToPhy(const ORect* Virtual, ORect* Physical, const OVideo* p);
	static void PhyToVirt(const ORect* Physical, ORect* Virtual, const OVideo* p);
	static void FillColor(void* Dst,int DstPitch,int x,int y,int Width,int Height,int BPP,int Value);
public:
	COOutVideo();
	~COOutVideo();

	virtual int Update();
	virtual int Blit( const constplanes Data, const constplanes DataLast, TIME_T time );
	virtual int Init();
	virtual int Done();
public:
	virtual int PropSet(int name ,const void* Data, int Size);
	virtual int PropGet(int name ,void* Data, int Size);
	virtual int Lock(planes Planes, BOOL OnlyAligned);
	virtual int Unlock();

	virtual void WinInvalidate(const ORect* Rect, BOOL Local);
	virtual void WinValidate(const ORect* Rect);
	virtual void WinUpdate();
	virtual void UpdateShow();


public:
	void OverlayClearBorder();
	void UpdateInputFormat();
	int OverlayUpdateFX( BOOL ForceUpdate);
	int UpdateInputDirection(BOOL Update);
	int OverlayUpdateShow(BOOL Temp);
	
private:
	virtual int Process(const  COPacket* Packet, const COFlowstate* State);
	virtual int UpdateInput();
public:
	BOOL m_bFuncLock;
	BOOL m_bFuncUpdateShow;
public:
	int m_SetFX;	
	int m_ClearFX;
	int m_Caps;

	// these are handled by overlay
	BOOL m_DoPowerOff; // use backup/restore in background
	BOOL m_Primary;
	BOOL m_Overlay;
	BOOL m_Disabled; // created with width=0 or height=0
	BOOL m_Inited;
	BOOL m_Background;
	BOOL m_Updating;
	BOOL m_ForceUpdate; 
	BOOL m_FullScreenViewport;
	BOOL m_Dirty;
	BOOL m_Visible;
	BOOL m_Clipping;
	BOOL m_AutoPrerotate;
	BOOL m_Show;
	BOOL m_InputHintDir;
	BOOL m_Play;
	BOOL m_TurningOff;
	TIME_T m_LastTime;
	TIME_T m_CurrTime;
	TIME_T m_BlitTime;
	int m_Total;
	int m_Dropped;
	unsigned int m_ColorKey;
	void* m_Soft;


	BOOL m_PreRotate;
	int m_InputDirection;
	int m_PrefDirection;
	BOOL m_UpdateInputFormat;
	void* m_Module;
	//idctbackup m_Backup;
	int m_ErrorTime;

	CORect m_Viewport;
	CORect m_SrcAlignedRect;
	CORect m_GUIAlignedRect;
	CORect m_DstAlignedRect;
	COBlitfx m_FX;
	COBlitfx m_OrigFX;
	COFraction m_Aspect;

	COOutVideoInterface *m_interface;
};

/*************** COCodec *************************/

class  _CPP_OPLAYER_EXPORT  COCodec:
    public CONode 
{
	friend class COFormatStream;
	friend class COFormatReader;
	friend class COFormat;
public:
    _CPP_UTIL_DYNAMIC_DECLARE(COCodec)  ;
    _CPP_UTIL_CLASSNAME_DECLARE(COCodec) ;
    _CPP_UTIL_QUERYOBJ_DECLARE(COCodec) ;
public:
	static void Init();
	static BOOL Register(const char* className, COCodecInfo *codecInfo, int pri, void *pfuncCreate );
	static COCodec *CreateCodecById(UINT32 Id);
	static COCodec *CreateCodecByCodecId(UINT32 CodecId);
	static COCodec *CreateCodecByContentType(const char * ContentType);


	COCodec();
	~COCodec();
    virtual int PropSet(int name ,const void* Data, int Size);
  
	virtual CONode *CreateOutVideo();
	virtual CONode *CreateOutAudio();
	virtual int Process(const  COPacket* Data, const COFlowstate* State);
	virtual int UpdateInput();
	virtual void OnInit();

public:
	virtual int UpdateOutput();
	virtual int Flush();
	virtual int ReSend();
public:
	BOOL m_bFuncUpdateOutput;
	BOOL m_bFuncFlush;
	BOOL m_bFuncReSend;
private:
	int Process(const  COPacket* Data, const COFlowstate* State, void *option);
	
public:
	COPacket m_Packet;
	BOOL m_Pending;
	BOOL m_NoHardDropping ;
	CONode *m_Out;
	const COCodecInfo *m_CodecInfo;

};



typedef enum tagOPlayerMsgType
{
    OPlayerMsgTypeError = -1,
	OPlayerMsgTypeWarning,
	OPlayerMsgTypeInfo,
	OPlayerMsgTypeDebug,
	OPlayerMsgTypeDetail,

}OPlayerMsgType;



typedef enum tagOPlayerIOEvent
{

    OPlayerIOEventOpenSuccess,
    OPlayerIOEventOpening,
    
    OPlayerIOEventOpenFailed ,
    OPlayerIOEventNotFoundStream ,
	OPlayerIOEventNotFoundFormat ,
	OPlayerIOEventBuffering,
	OPlayerIOEventStopBuffering,
	OPlayerIOEventPlaying,
	OPlayerIOEventPlay,
	OPlayerIOEventPause,
	OPlayerIOEventStop,
    OPlayerIOEventSynced,
    OPlayerIOEventDuration,
	OPlayerIOEventEof,

}OPlayerIOEvent;


/*************** COPlayer *************************/
class  _CPP_OPLAYER_EXPORT  COPlayer
{
public:
    COPlayer();
    ~COPlayer();


	static BOOL RegisterPlugin(const char *path);
    static BOOL RegisterPlugin(const unsigned short *path);

    void SetURL(const char *szUrl);
    const char *GetURL();
    void Play();
    void Pause();
    void Close();
	BOOL IsPlaying();
	BOOL IsPaused();

	void SetVideoInterface(COOutVideoInterface *interf);
	void UpdateViewport(const ORect *rt);
	void Update();
	void KeepConnect( BOOL bKeepConnect );
	BOOL KeepConnect();
	int  GetPlayedSeconds();
	int  GetTotalSeconds();

	BOOL GetPosition(OFraction *frac);
	
    int BufferTime();
    void SetBufferTime(int bufTime);

	BOOL SetSpeed(OFraction *frac);

    int NetworkTimeout();
    void SetNetworkTimeout( int milliseconds);

	void InSeek(BOOL bSeek);
	BOOL Seek(OFraction *frac);

	virtual COOutVideo *CreateOutVideo();
    virtual void OnMessage(OPlayerMsgType type  , const char *szMsg );
    virtual void OnIOEvent(OPlayerIOEvent ioevent , const char *szDescribe );
    virtual void OnProgress(int num ,int den );
	virtual void OnText( const char *szText , int nLen);

private:
    CObj *m_obj;
};


#endif





#endif








