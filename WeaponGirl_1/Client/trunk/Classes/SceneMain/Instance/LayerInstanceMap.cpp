////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerInstanceMap.cpp
// Author: 陈建军(Chen Jianjun)
// Created: 2015-11-20
////////////////////////////////////////////////////////////////////////
#include "LayerInstanceMap.h"
#include "Root.h"
#include "../SceneMain.h"
#include "LayerInstanceView.h"
#include "WidgetInstanceMapInfo.h"
#include "Mgr\InstanceMgr.h"
#include "Mgr\UserAttrMgr.h"

//////////////////////////////////////////////////////////////////////////
LayerInstanceMap::~LayerInstanceMap()
{
	CC_SAFE_RELEASE(m_pMapThroughCsbNode);
	CC_SAFE_RELEASE(m_pMapLockCsbNode);
}

//////////////////////////////////////////////////////////////////////////
bool LayerInstanceMap::init()
{
	this->setName("LayerInstanceMap");
	this->setCascadeOpacityEnabled(true);

	// 加载csb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerInstanceMap.csb");
	this->addChild(m_pCsbWidget);
	ui::Helper::doLayout(m_pCsbWidget);

	m_pMapThroughCsbNode = CSLoader::createNode("NodeInstanceMapThrough.csb");
	CHECKF(m_pMapThroughCsbNode);
	m_pMapThroughCsbNode->retain();
	m_pMapLockCsbNode = CSLoader::createNode("NodeInstanceMapLock.csb");
	CHECKF(m_pMapLockCsbNode);
	m_pMapLockCsbNode->retain();

	// 初始化列表
	auto listViewMap = dynamic_cast<ui::ListView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ListViewMap"));
	CHECKF(listViewMap);
	auto idInstance = InstanceMgr::getInstance()->getidCurInstance();
	CHECKF(idInstance);
	auto nSearchingChapter = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_instance, idInstance, INSTANCE_DATA_CHAPTER);
	auto scoreMax = UserAttrMgr::getInstance()->getAttr(USER_ATTR_score_max);

	VEC_DB_KEY vecKey;
	ConstTableMgr::getInstance()->EnumKey(CONST_TABLE_TYPE_instance, vecKey);
	std::map<int, int64_t> mapMapInfo;
	for (auto iter : vecKey)
	{
		auto nChapter = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_instance, iter, INSTANCE_DATA_CHAPTER);
		CHECKC_NOLOG(mapMapInfo.find(nChapter) == mapMapInfo.end());
		auto i64OpenScore = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_instance, iter, INSTANCE_DATA_OPEN_SCORE);
		mapMapInfo[nChapter] = i64OpenScore;
	}

	m_mapChapterInfo.clear();
	for (auto iter : mapMapInfo)
	{
		if (scoreMax >= iter.second)
		{
			auto pListItem = WidgetInstanceMapInfo::create(m_pMapThroughCsbNode, WIDGET_INSTANCE_MAP_TYPE_THROUGH, iter.first);
			CHECKC(pListItem);
			if (nSearchingChapter == iter.first)
			{
				pListItem->setSearching(true);
			}
			listViewMap->pushBackCustomItem(pListItem);
			m_mapChapterInfo.insert(iter.first, pListItem);
		}
		else
		{
			auto pListItem = WidgetInstanceMapInfo::create(m_pMapLockCsbNode, WIDGET_INSTANCE_MAP_TYPE_LOCK, iter.first);
			CHECKC(pListItem);
			listViewMap->pushBackCustomItem(pListItem);
			m_mapChapterInfo.insert(iter.first, pListItem);
		}
	}
	return true;
}

void LayerInstanceMap::setVisible(bool bVisible)
{
	if (bVisible)
	{
		this->checkMap();
	}
	Layer::setVisible(bVisible);
}

bool LayerInstanceMap::checkMap()
{
	auto idInstance = InstanceMgr::getInstance()->getidCurInstance();
	CHECKF(idInstance);
	auto nSearchingChapter = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_instance, idInstance, INSTANCE_DATA_CHAPTER);
	auto scoreMax = UserAttrMgr::getInstance()->getAttr(USER_ATTR_score_max);
	for (auto iter : m_mapChapterInfo)
	{
		WidgetInstanceMapInfo* pMapInfo = dynamic_cast<WidgetInstanceMapInfo*>(iter.second);
		CHECKC(pMapInfo);
		if (pMapInfo->getMapType() == WIDGET_INSTANCE_MAP_TYPE_LOCK)
		{
			if (scoreMax >= pMapInfo->getOpenScore())
			{
				pMapInfo->updateMapInfo(m_pMapThroughCsbNode);
			}
			continue;
		}

		if (nSearchingChapter != pMapInfo->getChapter())
		{
			if (pMapInfo->getSearching())
			{
				pMapInfo->setSearching(false);
			}
		}
		else
		{
			if (!pMapInfo->getSearching())
			{
				pMapInfo->setSearching(true);
			}
		}
	}
	return true;
}

bool LayerInstanceMap::updateMap(OBJID idInstance)
{
	CHECKF(idInstance);
	auto nChapter = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_instance, idInstance, INSTANCE_DATA_CHAPTER);
	auto iter = m_mapChapterInfo.find(nChapter);
	CHECKF(iter != m_mapChapterInfo.end());
	WidgetInstanceMapInfo* pMapInfo = dynamic_cast<WidgetInstanceMapInfo*>(iter->second);
	CHECKF(pMapInfo);
	CHECKF(pMapInfo->getMapType() == WIDGET_INSTANCE_MAP_TYPE_THROUGH);
	CHECKF(pMapInfo->updateThrough(ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_instance, idInstance, INSTANCE_DATA_MODE)));
	return true;
}