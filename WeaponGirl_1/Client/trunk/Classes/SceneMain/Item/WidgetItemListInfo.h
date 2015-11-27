////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: WidgetItemListInfo.h
// Author: 陈建军(Chen Jianjun)
// Created: 2015-10-28
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_WIDGET_ITEM_LIST_INFO_H_
#define _JPY_WIDGET_ITEM_LIST_INFO_H_

#include "Global/Global.h"

enum WIDGET_ITEM_TYPE
{
	WIDGET_ITEM_TYPE_EXPASION,	// 解锁按钮	
	WIDGET_ITEM_TYPE_NONE,		// 空
	WIDGET_ITEM_TYPE_ITEM,		// 物品
};

class WidgetItemListInfo : public ui::Widget
{
protected:
	WidgetItemListInfo();
	virtual ~WidgetItemListInfo();
public:
	static WidgetItemListInfo* create(Node* pCsbNode, WIDGET_ITEM_TYPE eType, DB_KEY idItem);
	bool init(Node* pCsbNode, WIDGET_ITEM_TYPE eType, DB_KEY idItem);
	bool setItemData(WIDGET_ITEM_TYPE eType, DB_KEY idItem);
	bool isSelected() const;
	void setSelected(bool bSelected);

	bool isNone()			{ return m_eType == WIDGET_ITEM_TYPE_NONE; }
	bool isItem()			{ return m_eType == WIDGET_ITEM_TYPE_ITEM; }
	bool isExpasionButton() { return m_eType == WIDGET_ITEM_TYPE_EXPASION;  }

protected:
	CC_SYNTHESIZE_READONLY(WIDGET_ITEM_TYPE, m_eType, Type);
	CC_SYNTHESIZE_READONLY(DB_KEY, m_id, ID);
};

#endif // end of _JPY_WIDGET_ITEM_LIST_INFO_H_