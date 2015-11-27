////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: WidgetPoker.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/11/24
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_WidgetPoker_H_
#define _JPY_WidgetPoker_H_

#include "Global/Global.h"

class Poker;
class WidgetPoker : public ui::Widget
{
protected:
	WidgetPoker();
	virtual ~WidgetPoker();
public:
	static WidgetPoker* create(Node* pCsbNode, DB_KEY idPoker);
	bool init(Node* pCsbNode, DB_KEY idPoker);

	bool isSelected();
	void selectPoker(bool bSelect);

	void setDetail(const std::string& text);
	void setCount(int nCount);

	DB_KEY getPokerID() const{ return m_idPoker; }
	Poker* getPoker() const;
protected:
	DB_KEY m_idPoker;
};

#endif // end of _JPY_WidgetPoker_H_