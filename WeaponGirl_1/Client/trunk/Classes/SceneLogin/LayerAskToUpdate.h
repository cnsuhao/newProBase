////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerAskToUpdate.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/10/19
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_LayerAskToUpdate_H_
#define _JPY_LayerAskToUpdate_H_

#include "Global/Global.h"

typedef std::function<void()> UpdateListener;
class LayerAskToUpdate : public Layer
{
public:
	static LayerAskToUpdate* create(int totalSize, const UpdateListener& listen);
	bool init(int totalSize, const UpdateListener& listen);

	void clickCancel(Ref* pSender);
	void clickOK(Ref* pSender);


protected:
	UpdateListener m_listener;
	CC_SYNTHESIZE_READONLY(ui::Widget*, m_pCsbWidget, CsbWidget);
};

#endif // end of _JPY_LayerAskToUpdate_H_