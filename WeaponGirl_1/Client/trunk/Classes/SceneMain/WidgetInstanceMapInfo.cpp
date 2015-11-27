////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: WidgetInstanceMapInfo.cpp
// Author: 陈建军(Chen Jianjun)
// Created: 2015-11-19
////////////////////////////////////////////////////////////////////////
#include "WidgetInstanceMapInfo.h"
#include "Mgr\InstanceMgr.h"
#include "LayerInstanceMap.h"
#include "ConstTable\ConstTableMgr.h"

//////////////////////////////////////////////////////////////////////////
WidgetInstanceMapInfo::WidgetInstanceMapInfo()
{
	m_nChapter = 0;
}

//////////////////////////////////////////////////////////////////////////
WidgetInstanceMapInfo::~WidgetInstanceMapInfo()
{

}

//////////////////////////////////////////////////////////////////////////
WidgetInstanceMapInfo* WidgetInstanceMapInfo::create(Node* pCsbNode, WIDGET_INSTANCE_MAP_TYPE eType, int nChapter)
{
	WidgetInstanceMapInfo* pRet = new(std::nothrow) WidgetInstanceMapInfo();
	if (pRet && pRet->init(pCsbNode, eType, nChapter))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

//////////////////////////////////////////////////////////////////////////
bool WidgetInstanceMapInfo::init(Node* pCsbNode, WIDGET_INSTANCE_MAP_TYPE eType, int nChapter)
{
	CHECKF(pCsbNode);
	CHECKF(nChapter);

	auto csbLayout = (ui::Widget*)pCsbNode->getChildByName("Layout");
	this->copyProperties(csbLayout);
	this->copyClonedWidgetChildren(csbLayout);

	// 设置章节名
	m_nChapter = nChapter;
	auto idInstance = InstanceMgr::getInstance()->getInstanceKey(E_INSTANCE_MODE_TYPE_EASY, nChapter, 1);
	CHECKF(idInstance);
	CHECKF(ui::Helper::setStringText(this, "TextChapterName", ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_instance, idInstance, INSTANCE_DATA_CHAPTER_NAME)));
	auto textBMFontNum = dynamic_cast<ui::TextBMFont*>(ui::Helper::seekWidgetByName(this, "TextBMFontNum"));
	CHECKF(textBMFontNum);
	textBMFontNum->setString(StringUtils::format("%d", nChapter));

	// 根据类型初始化各项数据
	if (WIDGET_INSTANCE_MAP_TYPE_THROUGH == eType)
	{
		if (InstanceMgr::getInstance()->isModeThrough(m_nChapter, E_INSTANCE_MODE_TYPE_EASY))
		{
			CHECKF(ui::Helper::setImageViewTexturePlist(this, "ImageViewStarEasy", "res/Instance/InstanceStarLight.png"));
		}

		if (InstanceMgr::getInstance()->isModeThrough(m_nChapter, E_INSTANCE_MODE_TYPE_NORMAL))
		{
			CHECKF(ui::Helper::setImageViewTexturePlist(this, "ImageViewStarNormal", "res/Instance/InstanceStarLight.png"));
		}

		if (InstanceMgr::getInstance()->isModeThrough(m_nChapter, E_INSTANCE_MODE_TYPE_DIFFICULTY))
		{
			CHECKF(ui::Helper::setImageViewTexturePlist(this, "ImageViewStarDifficulty", "res/Instance/InstanceStarLight.png"));
		}
	}
	else
	{
		if (WIDGET_INSTANCE_MAP_TYPE_OPEN == eType)
		{
			CHECKF(ui::Helper::setImageViewTexturePlist(this, "ImageViewBack", "res/Instance/InstanceMapChapterBox_1.png"));
		}
		CHECKF(ui::Helper::setDataText(this, "TextOpenScore", ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_instance, idInstance, INSTANCE_DATA_OPEN_SCORE)));
	}
	return true;
}
////////////////////////////////////////////////////////////////////////
