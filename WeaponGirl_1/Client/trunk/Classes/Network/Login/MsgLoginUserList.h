////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: MsgLoginUserList.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2014-11-4
////////////////////////////////////////////////////////////////////////
#ifndef _GAMESERVER_MSG_LOGIN_USER_LIST_H_
#define _GAMESERVER_MSG_LOGIN_USER_LIST_H_

#include "../NetMsg.h"

class CMsgLoginUserList : public CNetMsg  
{
public:
	CMsgLoginUserList();
	virtual ~CMsgLoginUserList();
	virtual void Process () override;

private:
	typedef struct
	{
		MSG_NUM_4BIT	nAccountID;
		MSG_NUM_4BIT	nCount;
		USER_LOGIN_SNAP	stInfo[1];
	}MSG_Info;

	MSG_Info* m_pInfo;
};


#endif // end of _GAMESERVER_MSG_LOGIN_USER_LIST_H_