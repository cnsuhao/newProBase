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
#include "Root.h"
#include "../SceneMain.h"
#include "LayerInstanceView.h"

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

	// 初始化数据
	m_nChapter = nChapter;
	m_eMapType = eType;
	auto idInstance = InstanceMgr::getInstance()->getInstanceKey(E_INSTANCE_MODE_TYPE_EASY, nChapter, 1);
	CHECKF(idInstance);
	auto textBMFontNum = dynamic_cast<ui::TextBMFont*>(ui::Helper::seekWidgetByName(this, "TextBMFontNum"));
	CHECKF(textBMFontNum);
	textBMFontNum->setString(StringUtils::format("%d", nChapter));
	m_i64OpenScore = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_instance, idInstance, INSTANCE_DATA_OPEN_SCORE);
	
	// 设置imageview
	auto imageViewBack = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(this, "ImageViewBack"));
	CHECKF(imageViewBack);
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

		imageViewBack->addClickEventListener([=](Ref*){
			auto sceneMain = Root::getInstance()->getSceneMain();
			CHECK(sceneMain);
			sceneMain->loadMainView("LayoutInstance");

			auto layerInstanceView = (LayerInstanceView*)sceneMain->getChildByName("LayerInstanceView");
			CHECK(layerInstanceView);
			CHECK(layerInstanceView->updateMap(m_nChapter));
		});

		CHECKF(ui::Helper::setStringText(this, "TextChapterName", ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_instance, idInstance, INSTANCE_DATA_CHAPTER_NAME)));
	}
	else
	{
		CHECKF(ui::Helper::setDataText(this, "TextOpenScore", m_i64OpenScore));
		imageViewBack->setShaderEffect(MY_SHADER_EFFECT_DARK);
	}
	imageViewBack->setAutoTouchAction();
	imageViewBack->setTouchEnabled(true);
	return true;
}

bool WidgetInstanceMapInfo::updateMapInfo(Node* pCsbNode)
{
	CHECKF(this->init(pCsbNode, WIDGET_INSTANCE_MAP_TYPE_THROUGH, m_nChapter));
	return true;
}

bool WidgetInstanceMapInfo::updateThrough(int nMode)
{
	if (InstanceMgr::getInstance()->isModeThrough(m_nChapter, nMode))
	{
		switch ((E_INSTANCE_MODE_TYPE)nMode)
		{
		case E_INSTANCE_MODE_TYPE_EASY: CHECKF(ui::Helper::setImageViewTexturePlist(this, "ImageViewStarEasy", "res/Instance/InstanceStarLight.png")); break;
		case E_INSTANCE_MODE_TYPE_NORMAL: CHECKF(ui::Helper::setImageViewTexturePlist(this, "ImageViewStarNormal", "res/Instance/InstanceStarLight.png")); break;
		case E_INSTANCE_MODE_TYPE_DIFFICULTY: CHECKF(ui::Helper::setImageViewTexturePlist(this, "ImageViewStarDifficulty", "res/Instance/InstanceStarLight.png")); break;
		default: break;
		}
	}
	return true;
}

bool WidgetInstanceMapInfo::setSearching(bool bSearching)
{
	if (bSearching)
	{
		CHECKF(ui::Helper::setImageViewTexturePlist(this, "ImageViewBack", "res/UiFrame/BoxChoose.png"));
	}
	else
	{
		CHECKF(ui::Helper::setImageViewTexturePlist(this, "ImageViewBack", "res/UiFrame/BoxNormal.png"));
	}
	m_bSearching = bSearching;
	return true;
}
////////////////////////////////////////////////////////////////////////
