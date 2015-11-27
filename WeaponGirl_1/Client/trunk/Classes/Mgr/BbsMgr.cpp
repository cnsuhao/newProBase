////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: BbsMgr.cpp
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/11/04
////////////////////////////////////////////////////////////////////////
#include "BbsMgr.h"

BbsMgr* BbsMgr::m_pInstance = nullptr;

//////////////////////////////////////////////////////////////////////////
BbsMgr* BbsMgr::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new BbsMgr();
	}
	return m_pInstance;
}

//////////////////////////////////////////////////////////////////////////
void BbsMgr::destroyInstance()
{

}

//////////////////////////////////////////////////////////////////////////
BbsMgr::BbsMgr()
	: m_idBBS(ID_NONE)
{

}

//////////////////////////////////////////////////////////////////////////
void BbsMgr::clearBBS()
{
	m_deqBBS.clear();
}

//////////////////////////////////////////////////////////////////////////
void BbsMgr::addBBS(const BBS_INFO& info, bool bHead /*= false*/)
{
	if (bHead)
	{
		m_deqBBS.push_front(info);
	}
	else
	{
		m_deqBBS.push_back(info);
	}
}

//////////////////////////////////////////////////////////////////////////
const BBS_INFO& BbsMgr::getBbsInfo(int nIndex) const
{
	static BBS_INFO empty = { 0 };
	if (nIndex >= 0 && nIndex < m_deqBBS.size())
	{
		return m_deqBBS[nIndex];
	}
	return empty;
}

//////////////////////////////////////////////////////////////////////////
void BbsMgr::clearReply(DB_KEY idBBS)
{
	m_deqReply.clear();
	m_idBBS = idBBS;
}

//////////////////////////////////////////////////////////////////////////
void BbsMgr::addReply(const BBS_REPLY_INFO& info, bool bHead /*= false*/)
{
	if (bHead)
	{
		m_deqReply.push_front(info);
	}
	else
	{
		m_deqReply.push_back(info);
	}
}

//////////////////////////////////////////////////////////////////////////
const BBS_REPLY_INFO& BbsMgr::getReplyInfo(int nIndex) const
{
	static BBS_REPLY_INFO empty = { 0 };
	if (nIndex >= 0 && nIndex < m_deqReply.size())
	{
		return m_deqReply[nIndex];
	}
	return empty;
}
