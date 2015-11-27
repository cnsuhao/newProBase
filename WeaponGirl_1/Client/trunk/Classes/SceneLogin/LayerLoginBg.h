////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerLoginBg.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/05/22
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_LAYER_LOGIN_BG_H_
#define _JPY_LAYER_LOGIN_BG_H_

#include "Global/Global.h"


class SceneLogin;
class LayerLoginBg : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(LayerLoginBg);

public:
	void sendReqLogin();

protected:
	SceneLogin* getFather() const { return (SceneLogin*)_parent; }

protected:
	CC_SYNTHESIZE_READONLY(ui::Widget*, m_pCsbWidget, CsbWidget);
};

#endif // end of _JPY_LAYER_LOGIN_BG_H_