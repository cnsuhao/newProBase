////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: ConstTable.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015-1-9
////////////////////////////////////////////////////////////////////////
#include "ConstTable.h"
#include <fstream>
#include <sstream>

void SpiltString(const std::string& srcString, const std::string& strSpiltFlag, std::vector<std::string>& rVecSplitString, int nMaxSplits)
{
	int nSplitLength = strSpiltFlag.size();
	if (0 == nSplitLength)
	{
		return;
	}

	int nStartPos = 0;
	int nBreakCount = 0;
	while (true)
	{
		int nEndPos = srcString.find_first_of(strSpiltFlag, nStartPos);
		if (nEndPos == std::string::npos)
		{
			nEndPos = srcString.size();
		}
		auto strSplit = srcString.substr(nStartPos, nEndPos - nStartPos);
		rVecSplitString.push_back(strSplit);

		if (++nBreakCount > nMaxSplits)
		{
			break;
		}
		nStartPos = nEndPos + nSplitLength;
		if (nStartPos > (int)(srcString.size()))
		{
			break;
		}
	}
}

int ReplaceStdString(std::string& str, const char* pszOld, const char* pszNew, bool bReplaceAll/* = true*/)
{
	CHECKF(pszOld && ::strlen(pszOld) > 0);
	CHECKF(pszNew && ::strlen(pszNew) >= 0);
	if (str.empty())
	{
		return 0;
	}

	std::string::size_type unOldSize = ::strlen(pszOld);
	std::string::size_type unNewSize = ::strlen(pszNew);

	int nReplaceCount = 0;
	std::string::size_type unPos = 0;
	while ((unPos = str.find(pszOld, unPos)) != str.npos)
	{
		nReplaceCount++;
		str.replace(unPos, unOldSize, pszNew);
		unPos += unNewSize;
		if (!bReplaceAll)
		{
			break;
		}
	}

	return nReplaceCount;
}


std::string LoadFileToString(const std::string& strFileName)
{
	const char SZ_UTF8_FILE_HEADER[3] = { (char)0xEF, (char)0xBB, (char)0xBF };	// utf8文件头
	std::ostringstream buf;
	std::ifstream inFile(strFileName.c_str(), std::ios::in);
	char ch;
	int nCount = 0;
	while (buf && inFile.get(ch))
	{
		if (nCount < 3)
		{
			if (SZ_UTF8_FILE_HEADER[nCount++] == ch)
			{
				continue;
			}
		}
		buf.put(ch);
	}
	inFile.close();
	return buf.str();
}

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

	// 加载数据, 服务器列表特殊处理
	if (CONST_TABLE_TYPE_server_list == m_eTableType)
	{
		return true;
	}

	std::string strFilePath = "config_files/";
	strFilePath += CONST_TABLE_INFOS[m_eTableType].pszFileName;
	std::string load_str = LoadFileToString(strFilePath);
	printf("const table[%s], size[%d] loaded\n", CONST_TABLE_INFOS[m_eTableType].pszFileName, load_str.size());

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

		if (vecFieldString.size() == CONST_TABLE_INFOS[m_eTableType].nFieldCount)
		{
			std::string strIndex1 = vecFieldString[CONST_TABLE_INFOS[m_eTableType].nKeyIndex1];
			std::string strIndex2 = vecFieldString[CONST_TABLE_INFOS[m_eTableType].nKeyIndex2];
			auto index = this->MakeIndex(atoi(strIndex1.c_str()), atoi(strIndex2.c_str()));
			m_mapData[index] = vecFieldString;
		}
		else
		{
			printf("ConstTableFile[%s] check extra ,\n", CONST_TABLE_INFOS[m_eTableType].pszFileName);
			return false;
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
bool ConstTable::EnumKey( VEC_DB_KEY& rVecKey ) const
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

