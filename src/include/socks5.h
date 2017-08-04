
#ifndef _SOCKS5_H_
#define _SOCKS5_H_

#define SOCKS_VER4		    0x04
#define SOCKS_VER5		    0x05

#define METHOD_AUTH_NO		0x00
#define METHOD_AUTH			0x02
#define METHOD_GSSAPI		0x01
#define METHOD_NO_ACCEPT	0xFF

#define SOCKS_AUTH_VER      0x01
#define SOCKS_AUTH_OK       0x00

#define CMD_CONNECT			0x01
#define CMD_BIND			0x02
#define CMD_UDP				0x03

#define FIELD_RSV			0x00

#define ATYP_IPV4			0x01
#define ATYP_DOMAINNAME		0x03
#define ATYP_IPV6			0x04

#define REP_SUCCESS			0x00
#define REP_FAIL_GENERAL	0x01
#define REP_CONNECT_DENY	0x02
#define REP_UNREACHABLE		0x03
#define REP_HOST_NOTFIND	0x04
#define REP_REFUSED			0x05
#define	REP_TTL_EXPIRED		0x06
#define REP_NOT_SUPPORT		0x07
#define REP_ATYP_NOTSUPPORT 0x08

#define SOCKS4_OK			0x5A
#define SOCKS4_REFUSE		0x5B
#define SOCKS4_CONNECT_FAIL	0x5C
#define SOCKS4_NOT_MATCH	0x5D

typedef struct tagSOCK4REQ_METHOD
{ 
	char Ver; 
	char Cmd; 
	char Port[2];
	char Ip[4];
	char User[1];
}SOCK4REQ_METHOD; 

typedef struct tagSOCK4ANS_METHOD
{ 
	char Ver; 
	char ReplyCode; 
	char Port[2];
	char Ip[4];
}SOCK4ANS_METHOD; 


typedef struct tagSOCK5REQ_METHOD
{ 
	char Ver; 
	char nMethods; 
	char Methods[255]; 
}SOCK5REQ_METHOD; 

typedef struct tagSOCK5ANS_METHOD
{ 
	char Ver; 
	char Method; 
}SOCK5ANS_METHOD; 



typedef struct tagSOCK5REQ_OTHER
{ 
	char Ver; 
	char Cmd; 
	char Rsv; 
	char Atyp; 
	char other[100]; 
}SOCK5REQ_OTHER; 

typedef struct tagSOCK5ANS_OTHER 
{ 
	char Ver; 
	char Rep; 
	char Rsv; 
	char Atyp; 
	char other[100]; 
}SOCK5ANS_OTHER; 

typedef struct tagSOCK5REQ_AUTH
{
	char Ver;
	char other[1];
}SOCK5REQ_AUTH;

typedef struct tagSOCK5ANS_AUTH
{
	char Ver;
	char Status;
}SOCK5ANS_AUTH;

typedef struct tagSOCK5UDP_DATA
{
	INT16 Rsv;
	char Frg;
	char Atyp;
	char other[100];

}SOCK5UDP_DATA,*PSOCK5UDP_DATA;

#endif





