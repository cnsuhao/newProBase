////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2015, WuHan GoodGame, All Rights Reserved
// Moudle: LogicDataMgr.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015-1-21
////////////////////////////////////////////////////////////////////////
#include "LogicDataMgr.h"
#include "ConstTable\ConstTableMgr.h"

LogicDataMgr* LogicDataMgr::m_pInstance = nullptr;

//////////////////////////////////////////////////////////////////////////
LogicDataMgr::LogicDataMgr()
{
	m_eConnectStatus = CONNECT_STATUS_none;
}


//////////////////////////////////////////////////////////////////////////
LogicDataMgr* LogicDataMgr::getInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new LogicDataMgr();
	}
	return m_pInstance;
}

//////////////////////////////////////////////////////////////////////////
void LogicDataMgr::destroyInstance()
{
	CC_SAFE_DELETE(m_pInstance);
}


////////////////////////////////////////////////////////////////////////
// Description: 当前登录服务器ip
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: std::string
////////////////////////////////////////////////////////////////////////
std::string LogicDataMgr::getLoginServerIp() const
{
	std::string result = "";
	auto idLoginServer = LogicDataMgr::getInstance()->GetMemoryDataAttr(LOGIC_DATA_LoginServerId);
	if (ConstTableMgr::getInstance()->IsExistSingle(CONST_TABLE_TYPE_server_list, idLoginServer))
	{
		result = ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_server_list, idLoginServer, SERVER_LIST_DATA_ip);
	}
	return result;
}

////////////////////////////////////////////////////////////////////////
// Description: 当前登录服务器端口
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: int
////////////////////////////////////////////////////////////////////////
int LogicDataMgr::getLoginServerPort() const
{
	int result = 0;
	auto idLoginServer = LogicDataMgr::getInstance()->GetMemoryDataAttr(LOGIC_DATA_LoginServerId);
	if (ConstTableMgr::getInstance()->IsExistSingle(CONST_TABLE_TYPE_server_list, idLoginServer))
	{
		result = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_server_list, idLoginServer, SERVER_LIST_DATA_port);
	}
	return result;
}

//////////////////////////////////////////////////////////////////////////
void LogicDataMgr::addLoginSnap( const USER_LOGIN_SNAP& rSnap )
{
	m_vecLoginSnap.push_back(rSnap);
}

//////////////////////////////////////////////////////////////////////////
bool LogicDataMgr::queryLoginSnap(int nIndex, OUT USER_LOGIN_SNAP& rSnap) const
{
	IF_OK (m_vecLoginSnap.size() > nIndex && nIndex >= 0)
	{
		rSnap = m_vecLoginSnap[nIndex];
		return true;
	}
	return false;
}

bool LogicDataMgr::isHaveMessageBox(const std::string& message)
{
	auto iter = m_setMessageBox.find(message);
	return (iter != m_setMessageBox.end());
}

void LogicDataMgr::addMessageBox(const std::string& message)
{
	m_setMessageBox.insert(message);
}

void LogicDataMgr::delMessageBox(const std::string& message)
{
	auto iter = m_setMessageBox.find(message);
	if (iter != m_setMessageBox.end())
	{
		m_setMessageBox.erase(iter);
	}
}