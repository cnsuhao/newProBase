////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameItem.cpp
// Author: 陈建军(Chen Jianjun)
// Created: 2015-10-27
////////////////////////////////////////////////////////////////////////
#include "./MsgGameItem.h"
#include "Mgr/ItemMgr.h"
#include "MyCocosCommon/LayerHint.h"

//////////////////////////////////////////////////////////////////////////
CMsgGameItem::CMsgGameItem()
{
	Init();
	m_pInfo = (MSG_Info *)m_bufMsg;
	m_head.usType = _MSG_GAME_ITEM;
}

//////////////////////////////////////////////////////////////////////////
CMsgGameItem::~CMsgGameItem()
{

}

//////////////////////////////////////////////////////////////////////////
void CMsgGameItem::Process()
{
	switch (m_pInfo->sAction)
	{
	case MSG_ITEM_ACTION_LIST:
		{
			for (int i = 0; i < m_pInfo->sCount; i++)
			{
				ItemMgr::getInstance()->addItem(m_pInfo->stItem[i]);
			}
		}
		break;
	case MSG_ITEM_ACTION_ADD:
		{
			for (int i = 0; i < m_pInfo->sCount; i++)
			{
				ItemMgr::getInstance()->addItem(m_pInfo->stItem[i]);
			}
		}
		break;
	case MSG_ITEM_ACTION_DEL:
		{
			for (int i = 0; i < m_pInfo->sCount; i++)
			{
				ItemMgr::getInstance()->delItem(m_pInfo->stItem[i].i64ID);
			}
		}
		break;
	case MSG_ITEM_ACTION_USE:
		{
			if (MSG_ITEM_RESULT_FAIL == m_pInfo->sResult)
			{

			}
		}
		break;
	case MSG_ITEM_ACTION_EXPANSION:
		{
			if (MSG_ITEM_RESULT_FAIL == m_pInfo->sResult)
			{
				AddHint("123");
			}
			else
			{
				ItemMgr::getInstance()->expansionPackage();
			}
		}
		break;
	case MSG_ITEM_ACTION_OVERFLOW:
		{
			if (MSG_ITEM_RESULT_FAIL == m_pInfo->sResult)
			{

			}
		}
		break;
	default:
		break;
	}
}

////////////////////////////////////////////////////////////////////////
// Description: 创建物品消息基础结构
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CMsgGameItem::CreateMsgItem(MSG_ITEM_ACTION eAction, MSG_ITEM_RESULT eResult, OBJID idUser /*= ID_NONE*/, OBJID idItem /*= ID_NONE*/, int nParam /*= 0*/)
{
	this->Init();
	m_head.usType    = _MSG_GAME_ITEM;
	m_head.usSize    = sizeof(MSG_Info)-sizeof(ITEM_INFO);

	m_pInfo->sAction = eAction;
	m_pInfo->sResult = eResult;

	m_pInfo->nUserID = idUser;
	m_pInfo->idItem  = idItem;
	m_pInfo->nParam  = nParam;

	m_pInfo->sCount  = 0;
	return true;
}