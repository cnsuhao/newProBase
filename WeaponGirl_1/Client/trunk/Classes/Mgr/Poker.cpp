////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: Poker.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/10/30
////////////////////////////////////////////////////////////////////////
#include "Poker.h"
#include "ConstTable\ConstTableMgr.h"

//////////////////////////////////////////////////////////////////////////
Poker::~Poker()
{

}

//////////////////////////////////////////////////////////////////////////
Poker* Poker::create(const MSG_POKER_INFO& info)
{
	Poker* pRet = new(std::nothrow) Poker();
	if (pRet && pRet->init(info))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

//////////////////////////////////////////////////////////////////////////
bool Poker::init(const MSG_POKER_INFO& info)
{
	this->SetMemoryDataAttr(POKER_ATTR_id, info.idPoker);
	this->SetMemoryDataAttr(POKER_ATTR_type, info.type);
	this->SetMemoryDataAttr(POKER_ATTR_lev, info.lev);
	this->SetMemoryDataAttr(POKER_ATTR_star, info.star);
	this->SetMemoryDataAttr(POKER_ATTR_strengthen, info.strengthen);
	this->SetMemoryDataAttr(POKER_ATTR_breakthrough, info.breakthrough);
	this->SetMemoryDataAttr(POKER_ATTR_randomAttrType, info.randomAttr / 10);
	this->SetMemoryDataAttr(POKER_ATTR_randomAttrData, info.randomAttr % 10);
	this->SetMemoryDataAttr(POKER_ATTR_pos1, info.pos1);
	this->SetMemoryDataAttr(POKER_ATTR_pos2, info.pos2);
	this->SetMemoryDataAttr(POKER_ATTR_pos3, info.pos3);
	this->SetMemoryDataAttr(POKER_ATTR_pos4, info.pos4);
	this->SetMemoryDataAttr(POKER_ATTR_weapon, info.weapon);
	this->SetMemoryDataAttr(POKER_ATTR_exScore, info.exScore);
	this->SetMemoryDataAttr(POKER_ATTR_totalScore, info.totalScore);
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool Poker::updateInfo(const MSG_POKER_INFO& info)
{
	CHECKF(this->GetMemoryDataAttr(POKER_ATTR_id) == info.idPoker);
	this->SetMemoryDataAttr(POKER_ATTR_type, info.type);
	this->SetMemoryDataAttr(POKER_ATTR_lev, info.lev);
	this->SetMemoryDataAttr(POKER_ATTR_star, info.star);
	this->SetMemoryDataAttr(POKER_ATTR_strengthen, info.strengthen);
	this->SetMemoryDataAttr(POKER_ATTR_breakthrough, info.breakthrough);
	this->SetMemoryDataAttr(POKER_ATTR_randomAttrType, info.randomAttr / 10);
	this->SetMemoryDataAttr(POKER_ATTR_randomAttrData, info.randomAttr % 10);
	this->SetMemoryDataAttr(POKER_ATTR_pos1, info.pos1);
	this->SetMemoryDataAttr(POKER_ATTR_pos2, info.pos2);
	this->SetMemoryDataAttr(POKER_ATTR_pos3, info.pos3);
	this->SetMemoryDataAttr(POKER_ATTR_pos4, info.pos4);
	this->SetMemoryDataAttr(POKER_ATTR_weapon, info.weapon);
	this->SetMemoryDataAttr(POKER_ATTR_exScore, info.exScore);
	this->SetMemoryDataAttr(POKER_ATTR_totalScore, info.totalScore);
	return true;
}

//////////////////////////////////////////////////////////////////////////
int64_t Poker::getTypeData(POKER_TYPE_DATA eType) const
{
	auto type = this->GetMemoryDataAttr(POKER_ATTR_type);
	CHECKF(ConstTableMgr::getInstance()->IsExistSingle(CONST_TABLE_TYPE_poker_type, type));
	return ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_poker_type, type, eType);
}

//////////////////////////////////////////////////////////////////////////
std::string Poker::getTypeStr(POKER_TYPE_DATA eType) const
{
	auto type = this->GetMemoryDataAttr(POKER_ATTR_type);
	IF_NOT(ConstTableMgr::getInstance()->IsExistSingle(CONST_TABLE_TYPE_poker_type, type))
	{
		return "";
	}
	return ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_poker_type, type, eType);
}

//////////////////////////////////////////////////////////////////////////
int64_t Poker::getStrengthenTypeData(POKER_STRENGTHEN_TYPE_DATA eType) const
{
	auto strengthen = this->GetMemoryDataAttr(POKER_ATTR_strengthen);
	CHECKF(ConstTableMgr::getInstance()->IsExistSingle(CONST_TABLE_TYPE_poker_strengthen_type, strengthen));
	return ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_poker_strengthen_type, strengthen, eType);
}

//////////////////////////////////////////////////////////////////////////
int64_t Poker::getScore() const
{
	auto stdScore = ::GetStdScore(this->GetMemoryDataAttr(POKER_ATTR_lev), this->GetMemoryDataAttr(POKER_ATTR_star));
	auto baseScore = this->getTypeData(POKER_TYPE_DATA_base_score);
	auto grow = this->getTypeData(POKER_TYPE_DATA_grow);	// 成长率
	auto strgenthen = this->getStrengthenTypeData(POKER_STRENGTHEN_TYPE_DATA_effect);	// 强化效果
	auto breakthrough = this->GetMemoryDataAttr(POKER_ATTR_breakthrough);	// 突破效果
	auto exScore = this->GetMemoryDataAttr(POKER_ATTR_exScore);	// 额外成长战力
	return ::GetFinalScore(stdScore, baseScore, grow, strgenthen, breakthrough) + exScore;
}
