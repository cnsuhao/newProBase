////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: MsgLoginUserList.cpp
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2014-11-4
////////////////////////////////////////////////////////////////////////
#include "MsgLoginUserList.h"
#include "Root.h"
#include "Mgr/LoginMgr.h"

//////////////////////////////////////////////////////////////////////////
CMsgLoginUserList::CMsgLoginUserList()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;
	m_head.usType= _MSG_LOGIN_USER_LIST;
	m_head.usSize = sizeof(MSG_Info);
}

//////////////////////////////////////////////////////////////////////////
CMsgLoginUserList::~CMsgLoginUserList()
{

}

//////////////////////////////////////////////////////////////////////////
void CMsgLoginUserList::Process( )
{
	CHECK(m_pInfo->nCount >= 0 && m_pInfo->nCount <= MAX_USER_AMOUNT);
	LogicDataMgr::getInstance()->clearLoginSnap();
	for (auto i = 0; i < m_pInfo->nCount; i++)
	{
		LogicDataMgr::getInstance()->addLoginSnap(m_pInfo->stInfo[i]);
	}
	LoginMgr::getInstance()->processUserSnap();
}
