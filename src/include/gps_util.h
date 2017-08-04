
#ifndef _GPS_UTIL_H_
#define _GPS_UTIL_H_



typedef struct tagGPS_XY
{
    double fValue;
    char   Area[4];
}GPS_XY,*PGPS_XY;


typedef struct tagGPS_INFO
{
    SYSTEMTIME tmUTC;
    char   SatelliteStatus[4];
    GPS_XY Latitude;//    N/S Indicator
    GPS_XY Longitude;//   E/W Indicator
    double fSpeedMarine;
    double fAngle;
	double fAltitude;
	int    SatelliteCount;

}GPS_INFO,*PGPS_INFO;

#ifdef __cplusplus
extern "C"
{
#endif

unsigned char MYAPI GPS_DataChecksum(const char *pszGPSData,unsigned char *pCheckSumOrig);
BOOL MYAPI GPS_DataIsValid(const char *szData);
BOOL MYAPI GPS_Gprmc(GPS_INFO *pGprmc,const char *szData);
BOOL MYAPI GPS_Gpgga(GPS_INFO *pGprmc,const char *szData);
double MYAPI GPS_Distance(const GPS_XY *pLat1,const GPS_XY *pLong1,
                          const GPS_XY *pLat2,const GPS_XY *pLong2);
#ifdef __cplusplus
}
#endif





















#endif













