////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: BbsMgr.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/11/04
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_BbsMgr_H_
#define _JYP_BbsMgr_H_

#include "Global/Global.h"

class BbsMgr : public Ref
{
public:
	static BbsMgr*	getInstance();
	static void		destroyInstance();
private:
	BbsMgr();
	static BbsMgr*	m_pInstance;

public:
	void clearBBS();
	void addBBS(const BBS_INFO& info, bool bHead = false);
	int  getBBSSize() const { return m_deqBBS.size(); }
	const BBS_INFO& getBbsInfo(int nIndex) const;

	void clearReply(DB_KEY idBBS);
	void addReply(const BBS_REPLY_INFO& info, bool bHead = false);
	int  getReplySize() const { return m_deqReply.size(); }
	const BBS_REPLY_INFO& getReplyInfo(int nIndex) const;

protected:
	std::deque<BBS_INFO>		m_deqBBS;
	DB_KEY						m_idBBS;
	std::deque<BBS_REPLY_INFO>	m_deqReply;
};

#endif // end of _JYP_BbsMgr_H_