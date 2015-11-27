////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: ConstTable.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015-1-9
////////////////////////////////////////////////////////////////////////
#include "ConstTable.h"

#include "cocostudio/CCSGUIReader.h"
#include "cocos2d.h"
using namespace cocos2d;
using namespace cocostudio;

////////////////////////////////////////////////////////////////////////
ConstTable::ConstTable(  )
{
	m_eIndexType = CONST_TABLE_INDEX_TYPE_none;
	m_pField = nullptr;
}

//////////////////////////////////////////////////////////////////////////
ConstTable::~ConstTable()
{

}

////////////////////////////////////////////////////////////////////////
// Description: 是否初始化成功
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool ConstTable::IsVaild() const
{
	if (m_eTableType < CONST_TABLE_TYPE_BEGIN || m_eTableType >= CONST_TABLE_TYPE_END)
	{
		return false;
	}

	if (m_eIndexType == CONST_TABLE_INDEX_TYPE_none)
	{
		return false;
	}

	if (m_pField == nullptr)
	{
		return false;
	}

	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 初始化
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool ConstTable::Init( CONST_TABLE_TYPE eType )
{
	CHECKF(eType >= CONST_TABLE_TYPE_BEGIN && eType < CONST_TABLE_TYPE_END);
	auto indexType = CONST_TABLE_INFOS[eType].eIndexType;
	CHECKF(indexType != CONST_TABLE_INDEX_TYPE_none);

	m_eTableType = eType;
	m_eIndexType = indexType;
	m_pField = CONST_TABLE_INFOS[eType].pFieldInfo;

	return this->Reload();
}

////////////////////////////////////////////////////////////////////////
// Description: 重新加载
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool ConstTable::Reload()
{
	CHECKF(this->IsVaild());
	m_vecField.clear();
	m_mapData.clear();

	LogSave("const table[%s] loading...", CONST_TABLE_INFOS[m_eTableType].pszFileName);

	// 加载数据, 服务器列表特殊处理
	std::string load_str;
	if (CONST_TABLE_TYPE_server_list == m_eTableType)
	{
		std::string strDataPath = FileUtils::getInstance()->getWritablePath() + SERVER_LIST_FILE_NAME;
		ssize_t size;
		char* zipBuffer = reinterpret_cast<char*>(FileUtils::getInstance()->getFileDataFromZip(strDataPath, CONST_TABLE_INFOS[m_eTableType].pszFileName, SERVER_LIST_FILE_PASSWORD, &size));
		CHECKF(zipBuffer);
		load_str = FileUtils::getInstance()->getRemoveBomStringData(zipBuffer, size);
		free(zipBuffer);
		LogSave("const table[%s], size[%d], path[%s] loaded", CONST_TABLE_INFOS[m_eTableType].pszFileName, size, strDataPath.c_str());
	}
	else
	{
		std::string strDataPath = FileUtils::getInstance()->getWritablePath() + RES_CONFIG_FILE_NAME;
		ssize_t size;
		char* zipBuffer = reinterpret_cast<char*>(FileUtils::getInstance()->getFileDataFromZip(strDataPath, CONST_TABLE_INFOS[m_eTableType].pszFileName, RES_CONFIG_FILE_PASSWORD, &size));
		CHECKF(zipBuffer);
		load_str = FileUtils::getInstance()->getRemoveBomStringData(zipBuffer, size);
		free(zipBuffer);
		LogSave("const table[%s], size[%d], path[%s] loaded", CONST_TABLE_INFOS[m_eTableType].pszFileName, size, strDataPath.c_str());
	}
	

	std::vector<std::string> vecSplitString;
	::SpiltString(load_str, "\n", vecSplitString, 10000);
	for (auto iter = vecSplitString.begin(); iter != vecSplitString.end(); iter++)
	{
		auto strData = *iter;
		if (strData.empty())
		{
			continue;
		}
		::ReplaceStdString(strData, "\r", "", true);

		std::vector<std::string> vecFieldString;
		::SpiltString(strData, ",", vecFieldString, 100);

		if (iter == vecSplitString.begin())
		{
			m_vecField = vecFieldString;
			continue;
		}

		IF_OK (vecFieldString.size() == CONST_TABLE_INFOS[m_eTableType].nFieldCount)
		{
			std::string strIndex1 = vecFieldString[CONST_TABLE_INFOS[m_eTableType].nKeyIndex1];
			std::string strIndex2 = vecFieldString[CONST_TABLE_INFOS[m_eTableType].nKeyIndex2];
			auto index = this->MakeIndex(atoi(strIndex1.c_str()), atoi(strIndex2.c_str()));
			m_mapData[index] = vecFieldString;
		}
		else
		{
			LogSave("ConstTableFile[%s] check extra ,", CONST_TABLE_INFOS[m_eTableType].pszFileName);
		}
	}

	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 计算索引
// Arguments:	
// Author: 彭文奇(Peng Wenqi)
// Return Value: int64_t
////////////////////////////////////////////////////////////////////////
int64_t ConstTable::MakeIndex( int32_t nIndex1Data, int32_t nIndex2Data ) const
{
	if (CONST_TABLE_INDEX_TYPE_single == m_eIndexType)
	{
		return nIndex1Data;
	}
	else
	{
		return (((int64_t)nIndex1Data) << 32) + nIndex2Data;
	}
}

////////////////////////////////////////////////////////////////////////
// Description: 是否存在
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool ConstTable::IsExist( int32_t nIndexData ) const
{
	CHECKF(this->IsVaild());
	CHECKF(CONST_TABLE_INDEX_TYPE_single == CONST_TABLE_INFOS[m_eTableType].eIndexType);
	auto index = this->MakeIndex(nIndexData, nIndexData);
	if (m_mapData.find(index) == m_mapData.end())
	{
		return false;
	}
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 是否存在
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool ConstTable::IsExist( int32_t nIndex1Data, int32_t nIndex2Data ) const
{
	CHECKF(this->IsVaild());
	CHECKF(CONST_TABLE_INDEX_TYPE_double == CONST_TABLE_INFOS[m_eTableType].eIndexType);
	auto index = this->MakeIndex(nIndex1Data, nIndex2Data);
	if (m_mapData.find(index) == m_mapData.end())
	{
		return false;
	}
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 枚举所有Key
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool ConstTable::EnumKey( OUT VEC_DB_KEY& rVecKey ) const
{
	rVecKey.clear();
	for (auto iter = m_mapData.begin(); iter != m_mapData.end(); iter++)
	{
		auto dbKey = iter->first;
		rVecKey.push_back(dbKey);
	}
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 获得数据
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: int64_t
////////////////////////////////////////////////////////////////////////
int64_t	ConstTable::GetData(int32_t nIndexData, int32_t nAttr) const
{
	CHECKF(this->IsVaild());	
	CHECKF(nAttr >= 0 && nAttr < CONST_TABLE_INFOS[m_eTableType].nFieldCount);
	CHECKF(CONST_TABLE_INDEX_TYPE_single == CONST_TABLE_INFOS[m_eTableType].eIndexType);
	CHECKF(m_pField[nAttr].eFieldType == FIELD_TYPE_int);
	auto iter = m_mapData.find(this->MakeIndex(nIndexData, nIndexData));
	CHECKF(iter != m_mapData.end());
	CHECKF(nAttr < iter->second.size());
	auto strData = (iter->second)[nAttr];
	return atoll(strData.c_str());
}

////////////////////////////////////////////////////////////////////////
// Description: 获得数据
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: int64_t
////////////////////////////////////////////////////////////////////////
int64_t	ConstTable::GetData(int32_t nIndex1Data, int32_t nIndex2Data, int32_t nAttr) const
{
	CHECKF(this->IsVaild());	
	CHECKF(nAttr >= 0 && nAttr < CONST_TABLE_INFOS[m_eTableType].nFieldCount);
	CHECKF(CONST_TABLE_INDEX_TYPE_double == CONST_TABLE_INFOS[m_eTableType].eIndexType);
	CHECKF(m_pField[nAttr].eFieldType == FIELD_TYPE_int);
	auto index = this->MakeIndex(nIndex1Data, nIndex2Data);
	auto iter = m_mapData.find(index);
	CHECKF(iter != m_mapData.end());
	CHECKF(nAttr < iter->second.size());
	auto strData = (iter->second)[nAttr];
	return atoll(strData.c_str());
}

////////////////////////////////////////////////////////////////////////
// Description: 获得字符串
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: const char*
////////////////////////////////////////////////////////////////////////
const char* ConstTable::GetStr( int32_t nIndexData, int32_t nAttr ) const
{
	CHECKF(this->IsVaild());	
	CHECKF(nAttr >= 0 && nAttr < CONST_TABLE_INFOS[m_eTableType].nFieldCount);
	CHECKF(CONST_TABLE_INDEX_TYPE_single == CONST_TABLE_INFOS[m_eTableType].eIndexType);
	CHECKF(m_pField[nAttr].eFieldType == FIELD_TYPE_str);
	auto iter = m_mapData.find(nIndexData);
	CHECKF(iter != m_mapData.end());
	CHECKF(nAttr < iter->second.size());
	return (iter->second)[nAttr].c_str();
}

////////////////////////////////////////////////////////////////////////
// Description: 获得字符串
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: const char*
////////////////////////////////////////////////////////////////////////
const char* ConstTable::GetStr( int32_t nIndex1Data, int32_t nIndex2Data, int32_t nAttr ) const
{
	CHECKF(this->IsVaild());	
	CHECKF(nAttr >= 0 && nAttr < CONST_TABLE_INFOS[m_eTableType].nFieldCount);
	CHECKF(CONST_TABLE_INDEX_TYPE_double == CONST_TABLE_INFOS[m_eTableType].eIndexType);
	CHECKF(m_pField[nAttr].eFieldType == FIELD_TYPE_str);
	auto index = this->MakeIndex(nIndex1Data, nIndex2Data);
	auto iter = m_mapData.find(index);
	CHECKF(iter != m_mapData.end());
	CHECKF(nAttr < iter->second.size());
	return (iter->second)[nAttr].c_str();
}

