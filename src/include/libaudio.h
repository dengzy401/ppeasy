
#ifndef _LIBAUDIO_H_
#define _LIBAUDIO_H_
	
	
typedef void *HAUDIO ;

typedef enum tagLibAudioOption
{
	LibAudioOptionDefault,
	
}LibAudioOption;
	

typedef void (MYAPI *_LibAudioCallback)(unsigned char *data,int len,void *usrData);

typedef struct tagLibAudioConfig
{
	unsigned int samplesRate;
	unsigned int channels;
	unsigned int bitsPerSample;

	unsigned int bytesPerFrame;
	unsigned int samplesPerFrame;

	unsigned int fps;
	
}LibAudioConfig,*LibAudioConfigPtr;

typedef struct tagLibAudioPar
{
	
	LibAudioConfig audioConfig;
	_LibAudioCallback callback;
	void *usrData;
	void *messageThreadHandle;
}LibAudioPar;


typedef struct tagLibAudioFrame
{
	UINT64 timestamp;
	unsigned int sequence ;
	int samplesRate;
	void *usrData;
	int bufferSize;
	int audioDataSize;
	unsigned char * audioData;
}LibAudioFrame;


#ifdef __cplusplus
extern "C"
{
#endif
    
int    MYAPI  LibAudioCount();
BOOL   MYAPI  LibAudioName(int index, char* sName, int nBufferSize,char* devPath ,int devPathLen);
HAUDIO MYAPI LibAudioOpen(const char *szDevPath , LibAudioOption opt,LibAudioPar *par);
BOOL   MYAPI LibAudioStartRecord( HAUDIO hAudio );
void   MYAPI LibAudioStopRecord(  HAUDIO hAudio );	
void   MYAPI LibAudioClose( HAUDIO hAudio )	;
BOOL   MYAPI LibAudioGetConfig(HAUDIO hAudio,LibAudioConfig *config);
int    MYAPI LibAudioGetMaxBufferSize( HAUDIO hAudio )	;


LibAudioFrame *  MYAPI LibAudioFrameCreate(int bufferLength);
LibAudioFrame *  MYAPI LibAudioFrameCopy(const LibAudioFrame *frame);
LibAudioFrame * MYAPI LibAudioFrameAddRef( LibAudioFrame *  frame);
long MYAPI LibAudioFrameRelease( LibAudioFrame *  frame);

#ifdef __cplusplus
}
#endif

#endif





