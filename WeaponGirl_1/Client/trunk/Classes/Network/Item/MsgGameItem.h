////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameItem.h
// Author: 陈建军(Chen Jianjun)
// Created: 2015-10-27
////////////////////////////////////////////////////////////////////////
#ifndef _GAMESERVER_MSG_GAME_ITEM_H_
#define _GAMESERVER_MSG_GAME_ITEM_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../NetMsg.h"

enum MSG_ITEM_ACTION
{
	MSG_ITEM_ACTION_LIST		= 1,	// 物品列表		C <-- S
	MSG_ITEM_ACTION_ADD			= 2,	// 增加物品		C <-- S
	MSG_ITEM_ACTION_DEL			= 3,	// 物品删除		C <-- S
	MSG_ITEM_ACTION_USE			= 4,	// 使用物品		C <-> S
	MSG_ITEM_ACTION_EXPANSION	= 5,	// 解锁格子		C <-> S
	MSG_ITEM_ACTION_OVERFLOW	= 10,	// 增加溢出		C <-- S
};

enum MSG_ITEM_RESULT
{
	MSG_ITEM_RESULT_SUCC = 0,
	MSG_ITEM_RESULT_FAIL,
};

class CMsgGameItem : public CNetMsg
{
public:
	CMsgGameItem();
	virtual ~CMsgGameItem();

protected:
	virtual void Process();

public:
	bool CreateMsgItem(MSG_ITEM_ACTION eAction, MSG_ITEM_RESULT eResult, OBJID idUser = ID_NONE, OBJID idItem = ID_NONE, int nParam = 0);

private:
	typedef struct
	{
		MSG_NUM_2BIT	sAction;
		MSG_NUM_2BIT	sResult;

		MSG_NUM_4BIT	nUserID;
		MSG_NUM_8BIT	idItem;
		MSG_NUM_4BIT	nParam;

		MSG_NUM_2BIT	sCount;
		ITEM_INFO		stItem[1];
	}MSG_Info;

	MSG_Info* m_pInfo;
};

#endif // end of _GAMESERVER_MSG_GAME_ITEM_H_