////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameSmeltMonster.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/11/18
////////////////////////////////////////////////////////////////////////
#include "MsgGameSmeltMonster.h"

//////////////////////////////////////////////////////////////////////////
CMsgGameSmeltMonster::CMsgGameSmeltMonster()
{
	Init();
	m_pInfo = (MSG_Info *)m_bufMsg;
	m_head.usType = _MSG_GAME_SMELT_MONSTER;
}

//////////////////////////////////////////////////////////////////////////
CMsgGameSmeltMonster::~CMsgGameSmeltMonster()
{

}

//////////////////////////////////////////////////////////////////////////
void CMsgGameSmeltMonster::Process()
{
	switch (m_pInfo->sAction)
	{
	case MSG_SMELT_MONSTER_ACTION_query:			// 查询				C <-> S
		break;
	case MSG_SMELT_MONSTER_ACTION_meet_monster:		// 遇怪				C <-- S
		break;
	case MSG_SMELT_MONSTER_ACTION_remove_monster:	// 怪物移除			C <-- S
		break;
	case MSG_SMELT_MONSTER_ACTION_update_monster:	// 更新怪物信息		C <-- S
		break;
	default:
		LogSave("CMsgGameSmeltMonster::Process error action[%d]", m_pInfo->sAction);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
bool CMsgGameSmeltMonster::CreateBase(MSG_SMELT_MONSTER_ACTION eAction)
{
	this->Init();
	m_head.usType = _MSG_GAME_SMELT_MONSTER;
	m_head.usSize = sizeof(MSG_Info) - sizeof(SMELT_MONSTER_INFO);

	m_pInfo->sAction = MSG_SMELT_MONSTER_ACTION_query;
	m_pInfo->sCount = 0;
	return true;
}
