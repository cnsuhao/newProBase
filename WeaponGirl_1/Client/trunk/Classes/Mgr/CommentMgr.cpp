////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: CommentMgr.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/11/03
////////////////////////////////////////////////////////////////////////
#include "CommentMgr.h"
#include "InstanceMgr.h"

CommentMgr* CommentMgr::m_pInstance = nullptr;
//////////////////////////////////////////////////////////////////////////
CommentMgr* CommentMgr::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new CommentMgr();
	}
	return m_pInstance;
}

//////////////////////////////////////////////////////////////////////////
void CommentMgr::destroyInstance()
{

}

//////////////////////////////////////////////////////////////////////////
CommentMgr::CommentMgr()
	: m_idCommentType(ID_NONE)
{

}

//////////////////////////////////////////////////////////////////////////
void CommentMgr::resetData(OBJID idCommentType)
{
	CHECK(idCommentType);
	m_deqComment.clear();
	m_idCommentType = idCommentType;
}

//////////////////////////////////////////////////////////////////////////
void CommentMgr::addData(const COMMENT_INFO& info, bool bHead /*= false*/)
{
	if (bHead)
	{
		m_deqComment.push_front(info);
	}
	else
	{
		m_deqComment.push_back(info);
	}

	// 新插入的信息同步
	if (bHead)
	{
		// 副本关卡攻略
		if (m_idCommentType >= 10000 && m_idCommentType < 100000)
		{
			InstanceMgr::getInstance()->updateStrategyNew(m_idCommentType, info);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
const COMMENT_INFO& CommentMgr::queryInfo(int nIndex) const
{
	static COMMENT_INFO empty = { 0 };
	IF_NOT(nIndex >= 0 && nIndex < m_deqComment.size())
	{
		return empty;
	}

	return m_deqComment[nIndex];
}

//////////////////////////////////////////////////////////////////////////
void CommentMgr::changeGood(DB_KEY idComment, bool bAdd)
{
	CHECK(idComment);
	for (auto& info : m_deqComment)
	{
		if (info.idComment == idComment)
		{
			if (bAdd)
			{
				info.nGoodCount++;
				info.nSelfGoodFlag = 1;
			}
			else
			{
				info.nGoodCount--;
				info.nSelfGoodFlag = 0;
			}

			// 新插入的信息同步
			// 副本关卡攻略
			if (m_idCommentType >= 10000 && m_idCommentType < 100000)
			{
				InstanceMgr::getInstance()->updateStrategyGood(m_idCommentType, info);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
void CommentMgr::endData()
{
	CHECK(m_idCommentType);

	// 副本关卡攻略
	if (m_idCommentType >= 10000 && m_idCommentType < 100000)
	{
		InstanceMgr::getInstance()->updateStrategy(m_idCommentType);
	}
}

