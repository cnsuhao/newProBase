////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameSmelt.cpp
// Author: ������(Peng Wenqi)
// Created: 2015/11/18
////////////////////////////////////////////////////////////////////////
#include "MsgGameSmelt.h"

//////////////////////////////////////////////////////////////////////////
CMsgGameSmelt::CMsgGameSmelt()
{
	Init();
	m_pInfo = (MSG_Info *)m_bufMsg;
	m_head.usType = _MSG_GAME_SMELT;
}

//////////////////////////////////////////////////////////////////////////
CMsgGameSmelt::~CMsgGameSmelt()
{

}

//////////////////////////////////////////////////////////////////////////
void CMsgGameSmelt::Process()
{
	switch (m_pInfo->sAction)
	{
	case MSG_SMELT_ACTION_query:			// ��ѯ				C <-> S
		{

		}
		break;
	case MSG_SMELT_ACTION_smelt_begin:		// ��ʼ����			C <-> S
		{

		}
		break;
	case MSG_SMELT_ACTION_smelt_end:		// ��������			C <-> S
		{

		}
		break;
	case MSG_SMELT_ACTION_uptemp:			// ����				C --> S
		{

		}
		break;
	default:
		LogSave("CMsgGameSmelt::Process error action[%d]", m_pInfo->sAction);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
bool CMsgGameSmelt::CreateQuery()
{
	this->Init();
	m_head.usType = _MSG_GAME_SMELT;
	m_head.usSize = sizeof(MSG_Info);

	m_pInfo->sAction = MSG_SMELT_ACTION_query;
	m_pInfo->sResult = MSG_SMELT_RESULT_success;
	
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool CMsgGameSmelt::CreateSmeltBegin(uint32_t unTemp, uint32_t unOre)
{
	this->Init();
	m_head.usType = _MSG_GAME_SMELT;
	m_head.usSize = sizeof(MSG_Info);

	m_pInfo->sAction = MSG_SMELT_ACTION_smelt_begin;
	m_pInfo->sResult = MSG_SMELT_RESULT_success;

	m_pInfo->data.SmeltBegin.unTemp = unTemp;
	m_pInfo->data.SmeltBegin.unOre = unOre;

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool CMsgGameSmelt::CreateSmeltEnd()
{
	this->Init();
	m_head.usType = _MSG_GAME_SMELT;
	m_head.usSize = sizeof(MSG_Info);

	m_pInfo->sAction = MSG_SMELT_ACTION_smelt_end;
	m_pInfo->sResult = MSG_SMELT_RESULT_success;

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool CMsgGameSmelt::CreateFindMonster(uint32_t unTemp)
{
	this->Init();
	m_head.usType = _MSG_GAME_SMELT;
	m_head.usSize = sizeof(MSG_Info);

	m_pInfo->sAction = MSG_SMELT_ACTION_find_monster;
	m_pInfo->sResult = MSG_SMELT_RESULT_success;

	m_pInfo->data.FindMonster.unTemp = unTemp;

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool CMsgGameSmelt::CreateBattle(int nIndex)
{
	this->Init();
	m_head.usType = _MSG_GAME_SMELT;
	m_head.usSize = sizeof(MSG_Info);

	m_pInfo->sAction = MSG_SMELT_ACTION_battle;
	m_pInfo->sResult = MSG_SMELT_RESULT_success;

	m_pInfo->data.Battle.nIndex = nIndex;
	return true;
}
