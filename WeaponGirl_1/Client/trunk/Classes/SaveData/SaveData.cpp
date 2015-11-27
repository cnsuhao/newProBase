////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: SaveData.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015-1-13
////////////////////////////////////////////////////////////////////////
#include "SaveData.h"
#include "RC4.h"
#include "Global/Global.h"
static const char* SAVE_DATA_KEY = "eG.JYP_861718-GoodGame-key";
static const char* DEFAULT_DATA_STRING = "_";	// 默认比较字符串, 由于加密算法不会产生下划线结果, 采用单下划线做初始值

////////////////////////////////////////////////////////////////////////
// Description: 设置保存数值
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool SetSaveData( SAVE_DATA eData, int32_t nData )
{
	CHECKF(eData >= SAVE_DATA_BEGIN && eData < SAVE_DATA_END);
	CHECKF(ARR_SAVE_DATA[eData].eFieldType == FIELD_TYPE_int);
	const char* pszName = ARR_SAVE_DATA[eData].pszFieldName;
	CHECKF(pszName);
	if (ARR_SAVE_DATA[eData].bEncrypt)
	{
		char szBuffer[16] = {0};
		memset(szBuffer, 0, 16);
		sprintf(szBuffer, "%d", nData);
		std::string strValue = rc4::Encrypt(szBuffer, SAVE_DATA_KEY);
		UserDefault::getInstance()->setStringForKey(pszName, strValue);
	}
	else
	{
		UserDefault::getInstance()->setIntegerForKey(pszName, nData);
	}
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 设置保存字符串
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool SetSaveStr( SAVE_DATA eData, const std::string& strData )
{
	CHECKF(eData >= SAVE_DATA_BEGIN && eData < SAVE_DATA_END);
	CHECKF(ARR_SAVE_DATA[eData].eFieldType == FIELD_TYPE_str);
	const char* pszName = ARR_SAVE_DATA[eData].pszFieldName;
	CHECKF(pszName);
	if (ARR_SAVE_DATA[eData].bEncrypt)
	{
		std::string strValue = rc4::Encrypt(strData.c_str(), SAVE_DATA_KEY);
		UserDefault::getInstance()->setStringForKey(pszName, strValue);
	}
	else
	{
		UserDefault::getInstance()->setStringForKey(pszName, strData);
	}

	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 获得存储数据
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: int64_t
////////////////////////////////////////////////////////////////////////
int64_t GetSaveData( SAVE_DATA eData )
{
	CHECKF(eData >= SAVE_DATA_BEGIN && eData < SAVE_DATA_END);
	CHECKF(ARR_SAVE_DATA[eData].eFieldType == FIELD_TYPE_int);
	const char* pszName = ARR_SAVE_DATA[eData].pszFieldName;
	CHECKF(pszName);
	if (ARR_SAVE_DATA[eData].bEncrypt)
	{
		std::string strValue = UserDefault::getInstance()->getStringForKey(pszName, DEFAULT_DATA_STRING);
		if (0 == strcmp(DEFAULT_DATA_STRING, strValue.c_str()))
		{
			return ARR_SAVE_DATA[eData].nDefault;
		}
		std::string strResult = rc4::Decrypt(strValue.c_str(), SAVE_DATA_KEY);
		return atoll(strResult.c_str());
	}
	else
	{
		return UserDefault::getInstance()->getIntegerForKey(pszName, ARR_SAVE_DATA[eData].nDefault);
	}
}

////////////////////////////////////////////////////////////////////////
// Description: 获得存储字符串
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: std::string
////////////////////////////////////////////////////////////////////////
std::string GetSaveStr( SAVE_DATA eData )
{
	IF_NOT (eData >= SAVE_DATA_BEGIN && eData < SAVE_DATA_END)
	{
		return "";
	}

	IF_NOT(ARR_SAVE_DATA[eData].eFieldType == FIELD_TYPE_str)
	{
		return "";
	}

	const char* pszName = ARR_SAVE_DATA[eData].pszFieldName;
	IF_NOT (pszName)
	{
		return "";
	}

	if (ARR_SAVE_DATA[eData].bEncrypt)
	{
		std::string strValue = UserDefault::getInstance()->getStringForKey(pszName, DEFAULT_DATA_STRING);
		if (0 == strcmp(DEFAULT_DATA_STRING, strValue.c_str()))
		{
			return ARR_SAVE_DATA[eData].szDefault;
		}
		return rc4::Decrypt(strValue.c_str(), SAVE_DATA_KEY);
	}
	else
	{
		return UserDefault::getInstance()->getStringForKey(pszName);
	}
}
