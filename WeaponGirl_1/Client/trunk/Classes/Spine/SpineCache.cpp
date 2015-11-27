////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2015, WuHan GoodGame, All Rights Reserved
// Moudle: SpineCache.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015-1-29
////////////////////////////////////////////////////////////////////////
#include "SpineCache.h"
#include "Root.h"
#include "SpineBase.h"

SpineCache* SpineCache::m_pInstance = nullptr;
//////////////////////////////////////////////////////////////////////////
SpineCache* SpineCache::getInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new SpineCache();
	}
	return m_pInstance;
}

//////////////////////////////////////////////////////////////////////////
void SpineCache::destroyInstance()
{
	CC_SAFE_DELETE(m_pInstance);
}

//////////////////////////////////////////////////////////////////////////
SpineCache::SpineCache()
{

}

//////////////////////////////////////////////////////////////////////////
SpineCache::~SpineCache()
{
	for (auto &data : m_mapData)
	{
		auto pData = data.second.pData;
		IF_OK (pData)
		{
			spSkeletonData_dispose(pData);
		}

		auto pAtlas = data.second.pAtlas;
		IF_OK (pAtlas)
		{
			spAtlas_dispose(pAtlas);
		}
	}
	m_mapData.clear();
}

////////////////////////////////////////////////////////////////////////
// Description: 启动时预加载缓存
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
bool SpineCache::proloadCache( void )
{
	VEC_DB_KEY vecDbKey;
	CHECKF(ConstTableMgr::getInstance()->EnumKey(CONST_TABLE_TYPE_spine_type, vecDbKey));
	for (auto &dbkey : vecDbKey)
	{
		int32_t idSpineType = dbkey;
		CHECKC(ConstTableMgr::getInstance()->IsExistSingle(CONST_TABLE_TYPE_spine_type, idSpineType));
		if (0 == ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_spine_type, idSpineType, SPINE_TYPE_preload))
		{
			continue;
		}

		// 缓存中存在
		auto iter = m_mapData.find(idSpineType);
		if (iter != m_mapData.end())
		{
			continue;
		}

		m_setProloadType.insert(idSpineType);
	}
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 加载一份缓存数据
// Arguments:	注意: 该接口数据并不加入单例缓存, 仍需要处理
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
bool SpineCache::loadCacheData( OBJID idSpineType, OUT ST_SPINE_DATA& rData )
{
	CHECKF(ConstTableMgr::getInstance()->IsExistSingle(CONST_TABLE_TYPE_spine_type, idSpineType));
	auto strJson = ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_spine_type, idSpineType, SPINE_TYPE_json);
	auto strAtlas = ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_spine_type, idSpineType, SPINE_TYPE_atlas);

	rData.bOwner = (0 == ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_spine_type, idSpineType, SPINE_TYPE_forever)) ? true : false;
	rData.fScale = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_spine_type, idSpineType, SPINE_TYPE_scale) / 10000.f;

	rData.pAtlas = spAtlas_createFromFile(strAtlas.c_str(), 0);
	IF_NOT (rData.pAtlas)
	{
		LogSave("SpineCache::proloadCache: type[%u] pAtlas is null!", idSpineType);
		return false;
	}
	
	auto pAtlasJson = spSkeletonJson_create(rData.pAtlas);
	pAtlasJson->scale = ::GetValueInRightRange(rData.fScale, 0.05f, 50.f);
	rData.pData = spSkeletonJson_readSkeletonDataFile(pAtlasJson, strJson.c_str());

	IF_NOT (rData.pData)
	{
		LogSave("SpineCache::proloadCache: type[%u] pData is null!", idSpineType);
		if (pAtlasJson->error)
		{
			LogSave("pAtlasJson->error[%s]", pAtlasJson->error);
		}
		spSkeletonJson_dispose(pAtlasJson);
		spAtlas_dispose(rData.pAtlas);
		return false;
	}

	spSkeletonJson_dispose(pAtlasJson);

	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 获得骨骼动画信息
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool SpineCache::getSkeletonInfo( OBJID idSpineType, OUT ST_SPINE_DATA& rData )
{
	CHECKF(idSpineType);
	CHECKF(ConstTableMgr::getInstance()->IsExistSingle(CONST_TABLE_TYPE_spine_type, idSpineType));

	// 缓存中存在
	auto iter = m_mapData.find(idSpineType);
	if (iter != m_mapData.end())
	{
		rData = iter->second;
		return true;
	}

	// 实时加载
	ST_SPINE_DATA stData = {0};
	CHECKF(this->loadCacheData(idSpineType, stData) && stData.pData);
	if (!stData.bOwner)
	{
		m_mapData[idSpineType] = stData;
	}
	rData = stData;
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void SpineCache::onTimerProloadCache(void)
{
	if (m_setProloadType.empty())
	{
		return;
	}

	auto iter = m_setProloadType.begin();
	OBJID idSpineType = *iter;
	m_setProloadType.erase(iter);

	// 缓存中存在
	if (m_mapData.find(idSpineType) != m_mapData.end())
	{
		return;
	}

	ST_SPINE_DATA stData = { 0 };
	IF_OK(this->loadCacheData(idSpineType, stData))
	{
		m_mapData[idSpineType] = stData;
	}
}

