////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: PokerMgr.cpp
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/10/30
////////////////////////////////////////////////////////////////////////
#include "PokerMgr.h"
#include "Poker.h"
#include "MoneyMgr.h"

PokerMgr* PokerMgr::m_pInstance = nullptr;

//////////////////////////////////////////////////////////////////////////
PokerMgr* PokerMgr::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new PokerMgr();
	}
	return m_pInstance;
}

//////////////////////////////////////////////////////////////////////////
void PokerMgr::destroyInstance()
{

}

//////////////////////////////////////////////////////////////////////////
PokerMgr::PokerMgr()
{
	m_eMyPokerSort = POKER_SORT_TYPE_color;
}

//////////////////////////////////////////////////////////////////////////
bool PokerMgr::updatePokerData(const MSG_POKER_INFO& rInfo)
{
	CHECKF(rInfo.idPoker);
	auto iter = m_mapPoker.find(rInfo.idPoker);
	if (iter != m_mapPoker.end())
	{
		return iter->second->updateInfo(rInfo);
	}
	else
	{
		auto pPoker = Poker::create(rInfo);
		CHECKF(pPoker);
		m_mapPoker.insert(rInfo.idPoker, pPoker);
		return true;
	}
}

//////////////////////////////////////////////////////////////////////////	
bool PokerMgr::updateBookData(OBJID idPokerType, int nCount)
{
	CHECKF(idPokerType);
	auto iter = m_mapBook.find(idPokerType);
	if (iter != m_mapBook.end())
	{
		iter->second = nCount;
	}
	else
	{
		m_mapBook[idPokerType] = nCount;
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool PokerMgr::deletePoker(DB_KEY idPoker)
{
	CHECKF(idPoker);
	auto iter = m_mapPoker.find(idPoker);
	if (iter != m_mapPoker.end())
	{
		m_mapPoker.erase(idPoker);
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
void PokerMgr::updateHolyData(uint32_t unHolyRefreshTime, uint32_t unHolyCanBuyTime, OBJID* idHolyPokerType, uint32_t* unHolyPokerPrice)
{
	m_unHolyRefreshTime = unHolyRefreshTime;
	m_unHolyCanBuyTime = unHolyCanBuyTime;

	for (int i = 0; i < POKER_HOLY_COUNT; i++)
	{
		m_idHolyPokerType[i] = idHolyPokerType[i];
		m_unHolyPokerPrice[i] = unHolyPokerPrice[i];
	}
}

//////////////////////////////////////////////////////////////////////////
int PokerMgr::getPokerCount() const
{
	return m_mapPoker.size();
}

//////////////////////////////////////////////////////////////////////////
int PokerMgr::getPokerCountMax() const
{
	return BASE_POKER_MAX_COUNT + MoneyMgr::getInstance()->getMoney(USER_MONEY_TYPE_PokerMaxBuy);
}

//////////////////////////////////////////////////////////////////////////
bool PokerMgr::queryPokerVector(OUT VEC_DB_KEY& vecPokerID, POKER_SORT_TYPE eSortType /*= POKER_SORT_TYPE_none*/) const
{
	std::vector<Poker*> vecPoker;
	for (auto iter : m_mapPoker)
	{
		auto pPoker = iter.second;
		CHECKC(pPoker);
		vecPoker.push_back(pPoker);
	}

	switch (eSortType)
	{
	case POKER_SORT_TYPE_none:
		break;
	case POKER_SORT_TYPE_color:
		{
			std::sort(vecPoker.begin(), vecPoker.end(), [this](const Poker* l, const Poker* r)->bool{
				CHECKF(l && r);
				int nBossL = l->GetMemoryDataAttr(POKER_ATTR_type) == BOSS_POKER_TYPE ? 1 : 0;
				int nBossR = r->GetMemoryDataAttr(POKER_ATTR_type) == BOSS_POKER_TYPE ? 1 : 0;
				if (nBossL != nBossR)
				{
					return nBossL > nBossR;
				}
				else if	(l->getTypeData(POKER_TYPE_DATA_color) != r->getTypeData(POKER_TYPE_DATA_color))
				{
					return l->getTypeData(POKER_TYPE_DATA_color) > r->getTypeData(POKER_TYPE_DATA_color);
				}
				else
				{
					return l->GetMemoryDataAttr(POKER_ATTR_id) < r->GetMemoryDataAttr(POKER_ATTR_id);
				}
			});
		}
		break;
	case POKER_SORT_TYPE_level:
		{
			std::sort(vecPoker.begin(), vecPoker.end(), [this](const Poker* l, const Poker* r)->bool{
				CHECKF(l && r);
				int nBossL = l->GetMemoryDataAttr(POKER_ATTR_type) == BOSS_POKER_TYPE ? 1 : 0;
				int nBossR = r->GetMemoryDataAttr(POKER_ATTR_type) == BOSS_POKER_TYPE ? 1 : 0;
				if (nBossL != nBossR)
				{
					return nBossL > nBossR;
				}
				else if (l->GetMemoryDataAttr(POKER_ATTR_lev) != r->GetMemoryDataAttr(POKER_ATTR_lev))
				{
					return l->GetMemoryDataAttr(POKER_ATTR_lev) > r->GetMemoryDataAttr(POKER_ATTR_lev);
				}
				else
				{
					return l->GetMemoryDataAttr(POKER_ATTR_id) < r->GetMemoryDataAttr(POKER_ATTR_id);
				}
			});
		}
		break;
	case POKER_SORT_TYPE_upstar:
		{
			std::sort(vecPoker.begin(), vecPoker.end(), [this](const Poker* l, const Poker* r)->bool{
				CHECKF(l && r);
				int nBossL = l->GetMemoryDataAttr(POKER_ATTR_type) == BOSS_POKER_TYPE ? 1 : 0;
				int nBossR = r->GetMemoryDataAttr(POKER_ATTR_type) == BOSS_POKER_TYPE ? 1 : 0;
				if (nBossL != nBossR)
				{
					return nBossL > nBossR;
				}
				else if (l->GetMemoryDataAttr(POKER_ATTR_star) != r->GetMemoryDataAttr(POKER_ATTR_star))
				{
					return l->GetMemoryDataAttr(POKER_ATTR_star) > r->GetMemoryDataAttr(POKER_ATTR_star);
				}
				else
				{
					return l->GetMemoryDataAttr(POKER_ATTR_id) < r->GetMemoryDataAttr(POKER_ATTR_id);
				}
			});
		}
		break;
	case POKER_SORT_TYPE_score:
		{
			std::sort(vecPoker.begin(), vecPoker.end(), [this](const Poker* l, const Poker* r)->bool{
				CHECKF(l && r);
				int nBossL = l->GetMemoryDataAttr(POKER_ATTR_type) == BOSS_POKER_TYPE ? 1 : 0;
				int nBossR = r->GetMemoryDataAttr(POKER_ATTR_type) == BOSS_POKER_TYPE ? 1 : 0;
				if (nBossL != nBossR)
				{
					return nBossL > nBossR;
				}
				else if (l->getScore() != r->getScore())
				{
					return l->getScore() > r->getScore();
				}
				else
				{
					return l->GetMemoryDataAttr(POKER_ATTR_id) < r->GetMemoryDataAttr(POKER_ATTR_id);
				}
			});
		}
		break;
	default:
		break;
	}

	vecPokerID.clear();
	for (auto pPoker : vecPoker)
	{
		vecPokerID.push_back(pPoker->GetMemoryDataAttr(POKER_ATTR_id));
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
Poker* PokerMgr::getPoker(DB_KEY idPoker) const
{
	auto iter = m_mapPoker.find(idPoker);
	if (iter == m_mapPoker.end())
	{
		return nullptr;
	}
	return iter->second;
}

//////////////////////////////////////////////////////////////////////////
int PokerMgr::getBookCount(OBJID idPokerType) const
{
	CHECKF(idPokerType);
	auto iter = m_mapBook.find(idPokerType);
	if (iter == m_mapBook.end())
	{
		return 0;
	}
	return iter->second;
}

//////////////////////////////////////////////////////////////////////////
bool PokerMgr::isHaveBook(OBJID idPokerType) const
{
	CHECKF(idPokerType);
	return m_mapBook.find(idPokerType) == m_mapBook.end();
}
