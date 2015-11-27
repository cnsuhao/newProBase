////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2015, WuHan GoodGame, All Rights Reserved
// Moudle: LogicDataMgr.h
// Author: ������(Peng Wenqi)
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

	// ��������, ��Ҫר�ýӿ�
public:
	CC_SYNTHESIZE(CONNECT_STATUS, m_eConnectStatus, ConnectStatus);

	// ��¼��������Ϣ
public:
	std::string getLoginServerIp() const;
	int			getLoginServerPort() const;


	// ��¼������Ϣ
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
