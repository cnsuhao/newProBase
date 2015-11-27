////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: MsgLoginConnect.cpp
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2014-11-3
////////////////////////////////////////////////////////////////////////
#include "Global/Global.h"
#include "MsgLoginConnect.h"

//////////////////////////////////////////////////////////////////////////
CMsgLoginConnect::CMsgLoginConnect()
{
	Init();
	m_pInfo	=(MSG_Info*)m_bufMsg;
	m_head.usType = _MSG_LOGIN_CONNECT;
	m_head.usSize = sizeof(MSG_Info);
}

//////////////////////////////////////////////////////////////////////////
CMsgLoginConnect::~CMsgLoginConnect()
{

}

//////////////////////////////////////////////////////////////////////////
bool CMsgLoginConnect::CreateAccountConnect( const char* pszAccountName, const char* pszAccountPwd )
{
	this->Init();

	::SafeCopy(m_pInfo->szAccountName, pszAccountName, sizeof(m_pInfo->szAccountName));
	::SafeCopy(m_pInfo->szAccountPassword, pszAccountPwd, sizeof(m_pInfo->szAccountPassword));

	m_head.usType = _MSG_LOGIN_CONNECT;
	m_head.usSize = sizeof(MSG_Info);

	return true;
}

