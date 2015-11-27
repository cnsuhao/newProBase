////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2015, WuHan GoodGame, All Rights Reserved
// Moudle: NetMsg.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2015-1-19
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_NET_MSG_H_
#define _JYP_NET_MSG_H_

#include "Global/Global.h"

#pragma pack (4)
struct MSG_HEAD
{
	unsigned short usSize;
	unsigned short usType;
};
const unsigned int MESSAGE_MAX_SIZE		= 1024;		// 消息报文最大长度

class CNetMsg
{
public:
	CNetMsg() {this->Init();}
	virtual ~CNetMsg(){}

public:
	virtual const char*		GetBufferData() const {return m_bufMsg;}
	virtual unsigned short	GetSize() const {return m_head.usSize;}
	virtual unsigned short	GetType() const {return m_head.usType;}
	virtual const MSG_HEAD& GetHead() const {return m_head;}

public:
	virtual void Init(void);
	virtual bool IsVaild() const;
	virtual bool Create(const char* pMsgBuffer, unsigned short usSize, unsigned short usType);
	virtual void Process();
	virtual void Process(void* pInfo) final {} // 该函数不得被继承

public:
	static CNetMsg* CreateMsg(int nMsgSize, unsigned short usMsgType, const char* pbufMsg);
	static CNetMsg* RegisterMsg(unsigned short usMsgType);

protected:
	MSG_HEAD	m_head;
	char		m_bufMsg[MESSAGE_MAX_SIZE];
};

#endif // end of _JYP_NET_MSG_H_
