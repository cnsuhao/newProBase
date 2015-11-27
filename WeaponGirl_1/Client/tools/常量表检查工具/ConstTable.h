////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: ConstTable.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015-1-9
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_CONST_TABLE_
#define _JYP_CONST_TABLE_

#include <stdint.h>
#include "../../trunk/Classes/ConstTable/ConstTableDefine.h"

#include <vector>
#include <map>
#include <set>
typedef std::vector<int64_t>	VEC_DB_KEY;


#define CC_SAFE_DELETE(p) do { delete (p); (p) = nullptr; } while(0)

#define	CHECK(x)					do{ if(!(x))	{return;}	}while(0)
#define	CHECKF(x)					do{ if(!(x))	{return 0;} }while(0)
#define	CHECKF1(x)					do{ if(!(x))	{return 1;} }while(0)
#define	CHECKC(x)					if(	!(x))		{continue;}
#define	CHECKBK(x)					if(	!(x))		{break;}
#define	CHECKB(x)					if(	!(x))		{}

#define IN
#define OUT


typedef std::map<int64_t, int32_t>	MAP_JSON_INDEX;

class ConstTable
{
public:
	ConstTable();
	~ConstTable();

public:
	bool		IsVaild() const;
	bool		Init(CONST_TABLE_TYPE eType);
	bool		Reload();
	bool		IsExist(int32_t nIndexData) const;
	bool		IsExist(int32_t nIndex1Data, int32_t nIndex2Data) const;

	int64_t		GetData(int32_t nIndexData, int32_t nAttr) const;
	int64_t		GetData(int32_t nIndex1Data, int32_t nIndex2Data, int32_t nAttr) const;

	const char* GetStr(int32_t nIndexData, int32_t nAttr) const;
	const char* GetStr(int32_t nIndex1Data, int32_t nIndex2Data, int32_t nAttr) const;

	bool		EnumKey		(VEC_DB_KEY& rVecKey) const;
	int			GetSize		() const {return m_mapData.size();}
	

private:
	int64_t		MakeIndex(int32_t nIndex1Data, int32_t nIndex2Data) const;	

private:
	CONST_TABLE_TYPE							m_eTableType;
	CONST_TABLE_INDEX_TYPE						m_eIndexType;
	std::map<int64_t, std::vector<std::string>> m_mapData;
	std::vector<std::string>					m_vecField;
	const ST_CONST_TABLE_FIELD*					m_pField;
};

#endif // end of _JYP_CONST_TABLE_