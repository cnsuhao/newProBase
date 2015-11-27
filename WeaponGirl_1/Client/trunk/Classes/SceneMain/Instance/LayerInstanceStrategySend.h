////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerInstanceStrategySend.h
// Author: ³Â½¨¾ü(Chen Jianjun)
// Created: 2015-11-26
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_LAYER_INSTANCE_STRATEGY_SEND_H_
#define _JPY_LAYER_INSTANCE_STRATEGY_SEND_H_

#include "Global/Global.h"

class SceneMain;
class LayerInstanceStrategySend : public Layer, public TouchPriorityBase
{
protected:
	virtual ~LayerInstanceStrategySend();
public:
	virtual bool init();
	CREATE_FUNC(LayerInstanceStrategySend);

protected:
	bool	initButtonListen(const std::string& strName, const ui::Widget::ccWidgetClickCallback& callback, bool bLight = false);
	SceneMain* getFather() const { return (SceneMain*)_parent; }
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
};

#endif // end of _JPY_LAYER_INSTANCE_STRATEGY_SEND_H_
