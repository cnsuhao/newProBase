//////////////////////////////////////////////////////////////////////////
// Copyright (C), 1999-2011, ZYHD Co., Ltd.
//
// File: 	MySocket.h
// Purpose:	跨平台socket封装(Win32与linux)
//
// Version	Author				Date		Modification
// v0.1		彭文奇(PengWenqi)	2011/11/17	Create
// 
//////////////////////////////////////////////////////////////////////////
#ifndef MY_SHELL_ZH2_MYSOCKET
#define MY_SHELL_ZH2_MYSOCKET

#include <stdio.h>


#ifdef WIN32
	#include <winsock2.h>
	#include <MSTcpIP.h>
	typedef int	socklen_t;
#else
	#include <sys/types.h>
	#include <arpa/inet.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <sys/stat.h>
	#include <netinet/tcp.h>

	typedef int	SOCKET;

	#define INVALID_SOCKET	-1
	#define SOCKET_ERROR	-1
#endif


class CMySocket 
{
public:
	CMySocket(SOCKET sock = INVALID_SOCKET) : m_sock(sock) {}
	~CMySocket(){}
	CMySocket& operator=(SOCKET s)	{m_sock = s;return (*this);}
	operator SOCKET(void)			{return m_sock;}

	// Static
public:
	static bool Init	(void);	
	static void Release	(void);

	// Function
public:
	bool	Create		();
	bool	Connect		(const char* pszIP, unsigned short usPort);
	bool	Bind		(unsigned short usPort);
	bool	Listen		(int nBacklog = 10); 
	bool	Accept		(CMySocket& s, char* pszFromIP = nullptr);
	int		Send		(const char* pszBuf, int nLen, int nFlags = 0);
	int		Recv		(char* pszBuf, int nLen, int nFlags = 0);
	int		Close		(void);

protected:
	void	SetSocket	(void);

protected:
	SOCKET m_sock;
};

#endif // end of MY_SHELL_ZH2_MYSOCKET
