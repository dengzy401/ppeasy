
#ifndef _LIBCPPUTIL_THREAD_H_
#define _LIBCPPUTIL_THREAD_H_

typedef int ( *_ObjThreadProc)(void *vData);
class  _CPP_UTIL_EXPORT  CObjThread 
{
public:
    CObjThread();
    virtual ~CObjThread();

    virtual int Run();
    
public:
	virtual BOOL Start(int nStackSize = 0);
	virtual BOOL Stop();
	void WaitForExit();

	void SetNativeObjThreadProc( _ObjThreadProc funcThread , void *vThreadParameter);
	BOOL IsRunning();
	INT_THREADID ThreadId(); 


private:
	CObj *m_obj ;
};




#endif
