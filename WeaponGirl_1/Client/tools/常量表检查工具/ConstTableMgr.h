////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: ConstTableMgr.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015-1-8
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_CONST_TABLE_MGR_
#define _JYP_CONST_TABLE_MGR_

#include "ConstTable.h"


class ConstTableMgr
{
public:
	static ConstTableMgr*	getInstance();
	static void				destroyInstance();
	bool					Init();
	bool					Reload(CONST_TABLE_TYPE eTableType);

private:
	static ConstTableMgr* _instance;

	// interface
public:
	bool		IsExistSingle	(CONST_TABLE_TYPE eTableType, int32_t nIndex) const;
	int64_t		GetDataSingle	(CONST_TABLE_TYPE eTableType, int32_t nIndex, int32_t nAttr) const;
	const char* GetStrSingle	(CONST_TABLE_TYPE eTableType, int32_t nIndex, int32_t nAttr) const;

	bool		IsExistDouble	(CONST_TABLE_TYPE eTableType, int32_t nIndex1, int32_t nIndex2) const;
	int64_t		GetDataDouble	(CONST_TABLE_TYPE eTableType, int32_t nIndex1, int32_t nIndex2, int32_t nAttr) const;
	const char* GetStrDouble	(CONST_TABLE_TYPE eTableType, int32_t nIndex1, int32_t nIndex2, int32_t nAttr) const;

	bool		EnumKey	(CONST_TABLE_TYPE eTableType, OUT VEC_DB_KEY& rVecKey) const;
	void		ResolveDoubleKey(IN int64_t dbKey, OUT int32_t& rKey1, OUT int32_t& rKey2) const;

private:
	std::map<CONST_TABLE_TYPE, ConstTable*> m_mapData;

};


#endif // end of _JYP_CONST_TABLE_MGR_

