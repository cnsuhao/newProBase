////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgCommentList.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/11/03
////////////////////////////////////////////////////////////////////////
#include "MsgCommentList.h"
#include "Mgr\CommentMgr.h"

//////////////////////////////////////////////////////////////////////////
CMsgCommentList::CMsgCommentList()
{
	Init();
	m_pInfo = (MSG_Info*)m_bufMsg;
	m_head.usType = _MSG_COMMENT_LIST;
	m_head.usSize = sizeof(MSG_Info);
}

//////////////////////////////////////////////////////////////////////////
CMsgCommentList::~CMsgCommentList()
{

}

//////////////////////////////////////////////////////////////////////////
void CMsgCommentList::Process()
{
	switch (m_pInfo->sAction)
	{
	case MSG_COMMENT_LIST_ACTION_alllist:
		{
			if (m_pInfo->nStartFlag != 0)
			{
				CommentMgr::getInstance()->resetData(m_pInfo->nCommentType);
			}

			for (int i = 0; i < m_pInfo->sCount; i++)
			{
				CommentMgr::getInstance()->addData(m_pInfo->info[i]);
			}

			if (m_pInfo->nEndFlag != 0)
			{
				// 通知数据读取完成
				CommentMgr::getInstance()->endData();
			}
		}
		break;
	case MSG_COMMENT_LIST_ACTION_new:
		{
			CommentMgr::getInstance()->addData(m_pInfo->info[0], true);
		}
		break;
	default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
bool CMsgCommentList::CreateNewComment(OBJID idCommentType, const char* pszText)
{
	CHECKF(idCommentType && pszText);

	this->Init();
	m_head.usType = _MSG_COMMENT_LIST;
	m_head.usSize = sizeof(MSG_Info);

	m_pInfo->sAction = MSG_COMMENT_LIST_ACTION_new;
	m_pInfo->sCount = 1;
	m_pInfo->nCommentType = idCommentType;
	m_pInfo->nStartFlag = 0;
	m_pInfo->nEndFlag = 0;

	SafeCopy(m_pInfo->info[0].szText, pszText, sizeof(m_pInfo->info[0].szText));

	return true;
}
