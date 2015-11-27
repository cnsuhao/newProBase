////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: WidgetInstanceViewInfo.h
// Author: ³Â½¨¾ü(Chen Jianjun)
// Created: 2015-11-19
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_WIDGET_INSTANCE_VIEW_INFO_H_
#define _JPY_WIDGET_INSTANCE_VIEW_INFO_H_

#include "Global/Global.h"

class WidgetInstanceViewInfo : public ui::Widget
{
protected:
	WidgetInstanceViewInfo();
	virtual ~WidgetInstanceViewInfo();
public:
	static WidgetInstanceViewInfo* create(int nChapter, const std::string& strCsbName);
	bool	init(int nChapter, const std::string& strCsbName);
	bool	updateMap(int nChapter, const std::string& strCsbName);

	bool	changeMode(int nMode);
	bool	changePass(int nPass);
	bool	winPass(int nPass);

protected:
	bool	cancelPass(int nPass);
	bool	selectPass(int nPass);

	ui::Widget*	getPassView(int nPassIndex);
protected:
	CC_SYNTHESIZE_READONLY(int,		m_nSelectChapter,   SelectChapter);
	CC_SYNTHESIZE_READONLY(int,		m_nSelectMode,		SelectMode);
	CC_SYNTHESIZE_READONLY(int,		m_nSelectPass,		SelectPass);
};

#endif // end of _JPY_WIDGET_INSTANCE_VIEW_INFO_H_