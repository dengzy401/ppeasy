


#ifndef _libTransCode_h_
#define _libTransCode_h_



typedef int ( *__TransCodeLogFunc)( void *control,int prio,const char *fmt, va_list ap );
typedef int ( *__TransCodeProgressFunc )( void *control, int is_last_report, TIME_T timer_start, TIME_T cur_time );

typedef struct tagTransCodeCtx
{
    int     m_nReturnCode;
    int     m_bExit;
    TIME_T  m_tmBegin;
    TIME_T  m_tmEnd;
    void *  m_usrData;
    __TransCodeLogFunc m_log;
    __TransCodeProgressFunc m_progress;
}TransCodeCtx;

#endif








