

#ifndef _libudpts_h_
#define _libudpts_h_

#ifndef FOURCCBE
#define FOURCCBE(a,b,c,d) \
	(((unsigned char)(a) << 24) | ((unsigned char)(b) << 16) | \
	((unsigned char)(c) << 8) | ((unsigned char)(d) << 0))
#endif

#ifndef FOURCCLE
#define FOURCCLE(a,b,c,d) \
	(((unsigned char)(a) << 0) | ((unsigned char)(b) << 8) | \
	((unsigned char)(c) << 16) | ((unsigned char)(d)<< 24))
#endif

#ifndef FOURCC
#ifdef IS_BIG_ENDIAN
#define FOURCC(a,b,c,d) FOURCCBE(a,b,c,d)
#else
#define FOURCC(a,b,c,d) FOURCCLE(a,b,c,d)
#endif
#endif

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

}XCodec ;

class  CIoUdpTS
{
public:
	CIoUdpTS();
	~CIoUdpTS();

	static unsigned int GetOStime();
	void SetNetworkDestAddress(const char *szIp , int nPort);
	bool Start();
	bool Stop();
	bool IsStarted();
	void SetFps(int fps);
	void SetVideoPCROffset(int offset);
	void SetAudioPCROffset(int offset);
    void SetMaxPES(int nMax);
	void EnablePCR(int bEnable);
	void SendFrame(unsigned char *encodedFrame, int nLen , XCodec codec, unsigned int  tmNow, int bKeyFrame);
public:
	void *m_obj;
};




#endif




