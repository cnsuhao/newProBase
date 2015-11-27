////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2015, WuHan GoodGame, All Rights Reserved
// Moudle: NetworkServe.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015-1-19
////////////////////////////////////////////////////////////////////////
#include "NetworkServe.h"
#include "NetMsg.h"
#include "Root.h"
#include "SaveData\RC4.h"

static const char* MSG_CLIENT_TO_SERVER_KEY = "nY7BDYhbzzG4afQIroRDZdDVpbclHa1dgNHpV6kfpSrCHUW3nyNdkOPmHVQTRq65v2bHlfVAbkgMjQbyLqsSLEtFDQ297qf3Oha5ImSGh9bnvU0xZ1doJwxs6bwNx3JmAeQXB0y9WmzMpiLP";
static const char* MSG_SERVER_TO_CLIENT_KEY = "wz7qln9oubmLcmpM8Yrs60TuqrHFnTLpKUR7JJ1qlMGSxPuG8cW1vOYsUcLZmmkl9qsxoWUlkvzGiNgiXdDGvt2zmABWi9lc";

struct MSG_BASE
{
	unsigned short	usMsgSize;
	unsigned short	usMsgType;
	char buffer[MESSAGE_MAX_SIZE];
};

NetworkServe* NetworkServe::_instance = nullptr;

//////////////////////////////////////////////////////////////////////////
// 线程锁
static std::mutex s_NetworkMutexDeqSend;
static std::mutex s_NetworkMutexDeqRecv;
#define NETWORK_LOCK_MSG_SEND	MyLock objLockMessage(&s_NetworkMutexDeqSend)
#define NETWORK_LOCK_MSG_RECV	MyLock objLockMessage(&s_NetworkMutexDeqRecv)

//////////////////////////////////////////////////////////////////////////
NetworkServe::NetworkServe()
	: m_thread(&NetworkServe::processThread, this)
{
	m_status = NETWORK_STATUS_IDLE;
	m_nMsgIndex = 0;
	m_strIp = "";
	m_usPort = 0;
}

//////////////////////////////////////////////////////////////////////////
NetworkServe* NetworkServe::getInstance()
{
	if (nullptr == _instance)
	{
		_instance = new (std::nothrow) NetworkServe();
		if (_instance)
		{
			_instance->startThread();
		}
	}

	return _instance;
}

//////////////////////////////////////////////////////////////////////////
void NetworkServe::destroyInstance()
{
	if (_instance)
	{
		_instance->endThread();
	}
	CC_SAFE_DELETE(_instance);
}

//////////////////////////////////////////////////////////////////////////
void NetworkServe::startThread()
{
	m_socket.Init();
	m_thread.detach();
}

//////////////////////////////////////////////////////////////////////////
void NetworkServe::endThread()
{
	m_status = NETWORK_STATUS_EXIT;
}

//////////////////////////////////////////////////////////////////////////
void NetworkServe::processThread()
{
	fd_set	fdRecv;
	fd_set	fdSend;
	timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 100;

	while (NETWORK_STATUS_EXIT != m_status)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		if (!m_bConnectCompleted && NETWORK_STATUS_CONNECTING == m_status)		// 连接中
		{
			m_strIp = m_strNeedConnectIp;
			m_usPort = m_usNeedConnectPort;
			m_bConnectResult = m_socket.Connect(m_strNeedConnectIp.c_str(), m_usNeedConnectPort);
			m_bConnectCompleted = true;
		}
		else if (NETWORK_STATUS_CONNECT == m_status)	// 连接上了
		{
			FD_ZERO(&fdRecv);
			FD_ZERO(&fdSend);

			FD_SET((SOCKET)m_socket, &fdRecv);
			FD_SET((SOCKET)m_socket, &fdSend);

			auto result = select((SOCKET)m_socket+1, &fdRecv, &fdSend, nullptr, &timeout);
			if (SOCKET_ERROR == result)
			{
				m_status = NETWORK_STATUS_IDLE;
				this->onClosed();
				continue;
			}

			if (result > 0)
			{
				// 可发送数据
				if (FD_ISSET((SOCKET)m_socket, &fdSend))
				{
					if (!this->processSendMsg())
					{
						m_status = NETWORK_STATUS_IDLE;
						this->onClosed();
						continue;
					}
				}

				// 可接收数据
				if (FD_ISSET((SOCKET)m_socket, &fdRecv))
				{
					if (!this->processRecvMsg())
					{
						m_status = NETWORK_STATUS_IDLE;
						this->onClosed();
						continue;
					}
				}
			}
		}
	}

	if (NETWORK_STATUS_CONNECT == m_status)
	{
		m_socket.Close();
		m_status = NETWORK_STATUS_IDLE;
	}
	m_socket.Release();
}

////////////////////////////////////////////////////////////////////////
// Description:  获得消息秘钥
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: uint32_t
////////////////////////////////////////////////////////////////////////
uint32_t NetworkServe::GetMsgKey( uint32_t unMsgType, uint32_t unMsgIndex )
{
	int64_t i64MyRand = unMsgType + unMsgIndex;
	i64MyRand *= ((int64_t)22695477);
	i64MyRand ++;
	i64MyRand %= 100000007;
	return (uint32_t)i64MyRand;
}

////////////////////////////////////////////////////////////////////////
// Description: 异步线程 处理消息发送
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool NetworkServe::processSendMsg()
{
	NETWORK_LOCK_MSG_SEND;
	for (auto &iter : m_deqSendMsg)
	{
		auto pMsg = iter;
		IF_NOT (pMsg)
		{
			m_deqSendMsg.pop_front();
			return false;
		}

		MSG_BASE stMsgBase = {0};
		stMsgBase.usMsgSize = pMsg->GetSize() + 4;
		stMsgBase.usMsgType = pMsg->GetType();
		memcpy(stMsgBase.buffer, pMsg->GetBufferData(), pMsg->GetSize());

		// 加入消息尾
		m_nMsgIndex++;
		char szBuffer[MESSAGE_MAX_SIZE + 12] = {0};
		memcpy(szBuffer, &stMsgBase, pMsg->GetSize() + 4);
		unsigned short* pMsgLen = (unsigned short*)szBuffer;
		*pMsgLen = pMsg->GetSize() + 12;
		int* pCount = (int*)(szBuffer + pMsg->GetSize() + 4);
		*pCount = m_nMsgIndex;
		int* pMsgKey = (int*)(szBuffer + pMsg->GetSize() + 8);
		*pMsgKey = this->GetMsgKey(pMsg->GetType(), m_nMsgIndex);

		// 发送加密
		char szRc4Buffer[MESSAGE_MAX_SIZE + 12] = { 0 };
		memcpy(szRc4Buffer, szBuffer, sizeof(szRc4Buffer));
		uint32_t outLen;
		rc4::RC4((unsigned char*)szBuffer + 2, pMsg->GetSize() + 10, (unsigned char*)MSG_CLIENT_TO_SERVER_KEY, strlen(MSG_CLIENT_TO_SERVER_KEY), (unsigned char*)szRc4Buffer + 2, &outLen);
		int nSendResult = m_socket.Send(szRc4Buffer, pMsg->GetSize() + 12);

		// 不加密发送
//		int nSendResult = m_socket.Send(szBuffer, pMsg->GetSize() + 12);

		CC_SAFE_DELETE(pMsg);
		m_deqSendMsg.pop_front();

		if (SOCKET_ERROR == nSendResult)
		{
			return false;
		}
		return true;	// 每次调用仅发一包
	}

	return true;
}


////////////////////////////////////////////////////////////////////////
// Description: 异步线程 处理消息接受
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
bool NetworkServe::processRecvMsg()
{
	MSG_BASE stBase = {0};
	auto result = m_socket.Recv((char*)&stBase, 4);
	if (SOCKET_ERROR == result)
	{
		return false;
	}

	if (stBase.usMsgSize <= 4 || stBase.usMsgSize > MESSAGE_MAX_SIZE + 4)
	{
		LogSave("MsgSize Error! MsgType[%d] MsgSize[%d]", stBase.usMsgType, stBase.usMsgSize);
		return false;
	}

	result = m_socket.Recv(stBase.buffer, stBase.usMsgSize - 4);
	if (SOCKET_ERROR == result)
	{
		return false;
	}

	// 消息解密
	MSG_BASE stRc4 = { 0 };
	stRc4.usMsgSize = stBase.usMsgSize - 4;
	uint32_t outLen;
	rc4::RC4((const unsigned char*)&stBase.usMsgType, stBase.usMsgSize - 2, (unsigned char*)MSG_SERVER_TO_CLIENT_KEY, strlen(MSG_SERVER_TO_CLIENT_KEY), (unsigned char*)&stRc4.usMsgType, &outLen);

	auto pMsg = CNetMsg::CreateMsg(stRc4.usMsgSize, stRc4.usMsgType, stRc4.buffer);
	if (pMsg)
	{
		NETWORK_LOCK_MSG_RECV;
		m_deqRecvMsg.push_back(pMsg);
	}

	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 主线程每秒心跳
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void NetworkServe::onTimer(float dt)
{
	// 连接后处理完毕
	if (m_bConnectCompleted && NETWORK_STATUS_CONNECTING == m_status)
	{
		if (m_bConnectResult)
		{
			m_status = NETWORK_STATUS_CONNECT;
			this->onConnectOK();

			if (m_connectSuccessProcess)
			{
				m_connectSuccessProcess();
			}
		}
		else
		{
			m_status = NETWORK_STATUS_IDLE;

			if (m_connectFailedProcess)
			{
				m_connectFailedProcess();
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////
// Description: 发送消息接口
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool NetworkServe::sendMsg( const CNetMsg& rMsg )
{
	CHECKF(NETWORK_STATUS_CONNECT == m_status);

	auto pMsg = new (std::nothrow) CNetMsg;
	CHECKF(pMsg);
	CHECKF(pMsg->Create(rMsg.GetBufferData(), rMsg.GetSize(), rMsg.GetType()));

	NETWORK_LOCK_MSG_SEND;
	m_deqSendMsg.push_back(pMsg);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 接收消息接口
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void NetworkServe::recvMsg()
{
	while (!m_deqRecvMsg.empty())
	{
		auto pMsg = *(m_deqRecvMsg.begin());
		{
			NETWORK_LOCK_MSG_RECV;
			m_deqRecvMsg.pop_front();
		}
		CHECKC(pMsg);
		pMsg->Process();
		CC_SAFE_DELETE(pMsg);
	}
}

////////////////////////////////////////////////////////////////////////
// Description: 断开时, 处理接收的消息
// Arguments:	该函数仅提供给主线程调用
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void NetworkServe::recvMsgBreak()
{
	LogSave("m_deqRecvMsgBreak size(%d)", m_deqRecvMsgBreak.size());

	while (!m_deqRecvMsgBreak.empty())
	{
		auto pMsg = *(m_deqRecvMsgBreak.begin());
		{
			m_deqRecvMsgBreak.pop_front();
		}
		CHECKC(pMsg);
		pMsg->Process();
		CC_SAFE_DELETE(pMsg);
	}
	m_deqRecvMsgBreak.clear();
}

////////////////////////////////////////////////////////////////////////
// Description: 连接成功后通知
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void NetworkServe::onConnectOK()
{
	// 根节点处理
	Root::getInstance()->OnConnectOK();
}

////////////////////////////////////////////////////////////////////////
// Description: 连接关闭通知
// Arguments:	主动close将无此通知
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void NetworkServe::onClosed()
{
	LogSave("NetworkServe::onClosed");

	m_status = NETWORK_STATUS_IDLE;

	LogicDataMgr::getInstance()->setConnectStatus(CONNECT_STATUS_none);
	LogicDataMgr::getInstance()->SetMemoryDataAttr(LOGIC_DATA_NeedProcessNetBreak, 1);

	// 接收缓冲区, 移动到断开处理队列
	{
		NETWORK_LOCK_MSG_RECV;
		m_deqRecvMsgBreak = m_deqRecvMsg;
		m_deqRecvMsg.clear();
	}

	// 发送缓冲区
	{
		NETWORK_LOCK_MSG_SEND;
		for (auto pMsg : m_deqSendMsg)
		{ 
			CC_SAFE_DELETE(pMsg);
		}
		m_deqSendMsg.clear();
	}

	// 消息序号
	m_nMsgIndex = 0;

	// ip端口
	m_strIp = "";
	m_usPort = 0;
}

////////////////////////////////////////////////////////////////////////
// Description: 连接
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool NetworkServe::connect(const std::string& ip, unsigned short port, const ConnectListener& succ /*= nullptr*/, const ConnectListener& fail /*= nullptr*/)
{
	CHECKF(m_status == NETWORK_STATUS_IDLE);
	CHECKF(m_socket.Create());
	
	m_strNeedConnectIp = ip;
	m_usNeedConnectPort = port;
	m_connectSuccessProcess = succ;
	m_connectFailedProcess = fail;
	m_bConnectCompleted = false;
	m_status = NETWORK_STATUS_CONNECTING;

	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 关闭套接字
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void NetworkServe::closeSocket()
{
	LogSave("NetworkServe::closeSocket");
	
	m_status = NETWORK_STATUS_IDLE;

	if (NETWORK_STATUS_CONNECT == m_status)
	{
		m_socket.Close();
	}

	// 关闭前处理完接收到的消息
	this->recvMsg();

	// 接收缓冲区
	{
		NETWORK_LOCK_MSG_RECV;
		for (auto pMsg : m_deqRecvMsg)
		{
			CC_SAFE_DELETE(pMsg);
		}
		m_deqRecvMsg.clear();
	}

	// 发送缓冲区
	{
		NETWORK_LOCK_MSG_SEND;
		for (auto pMsg : m_deqSendMsg)
		{
			CC_SAFE_DELETE(pMsg);
		}
		m_deqSendMsg.clear();
	}

	// 消息序号
	m_nMsgIndex = 0;

	// ip端口
	m_strIp = "";
	m_usPort = 0;

	// 根节点处理, 主动关闭不进行根节点处理
//	Root::getInstance()->OnConnectBreak();
}

