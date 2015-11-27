////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerHint.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/7/7
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_LAYER_HINT_H_
#define _JPY_LAYER_HINT_H_

#include "Global/Global.h"


class LayerHint : public Layer
{
public:
	static LayerHint* create(const std::string& strHint, Color4B textColor = Color4B::WHITE);
	virtual bool init(const std::string& strHint, Color4B textColor);

	static void runShowAction(LayerHint* layerHint);

protected:
	CC_SYNTHESIZE_READONLY(ui::Widget*, m_pCsbWidget, CsbWidget);
};

void AddHint(const std::string& strHint, Scene* fatherScene = nullptr);

#endif // end of _JPY_LAYER_HINT_H_