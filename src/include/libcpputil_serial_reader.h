

#ifndef _libcpputil_serial_reader_h_
#define _libcpputil_serial_reader_h_

class  _CPP_UTIL_EXPORT CSerialReader
{
public:
	CSerialReader();
	virtual ~CSerialReader();

	void SetDevivePath(const char *path);
	void SetBandrate(const char *bandrate);
	const char *GetDevivePath();
	BOOL Start();
	void Stop();
	BOOL IsRunning();
    void SetReadTimeout(int milliseconds);
	int  Write(const void *data , int nLen, int timeout = 1000);
	BOOL EnableBinMode(BOOL bEnable);

	virtual void OnData(const unsigned char *data, int nLen );
    virtual void OnIdle();
private:
	void *m_obj;
};


#endif


















