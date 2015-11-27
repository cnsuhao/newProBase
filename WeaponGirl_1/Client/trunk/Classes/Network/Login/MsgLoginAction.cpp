////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: MsgLoginAction.cpp
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2014-11-4
////////////////////////////////////////////////////////////////////////
#include "MsgLoginAction.h"

//////////////////////////////////////////////////////////////////////////
CMsgLoginAction::CMsgLoginAction()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;
	m_head.usType = _MSG_LOGIN_CONNECT_ACTION;
	m_head.usSize = sizeof(MSG_Info);
}

//////////////////////////////////////////////////////////////////////////
CMsgLoginAction::~CMsgLoginAction()
{

}

//////////////////////////////////////////////////////////////////////////
bool CMsgLoginAction::CreateChooseUser( OBJID idUser )
{
	CHECKF(idUser);

	this->Init();
	m_head.usType = _MSG_LOGIN_CONNECT_ACTION;
	m_head.usSize = sizeof(MSG_Info);

	m_pInfo->sAction	= MSG_LOGIN_ACTION_TYPE_CHOOSE_USER;
	m_pInfo->nUserID	= idUser;

	return true;
}

void CMsgLoginAction::Process()
{

}

