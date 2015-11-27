////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: ConstTableMgr.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015-1-8
////////////////////////////////////////////////////////////////////////
#include "ConstTableMgr.h"
#include "ConstTable.h"

#include "network/HttpClient.h"

ConstTableMgr* ConstTableMgr::_instance = nullptr;
//////////////////////////////////////////////////////////////////////////
ConstTableMgr* ConstTableMgr::getInstance()
{
	if (nullptr == _instance)
	{
		_instance = new ConstTableMgr();
	}
	
	return _instance;
}

//////////////////////////////////////////////////////////////////////////
void ConstTableMgr::destroyInstance()
{
	CC_SAFE_DELETE(_instance);
}

////////////////////////////////////////////////////////////////////////
// Description: 加载静态表管理器
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool ConstTableMgr::Init()
{ 
	for (int32_t i = CONST_TABLE_TYPE_BEGIN; i < CONST_TABLE_TYPE_END; i++)
	{
		const CONST_TABLE_TYPE eTableType = (CONST_TABLE_TYPE)i;
		auto iter = m_mapData.find(eTableType);
		CHECKF(iter == m_mapData.end());
		ConstTable* pTable = new ConstTable;
		CHECKF(pTable);
		IF_NOT(pTable->Init(eTableType))
		{
			LogSave("ConstTable[%d] Init Failed!", eTableType);
			CC_SAFE_DELETE(pTable);
			continue;
		}
		m_mapData[eTableType] = pTable;
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool ConstTableMgr::ReloadAll()
{
	for (int32_t i = CONST_TABLE_TYPE_BEGIN; i < CONST_TABLE_TYPE_END; i++)
	{
		this->Reload((CONST_TABLE_TYPE)i);
	}
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 是否存在(单键表)
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool ConstTableMgr::IsExistSingle( CONST_TABLE_TYPE eTableType, int32_t nIndex ) const
{
	auto iter = m_mapData.find(eTableType);
	if (iter == m_mapData.end())
	{
		LogSave("ConstTableMgr::IsExistSingle eTableType[%d] nIndex[%d]", eTableType, nIndex);
		return false;
	}
	return iter->second->IsExist(nIndex);
}

////////////////////////////////////////////////////////////////////////
// Description: 是否存在(双键表)
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool ConstTableMgr::IsExistDouble( CONST_TABLE_TYPE eTableType, int32_t nIndex1, int32_t nIndex2 ) const
{
	auto iter = m_mapData.find(eTableType);
	CHECKF(iter != m_mapData.end());
	return iter->second->IsExist(nIndex1, nIndex2);
}

////////////////////////////////////////////////////////////////////////
// Description: 获取数据(单键表)
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: int64_t
////////////////////////////////////////////////////////////////////////
int64_t ConstTableMgr::GetDataSingle( CONST_TABLE_TYPE eTableType, int32_t nIndex, int32_t nAttr ) const
{
	auto iter = m_mapData.find(eTableType);
	CHECKF(iter != m_mapData.end());
	return iter->second->GetData(nIndex, nAttr);
}

////////////////////////////////////////////////////////////////////////
// Description: 获取数据(双键表)
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: int64_t
////////////////////////////////////////////////////////////////////////
int64_t ConstTableMgr::GetDataDouble( CONST_TABLE_TYPE eTableType, int32_t nIndex1, int32_t nIndex2, int32_t nAttr ) const
{
	auto iter = m_mapData.find(eTableType);
	CHECKF(iter != m_mapData.end());
	return iter->second->GetData(nIndex1, nIndex2, nAttr);
}

////////////////////////////////////////////////////////////////////////
// Description: 获取数据(单键表)
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: const char*
////////////////////////////////////////////////////////////////////////
std::string ConstTableMgr::GetStrSingle( CONST_TABLE_TYPE eTableType, int32_t nIndex, int32_t nAttr ) const
{
	auto iter = m_mapData.find(eTableType);
	IF_OK(iter != m_mapData.end())
	{
		auto pszString = iter->second->GetStr(nIndex, nAttr);
		if (pszString)
		{
			return pszString;
		}
	}
	return "";
}

////////////////////////////////////////////////////////////////////////
// Description: 获取数据(双键表)
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: const char*
////////////////////////////////////////////////////////////////////////
std::string ConstTableMgr::GetStrDouble( CONST_TABLE_TYPE eTableType, int32_t nIndex1, int32_t nIndex2, int32_t nAttr ) const
{
	auto iter = m_mapData.find(eTableType);
	IF_OK(iter != m_mapData.end())
	{
		auto pszString = iter->second->GetStr(nIndex1, nIndex2, nAttr);
		if (pszString)
		{
			return pszString;
		}
	}
	return "";
}

////////////////////////////////////////////////////////////////////////
// Description: 重新加载
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
bool ConstTableMgr::Reload( CONST_TABLE_TYPE eTableType )
{
	auto iter = m_mapData.find(eTableType);
	if (iter != m_mapData.end())
	{
		return iter->second->Reload();
	}
	else
	{
		ConstTable* pTable = new ConstTable;
		CHECKF(pTable);
		IF_NOT(pTable->Init(eTableType))
		{
			LogSave("ConstTable[%d] Init Failed!", eTableType);
			return false;
		}
		m_mapData[eTableType] = pTable;
		return true;
	}	
}

////////////////////////////////////////////////////////////////////////
// Description: 枚举Key
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool ConstTableMgr::EnumKey( CONST_TABLE_TYPE eTableType, OUT VEC_DB_KEY& rVecKey ) const
{
	auto iter = m_mapData.find(eTableType);
	CHECKF(iter != m_mapData.end());
	return iter->second->EnumKey(rVecKey);
}

////////////////////////////////////////////////////////////////////////
// Description: 分解index
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void ConstTableMgr::ResolveDoubleKey( IN int64_t dbKey, OUT int32_t& rKey1, OUT int32_t& rKey2 ) const
{
	rKey1 = (int32_t)(dbKey >> 32) & 0xFFFFFFFF;
	rKey2 = (int32_t)(dbKey & 0xFFFFFFFF);
}

////////////////////////////////////////////////////////////////////////
// Description: 获得配置文字
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: std::string
////////////////////////////////////////////////////////////////////////
std::string ConstTableMgr::GetConfigText(CONFIG_TEXT_ID id) const
{
	if (this->IsExistSingle(CONST_TABLE_TYPE_config_text, id))
	{
		return ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_config_text, id, CONFIG_TEXT_DATA_TEXT);
	}

	LogSave("ConfigText %d not config!", id);
	std::string strDefault = StringUtils::format("ConfigText[%d] NotConfig", id);
	return strDefault;
}

////////////////////////////////////////////////////////////////////////
// Description: 获得最新服务器id
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: OBJID
////////////////////////////////////////////////////////////////////////
OBJID ConstTableMgr::GetNewestServerID() const
{
	VEC_DB_KEY vec;
	CHECKF(ConstTableMgr::getInstance()->EnumKey(CONST_TABLE_TYPE_server_list, vec));
	OBJID idMaxServer = ID_NONE;
	for (auto id : vec)
	{
		if (id > idMaxServer)
		{
			idMaxServer = id;
		}
	}
	return idMaxServer;
}

