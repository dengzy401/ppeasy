

#ifndef _GPS_PROG_MGR_H_
#define _GPS_PROG_MGR_H_

#include "gps_util.h"

typedef enum tagGPSAccessStatus
{
    GPSAcFail = 0 ,
    GPSAcOK  = 1 ,
    GPSAcAlready  = 2,
    GPSAcLeave = 3

}GPSAccessStatus;

typedef void (MYAPI *_GpsItemProgCallback)( GPS_ITEM_PROG *pProg);
typedef GPS_INFO GPS_GPRMC;
#ifdef __cplusplus
extern "C"
{
#endif

BOOL MYAPI InitGpsMgr();
void MYAPI GpsFreeAllItems();
void MYAPI SafeGpsFreeAllItems();
int MYAPI GpsLoadProgFromData(const char *szFile, _GpsItemProgCallback pFuncCallBack);
int MYAPI SafeGpsLoadProgFromData(const char *szFile, _GpsItemProgCallback pFuncCallBack);
GPSAccessStatus MYAPI GPSAccessItem(const GPS_GPRMC *pGprmc,char *szFile,int nLen);
GPSAccessStatus MYAPI SafeGPSAccessItem(const GPS_GPRMC *pGprmc,char *szFile,int nLen);

#ifdef __cplusplus
}
#endif


#endif

