

#ifndef _LIBCPPUTIL_GPS_READER_H_
#define _LIBCPPUTIL_GPS_READER_H_

class  _CPP_UTIL_EXPORT CGPSReader
{
public:
	CGPSReader();
	virtual ~CGPSReader();

	void SetDevivePath(const char *path);
	void SetBandrate(const char *bandrate);
	const char *GetDevivePath();
	BOOL Start();
	void Stop();
	BOOL IsRunning();

    virtual CObj *CreateCtx();
    virtual void OnGpsData(CObj*ctx,const char *Header, const char *data);
private:
	void *m_obj;
};


#endif


















