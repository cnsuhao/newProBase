////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: GreenTipsMgr.cpp
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/11/20
////////////////////////////////////////////////////////////////////////
#include "GreenTipsMgr.h"

GreenTipsMgr* GreenTipsMgr::m_pInstance = nullptr;

//////////////////////////////////////////////////////////////////////////
GreenTipsMgr* GreenTipsMgr::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new GreenTipsMgr();
	}
	return m_pInstance;
}

//////////////////////////////////////////////////////////////////////////
void GreenTipsMgr::destroyInstance()
{

}

//////////////////////////////////////////////////////////////////////////
GreenTipsMgr::GreenTipsMgr()
{

}

//////////////////////////////////////////////////////////////////////////
bool GreenTipsMgr::isHaveTips(GREEN_TIPS_TYPE eType) const
{
	switch (eType)
	{
	case GREEN_TIPS_TYPE_MainViewHome:
		break;
	case GREEN_TIPS_TYPE_MainViewInstance:
		break;
	case GREEN_TIPS_TYPE_MainViewLottery:
		break;
	case GREEN_TIPS_TYPE_MainViewChallenge:
		break;
	case GREEN_TIPS_TYPE_MainViewSmelt:
		break;
	case GREEN_TIPS_TYPE_MainViewPoker:
		break;
	case GREEN_TIPS_TYPE_MainViewActivity:
		break;
	case GREEN_TIPS_TYPE_BottomButtonMail:
		break;
	case GREEN_TIPS_TYPE_BottomButtonAchievement:
		break;
	case GREEN_TIPS_TYPE_BottomButtonFriend:
		break;
	case GREEN_TIPS_TYPE_BottomButtonShop:
		break;
	case GREEN_TIPS_TYPE_BottomButtonNotify:
		break;
	case GREEN_TIPS_TYPE_BottomButtonSetup:
		break;
	default:
		return false;
		break;
	}

	return false;
}