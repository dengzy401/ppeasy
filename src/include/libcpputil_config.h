


#ifndef _LIBCPPUTIL_CONFIG_H_
#define _LIBCPPUTIL_CONFIG_H_


class _CPP_UTIL_EXPORT CObjConfig 
{
public:
	CObjConfig();
	virtual ~CObjConfig();
public:
	virtual BOOL Init(int argc = 0,char *argv[] = NULL ,void *hInsWin32 = NULL);
	static BOOL IsHaveDriveLabel(const char *szPath);
	void SetAppName(const char *name);
	void SetCompanyName(const char *name);
	void Log(int nLevel,const char *fmt, ...);
	void VLog(int nLevel,const char *fmt, va_list _ArgList);
    DLL_HANDLE LoadPlugin( const char * dlPath , const char *szName );
public:
	char m_szPathIniFile[LEN_MAX_PATH];
	char m_szPathWorkDir[LEN_MAX_PATH];
	char m_szPathKeyFile[LEN_MAX_PATH];
	char m_szBoottime[40];
	char m_szAppName[40];
	char m_szCompanyName[40];

	char m_szPathLogFile[LEN_MAX_PATH];
	char m_szPathLogFileDir[LEN_MAX_PATH];
	char m_szPathLogFileDefault[LEN_MAX_PATH];
	int  m_nLogLevel;
	BOOL m_IsLogConsole;
	BOOL m_bKeepLogfile;
	int  m_nMaxLogFileSize;
private:
	BOOL m_bInited;
public:
	MTX_OBJ m_mtxLog;
};


#endif



