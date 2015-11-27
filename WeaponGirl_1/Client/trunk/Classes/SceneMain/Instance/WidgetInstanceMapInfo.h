////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: WidgetInstanceMapInfo.h
// Author: 陈建军(Chen Jianjun)
// Created: 2015-11-20
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_WIDGET_INSTANCE_MAP_INFO_H_
#define _JPY_WIDGET_INSTANCE_MAP_INFO_H_

#include "Global/Global.h"

enum WIDGET_INSTANCE_MAP_TYPE
{
	WIDGET_INSTANCE_MAP_TYPE_THROUGH,	// 通过	
	WIDGET_INSTANCE_MAP_TYPE_LOCK,		// 已锁
};
class WidgetInstanceMapInfo : public ui::Widget
{
protected:
	WidgetInstanceMapInfo();
	virtual ~WidgetInstanceMapInfo();
public:
	static WidgetInstanceMapInfo* create(Node* pCsbNode, WIDGET_INSTANCE_MAP_TYPE eType, int nChapter);
	bool	init(Node* pCsbNode, WIDGET_INSTANCE_MAP_TYPE eType, int nChapter);

	bool	updateMapInfo(Node* pCsbNode);
	bool	updateThrough(int nMode);
	bool	setSearching(bool bSearching);
protected:
	CC_SYNTHESIZE_READONLY(int,	m_nChapter,	Chapter);
	CC_SYNTHESIZE_READONLY(WIDGET_INSTANCE_MAP_TYPE,	m_eMapType,		MapType);
	CC_SYNTHESIZE_READONLY(int64_t,		m_i64OpenScore,		OpenScore);
	CC_SYNTHESIZE_READONLY(bool,		m_bSearching,		Searching);
};

#endif // end of _JPY_WIDGET_INSTANCE_MAP_INFO_H_