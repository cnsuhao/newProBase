//////////////////////////////////////////////////////////////////////////
// Copyright (C), 1999-2011, ZYHD Co., Ltd.
//
// File: 	MySocket.cpp
// Purpose:	
//
// Version	Author				Date		Modification
// v0.1		彭文奇(PengWenqi)	2011/11/17	Create
// 
//////////////////////////////////////////////////////////////////////////
#include "MySocket.h"
#include "Global/Global.h"

#ifdef WIN32
	#pragma comment(lib, "wsock32")
#else
	#include <errno.h>
#endif

//////////////////////////////////////////////////////////////////////////
// Func:	初始化(windows专用)
// Return:	bool
// Date: 	2011/11/17
// Author:	彭文奇(PengWenqi)
// Purpose:	
//////////////////////////////////////////////////////////////////////////
bool CMySocket::Init()
{
#ifdef WIN32
	WSADATA wsaData;
	WORD usVersion = MAKEWORD(2, 0);
	int nRet = WSAStartup(usVersion, &wsaData);
	if (nRet) 
	{
		cocos2d::log("Initilize winsock error !");
		return false;
	}
#endif
	return true;
}

//////////////////////////////////////////////////////////////////////////
// Func:	清理(windows专用)
// Return:	void
// Date: 	2011/11/17
// Author:	彭文奇(PengWenqi)
// Purpose:	
//////////////////////////////////////////////////////////////////////////
void CMySocket::Release()
{
#ifdef WIN32
		WSACleanup();
#endif
}

//////////////////////////////////////////////////////////////////////////
// Func:	创建套接字
// Return:	bool
// Date: 	2011/11/17
// Author:	彭文奇(PengWenqi)
// Purpose:	
//////////////////////////////////////////////////////////////////////////
bool CMySocket::Create()
{
	if (INVALID_SOCKET != m_sock)
	{
		this->Close();
	}

	m_sock = socket(AF_INET, SOCK_STREAM, 0);
	if ( m_sock == INVALID_SOCKET ) 
	{
		return false;
	}
	cocos2d::log("CMySocket::Create Socket[%d]", (int)m_sock);
	return true;
}

//////////////////////////////////////////////////////////////////////////
// Func:	连接
// Return:	bool
// Date: 	2011/11/17
// Author:	彭文奇(PengWenqi)
// Purpose:	
//////////////////////////////////////////////////////////////////////////
bool CMySocket::Connect(const char* pszIP, unsigned short usPort)
{
	cocos2d::log("CMySocket::Connect ip[%s] port[%d]", pszIP, usPort);
	sockaddr_in stSockAddr;
	stSockAddr.sin_family = AF_INET;
	stSockAddr.sin_addr.s_addr = inet_addr(pszIP);
	stSockAddr.sin_port = htons(usPort);
	int nRet = connect(m_sock, (sockaddr*)&stSockAddr, sizeof(stSockAddr));
	if (SOCKET_ERROR == nRet) 
	{
		return false;
	}

	this->SetSocket();

	return true;
}

//////////////////////////////////////////////////////////////////////////
// Func:	设置KeepAlive和接收超时等内容
// Return:	
// Date: 	2011/12/12
// Author:	彭文奇(PengWenqi)
// Purpose:	
//////////////////////////////////////////////////////////////////////////
void CMySocket::SetSocket(void)
{
	int nMillisec = 30000;
	setsockopt(m_sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&nMillisec, sizeof(nMillisec));


	int nKeepAlive = 1;
	const int KEEPALIVE_INTERVAL	= 30;
	const int KEEPALIVE_TIME		= 5;
#if defined(_WIN32) || defined(WIN32)
	struct tcp_keepalive inKeepAlive		= {0};
	struct tcp_keepalive outKeepAlive		= {0};
	DWORD lInLen			= sizeof(struct tcp_keepalive);
	DWORD lOutLen = sizeof(struct tcp_keepalive);
	DWORD lBytesReturn = 0;

	inKeepAlive.onoff				= 1;
	inKeepAlive.keepaliveinterval	= KEEPALIVE_INTERVAL * 1000;
	inKeepAlive.keepalivetime		= KEEPALIVE_TIME * 1000;

	int sRet = setsockopt (m_sock, SOL_SOCKET, SO_KEEPALIVE,
		(char *) &nKeepAlive, sizeof(nKeepAlive));

	sRet = WSAIoctl(m_sock, _WSAIOW(IOC_VENDOR,4),
		&inKeepAlive,	lInLen,
		&outKeepAlive,	lOutLen,
		&lBytesReturn,	NULL,	NULL);
#else
	int keepIdle					= KEEPALIVE_INTERVAL;
	int keepInterval				= KEEPALIVE_TIME;
	int keepCount					= 3;

	int sRet = setsockopt (m_sock, SOL_SOCKET, SO_KEEPALIVE,
				(char*) &nKeepAlive, sizeof(nKeepAlive));

	sRet = setsockopt (m_sock, IPPROTO_TCP, TCP_KEEPIDLE,
				(char*) &keepIdle, sizeof(keepIdle));

	sRet = setsockopt (m_sock, IPPROTO_TCP, TCP_KEEPINTVL,
				(char*) &keepInterval, sizeof(keepInterval));

	sRet = setsockopt (m_sock, IPPROTO_TCP, TCP_KEEPCNT,
				(char*) &keepCount, sizeof(keepCount));
#endif
	//--------------------END
	
}

//////////////////////////////////////////////////////////////////////////
// Func:	绑定
// Return:	bool
// Date: 	2011/11/17
// Author:	彭文奇(PengWenqi)
// Purpose:	
//////////////////////////////////////////////////////////////////////////
bool CMySocket::Bind(unsigned short usPort)
{
	sockaddr_in stSockAddr;
	stSockAddr.sin_family = AF_INET;
	stSockAddr.sin_addr.s_addr = INADDR_ANY;
	stSockAddr.sin_port = htons(usPort);

	int nOpt =  1;
	if (setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (char*)&nOpt, sizeof(nOpt)) < 0)
	{
		return false;
	}

	int nRet = bind(m_sock, (struct sockaddr*)&stSockAddr, sizeof(stSockAddr));
	if (SOCKET_ERROR == nRet) 
	{
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
// Func:	监听
// Return:	bool
// Date: 	2011/11/17
// Author:	彭文奇(PengWenqi)
// Purpose:	
//////////////////////////////////////////////////////////////////////////
bool CMySocket::Listen(int nBacklog)
{
	int nRet = listen(m_sock, nBacklog);
	if (SOCKET_ERROR == nRet) 
	{
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
// Func:	接受
// Return:	bool
// Date: 	2011/11/17
// Author:	彭文奇(PengWenqi)
// Purpose:	
//////////////////////////////////////////////////////////////////////////
bool CMySocket::Accept(CMySocket& s, char* pszFromIP /*= nullptr*/)
{
	struct sockaddr_in cliaddr;
	socklen_t nAddrLen = sizeof(cliaddr);
	SOCKET sock = accept(m_sock, (struct sockaddr*)&cliaddr, &nAddrLen);
	if (SOCKET_ERROR == sock)
	{
		return false;
	}

	s = sock;
	if (pszFromIP != nullptr)
	{
		sprintf(pszFromIP, "%s", inet_ntoa(cliaddr.sin_addr));
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
// Func:	发送
// Return:	int
// Date: 	2011/11/17
// Author:	彭文奇(PengWenqi)
// Purpose:	
//////////////////////////////////////////////////////////////////////////
int CMySocket::Send(const char* pszBuf, int nLen, int nFlags)
{
	if (nullptr == pszBuf || nLen <= 0)
	{
		return -1;
	}

	int nBytes = 0;
	int nCount = 0;

	while (nCount < nLen) 
	{
		nBytes = send(m_sock, pszBuf + nCount, nLen - nCount, nFlags);
		if (-1 == nBytes || 0 == nBytes)
		{
			return -1;
		}
		nCount += nBytes;
	} 

	return nCount;
}

//////////////////////////////////////////////////////////////////////////
// Func:	接收
// Return:	int
// Date: 	2011/11/17
// Author:	彭文奇(PengWenqi)
// Purpose:	
//////////////////////////////////////////////////////////////////////////
int CMySocket::Recv(char* pszBuf, int nLen, int nFlags)
{
	if (nullptr == pszBuf || nLen <= 0)
	{
		return -1;
	}

	int nBytes = 0;
	int nCount = 0;

	while (nCount < nLen)
	{
		nBytes = recv(m_sock, pszBuf + nCount, nLen - nCount, nFlags);
		if (-1 == nBytes || 0 == nBytes)
		{
			return -1;
		}
		nCount += nBytes;
	}

	return nCount;
}

//////////////////////////////////////////////////////////////////////////
// Func:	关闭
// Return:	int
// Date: 	2011/11/17
// Author:	彭文奇(PengWenqi)
// Purpose:	
//////////////////////////////////////////////////////////////////////////
int CMySocket::Close()
{
#ifdef WIN32
	return (closesocket(m_sock));
#else
	return (close(m_sock));
#endif
}
