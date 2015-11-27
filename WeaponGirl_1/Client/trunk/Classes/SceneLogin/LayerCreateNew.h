////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerCreateNew.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/05/24
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_LAYER_CREATE_NEW_H_
#define _JPY_LAYER_CREATE_NEW_H_

#include "Global/Global.h"


class SceneLogin;
class LayerCreateNew : public Layer, public TouchPriorityBase
{
public:
	virtual bool init();
	CREATE_FUNC(LayerCreateNew);

protected:
	void clickOK(Ref* pSender);
	SceneLogin* getFather() const { return (SceneLogin*)_parent; }
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);

protected:
	void clickChooseJob(Ref* pSender);
	void clickRandomName(Ref* pSender);
	void clickCreateUser(Ref* pSender);
};

#endif // end of _JPY_LAYER_CREATE_NEW_H_