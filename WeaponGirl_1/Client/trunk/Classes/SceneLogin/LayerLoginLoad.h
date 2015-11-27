////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerLoginLoad.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/05/26
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_LAYER_LOGIN_LOAD_H_
#define _JPY_LAYER_LOGIN_LOAD_H_

#include "Global/Global.h"

class SceneLogin;
class LayerLoginLoad : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(LayerLoginLoad);

protected:
	SceneLogin* getFather() const { return (SceneLogin*)_parent; }
	CC_SYNTHESIZE_READONLY(ui::Widget*,		m_pCsbWidget,	CsbWidget);
	CC_SYNTHESIZE_READONLY(ui::LoadingBar*, m_loadbar,		LoadBar);
	

public:
	void setPercent(float fPercent);
};

#endif // end of _JPY_LAYER_LOGIN_LOAD_H_