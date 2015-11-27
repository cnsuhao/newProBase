////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2015, WuHan GoodGame, All Rights Reserved
// Moudle: NetworkServe.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2015-1-19
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_NETWORK_SERVE_H_
#define _JYP_NETWORK_SERVE_H_

#include "Global/Global.h"
#include "MySocket.h"

class CNetMsg;
typedef std::deque<CNetMsg*> DEQ_MSG;

enum NETWORK_STATUS
{
	NETWORK_STATUS_IDLE,		// 空闲
	NETWORK_STATUS_CONNECTING,	// 连接中
	NETWORK_STATUS_CONNECT,		// 连接
	NETWORK_STATUS_EXIT,		// 退出异步线程
};

typedef std::function<void()> ConnectListener;

class NetworkServe 
{
public:
	static NetworkServe*	getInstance();
	static void				destroyInstance();
private:
	static NetworkServe* _instance;
	NetworkServe();

protected:
	void			startThread();
	void			endThread();
	void			processThread();

	// 主线程调用接口
public:
	bool			sendMsg(const CNetMsg& rMsg);	// 发送消息
	void			recvMsg();						// 接收消息
	void			recvMsgBreak();					// 断开时, 处理接收的消息
	void			onConnectOK();					// 连接成功后回调
	void			onClosed();						// 关闭后回调
	void			onTimer(float dt);				// 每秒心跳

public:
	bool			connect(const std::string& ip, unsigned short port, const ConnectListener& succ = nullptr, const ConnectListener& fail = nullptr);
	void			closeSocket();
	NETWORK_STATUS	getStatus() const {return m_status;}
	std::string		getIp() const {return m_strIp;}
	unsigned short  getPort() const {return m_usPort;}

private:
	bool			processSendMsg();
	bool			processRecvMsg();
	uint32_t		GetMsgKey( uint32_t unMsgType, uint32_t unMsgIndex );

private:
	DEQ_MSG				m_deqRecvMsg;
	DEQ_MSG				m_deqSendMsg;
	DEQ_MSG				m_deqRecvMsgBreak;

	NETWORK_STATUS		m_status;	

	std::thread			m_thread;
	CMySocket			m_socket;

	std::string			m_strIp;
	unsigned short		m_usPort;

	int					m_nMsgIndex;

	bool				m_bConnectCompleted;		// 连接完成
	bool				m_bConnectResult;			// 连接结果
	std::string			m_strNeedConnectIp;			// 需要连接ip
	unsigned short		m_usNeedConnectPort;		// 需要连接端口
	ConnectListener		m_connectSuccessProcess;	// 连接后成功处理
	ConnectListener		m_connectFailedProcess;		// 连接后失败处理
};

#endif // end of _JYP_NETWORK_SERVE_H_