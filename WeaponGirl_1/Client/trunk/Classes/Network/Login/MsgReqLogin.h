////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: MsgReqLogin.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2015-4-2
////////////////////////////////////////////////////////////////////////
#ifndef _GAMESERVER_MSG_REQ_LOGIN_H_
#define _GAMESERVER_MSG_REQ_LOGIN_H_

#include "../NetMsg.h"

class CMsgReqLogin : public CNetMsg  
{
public:
	CMsgReqLogin();
	virtual ~CMsgReqLogin();
	virtual void	Process		();

public:
	bool CreateEmpty();

private:
	typedef struct
	{
		MSG_NUM_4BIT	nLine;			// 返回 游戏服线路号
		MSG_STR_16BIT	szAccIp;		// 返回 游戏服ip
		MSG_NUM_4BIT	nAccPort;		// 返回 游戏服端口
	}MSG_Info;

	MSG_Info* m_pInfo;
};


#endif // end of _GAMESERVER_MSG_REQ_LOGIN_H_