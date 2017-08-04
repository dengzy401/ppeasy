
#ifndef _LIBCOUNTER_H_
#define _LIBCOUNTER_H_


#if defined(__cplusplus) 
extern "C"
{
#endif

    void  LibCounterInit();
    int  LibCounterIncEx(const char *szCounterName,int nCount);
    int  LibCounterDecEx(const char *szCounterName,int nCount);
    int  LibCounterInc(const char *szCounterName);
    int  LibCounterDec(const char *szCounterName);
    int  LibCounter(const char *szCounterName);
    int  LibCounterDelete(const char *szCounterName);


#if defined(__cplusplus) 
}
#endif
#endif