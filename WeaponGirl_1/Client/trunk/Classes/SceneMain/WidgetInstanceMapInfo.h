////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: WidgetInstanceMapInfo.h
// Author: �½���(Chen Jianjun)
// Created: 2015-11-20
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_WIDGET_INSTANCE_MAP_INFO_H_
#define _JPY_WIDGET_INSTANCE_MAP_INFO_H_

#include "Global/Global.h"

enum WIDGET_INSTANCE_MAP_TYPE
{
	WIDGET_INSTANCE_MAP_TYPE_THROUGH,	// ͨ��	
	WIDGET_INSTANCE_MAP_TYPE_OPEN,		// ����
	WIDGET_INSTANCE_MAP_TYPE_LOCK,		// ����
};
class WidgetInstanceMapInfo : public ui::Widget
{
protected:
	WidgetInstanceMapInfo();
	virtual ~WidgetInstanceMapInfo();
public:
	static WidgetInstanceMapInfo* create(Node* pCsbNode, WIDGET_INSTANCE_MAP_TYPE eType, int nChapter);
	bool	init(Node* pCsbNode, WIDGET_INSTANCE_MAP_TYPE eType, int nChapter);

protected:
	CC_SYNTHESIZE_READONLY(int,	m_nChapter,	Chapter);
};

#endif // end of _JPY_WIDGET_INSTANCE_MAP_INFO_H_