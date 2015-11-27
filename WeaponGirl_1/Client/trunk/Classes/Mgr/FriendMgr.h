////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: FriendMgr.h
// Author: ³Â½¨¾ü(Chen Jianjun)
// Created: 2015-11-3
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_FRIEND_MGR_H_
#define _JYP_FRIEND_MGR_H_

#include "Global/Global.h"

class FriendMgr : public Ref
{
public:
	static FriendMgr*	getInstance();
	static void			destroyInstance();
private:
	FriendMgr();
	static FriendMgr*	m_pInstance;

public:
	const std::map<OBJID, ST_FRIEDN_INFO>* getFriendInfo();
	void updateFriendInfo(ST_FRIEDN_INFO& info);

	const std::map<OBJID, ST_FRIEDN_INFO>* getRequestInfo();
	void updateRequestInfo(ST_FRIEDN_INFO& info);

protected:
	std::map<OBJID, ST_FRIEDN_INFO> m_mapFriendInfo;
	std::map<OBJID, ST_FRIEDN_INFO> m_mapRequstInfo;
};

#endif // end of _JYP_FRIEND_MGR_H_