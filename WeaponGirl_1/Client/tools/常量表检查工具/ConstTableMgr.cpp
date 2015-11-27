////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: ConstTableMgr.cpp
// Author: ������(Peng Wenqi)
// Created: 2015-1-8
////////////////////////////////////////////////////////////////////////
#include "ConstTableMgr.h"
#include "ConstTable.h"


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
// Description: ���ؾ�̬�������
// Arguments:
// Author: ������(Peng Wenqi)
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
		if(!pTable->Init(eTableType))
		{
			printf("ConstTable[%d] Init Failed!\n", eTableType);
			return false;
		}
		m_mapData[eTableType] = pTable;
	}
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: �Ƿ����(������)
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool ConstTableMgr::IsExistSingle( CONST_TABLE_TYPE eTableType, int32_t nIndex ) const
{
	auto iter = m_mapData.find(eTableType);
	CHECKF(iter != m_mapData.end());
	return iter->second->IsExist(nIndex);
}

////////////////////////////////////////////////////////////////////////
// Description: �Ƿ����(˫����)
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool ConstTableMgr::IsExistDouble( CONST_TABLE_TYPE eTableType, int32_t nIndex1, int32_t nIndex2 ) const
{
	auto iter = m_mapData.find(eTableType);
	CHECKF(iter != m_mapData.end());
	return iter->second->IsExist(nIndex1, nIndex2);
}

////////////////////////////////////////////////////////////////////////
// Description: ��ȡ����(������)
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: int64_t
////////////////////////////////////////////////////////////////////////
int64_t ConstTableMgr::GetDataSingle( CONST_TABLE_TYPE eTableType, int32_t nIndex, int32_t nAttr ) const
{
	auto iter = m_mapData.find(eTableType);
	CHECKF(iter != m_mapData.end());
	return iter->second->GetData(nIndex, nAttr);
}

////////////////////////////////////////////////////////////////////////
// Description: ��ȡ����(˫����)
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: int64_t
////////////////////////////////////////////////////////////////////////
int64_t ConstTableMgr::GetDataDouble( CONST_TABLE_TYPE eTableType, int32_t nIndex1, int32_t nIndex2, int32_t nAttr ) const
{
	auto iter = m_mapData.find(eTableType);
	CHECKF(iter != m_mapData.end());
	return iter->second->GetData(nIndex1, nIndex2, nAttr);
}

////////////////////////////////////////////////////////////////////////
// Description: ��ȡ����(������)
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: const char*
////////////////////////////////////////////////////////////////////////
const char* ConstTableMgr::GetStrSingle( CONST_TABLE_TYPE eTableType, int32_t nIndex, int32_t nAttr ) const
{
	auto iter = m_mapData.find(eTableType);
	CHECKF(iter != m_mapData.end());
	return iter->second->GetStr(nIndex, nAttr);
}

////////////////////////////////////////////////////////////////////////
// Description: ��ȡ����(˫����)
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: const char*
////////////////////////////////////////////////////////////////////////
const char* ConstTableMgr::GetStrDouble( CONST_TABLE_TYPE eTableType, int32_t nIndex1, int32_t nIndex2, int32_t nAttr ) const
{
	auto iter = m_mapData.find(eTableType);
	CHECKF(iter != m_mapData.end());
	return iter->second->GetStr(nIndex1, nIndex2, nAttr);
}

////////////////////////////////////////////////////////////////////////
// Description: ���¼���
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
bool ConstTableMgr::Reload( CONST_TABLE_TYPE eTableType )
{
	auto iter = m_mapData.find(eTableType);
	CHECKF(iter != m_mapData.end());
	return iter->second->Reload();
}

////////////////////////////////////////////////////////////////////////
// Description: ö��Key
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool ConstTableMgr::EnumKey( CONST_TABLE_TYPE eTableType, OUT VEC_DB_KEY& rVecKey ) const
{
	auto iter = m_mapData.find(eTableType);
	CHECKF(iter != m_mapData.end());
	return iter->second->EnumKey(rVecKey);
}

////////////////////////////////////////////////////////////////////////
// Description: �ֽ�index
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void ConstTableMgr::ResolveDoubleKey( IN int64_t dbKey, OUT int32_t& rKey1, OUT int32_t& rKey2 ) const
{
	rKey1 = (int32_t)(dbKey >> 32) & 0xFFFFFFFF;
	rKey2 = (int32_t)(dbKey & 0xFFFFFFFF);
}



