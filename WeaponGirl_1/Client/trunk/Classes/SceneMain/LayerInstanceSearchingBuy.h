////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerInstanceSearchingBuy.h
// Author: ³Â½¨¾ü(Chen Jianjun)
// Created: 2015-11-21
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_LAYER_INSTANCE_SEARCHING_BUY_H_
#define _JPY_LAYER_INSTANCE_SEARCHING_BUY_H_

#include "Global/Global.h"

class SceneMain;
class LayerInstanceSearchingBuy : public Layer, public TouchPriorityBase
{
protected:
	virtual ~LayerInstanceSearchingBuy();
public:
	virtual bool init();
	CREATE_FUNC(LayerInstanceSearchingBuy);

	bool	addBuyNum();
	bool	decBuyNum();

protected:
	bool initButtonListen(const std::string& strName, const ui::Widget::ccWidgetClickCallback& callback);
	int		m_nBuyNum;
	SceneMain* getFather() const { return (SceneMain*)_parent; }
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
};

#endif // end of _JPY_LAYER_INSTANCE_SEARCHING_BUY_H_
