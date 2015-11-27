////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameSmeltMonster.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/11/18
////////////////////////////////////////////////////////////////////////
#ifndef _GAMESERVER_MSG_MsgGameSmeltMonster_H_
#define _GAMESERVER_MSG_MsgGameSmeltMonster_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../NetMsg.h"

enum MSG_SMELT_MONSTER_ACTION
{
	MSG_SMELT_MONSTER_ACTION_query = 1,			// 查询				C <-> S
	MSG_SMELT_MONSTER_ACTION_meet_monster,		// 遇怪				C <-- S
	MSG_SMELT_MONSTER_ACTION_remove_monster,	// 怪物移除			C <-- S
	MSG_SMELT_MONSTER_ACTION_update_monster,	// 更新怪物信息		C <-- S
};

class CMsgGameSmeltMonster : public CNetMsg
{
public:
	CMsgGameSmeltMonster();
	virtual ~CMsgGameSmeltMonster();
	virtual void Process();

public:
	bool CreateBase(MSG_SMELT_MONSTER_ACTION eAction);

private:
	typedef struct
	{
		MSG_NUM_2BIT	sAction;
		MSG_NUM_2BIT	sCount;
		
		SMELT_MONSTER_INFO stInfo[1];
	}MSG_Info;

	MSG_Info* m_pInfo;
};

#endif	// end of _GAMESERVER_MSG_MsgGameSmelt_H_