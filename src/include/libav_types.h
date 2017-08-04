

#ifndef _libav_types_h_
#define _libav_types_h_





#ifndef _H264_TYPE_
#define _H264_TYPE_

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
	NALU_TYPE_PREFIX   = 14,
	NALU_TYPE_SUB_SPS  = 15,
	NALU_TYPE_SLC_EXT  = 20,
	NALU_TYPE_VDRD     = 24  // View and Dependency Representation Delimiter NAL Unit

} NaluType;


typedef struct
{
	int startcodeprefix_len;      //! 4 for parameter sets and first slice in picture, 3 for everything else (suggested)
	int len;                 //! Length of the NAL unit (Excluding the start code, which does not belong to the NALU)
	//	unsigned max_size;            //! Nal Unit Buffer size
	int forbidden_bit;            //! should be always FALSE
	int nal_reference_idc;        //! NALU_PRIORITY_xxxx
	NaluType nal_unit_type;            //! NALU_TYPE_xxxx    
	unsigned char *buf;                    //! contains the first byte followed by the EBSP
	unsigned short lost_packets;  //! true, if packet loss is detected
} NALU_T;

#endif // _H264_TYPE_




#ifndef _AAC_TYPE_
#define _AAC_TYPE_

typedef enum tagADTSSampleRate
{
	ADTSSampleRateUnknown = -1 ,
	ADTSSampleRate96000 = 0 ,
	ADTSSampleRate88200 = 1 ,
	ADTSSampleRate64000 = 2 ,
	ADTSSampleRate48000 = 3 ,
	ADTSSampleRate44100 = 4 ,
	ADTSSampleRate32000 = 5 ,
	ADTSSampleRate24000 = 6 ,
	ADTSSampleRate22050 = 7 ,
	ADTSSampleRate16000 = 8 ,
	ADTSSampleRate12000 = 9 ,
	ADTSSampleRate11025 = 10 ,
	ADTSSampleRate8000  = 11 ,
	ADTSSampleRate7350  = 12 ,
	ADTSSampleRateWrittenExplictly = 15 ,

}ADTSSampleRate;

typedef enum tagADTSProfile
{
	ADTSProfileUnknown = -1 ,
	ADTSProfileMain = 0 ,
	ADTSProfileLowComplexity = 1 ,
	ADTSProfileScalableSamplingRate = 2 ,
}ADTSProfile;

typedef enum tagADTSId
{
	ADTSIdUnknown = -1 ,
	ADTSIdMpeg4 = 0 ,
	ADTSIdMpeg2 = 1 ,
}ADTSId;


typedef struct tagADTSHeader
{
	unsigned int syncword ;
	ADTSId id ;
	unsigned int layer ;
	ADTSProfile profile;
	ADTSSampleRate sampling_frequency_index ;
	unsigned int channels;
	unsigned int frame_length ;
	unsigned int sample_rate;
	
	unsigned int adts_buffer_fullness;
	double frame_dur;
}ADTSHeader;


typedef struct tagAudioProp
{
	int channels;
	int samplerate ;

}AudioProp;


#endif // _AAC_TYPE_
















#endif






