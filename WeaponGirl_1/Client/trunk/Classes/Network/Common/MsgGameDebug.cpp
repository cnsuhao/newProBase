////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameDebug.cpp
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/10/13
////////////////////////////////////////////////////////////////////////

#include "MsgGameDebug.h"
#include "MyCocosCommon\LayerHint.h"


//////////////////////////////////////////////////////////////////////////
CMsgGameDebug::CMsgGameDebug()
{
	Init();
	m_pInfo = (MSG_Info*)m_bufMsg;
	m_head.usType = _MSG_GAME_DEBUG;
	m_head.usSize = sizeof(MSG_Info);
}

//////////////////////////////////////////////////////////////////////////
CMsgGameDebug::~CMsgGameDebug()
{

}

//////////////////////////////////////////////////////////////////////////
void CMsgGameDebug::Process()
{
	::AddHint(m_pInfo->szString);
}

//////////////////////////////////////////////////////////////////////////
bool CMsgGameDebug::CreateString(const char* pszString)
{
	CHECKF(pszString);

	this->Init();
	m_head.usType = _MSG_GAME_DEBUG;
	m_head.usSize = sizeof(MSG_Info);

	::SafeCopy(m_pInfo->szString, pszString, sizeof(m_pInfo->szString));

	return true;
}
