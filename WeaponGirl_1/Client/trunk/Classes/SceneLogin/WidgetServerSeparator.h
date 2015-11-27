////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: WidgetServerSeparator.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/10/10
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_WidgetServerSeparator_H_
#define _JPY_WidgetServerSeparator_H_

#include "Global/Global.h"

class WidgetServerSeparator : public ui::Widget
{
protected:
	WidgetServerSeparator();
	virtual ~WidgetServerSeparator();
public:
	static WidgetServerSeparator* create(Node* pCsbNode, const std::string& text = "");
	bool init(Node* pCsbNode, const std::string& text);
};

#endif // end of _JPY_WidgetServerSeparator_H_