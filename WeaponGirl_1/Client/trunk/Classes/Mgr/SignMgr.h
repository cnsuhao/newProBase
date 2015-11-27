////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: SignMgr.h
// Author: ³Â½¨¾ü(Chen Jianjun)
// Created: 2015-10-31
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_SIGN_MGR_H_
#define _JYP_SIGN_MGR_H_

#include "Global/Global.h"

class SignMgr : public Ref
{
public:
	static SignMgr*	getInstance();
	static void		destroyInstance();
private:
	SignMgr();
	static SignMgr*	m_pInstance;

public:
	bool getSignAwardInfo(std::vector<ST_SIGN_AWARD_INFO>& vecInfo);
	void addSignAwardInfo(ST_SIGN_AWARD_INFO& info);
	void signSuc();

protected:
	std::vector<ST_SIGN_AWARD_INFO> m_vecSignAwardInfo;
};

#endif // end of _JYP_SIGN_MGR_H_