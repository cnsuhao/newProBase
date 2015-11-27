////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: WidgetServerInfo.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/10/10
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_WidgetServerInfo_H_
#define _JPY_WidgetServerInfo_H_

#include "Global/Global.h"

class WidgetServerInfo : public ui::Widget
{
protected:
	WidgetServerInfo();
	virtual ~WidgetServerInfo();
public:
	static WidgetServerInfo* create(Node* pCsbNode, OBJID idServer);
	bool init(Node* pCsbNode, OBJID idServer);
	CC_SYNTHESIZE_READONLY(OBJID, m_idServer, ServerID);
};

#endif // end of _JPY_WidgetServerInfo_H_