////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameUserAttr.cpp
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2014-11-10
////////////////////////////////////////////////////////////////////////
#include "./MsgGameUserAttr.h"
#include "Mgr/UserAttrMgr.h"

//////////////////////////////////////////////////////////////////////////
CMsgGameUserAttr::CMsgGameUserAttr()
{
	Init();
	m_pInfo = (MSG_Info*)m_bufMsg;
	m_head.usType = _MSG_GAME_USER_ATTR;
	m_head.usSize = sizeof(MSG_Info);
}

//////////////////////////////////////////////////////////////////////////
CMsgGameUserAttr::~CMsgGameUserAttr()
{

}

//////////////////////////////////////////////////////////////////////////
void CMsgGameUserAttr::Process()
{
	for (int i = 0; i < m_pInfo->nCount; i++)
	{
		UserAttrMgr::getInstance()->updateAttr((USER_ATTR)(m_pInfo->stInfo[i].nType), m_pInfo->stInfo[i].i64Data);
	}
}

