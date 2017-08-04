

#ifndef _libcpputil_named_timer_h_
#define _libcpputil_named_timer_h_



class  _CPP_UTIL_EXPORT  CObjTimerItem :
	public CObj 
{

	friend class CObjNamedTimerImp;
public:
	_CPP_UTIL_DYNAMIC_DECLARE(CObjTimerItem)  ;
	_CPP_UTIL_CLASSNAME_DECLARE(CObjTimerItem) ;
	_CPP_UTIL_QUERYOBJ_DECLARE(CObjTimerItem) ;
public:
	void * operator new( size_t cb );
	void operator delete( void* p );
public:
	CObjTimerItem();
	virtual ~CObjTimerItem();
	virtual BOOL Execute(CObj *ctx); // return FALSE the item will be delete
public:
	unsigned int m_nInterval;
	BOOL   m_bOneShot;
private:
	TIME_T m_tmAccess;
};




class  _CPP_UTIL_EXPORT  CObjNamedTimer :
	public CObj 
{

public:
	_CPP_UTIL_DYNAMIC_DECLARE(CObjNamedTimer)  ;
	_CPP_UTIL_CLASSNAME_DECLARE(CObjNamedTimer) ;
	_CPP_UTIL_QUERYOBJ_DECLARE(CObjNamedTimer) ;
public:
	CObjNamedTimer();
	virtual ~CObjNamedTimer();
	virtual CObj * CreateThreadContext();
	BOOL Start(int nStackSize = 0);
	BOOL Stop();
	void Precision(int milliseconds);
	int  Precision();
	BOOL AddItem(const char *szName , CObjTimerItem *item , BOOL bForce = TRUE );
	BOOL RemoveItem(const char *szName);
	CObjTimerItem * RemoveItemNoRelease(const char *szName);
	BOOL ItemExist(const char *szName);

private:
	CObj *m_pCore;
};


















#endif



