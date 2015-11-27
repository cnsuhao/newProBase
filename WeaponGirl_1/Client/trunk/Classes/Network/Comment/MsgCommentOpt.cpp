////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgCommentOpt.cpp
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/11/03
////////////////////////////////////////////////////////////////////////
#include "MsgCommentOpt.h"
#include "Mgr\CommentMgr.h"

//////////////////////////////////////////////////////////////////////////
CMsgCommentOpt::CMsgCommentOpt()
{
	Init();
	m_pInfo = (MSG_Info*)m_bufMsg;
	m_head.usType = _MSG_COMMENT_OPT;
	m_head.usSize = sizeof(MSG_Info);
}

//////////////////////////////////////////////////////////////////////////
CMsgCommentOpt::~CMsgCommentOpt()
{

}


//////////////////////////////////////////////////////////////////////////
void CMsgCommentOpt::Process()
{
	switch (m_pInfo->nAction)
	{
	case MSG_COMMENT_OPT_ACTION_add_good:
		{
			CommentMgr::getInstance()->changeGood(m_pInfo->idComment, true);
		}
		break;
	case MSG_COMMENT_OPT_ACTION_dec_good:
		{
			CommentMgr::getInstance()->changeGood(m_pInfo->idComment, false);
		}
		break;
	default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
bool CMsgCommentOpt::CreateCommentOpt(MSG_COMMENT_OPT_ACTION eAciton, OBJID idCommentType, int64_t idComment)
{
	this->Init();
	m_head.usType = _MSG_COMMENT_OPT;
	m_head.usSize = sizeof(MSG_Info);

	m_pInfo->nAction = eAciton;
	m_pInfo->idCommentType = idCommentType;
	m_pInfo->idComment = idComment;

	return true;
}
