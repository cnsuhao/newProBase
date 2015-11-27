////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MoneyMgr.h
// Author: ≈ÌŒƒ∆Ê(Peng Wenqi)
// Created: 2015/10/16
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_MoneyMgr_H_
#define _JYP_MoneyMgr_H_

#include "Global/Global.h"

struct MONEY_INFO
{
	int64_t		data;
	uint32_t	timestart;
	uint32_t	addspeed;
};

class MoneyMgr : public Ref
{
public:
	static MoneyMgr*	getInstance();
	static void			destroyInstance();
private:
	MoneyMgr();
	static MoneyMgr*	m_pInstance;

public:
	static std::string getBigForamt(int64_t data);
	static std::string getDivisionForamt(int64_t data);

public:
	void	clearMoneyData();
	void	updateMoneyData(USER_MONEY_TYPE moneyType, int64_t moneyData, uint32_t timestart, uint32_t addspeed);
	int64_t	getMoney(USER_MONEY_TYPE moneyType) const;
	std::string getMoneyBigFormat(USER_MONEY_TYPE moneyType) const;
	std::string getMoneyDivisionForamt(USER_MONEY_TYPE moneyType) const;
	std::string getMoneySpriteFrameName(USER_MONEY_TYPE moneyType) const;
	

protected:
	std::map<int, MONEY_INFO> m_mapData;	// first∂‘”¶ USER_MONEY_TYPE

	CC_SYNTHESIZE(int, m_VasFirstMask, VasFirstMask);
	CC_SYNTHESIZE(int, m_MonthCardID, MonthCardID);
	CC_SYNTHESIZE(bool, m_MonthCardTodayCanGet, MonthCardTodayCanGet);
	CC_SYNTHESIZE(int, m_MonthCardLeftCount, MonthCardLeftCount);
};

#endif // end of _JYP_MoneyMgr_H_