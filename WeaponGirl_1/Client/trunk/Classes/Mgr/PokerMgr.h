////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: PokerMgr.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/10/30
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_PokerMgr_H_
#define _JYP_PokerMgr_H_

#include "Global/Global.h"

class Poker;
class PokerMgr : public Ref
{
public:
	static PokerMgr*	getInstance();
	static void			destroyInstance();
private:
	PokerMgr();
	static PokerMgr*	m_pInstance;

public:
	bool updatePokerData(const MSG_POKER_INFO& rInfo);	// 更新卡牌数据
	bool updateBookData(OBJID idPokerType, int nCount);	// 更新图鉴数据
	bool deletePoker(DB_KEY idPoker);					// 卡牌数据删除
	void updateHolyData(uint32_t unHolyRefreshTime, uint32_t unHolyCanBuyTime, OBJID* idHolyPokerType, uint32_t* unHolyPokerPrice);

public:
	int			getPokerCount() const;
	int			getPokerCountMax() const;
	bool		queryPokerVector(OUT VEC_DB_KEY& vecPokerID, POKER_SORT_TYPE eSortType = POKER_SORT_TYPE_none) const;
	Poker*		getPoker(DB_KEY idPoker) const;
public:
	int getBookCount(OBJID idPokerType) const;	// 获得卡牌灵魂数量
	bool isHaveBook(OBJID idPokerType) const;	// 是否拥有卡牌图鉴

protected:
	CC_SYNTHESIZE(POKER_SORT_TYPE, m_eMyPokerSort, MyPokerSort);

protected:
	cocos2d::Map<DB_KEY, Poker*> m_mapPoker;	// first对应 USER_MONEY_TYPE
	std::map<OBJID, int>		 m_mapBook;	// first为卡牌类型 second为灵魂数量

	uint32_t	m_unHolyRefreshTime;
	uint32_t	m_unHolyCanBuyTime;
	OBJID		m_idHolyPokerType[POKER_HOLY_COUNT];
	uint32_t	m_unHolyPokerPrice[POKER_HOLY_COUNT];
};

#endif // end of _JYP_PokerMgr_H_