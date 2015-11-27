////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2012, WuHan ChuangYou, All Rights Reserved
// Moudle: TMemoryData.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2012-10-29
////////////////////////////////////////////////////////////////////////
#ifndef	_COMMON_T_MEMORY_DATA_H_
#define _COMMON_T_MEMORY_DATA_H_

#include <map>
#include <stdint.h>


template <typename T>
class TMemoryData
{
	typedef std::map<T, int64_t> MAP_STRING_TYPE;
public:
	//////////////////////////////////////////////////////////////////////////
	bool IsExist(T eAttr) const
	{
		auto iter = m_mapData.find(eAttr);
		if (iter == m_mapData.end())
		{
			return false;
		}
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	int64_t GetAttr(T eAttr) const
	{
		auto iter = m_mapData.find(eAttr);
		if (iter != m_mapData.end())
		{
			return iter->second;
		}
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////
	bool SetAttr(T eAttr, int64_t iNewData)
	{
		// 对于不存在的0值, 不必插入, 节约内存
		if (0 == iNewData && !this->IsExist(eAttr))
		{
			return true;
		}

		m_mapData[eAttr] = iNewData;
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	void AddAttr(T eAttr, int64_t iAddData)
	{
		int64_t iOldData = this->GetAttr(eAttr);
		m_mapData[eAttr] = iOldData + iAddData;
	}

	//////////////////////////////////////////////////////////////////////////
	void DecAttr(T eAttr, int64_t iDecData)
	{
		int64_t iOldData = this->GetAttr(eAttr);
		m_mapData[eAttr] = iOldData - iDecData;
	}

private:
	MAP_STRING_TYPE m_mapData;
};

#define DEFINE_mda(ENUM_ATTR)																										\
		virtual bool	IsExistMemoryData(ENUM_ATTR eAttr) const				{return m_memoryData.IsExist(eAttr);}				\
		virtual int64_t	GetMemoryDataAttr(ENUM_ATTR eAttr) const				{return m_memoryData.GetAttr(eAttr);}				\
		virtual bool	SetMemoryDataAttr(ENUM_ATTR eAttr, int64_t iNewData)	{return m_memoryData.SetAttr(eAttr, iNewData);}	\
		virtual void	AddMemoryDataAttr(ENUM_ATTR eAttr, int64_t iAddData)	{m_memoryData.AddAttr(eAttr, iAddData);}	\
		virtual void	DecMemoryDataAttr(ENUM_ATTR eAttr, int64_t iDecData)	{m_memoryData.DecAttr(eAttr, iDecData);}	\
	protected:																														\
		TMemoryData<ENUM_ATTR> m_memoryData;

#endif // end of _COMMON_T_MEMORY_DATA_H_
