////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerPokerView.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/11/24
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_LayerPokerView_H_
#define _JPY_LayerPokerView_H_

#include "Global/Global.h"

class SceneMain;
class LayerPokerView : public Layer, public TouchPriorityBase
{
protected:
	virtual ~LayerPokerView();
public:
	virtual bool init();
	CREATE_FUNC(LayerPokerView);

public:
	void clickMyPoker(Ref* pSender);
	void clickFightGroup(Ref* pSender);
	void clickDistractAbility(Ref* pSender);
	void clickDelete(Ref* pSender);
	void clickBossWeapon(Ref* pSender);

protected:
	SceneMain* getFather() const { return (SceneMain*)_parent; }
	virtual bool onTouchBegan(Touch *touch, Event *unused_event) { return false; }	// View类不吞事件
};

#endif // end of _JPY_LayerPokerView_H_
