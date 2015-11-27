////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: MsgLoginKickReason.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2014-11-4
////////////////////////////////////////////////////////////////////////
#ifndef _GAMESERVER_MSG_LOGIN_KICK_REASON_H_
#define _GAMESERVER_MSG_LOGIN_KICK_REASON_H_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../NetMsg.h"

class CMsgKickReason : public CNetMsg
{
public:
	CMsgKickReason();
	virtual ~CMsgKickReason();
	virtual void Process();

private:
	typedef struct
	{
		MSG_NUM_4BIT	nReason;
		MSG_NUM_4BIT	nParam;
	}MSG_Info;
	
	MSG_Info* m_pInfo;
};

#endif	// end of _GAMESERVER_MSG_LOGIN_KICK_REASON_H_