


#ifndef _LIBAUDIOOUT_H_
#define _LIBAUDIOOUT_H_

typedef struct tagLibAudioOutFormat 
{
    unsigned int formatType;
    unsigned int numChannels;
    unsigned int samplesPerSec;
    unsigned int bitsPerSample;
    unsigned int containerSize;
    unsigned int channelMask;
    unsigned int endianness;
	unsigned int buffersInQueue;
} LibAudioOutFormat;

typedef enum tagLibAudioOutStatus
{
	LibAudioOutStatusUnknown ,
	LibAudioOutStatusPlaying ,
	LibAudioOutStatusPaused ,
	LibAudioOutStatusStoped 
}LibAudioOutStatus;
typedef void* LibAudioOutHandle;
typedef void* LibAudioOutBuffer;
typedef int ( *_LibAudioOutBufferCallback)(LibAudioOutHandle handle,void *usrDataCallback,
                                           void *usrDataBuffer, LibAudioOutBuffer buffer,int bufferSize,int bufferUsed);

#ifdef __cplusplus
extern "C"
{
#endif

LibAudioOutBuffer MYAPI LibAudioOutAllocBuffer(LibAudioOutHandle handle, int size);
void  MYAPI  LibAudioOutFreeBuffer(LibAudioOutHandle handle, LibAudioOutBuffer buffer);
void * MYAPI LibAudioOutLockBuffer(LibAudioOutBuffer buffer);

LibAudioOutHandle MYAPI LibAudioOutCreateOutput(const char *szDevName,LibAudioOutFormat *format,_LibAudioOutBufferCallback callback,
                                          void *usrDataCallback,void *callbackThread,unsigned int threadMode);
void MYAPI LibAudioOutClose(LibAudioOutHandle handle);
BOOL MYAPI LibAudioOutStart(LibAudioOutHandle handle);
BOOL MYAPI LibAudioOutStop(LibAudioOutHandle handle);
BOOL MYAPI LibAudioOutPause(LibAudioOutHandle handle);
BOOL MYAPI LibAudioOutEnqueue(LibAudioOutHandle handle,LibAudioOutBuffer audioData ,int audioDataSize,void *usrDataBuffer);
BOOL MYAPI LibAudioOutSetVolume(LibAudioOutHandle handle,int vol);
int MYAPI LibAudioOutGetVolume(LibAudioOutHandle handle);
LibAudioOutStatus MYAPI LibAudioOutPlayStatus(LibAudioOutHandle handle);


#ifdef __cplusplus
}
#endif



#endif



