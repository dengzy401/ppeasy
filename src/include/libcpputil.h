
#ifndef _LIBCPPUTIL_H_
#define _LIBCPPUTIL_H_

#define _INET_ADDR_STR_LEN 84
typedef struct tagINET_ADDR_STR
{
	char szAddr[_INET_ADDR_STR_LEN];
    int  nPort;
}INET_ADDR_STR;


typedef void ( MYAPI *_BugReportProc)(const char *szMsg,const char *szFileName,int nLine);
#ifdef __cplusplus
extern "C"
{
#endif

void MYAPI DbgPrintfObjRef();
void MYAPI SetBugReportProc(void * pFunc);
void  MYAPI LibCppUtilInit(INT64 nMaxFreeMem);

void MYAPI LibCppUtilGetMemState(INT64 *pnMemFree, INT64 *pnMemUsed, INT64 *pnMemMax);

#ifdef __cplusplus
}
#endif

#if defined(_NO_CPP_UTIL_EXPORT)
	#define _CPP_UTIL_EXPORT
#elif !defined(_CPP_UTIL_EXPORT)
	#ifdef WIN32
		#ifdef _MSC_VER
		#define _CPP_UTIL_EXPORT __declspec(dllimport)
		#else
		#define _CPP_UTIL_EXPORT
		#endif
	#else
	#define _CPP_UTIL_EXPORT
	#endif
#endif

#ifdef __cplusplus


#define _CPP_UTIL_DYNAMIC(class_name) \
    public: \
    static class_name * CreateObj() \
    { \
        class_name *pObj = NULL ; \
        pObj = new class_name() ; \
        if( pObj == NULL ) \
        { \
        return NULL ; \
        } \
        pObj->m_bAlloced = TRUE ; \
        pObj->m_nObjSize = sizeof(class_name) ; \
        pObj->AddObjRef(); \
        return pObj ; \
    }

#define _CPP_UTIL_DYNAMIC_DECLARE(class_name) \
    public: \
    static class_name * CreateObj();

#define _CPP_UTIL_DYNAMIC_IMP(class_name) \
    class_name * class_name::CreateObj() \
    { \
        class_name *pObj = NULL ; \
        pObj = new class_name() ; \
        if( pObj == NULL ) \
        { \
        return NULL ; \
        } \
        pObj->m_bAlloced = TRUE ; \
        pObj->m_nObjSize = sizeof(class_name) ; \
        pObj->AddObjRef(); \
        return pObj ; \
    }

#define _CPP_UTIL_CLASSNAME_DECLARE(class_name) \
	public: \
	virtual const char * GetClassName(); \
    public: \
    static const char * GetObjName();

#define _CPP_UTIL_CLASSNAME_IMP(class_name) \
	const char * class_name::GetClassName() \
	{ \
		return GetObjName(); \
	} \
    const char * class_name::GetObjName() \
    { \
    static char szObjName[]=""#class_name"" ;    \
    return     szObjName ;    \
    }
#define _CPP_UTIL_CLASSNAME(class_name) \
	public: \
	virtual const char * GetClassName() \
	{ \
		return GetObjName(); \
	} \
    public: \
    static const char * GetObjName() \
    { \
    static char szObjName[]=""#class_name"" ;    \
    return     szObjName ;    \
    }

#define _CPP_UTIL_QUERYOBJ_DECLARE(class_name) \
    public: \
    virtual void * QueryObj(const char *szObjName);
#define _CPP_UTIL_DYNCAST(obj,class_name)    ((obj)==NULL?NULL:((class_name *)((obj)->QueryObj(""#class_name""))))
#define _CPP_UTIL_FORCECAST(obj,class_name)  ((class_name *)(obj))

#define _CPP_UTIL_QUERYOBJ(base_class_name) \
    public: \
    virtual void * QueryObj(const char *szObjName)   \
    {    \
        if( szObjName == NULL )  \
        {               \
            return NULL ;  \
        } \
        if( strcmp( szObjName, GetObjName() ) == 0 ) \
        {     \
            return this;   \
        }     \
        else   \
        {       \
            return base_class_name::QueryObj(szObjName) ;  \
        }   \
    }

#define _CPP_UTIL_QUERYOBJ_IMP(class_name,base_class_name) \
    void * class_name::QueryObj(const char *szObjName)   \
    {    \
        if( szObjName == NULL )  \
        {               \
            return NULL ;  \
        } \
        if( strcmp( szObjName, GetObjName() ) == 0 ) \
        {     \
            return this;   \
        }     \
        else   \
        {       \
            return base_class_name::QueryObj(szObjName) ;  \
        }   \
    }









class  _CPP_UTIL_EXPORT  CObj
{
public:

    _CPP_UTIL_DYNAMIC_DECLARE(CObj)  ;
    _CPP_UTIL_CLASSNAME_DECLARE(CObj) ;
    _CPP_UTIL_QUERYOBJ_DECLARE(CObj) ;

    CObj();
    CObj(const CObj &src);
    virtual ~CObj();

    void * operator new( size_t cb );
    void operator delete( void* p );
    CObj & operator =(  const CObj& src );


    long AddObjRef();
    long ReleaseObj();
private:

public:


    BOOL ListIsEmpty() const;
    void ListAddHead(CObj *newEntry);
    void ListAddTail(CObj *newEntry);
    BOOL  ListDel(CObj *oldEntry) const;
    void ListMoveHead(CObj *EntryMv);
    void ListMoveTail(CObj *EntryMv);
    void ListInsert(CObj *newItem,CObj *prev, CObj *next);
    int  ListItemsCount() const;

    CObj * ListRemoveHead() const;
    CObj * ListRemoveTail();

    static void  _ListAdd(CObj *newItem,CObj *prev, CObj *next,CObj *head  );
    static void  _ListDel(CObj *prev, CObj *next,CObj *head );

public:
    CObj *m_pPreObj;
    CObj *m_pNextObj;

private:

    INT32 m_nListCount;

    /* no copy*/
protected:
    INT32 m_nRef;
protected:
    int m_nObjSize;
    BOOL m_bAlloced;


};
_CPP_UTIL_EXPORT void LibCppDumpCObjList(CObj *pHead);

class  _CPP_UTIL_EXPORT  CUtilList
{
public:
    _CPP_UTIL_DYNAMIC_DECLARE(CUtilList)  ;
    CUtilList();
    CUtilList(const CUtilList &src);
    virtual ~CUtilList();
    CUtilList & operator =(  const CUtilList& src );

    void * operator new( size_t cb );
    void operator delete( void* p );

    int AddObjRef();
    int ReleaseObj();

public:
    BOOL ListIsEmpty() const;
    void ListAddHead(LIST_ITEM *newEntry);
    void ListAddTail(LIST_ITEM *newEntry);
    void ListDel(LIST_ITEM *oldEntry) const;
    void ListMoveHead(LIST_ITEM *EntryMv);
    void ListMoveTail(LIST_ITEM *EntryMv);
    void ListInsert(LIST_ITEM *newItem,LIST_ITEM *prev, LIST_ITEM *next);
    int  ListItemsCount();

    LIST_ITEM * ListRemoveHead() const;
    LIST_ITEM * ListRemoveTail();

    static void  _ListAdd(LIST_ITEM *newItem,LIST_ITEM *prev, LIST_ITEM *next,CUtilList *head  );
    static void  _ListDel(LIST_ITEM *prev, LIST_ITEM *next,CUtilList *head );
protected:
    LIST_ITEM m_listHead;
    int m_nListCount;

    /* no copy*/
protected:
    INT32 m_nRef;
protected:
    int m_nObjSize;
    BOOL m_bAlloced;
};


template <class T>
class CObjPtr
{
public:
	CObjPtr()
	{
		p = NULL;
	}
	CObjPtr( int nNull ) 
	{
		p = NULL;
	}
	CObjPtr( T* lp) 
	{
		p = lp;
		if (p != NULL)
		{
			p->AddObjRef();
		}
	}
	CObjPtr( const CObjPtr<T>& lp)
	{
		p = NULL;
		*this = lp ;
	}
	~CObjPtr()
	{
		if (p)
		{
			p->ReleaseObj();
		}
	}
public:
	BOOL CopyTo( T** ppT) 
	{
		
		if (ppT == NULL)
		{
			return FALSE;
		}
		*ppT = p;
		if ( p )
		{
			p->AddRef();
		}
		return TRUE ;
	}
	T* operator=( const CObjPtr<T>& lp )
	{
		*this = lp.p ;
		return *this ;
	}
	T* operator=(  T* lp) 
	{
		if( p != lp )
		{
			if( p != NULL )
			{
				p->ReleaseObj();
			}
			p = lp ;
			if( p != NULL )
			{
				p->AddObjRef();
			}
		}
		return *this;
	}

	operator T*() const 
	{
		return p;
	}
	T& operator*() const
	{
		return *p;
	}
	T** operator&()
	{
		return &p;
	}
	bool operator!() const
	{
		return (p == NULL);
	}
	bool operator==( T* lp) const
	{
		return p == lp;
	}
	bool operator !=( T* lp) const
	{
		return !(operator==(lp));
	}
	T* operator->() 
	{
		return p;
	}
	void Attach( T* lp)
	{
        if ( p == lp )
        {
            return ;
        }
		if (p)
		{
			p->ReleaseObj();
		}
		p = lp;
	}
	T* Detach()
	{
		T* lp = p;
		p = NULL;
		return lp;
	}

public:
	T *p;
};

#ifdef _MTX_OBJ_
class CMtxAutoLock
{
public:
	CMtxAutoLock(MTX_OBJ *obj)
	{
		m_mtx = obj ;
		MtxLock( m_mtx ) ;
	}
	~CMtxAutoLock()
	{
		MtxUnLock( m_mtx ) ;
	}
private:
	MTX_OBJ *m_mtx;
};


template <class T>
class CObjAlloter
{
public:
	CObjAlloter()
	{
		MtxInit( &m_mtx ,0 );
	}
	virtual ~CObjAlloter()
	{
		RemoveAll();
		MtxDestroy( &m_mtx );
	}
	void RemoveAll()
	{
		T *v = NULL ;
		CMtxAutoLock lock(&m_mtx);
		while( ( v =  (T*)m_lst.ListRemoveHead() ) != NULL )
		{
			v->ReleaseObj();
		}
	}
	virtual T *CreateObj()
	{
		return NULL ;
	}
	T *GetObj()
	{
		T *v = NULL ;
		CMtxAutoLock lock(&m_mtx);
		v =  (T*)(m_lst.ListRemoveHead()) ;

		if( v == NULL )
		{
			v = CreateObj();
		}
		return v ;
	}
	T *GetFirst()
	{
		CMtxAutoLock lock(&m_mtx);
		return (T*)(m_lst.ListRemoveHead()) ;
	}
	T *GetLast()
	{
		CMtxAutoLock lock(&m_mtx);
		return (T*)(m_lst.ListRemoveTail()) ;
	}
	void PutFirst( T * v)
	{
		CMtxAutoLock lock(&m_mtx);
		m_lst.ListAddHead( v );
	}
	void PutLast( T * v)
	{
		CMtxAutoLock lock(&m_mtx);
		m_lst.ListAddTail( v );
	}
	int Count()
	{
		return m_lst.ListItemsCount();
	}
public:
	MTX_OBJ m_mtx;
	CObj m_lst;

};














#endif // _MTX_OBJ


class _CPP_UTIL_EXPORT CObjBuffer
{
public:
	CObjBuffer();
	virtual ~CObjBuffer();

	void Clear();
	void Drop();
	BOOL Alloc(int Size, int Align);
	BOOL Write( const void* Ptr, int Length, int Align);
	BOOL Read( const unsigned char** Ptr, int Length);
	void Pack(int Length);
	int  DataLength();
public:
	unsigned char*	Data;
	int		WritePos;
	int		ReadPos;
	int		Allocated;
	int		SafeTail;
	BOOL	bMalloc2;
};

class  _CPP_UTIL_EXPORT  CObjArray :
    public CObj
{

public:
    _CPP_UTIL_DYNAMIC_DECLARE(CObjArray);
    _CPP_UTIL_CLASSNAME_DECLARE(CObjArray);
    _CPP_UTIL_QUERYOBJ_DECLARE(CObjArray);
public:
    CObjArray();
    virtual ~CObjArray();

    CObjArray(const CObjArray& _this);
    CObjArray& operator = (const CObjArray& _this);

    void Add(CObj *);
    int  GetCount();
    void Clear();
    CObj *GetAt(int i);
private:

    CObjBuffer m_arry;
};

class _CPP_UTIL_EXPORT CObjMemIO
{
public:
	CObjMemIO(const void *bytes , int nLen);
	virtual ~CObjMemIO();

	int Write(const void *data , int nLen);
	int ReadLine(void *data , int nDataLen);
	BOOL IsEof();

public:
	unsigned char *m_buf;
	int m_nBufLen;
	int m_nSeekPos;
};


#endif // C++


#endif

























































