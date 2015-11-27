////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2012, WuHan GoodGame, All Rights Reserved
// Moudle: MsgSmallAction.cpp
// Author: ������(Lee MengSong)
// Created: 2012-10-23
////////////////////////////////////////////////////////////////////////
#include "./MsgGameSmallAction.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMsgGameSmallAction::CMsgGameSmallAction()
{
	Init();
	m_pInfo = (MSG_Info *)m_bufMsg;
	m_head.usType = _MSG_GAME_SMALLACTION;
	m_head.usSize = sizeof(MSG_Info);
}

//////////////////////////////////////////////////////////////////////////
CMsgGameSmallAction::~CMsgGameSmallAction()
{
}

////////////////////////////////////////////////////////////////////////
// Description:  ����SmallAction
// Arguments:
// Author: ������(Lee MengSong)
// Return Value: None
////////////////////////////////////////////////////////////////////////
bool CMsgGameSmallAction::createSmallAction(MSG_SMALL_ACTION eAction, MSG_SMALL_RESULT eResult)
{
	this->Init();
	m_head.usType = _MSG_GAME_SMALLACTION;
	m_head.usSize = sizeof(MSG_Info) - sizeof(MSG_NUM_4BIT);

	m_pInfo->sAction = (MSG_NUM_2BIT)eAction;
	m_pInfo->sResult = (MSG_NUM_2BIT)eResult;
	m_pInfo->nParamNumber = 0;

	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  ���Ӳ���
// Arguments:
// Author: ������(Lee MengSong)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CMsgGameSmallAction::appendParam(int nAddParam)
{
	CHECKF(sizeof(MSG_Info) + sizeof(MSG_NUM_4BIT) * m_pInfo->nParamNumber < MAX_PACKETSIZE);
	m_pInfo->nParam[m_pInfo->nParamNumber] = nAddParam;
	m_head.usSize = sizeof(MSG_Info) + sizeof(MSG_NUM_4BIT) * m_pInfo->nParamNumber;
	++(m_pInfo->nParamNumber);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description:  ���Param��������
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: int
////////////////////////////////////////////////////////////////////////
int CMsgGameSmallAction::getParamVector(OUT VEC_INT& rVec)
{
	rVec.clear();
	CHECKF(m_pInfo->nParamNumber >= 0 && m_pInfo->nParamNumber < (MAX_PACKETSIZE - 8) / sizeof(int));
	for (int i = 0; i < m_pInfo->nParamNumber; ++i)
	{
		rVec.push_back(m_pInfo->nParam[i]);
	}
	return rVec.size();
}

////////////////////////////////////////////////////////////////////////
// Description:  ������Ϣ
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: None
////////////////////////////////////////////////////////////////////////
void CMsgGameSmallAction::Process()
{
// 	switch (m_pInfo->sAction)
// 	{
// 	default:
// 		break;
// 	}

}

