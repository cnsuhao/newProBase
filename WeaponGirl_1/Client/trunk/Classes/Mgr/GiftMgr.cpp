////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: GiftMgr.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/11/05
////////////////////////////////////////////////////////////////////////
#include "GiftMgr.h"

GiftMgr* GiftMgr::m_pInstance = nullptr;
//////////////////////////////////////////////////////////////////////////
GiftMgr* GiftMgr::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new GiftMgr();
	}
	return m_pInstance;
}

//////////////////////////////////////////////////////////////////////////
void GiftMgr::destroyInstance()
{

}

//////////////////////////////////////////////////////////////////////////
GiftMgr::GiftMgr()
{

}

//////////////////////////////////////////////////////////////////////////
void GiftMgr::addInfo(const GIFT_INFO& info)
{
	m_deqGift.push_back(info);
}

//////////////////////////////////////////////////////////////////////////
void GiftMgr::notifyGetGift(DB_KEY idGift)
{
	GIFT_INFO info = { 0 };
	for (auto iter = m_deqGift.begin(); iter != m_deqGift.end(); iter++)
	{
		if (iter->idGift == idGift)
		{
			memcpy(&info, &*iter, sizeof(GIFT_INFO));
			m_deqGift.erase(iter);
			break;
		}
	}

	CHECK(info.idGift);
	info.nGetFlag = 1;
	m_deqGift.push_back(info);	// 领取的放到队尾
}

//////////////////////////////////////////////////////////////////////////
const GIFT_INFO& GiftMgr::getGiftInfo(int nIndex) const
{
	static GIFT_INFO empty = { 0 };
	if (nIndex >= 0 && nIndex < m_deqGift.size())
	{
		return m_deqGift[nIndex];
	}
	return empty;
}

