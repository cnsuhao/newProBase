////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: WidgetItemListInfo.cpp
// Author: 陈建军(Chen Jianjun)
// Created: 2015-10-28
////////////////////////////////////////////////////////////////////////
#include "WidgetItemListInfo.h"
#include "Mgr\ItemMgr.h"

//////////////////////////////////////////////////////////////////////////
WidgetItemListInfo::WidgetItemListInfo()
{
	m_id = ID_NONE;
}

//////////////////////////////////////////////////////////////////////////
WidgetItemListInfo::~WidgetItemListInfo()
{

}

//////////////////////////////////////////////////////////////////////////
WidgetItemListInfo* WidgetItemListInfo::create(Node* pCsbNode, WIDGET_ITEM_TYPE eType, DB_KEY idItem)
{
	WidgetItemListInfo* pRet = new(std::nothrow) WidgetItemListInfo();
	if (pRet && pRet->init(pCsbNode, eType, idItem))
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
bool WidgetItemListInfo::init(Node* pCsbNode, WIDGET_ITEM_TYPE eType, DB_KEY idItem)
{
	// 根据csb加载基础
	auto csbLayout = (ui::Widget*)pCsbNode->getChildByName("Layout");

	this->copyProperties(csbLayout);
	this->copyClonedWidgetChildren(csbLayout);

	CHECKF(this->setItemData(eType, idItem));

	// 初始未被选中
	auto imageViewFrame = (ui::ImageView*)this->getChildByName("ImageViewFrame");
	CHECKF(imageViewFrame);
	//imageViewFrame->loadTexture("item/100002.png", Widget::TextureResType::PLIST);
	imageViewFrame->setVisible(false);
	return true;
}

bool WidgetItemListInfo::setItemData(WIDGET_ITEM_TYPE eType, DB_KEY idItem)
{
	m_eType = eType;
	m_id	= idItem;

	if (eType == WIDGET_ITEM_TYPE_NONE)
	{
		auto imageViewIcon = (ui::ImageView*)this->getChildByName("ImageViewIcon");
		CHECKF(imageViewIcon);
		imageViewIcon->loadTexture(::getLookfaceFileName(1001), Widget::TextureResType::PLIST);
	}
	else if (eType == WIDGET_ITEM_TYPE_ITEM)
	{
		CHECKF(idItem);
		auto pItemInfo = ItemMgr::getInstance()->getItem(idItem);
		CHECKF(pItemInfo);

		auto imageViewIcon = (ui::ImageView*)this->getChildByName("ImageViewIcon");
		CHECKF(imageViewIcon);
		imageViewIcon->loadTexture(::getItemIconFileName(pItemInfo->getData(ITEM_DATA_TYPE)), Widget::TextureResType::PLIST);
		//imageViewIcon->setShaderEffect(MY_SHADER_EFFECT_DOT);
	}
	else if (eType == WIDGET_ITEM_TYPE_EXPASION)
	{
		auto imageViewIcon = (ui::ImageView*)this->getChildByName("ImageViewIcon");
		CHECKF(imageViewIcon);
		imageViewIcon->loadTexture(::getLookfaceFileName(1003), Widget::TextureResType::PLIST);
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool WidgetItemListInfo::isSelected() const
{
	auto imageViewFrame = (ui::ImageView*)this->getChildByName("ImageViewFrame");
	CHECKF(imageViewFrame);
	return imageViewFrame->isVisible();
}

//////////////////////////////////////////////////////////////////////////
void WidgetItemListInfo::setSelected(bool bSelected)
{
	auto imageViewFrame = (ui::ImageView*)this->getChildByName("ImageViewFrame");
	CHECK(imageViewFrame);
	//imageViewFrame->setVisible(bSelected);
}

