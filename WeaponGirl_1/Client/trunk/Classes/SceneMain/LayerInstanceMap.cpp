////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerInstanceMap.cpp
// Author: 陈建军(Chen Jianjun)
// Created: 2015-11-20
////////////////////////////////////////////////////////////////////////
#include "LayerInstanceMap.h"
#include "Root.h"
#include "SceneMain.h"
#include "LayerInstanceView.h"
#include "WidgetInstanceMapInfo.h"
#include "Mgr\InstanceMgr.h"

//////////////////////////////////////////////////////////////////////////
LayerInstanceMap::~LayerInstanceMap()
{
	CC_SAFE_RELEASE(m_pMapThroughCsbNode);
	CC_SAFE_RELEASE(m_pMapOpenCsbNode);
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
	m_pMapOpenCsbNode = CSLoader::createNode("NodeInstanceMapOpen.csb");
	CHECKF(m_pMapOpenCsbNode);
	m_pMapOpenCsbNode->retain();

	// 初始化列表
	m_mapChapterNode.clear();
	auto listViewMap = dynamic_cast<ui::ListView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ListViewMap"));
	CHECKF(listViewMap);
	auto pInstanceInfo = InstanceMgr::getInstance()->getInstanceInfo();
	CHECKF(pInstanceInfo);
	for (auto iter : *pInstanceInfo)
	{
		auto nChapter  = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_instance, iter.first, INSTANCE_DATA_CHAPTER);
		auto iter = m_mapChapterNode.find(nChapter);
		CHECKC_NOLOG(iter == m_mapChapterNode.end());
		auto pListItem = WidgetInstanceMapInfo::create(m_pMapThroughCsbNode, WIDGET_INSTANCE_MAP_TYPE_THROUGH, nChapter);
		CHECKC(pListItem);
		pListItem->addClickEventListener(CC_CALLBACK_1(LayerInstanceMap::clickMap, this));
		listViewMap->pushBackCustomItem(pListItem);
		m_mapChapterNode.insert(nChapter, pListItem);
	}

	VEC_DB_KEY vecKey;
	ConstTableMgr::getInstance()->EnumKey(CONST_TABLE_TYPE_instance, vecKey);
	for (auto iter : vecKey)
	{
		auto nChapter = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_instance, iter, INSTANCE_DATA_CHAPTER);
		auto iter = m_mapChapterNode.find(nChapter);
		CHECKC_NOLOG(iter == m_mapChapterNode.end());
		auto pListItem = WidgetInstanceMapInfo::create(m_pMapOpenCsbNode, WIDGET_INSTANCE_MAP_TYPE_LOCK, nChapter);
		CHECKC(pListItem);
		pListItem->addClickEventListener(CC_CALLBACK_1(LayerInstanceMap::clickMap, this));
		listViewMap->pushBackCustomItem(pListItem);
		m_mapChapterNode.insert(nChapter, pListItem);
	}
	return true;
}

void LayerInstanceMap::clickMap(Ref* pSender)
{
	CHECK(pSender);
	auto nChapter = (dynamic_cast<WidgetInstanceMapInfo*>(pSender))->getChapter();
	CHECK(nChapter);

	// 检测是否能开启

	auto sceneMain = Root::getInstance()->getSceneMain();
	CHECK(sceneMain);
	sceneMain->loadMainView("LayoutInstance");

	auto layerInstanceView = (LayerInstanceView*)sceneMain->getChildByName("LayerInstanceView");
	CHECK(layerInstanceView);
	CHECK(layerInstanceView->updateMap(nChapter));
}