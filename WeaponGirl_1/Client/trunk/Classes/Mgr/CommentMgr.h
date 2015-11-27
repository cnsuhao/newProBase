////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: CommentMgr.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/11/03
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_CommentMgr_H_
#define _JYP_CommentMgr_H_

#include "Global/Global.h"

class CommentMgr : public Ref
{
public:
	static CommentMgr*	getInstance();
	static void			destroyInstance();
private:
	CommentMgr();
	static CommentMgr*	m_pInstance;

public:
	void resetData(OBJID idCommentType);
	void addData(const COMMENT_INFO& info, bool bHead = false);
	OBJID getCommentType() const { return m_idCommentType; }
	int  getSize() const { return m_deqComment.size(); }
	const COMMENT_INFO& queryInfo(int nIndex) const;
	void changeGood(DB_KEY idComment, bool bAdd);
	void endData();

protected:
	OBJID						m_idCommentType;
	std::deque<COMMENT_INFO>	m_deqComment;
};

#endif // end of _JYP_CommentMgr_H_