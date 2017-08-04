

#ifndef _LIBCPPUTIL_EVENT_H_
#define _LIBCPPUTIL_EVENT_H_


class  _CPP_UTIL_EXPORT  CObjEvent :
    public CObj 
{

public:
    _CPP_UTIL_DYNAMIC_DECLARE(CObjEvent)  ;
    _CPP_UTIL_CLASSNAME_DECLARE(CObjEvent) ;
    _CPP_UTIL_QUERYOBJ_DECLARE(CObjEvent) ;
public:
    void * operator new( size_t cb );
    void operator delete( void* p );
public:
    CObjEvent();
    virtual ~CObjEvent();
	static int ObjCount();
    virtual void OnLeaveQueue();
	virtual BOOL Post(BOOL bNotify = TRUE);
    virtual int OnExecute(CObj *sender = NULL);

};

class  _CPP_UTIL_EXPORT  CObjEventQueue 
{
public:
   
    CObjEventQueue(int nThreads = 1,int nStackSize = 0,int nWaitMilliSecond = -1 );
    virtual ~CObjEventQueue();

    virtual CObj * CreateThreadContext(const CObj *threadObj);
    virtual int ProcessEvent(CObjEvent *pEvent,CObj *pThreadContext);
    virtual void OnQueueEmpty(CObj *pThreadContext,const CObj *threadObj);
    virtual void OnQueueEmptyInThread(CObj *pThreadContext,const CObj *threadObj);
    virtual void OnQueueWaitTimeout(CObj *pThreadContext,const CObj *threadObj,int nWaitMilliSecond);
public:
    BOOL Start();
    void Shutdown();
    void SetStackSize( int nStackSize = 0 );

    BOOL PostEvent(CObjEvent *pEvent,BOOL bNotify = TRUE );
    BOOL PostEvent(CObjEvent *pEvent,const CObj *threadObj,BOOL bNotify = TRUE);
    CObjEvent *GetNextEvent();
    CObjEvent *GetNextEvent(const CObj *threadObj);
    int GetEventCount();
    int GetEventCount(const CObj *threadObj);
    void NotifyEvent();
    void NotifyEvent(const CObj *threadObj);

    const CObj * GetIdleThreadObj();
	const CObj * GetNextThreadObj();

	void SetName(const char *szName);
private:
    CObj *m_pEventObj;


};




#endif
















































