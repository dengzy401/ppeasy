

#ifndef _MAP_EXT_H_
#define _MAP_EXT_H_


#ifdef __cplusplus

#if defined(_ADAPI_H_)

class CStrKey
{
public:
    CStrKey(const char *szKey = NULL)
    {
        
        m_szKey = NULL ;
        *this = szKey ;

    }
    CStrKey(const CStrKey &_this)
    {
        m_szKey = NULL;
        *this = _this;
        return ;
    }
    ~CStrKey( )
    {

         MemoryRelease( m_szKey );
 
    }
    int Length()
    {
        return  MemoryStringLen(m_szKey);
    }
    void SetString(const char *str, int nLen = -1)
    {
        if (m_szKey != NULL)
        {
            MemoryRelease(m_szKey);
            m_szKey = NULL;
        }
        if (str == NULL)
        {
            m_szKey = MemoryEmptyString();
        }
        else
        {
            m_szKey = MemoryString(str, nLen, 16);
        }
    }
    CStrKey & operator = (const char *szKey)
    {
        if( m_szKey != NULL )
        {
            MemoryRelease( m_szKey );
            m_szKey = NULL ;
        }
        if( szKey == NULL )
        {
            m_szKey = MemoryEmptyString();
        }
        else
        {
            m_szKey = MemoryString( szKey , -1, 16 );
        }

        return *this;
    }
    CStrKey & operator = (const CStrKey &_this)
    {

        if( this == &_this )
        {
            return *this;
        }
 
        MemoryAddRef( _this.m_szKey );
        MemoryRelease( m_szKey );

        m_szKey = _this.m_szKey ;
        
        return *this;
    }
    bool operator == (const  CStrKey &_this) const
    {
        return (strcmp(m_szKey,_this.m_szKey) == 0 );
    }
    bool operator > (const  CStrKey &_this) const
    {
        return (strcmp(m_szKey,_this.m_szKey) > 0 );
    }
    bool operator < (const  CStrKey &_this) const
    {
        return (strcmp(m_szKey,_this.m_szKey) < 0 );
    }
    bool operator >= (const  CStrKey &_this) const
    {
        return (strcmp(m_szKey,_this.m_szKey) >= 0 );
    }
    bool operator <= (const  CStrKey &_this) const
    {
        return (strcmp(m_szKey,_this.m_szKey) <= 0 );
    }
    operator const char *()
    {
        return m_szKey ;
    }
public:
    char *m_szKey;
};

struct hash_CStrKey{

    size_t operator()(const CStrKey& str) const

    {


#if !defined(_NO_BKDRHASH_)
		unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
		unsigned int hash = 0;

		for (size_t i = 0 ; str.m_szKey[i] ; i ++)
		{
			hash = hash * seed + str.m_szKey[i] ;
		}

		return (hash & 0x7FFFFFFF);


#else
        unsigned long __h = 0;

        for (size_t i = 0 ; str.m_szKey[i] ; i ++)

        {

            __h = 5*__h + str.m_szKey[i];

        }

        return size_t(__h);
#endif


    }


};

struct hash_CStrKey2Int{

	size_t operator()(const CStrKey& str) const

	{
		return atoi( str.m_szKey );
	}

};

#endif

template<class type>
class CMapPtrValue
{
public:
    CMapPtrValue( type * vData = NULL )
    {
        m_pData =  vData ;
    }
    CMapPtrValue( const CMapPtrValue &_this)
    {
        m_pData = _this.m_pData;
    }
    CMapPtrValue & operator = ( const CMapPtrValue &_this )
    {
        m_pData = _this.m_pData;
        return *this;
    }
    operator type * ()
    {
        return m_pData ;
    }
    type * DetachData()
    {
        type * p = m_pData ;
        m_pData = NULL ;
        return p ; 
    }
    void AttechData( type * p )
    {
        DeleteAttechedData() ;
        m_pData = p ;
    }
    void DeleteAttechedData()
    {
        if( m_pData )
        {
            delete m_pData ;
            m_pData = NULL ;
        }
    }
public:   
    type* m_pData; 
};






template<class type>
class CMapValue
{
public:
    CMapValue( type * vData = NULL )
    {
        if( vData  )
        {
            m_Data =  *vData ;
        }
    }
    CMapValue( const CMapValue &_this)
    {
        m_Data = _this.m_Data;
    }
    CMapValue( const type &data )
    {
        m_Data = data;
    }
    CMapValue & operator = ( const CMapValue &_this )
    {
        m_Data = _this.m_Data;
        return *this;
    }
    CMapValue & operator = ( type &data )
    {
        m_Data = data ;
        return *this;
    }
    operator type * ()
    {
        return &m_Data ;
    }
    type & GetData()
    {
        return m_Data ;
    }
public:   
    type m_Data; 
};






#else



#endif




#endif









