////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: MsgLoginConnect.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2014-11-3
////////////////////////////////////////////////////////////////////////
#ifndef _GAMESERVER_MSG_LOGIN_CONNECT_H_
#define _GAMESERVER_MSG_LOGIN_CONNECT_H_

#include "../NetMsg.h"

class CMsgLoginConnect : public CNetMsg  
{
public:
	CMsgLoginConnect();
	virtual ~CMsgLoginConnect();

public:
	bool CreateAccountConnect(const char* pszAccountName, const char* pszAccountPwd);

private:
	typedef struct
	{
		char szAccountName[64];
		char szAccountPassword[128];
	}MSG_Info;

	MSG_Info* m_pInfo;
};


#endif // end of _GAMESERVER_MSG_LOGIN_CONNECT_H_