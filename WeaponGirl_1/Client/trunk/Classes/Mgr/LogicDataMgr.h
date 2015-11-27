////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2015, WuHan GoodGame, All Rights Reserved
// Moudle: LogicDataMgr.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2015-1-21
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_LOGIC_DATA_H_
#define _JYP_LOGIC_DATA_H_

#include "Global/Global.h"

class LogicDataMgr : public Ref
{
public:
	static LogicDataMgr*	getInstance();
	static void			destroyInstance();
private:
	LogicDataMgr();
	static LogicDataMgr*	m_pInstance;

public:
	DEFINE_mda(LOGIC_DATA);

public:
	DEFINE_msa(LOGIC_STRING);

	// 特殊属性, 需要专用接口
public:
	CC_SYNTHESIZE(CONNECT_STATUS, m_eConnectStatus, ConnectStatus);

	// 登录服务器信息
public:
	std::string getLoginServerIp() const;
	int			getLoginServerPort() const;


	// 登录快照信息
public:
	void clearLoginSnap(){m_vecLoginSnap.clear();}
	void addLoginSnap(const USER_LOGIN_SNAP& rSnap);
	int  getLoginSnapSize() const { return m_vecLoginSnap.size(); }
	bool queryLoginSnap(int nIndex, OUT USER_LOGIN_SNAP& rSnap) const;
private:
	std::vector<USER_LOGIN_SNAP>	m_vecLoginSnap;

	// MessageBox
public:
	bool isHaveMessageBox(const std::string& message);
	void addMessageBox(const std::string& message);
	void delMessageBox(const std::string& message);
protected:
	std::set<std::string> m_setMessageBox;

};

#endif // end of _JYP_LOGIC_DATA_H_
