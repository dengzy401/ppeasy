

#ifndef _libcpputil_var_h_
#define _libcpputil_var_h_


#ifndef _LIBCPPUTIL_H_
#include "libcpputil.h"
#endif

typedef struct tagCObjString
{
	char *str;
	int  len;
}CObjString;

typedef struct tagCObjBinary
{
	void *data;
	int  len;
}CObjBinary;

class  _CPP_UTIL_EXPORT  CObjVar
{

public:
	typedef enum tagObjVarType
	{
		ObjVarTypeUnknown,
		ObjVarTypeNULL,
		ObjVarTypeBool,
		ObjVarTypeInt32,
		ObjVarTypeInt64,
		ObjVarTypeDouble,
		ObjVarTypePtr,
		ObjVarTypeObj,
		ObjVarTypeString,
		ObjVarTypeBinary,

	}ObjVarType;

	typedef union tagVarValue
	{
		bool   b;
		INT32  int_32;
		INT64  int_64;
		double db;
		void *  ptr;
		CObj *  obj;
		CObjString	str;
		CObjBinary  bin;
	}VarValue;
public:
	CObjVar();
	virtual ~CObjVar();

	void * operator new( size_t cb );
	void operator delete( void* p );


	CObjVar(const CObjVar& _this);  
	CObjVar(const char *str);  
	CObjVar(const double fv);  
	CObjVar(const int uv);  
	CObjVar(const bool b); 
	CObjVar(CObj *obj);
	CObjVar(void *ptr);  

	CObjVar& operator = (const CObjVar& _this); 
	CObjVar& operator = (const char *str); 
	CObjVar& operator = (const double fv); 
	CObjVar& operator = (const  int uv); 
	CObjVar& operator = (const  bool b); 
	CObjVar& operator = (CObj *obj); 


	BOOL operator == (const CObjVar& _this) const; 
	BOOL operator != (const CObjVar& _this) const; 

	BOOL operator == (const  int uv) const; 
	BOOL operator != (const  int uv) const; 


	BOOL IsEmpty() const;
    BOOL IsNull() const;
	BOOL SetString( const char *str , int nLen = -1 );
	void SetNull();
    void Trim();

	void Clear();
	int  DataLength() const;
    int  StringLength( ) const;
	const void* Data() const ;


    INT64   toInt64();
	operator int() const; 
	operator double() const; 
	operator CObj *() const; 
	operator const char *() const; 
public:
	ObjVarType m_type;
	VarValue m_value;
};


class  _CPP_UTIL_EXPORT  CObjVarRef :
	public CObj 
{

public:
	_CPP_UTIL_DYNAMIC_DECLARE(CObjVarRef)  ;
	_CPP_UTIL_CLASSNAME_DECLARE(CObjVarRef) ;
	_CPP_UTIL_QUERYOBJ_DECLARE(CObjVarRef) ;
public:
	CObjVar m_var;
};

class  _CPP_UTIL_EXPORT  CObjVarArray :
    public CObj
{

public:
    _CPP_UTIL_DYNAMIC_DECLARE(CObjVarArray);
    _CPP_UTIL_CLASSNAME_DECLARE(CObjVarArray);
    _CPP_UTIL_QUERYOBJ_DECLARE(CObjVarArray);
public:
    CObjVarArray();
    virtual ~CObjVarArray();

    CObjVarArray(const CObjVarArray& _this);
    CObjVarArray& operator = (const CObjVarArray& _this);

    void Add(CObjVarRef *);
    int  GetCount()  ;
    void Clear();
    BOOL IsExist(const char *str,BOOL ignoreCase = TRUE);
    CObjVarRef *GetAt(int i) ;
    int  Split(const char *str,const char *split,BOOL skipEmpty = TRUE);
    int  SplitByChars(const char *str, const char *splitChars, BOOL skipEmpty = TRUE);
private:

    CObjBuffer m_arry;
};


class _CPP_UTIL_EXPORT   CRefString
{
public:
    CRefString(const char *szKey = NULL);
    CRefString(const CRefString &_this);
    virtual ~CRefString();
    int Length();
    void SetString(const char *str, int nLen = -1);
    CRefString & operator = (const char *szKey);
    CRefString & operator = (const CRefString &_this);
    bool operator == (const  CRefString &_this) const;
    bool operator > (const  CRefString &_this) const;
    bool operator < (const  CRefString &_this) const;
    bool operator >= (const  CRefString &_this) const;
    bool operator <= (const  CRefString &_this) const;
    operator const char *();
public:
    char *m_szString;
};

#endif



