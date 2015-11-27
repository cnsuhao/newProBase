////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameInstanceList.h
// Author: ³Â½¨¾ü(Chen Jianjun)
// Created: 2015-11-13
////////////////////////////////////////////////////////////////////////
#ifndef _GAMEKERNEL_MSG_GAME_INSTANCE_LIST_H_
#define _GAMEKERNEL_MSG_GAME_INSTANCE_LIST_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./Network/NetMsg.h"

class CMsgGameInstanceList : public CNetMsg
{
public:
	CMsgGameInstanceList();
	virtual ~CMsgGameInstanceList();

protected:
	virtual void Process();

private:
	typedef struct
	{
		MSG_NUM_4BIT			nInfoCount;
		ST_INSTANCE_LIST_INFO	stInfo[1];
	}MSG_Info;

	MSG_Info* m_pInfo;
};

#endif