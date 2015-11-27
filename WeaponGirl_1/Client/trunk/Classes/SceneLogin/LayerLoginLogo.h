////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerLoginLogo.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/10/12
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_CONST_LayerLoginLogo_
#define _JYP_CONST_LayerLoginLogo_

#include "Global/Global.h"

class SceneLogin;
class LayerLoginLogo : public Layer, public TouchPriorityBase
{
public:
	virtual bool init();
	CREATE_FUNC(LayerLoginLogo);

protected:
	SceneLogin* getFather() const { return (SceneLogin*)_parent; }
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
};


#endif // end of _JYP_CONST_LayerLoginLogo_