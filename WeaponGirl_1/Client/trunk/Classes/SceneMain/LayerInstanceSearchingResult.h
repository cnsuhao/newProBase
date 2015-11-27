////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerInstanceSearchingResult.h
// Author: ³Â½¨¾ü(Chen Jianjun)
// Created: 2015-11-21
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_LAYER_INSTANCE_SEARCHING_RESULT_H_
#define _JPY_LAYER_INSTANCE_SEARCHING_RESULT_H_

#include "Global/Global.h"

class SceneMain;
class LayerInstanceSearchingResult : public Layer, public TouchPriorityBase
{
protected:
	virtual ~LayerInstanceSearchingResult();
public:
	virtual bool init();
	CREATE_FUNC(LayerInstanceSearchingResult);

protected:
	bool initButtonListen(const std::string& strName, const ui::Widget::ccWidgetClickCallback& callback);
	SceneMain* getFather() const { return (SceneMain*)_parent; }
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
};

#endif // end of _JPY_LAYER_INSTANCE_SEARCHING_RESULT_H_
