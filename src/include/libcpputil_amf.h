
#ifndef _libcpputil_amf_h_
#define _libcpputil_amf_h_

#if defined(WIN32)
#undef GetProp
#endif

typedef enum tagRTMPPacketType
{
	RTMPPacketTypeUnkown = 0x00 ,
	RTMPPacketType_ChunkSize	 = 	0x01 ,   //	Chunk Size	changes the chunk size for packets
	RTMPPacketType_Unknown0x02	 = 	0x02 ,	//  Unknown	anyone know this one?
	RTMPPacketType_BytesRead	 = 	0x03 ,	//  Bytes Read	send every x bytes read by both sides
	RTMPPacketType_Ctrl			 = 	0x04 ,	//  Ping	ping is a stream control message, has subtypes
	RTMPPacketType_WindowAck		 = 	0x05 ,	//  Server BW	the servers downstream bw
	RTMPPacketType_SetPeerBandwidth		 = 	0x06 ,	//  Client BW	the clients upstream bw
	RTMPPacketType_Unknown0x07	 = 	0x07 ,	//  Unknown	anyone know this one?
	RTMPPacketType_Audio		 = 	0x08 ,	//  Audio Data	packet containing audio
	RTMPPacketType_Video		 = 	0x09 ,	//  Video Data	packet containing video data
	//  0x0A - 0x11	Unknown	anyone know?
	RTMPPacketType_FlexStreamSend	 = 		0x0F ,    //  TYPE_FLEX_STREAM_SEND
	RTMPPacketType_FlexSharedObject	 = 		0x10 ,    //  TYPE_FLEX_SHARED_OBJECT
	RTMPPacketType_FlexMessage		 = 		0x11 ,    //  TYPE_FLEX_MESSAGE
	RTMPPacketType_Script		 = 	0x12 ,	//  info Notify	an invoke which does not expect a reply
	RTMPPacketType_Shared		 = 	0x13 ,	//  Shared Object	has subtypes
	RTMPPacketType_Invoke		 = 	0x14 ,	//  Invoke	like remoting call, used for stream actions too.
	RTMPPacketType_StreamData		 = 	0x16 ,	// FLV stream
}RTMPPacketType;

typedef enum tagRtmpAmfType
{
	AMFTYPE_NUMBER = 0x00 ,
	/**
	* Boolean value marker constant
	*/
	AMFTYPE_BOOLEAN = 0x01, 
	/**
	* String marker constant
	*/
	AMFTYPE_STRING = 0x02,
	/**
	* Object marker constant
	*/
	AMFTYPE_OBJECT = 0x03,
	/**
	* Movieclip marker constant
	*/
	AMFTYPE_MOVIECLIP = 0x04 ,
	/**
	* Null marker constant
	*/
	AMFTYPE_NULL = 0x05,
	/**
	* Undefined marker constant
	*/
	AMFTYPE_UNDEFINED = 0x06,
	/**
	* Object reference marker constant
	*/
	AMFTYPE_REFERENCE = 0x07,
	/**
	* Mixed array marker constant
	*/
	AMFTYPE_MIXED_ARRAY = 0x08,
	/**
	* End of object marker constant
	*/
	AMFTYPE_END_OF_OBJECT = 0x09,
	/**
	* Array marker constant
	*/
	AMFTYPE_ARRAY = 0x0A,
	/**
	* Date marker constant
	*/
	AMFTYPE_DATE = 0x0B,
	/**
	* Long string marker constant
	*/
	AMFTYPE_LONG_STRING = 0x0C,
	/**
	* Unsupported type marker constant
	*/
	AMFTYPE_UNSUPPORTED = 0x0D,
	/**
	* Recordset marker constant
	*/
	AMFTYPE_RECORDSET = 0x0E,
	/**
	* XML marker constant
	*/
	AMFTYPE_XML = 0x0F,
	/**
	* Class marker constant
	*/
	AMFTYPE_CLASS_OBJECT = 0x10,
	/**
	* Object marker constant (for AMF3)
	*/
	AMFTYPE_AMF3_OBJECT = 0x11,

	AMFTYPE_INVALID = 0xFF ,

}RtmpAmfType;


class CAMFObject;
class CAMFObjectProperty;

class _CPP_UTIL_EXPORT CAMFBuffer:
	public CObjBuffer
{
public:
	CAMFBuffer();
	~CAMFBuffer();
	BOOL SetReadPos(int pos, int Align = -1);
    BOOL SetWritePos(int pos, int Align = -1);
	BOOL Write( const void* Ptr, int Length, int Align);
public:
	int m_chunksize;
	int m_amfsize;
	UINT8 m_channelId;
};



class _CPP_UTIL_EXPORT CAMFObjectProperty:
	public CObj
{
	_CPP_UTIL_DYNAMIC_DECLARE(CAMFObjectProperty)  ;
	_CPP_UTIL_CLASSNAME_DECLARE(CAMFObjectProperty) ;
	_CPP_UTIL_QUERYOBJ_DECLARE(CAMFObjectProperty) ;
public:
	CAMFObjectProperty();
	virtual ~CAMFObjectProperty();
	CAMFObject *GetAMFObject();
	void Dump();
	void Encode(CAMFBuffer &buf);
public:
	RtmpAmfType m_type;
	CObjVar m_name ;
	CObjVar m_value;
	int     m_UTCOffset;
};




class _CPP_UTIL_EXPORT CAMFObject:
	public CObj
{
	_CPP_UTIL_DYNAMIC_DECLARE(CAMFObject)  ;
	_CPP_UTIL_CLASSNAME_DECLARE(CAMFObject) ;
	_CPP_UTIL_QUERYOBJ_DECLARE(CAMFObject) ;
public:
	static CAMFObject *CreateFromAMFBuffer(const UINT8 *buf , int nLen);

	static UINT8 HeadSize2HeadType( int size );
	static void EncodeInt8(CAMFBuffer &buf, INT8 nVal);
	static void EncodeInt16(CAMFBuffer &buf, INT16 nVal);
	static void EncodeInt24(CAMFBuffer &buf, int nVal);
	static void EncodeInt32(CAMFBuffer &buf, INT32 nVal);
	static void EncodeInt32LE(CAMFBuffer &buf, INT32 nVal);

	static void EncodeObjectBegin(CAMFBuffer &buf);
	static void EncodeObjectEnd(CAMFBuffer &buf);
	static void EncodeString(CAMFBuffer &buf, const CObjVar &bv);
	static void EncodeString(CAMFBuffer &buf, const  char * bv);
	static void EncodeNumber(CAMFBuffer &buf, double dVal);
	static void EncodeBoolean(CAMFBuffer &buf, int bVal);
	static void EncodeNull(CAMFBuffer &buf);
	static void EncodeNamedString(CAMFBuffer &buf, const CObjVar &strName, const CObjVar &strValue);
	static void EncodeNamedString(CAMFBuffer &buf, const char *strName, const char *strValue);
	static void EncodeNamedNumber(CAMFBuffer &buf, const CObjVar &strName, double dVal);
	static void EncodeNamedNumber(CAMFBuffer &buf, const char *strName, double dVal);
	static void EncodeNamedBoolean(CAMFBuffer &buf, const CObjVar &strName, int bVal);
	static void EncodeNamedBoolean(CAMFBuffer &buf, const char *strName, int bVal);
	static void EncodeNamedNull(CAMFBuffer &buf, const CObjVar &strName);
	static void EncodeNamedNull(CAMFBuffer &buf, const char *strName);

	static int EncodeInt8(UINT8 *buf, INT8 nVal);
	static int EncodeInt16(UINT8 *buf, INT16 nVal);
	static int EncodeInt24(UINT8 *buf, int nVal);
	static int EncodeInt32(UINT8 *buf, INT32 nVal);
	static int EncodeInt32LE(UINT8 *buf,int nVal);


	static int EncodeObjectBegin(UINT8 *buf);
	static int EncodeObjectEnd(UINT8 *buf);

	static int EncodeNumber(UINT8 *buf, double dVal);
	static int EncodeBoolean(UINT8 *buf, int bVal);
	static int EncodeNull(UINT8 *buf);
	static int EncodeString(UINT8 *buf, const CObjVar &bv);
	static int EncodeString(UINT8 *buf, const char *bv);
	static int EncodeNamedString(UINT8 *buf, const char *strName, const char *strValue);
	static int EncodeNamedNumber(UINT8 *buf, const char *strName, double dVal);
	static int EncodeNamedBoolean(UINT8 *buf, const char *strName, int bVal);

	static INT16 DecodeInt16(const UINT8 *data);
	static INT32 DecodeInt24(const UINT8 *data);
	static UINT32 DecodeInt32(const UINT8 *data);
	static UINT32 DecodeInt32LE(const UINT8 *data);


	CAMFObject();
	virtual ~CAMFObject();
	void Dump();
	void Encode(CAMFBuffer &buf);
	CObjVar *SearchVar(const char *name);

	int  PropCount();
	BOOL AddProp(CAMFObjectProperty *prop);
	CAMFObjectProperty *GetProp(int index);
private:
	CObjBuffer m_props;
	MTX_OBJ    m_mtx;
	int        m_count;
};










#endif


