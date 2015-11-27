////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LoginMgr.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/05/26
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_MGR_LOGIN_MGR_H_
#define _JYP_MGR_LOGIN_MGR_H_

#include "Global/Global.h"
#include "Network/Login/MsgGameLoginQuery.h"

class LoginMgr : public Ref
{
public:
	static LoginMgr*	getInstance();
	static void			destroyInstance();
private:
	static LoginMgr*	m_pInstance;
	LoginMgr();

protected:
	CC_SYNTHESIZE_READONLY(bool, m_bReConnect, ReConnect);

protected:
	void	setLoginPercent(float fPercent);
	void	sendReq(MSG_LOGIN_QUERY_ACTION eAction, MSG_LOGIN_QUERY_RESULT eResult = MSG_LOGIN_QUERY_RESULT_SUCC, int nParam1 = 0, int nParam2 = 0);
	void	loginFinish();

public:
	void		onTimerHeartbeat();
	void		updateHeartbeat(uint32_t unServerUtcSecond);
	uint32_t	getHeartbeat() const;

public:
	void	processUserSnap();
	void	processUserInfo();

	void	processUserServerGroup();
	void	processUserMoney();
	void	processUserMaskInfo();
	void	processUserPackage();
	void	processUserFriend();
	void	processUserTmpData();
	void	processTask();
	void	processUserMail();
	void	processUserSign();
	void	processUserSelfSyndicate();
};

#endif // end of _JYP_MGR_LOGIN_MGR_H_