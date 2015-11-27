////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: GiftMgr.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/11/05
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_GiftMgr_H_
#define _JYP_GiftMgr_H_

#include "Global/Global.h"

class GiftMgr : public Ref
{
public:
	static GiftMgr*	getInstance();
	static void		destroyInstance();
private:
	GiftMgr();
	static GiftMgr*	m_pInstance;

public:
	void clear() { m_deqGift.clear(); };
	void addInfo(const GIFT_INFO& info);
	void notifyGetGift(DB_KEY idGift);
	int  getSize() const { return m_deqGift.size(); }
	const GIFT_INFO& getGiftInfo(int nIndex) const;

protected:
	std::deque<GIFT_INFO>		m_deqGift;
};

#endif // end of _JYP_GiftMgr_H_