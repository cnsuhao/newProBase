////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2015, WuHan GoodGame, All Rights Reserved
// Moudle: NetworkServe.h
// Author: ������(Peng Wenqi)
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
	NETWORK_STATUS_IDLE,		// ����
	NETWORK_STATUS_CONNECTING,	// ������
	NETWORK_STATUS_CONNECT,		// ����
	NETWORK_STATUS_EXIT,		// �˳��첽�߳�
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

	// ���̵߳��ýӿ�
public:
	bool			sendMsg(const CNetMsg& rMsg);	// ������Ϣ
	void			recvMsg();						// ������Ϣ
	void			recvMsgBreak();					// �Ͽ�ʱ, ������յ���Ϣ
	void			onConnectOK();					// ���ӳɹ���ص�
	void			onClosed();						// �رպ�ص�
	void			onTimer(float dt);				// ÿ������

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

	bool				m_bConnectCompleted;		// �������
	bool				m_bConnectResult;			// ���ӽ��
	std::string			m_strNeedConnectIp;			// ��Ҫ����ip
	unsigned short		m_usNeedConnectPort;		// ��Ҫ���Ӷ˿�
	ConnectListener		m_connectSuccessProcess;	// ���Ӻ�ɹ�����
	ConnectListener		m_connectFailedProcess;		// ���Ӻ�ʧ�ܴ���
};

#endif // end of _JYP_NETWORK_SERVE_H_