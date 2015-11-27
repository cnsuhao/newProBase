////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: Poker.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/10/30
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_Poker_H_
#define _JYP_Poker_H_

#include "Global/Global.h"
#include "ConstTable/ConstTableDefine.h"

class Poker : public Ref
{
protected:
	virtual ~Poker();
public:
	static Poker* create(const MSG_POKER_INFO& info);
	virtual bool init(const MSG_POKER_INFO& info);
	virtual bool updateInfo(const MSG_POKER_INFO& info);

	virtual int64_t getTypeData(POKER_TYPE_DATA eType) const;
	virtual std::string getTypeStr(POKER_TYPE_DATA eType) const;
	virtual int64_t getStrengthenTypeData(POKER_STRENGTHEN_TYPE_DATA eType) const;

	virtual int64_t getScore() const;

public:
	DEFINE_mda(POKER_ATTR);
};

#endif // end of _JYP_Poker_H_