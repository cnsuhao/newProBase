////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: TMemoryString.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015-1-16
////////////////////////////////////////////////////////////////////////
#ifndef	_COMMON_T_MEMORY_STRING_H_
#define _COMMON_T_MEMORY_STRING_H_

#include <map>
#include <string>


template <typename T>
class TMemoryString
{
	typedef std::map<T, std::string> MAP_STRING_TYPE;
public:
	//////////////////////////////////////////////////////////////////////////
	bool IsExist(T eAttr) const
	{
		auto iter = m_mapStringData.find(eAttr);
		if (iter == m_mapStringData.end())
		{
			return false;
		}
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	std::string GetAttr(T eAttr) const
	{
		auto iter = m_mapStringData.find(eAttr);
		if (iter != m_mapStringData.end())
		{
			return iter->second;
		}
		return "";
	}

	//////////////////////////////////////////////////////////////////////////
	bool SetAttr(T eAttr, const std::string& rNewString)
	{
		m_mapStringData[eAttr] = rNewString;
		return true;
	}

private:
	MAP_STRING_TYPE m_mapStringData;
};

#define DEFINE_msa(ENUM_ATTR)																														\
	virtual bool		IsExistMemoryString(ENUM_ATTR eAttr) const								{return m_mapStringData.IsExist(eAttr);}			\
	virtual std::string	GetMemoryStringAttr(ENUM_ATTR eAttr) const								{return m_mapStringData.GetAttr(eAttr);}			\
	virtual bool		SetMemoryStringAttr(ENUM_ATTR eAttr, const std::string& rNewString)	{return m_mapStringData.SetAttr(eAttr, rNewString);}	\
	protected:																																		\
		TMemoryString<ENUM_ATTR> m_mapStringData;

#endif // end of _COMMON_T_MEMORY_STRING_H_