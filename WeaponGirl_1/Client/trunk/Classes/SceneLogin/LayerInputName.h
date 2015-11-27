////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerInputName.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/05/22
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_LAYER_INPUT_NAME_H_
#define _JPY_LAYER_INPUT_NAME_H_

#include "Global/Global.h"

class SceneLogin;
class LayerInputName : public Layer, public TouchPriorityBase
{
public:
	virtual bool init();
	CREATE_FUNC(LayerInputName);

protected:
	void clickOK(Ref* pSender);
	SceneLogin* getFather() const { return (SceneLogin*)_parent; }
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);

};

#endif // end of _JPY_LAYER_INPUT_NAME_H_