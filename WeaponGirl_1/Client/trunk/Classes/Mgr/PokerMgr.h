////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: PokerMgr.h
// Author: ������(Peng Wenqi)
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
	bool updatePokerData(const MSG_POKER_INFO& rInfo);	// ���¿�������
	bool updateBookData(OBJID idPokerType, int nCount);	// ����ͼ������
	bool deletePoker(DB_KEY idPoker);					// ��������ɾ��
	void updateHolyData(uint32_t unHolyRefreshTime, uint32_t unHolyCanBuyTime, OBJID* idHolyPokerType, uint32_t* unHolyPokerPrice);

public:
	int			getPokerCount() const;
	int			getPokerCountMax() const;
	bool		queryPokerVector(OUT VEC_DB_KEY& vecPokerID, POKER_SORT_TYPE eSortType = POKER_SORT_TYPE_none) const;
	Poker*		getPoker(DB_KEY idPoker) const;
public:
	int getBookCount(OBJID idPokerType) const;	// ��ÿ����������
	bool isHaveBook(OBJID idPokerType) const;	// �Ƿ�ӵ�п���ͼ��

protected:
	CC_SYNTHESIZE(POKER_SORT_TYPE, m_eMyPokerSort, MyPokerSort);

protected:
	cocos2d::Map<DB_KEY, Poker*> m_mapPoker;	// first��Ӧ USER_MONEY_TYPE
	std::map<OBJID, int>		 m_mapBook;	// firstΪ�������� secondΪ�������

	uint32_t	m_unHolyRefreshTime;
	uint32_t	m_unHolyCanBuyTime;
	OBJID		m_idHolyPokerType[POKER_HOLY_COUNT];
	uint32_t	m_unHolyPokerPrice[POKER_HOLY_COUNT];
};

#endif // end of _JYP_PokerMgr_H_