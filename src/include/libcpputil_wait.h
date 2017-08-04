
#ifndef _LIBCPPUTIL_WAIT_H_
#define _LIBCPPUTIL_WAIT_H_




class  _CPP_UTIL_EXPORT  CObjWait :
    public CObj
{
public:
    typedef enum tagWaitRet
    {
		WaitRetError = -1,
        WaitRetSuccess,
        WaitRetTimeout,
        

    }WaitRet ;

public: 
	static CObjWait * CreateObj(BOOL bManualReset = FALSE );
    _CPP_UTIL_CLASSNAME_DECLARE(CObjWait) ;
    _CPP_UTIL_QUERYOBJ_DECLARE(CObjWait) ;
public:

    CObjWait(BOOL bManualReset = FALSE);
    virtual ~CObjWait();

    CObjWait::WaitRet WaitForEvent(int dwMilliseconds);
    void SetEvent();
	BOOL ResetEvent();
private:
    void *m_pObj;

};



#endif






















