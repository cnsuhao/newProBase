////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerMoneyAddHint.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/10/19
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_LAYER_LayerMoneyAddHint_H_
#define _JPY_LAYER_LayerMoneyAddHint_H_

#include "Global/Global.h"


class LayerMoneyAddHint : public Layer
{
public:
	static LayerMoneyAddHint* create(USER_MONEY_TYPE eType, int64_t addData);
	virtual bool init(USER_MONEY_TYPE eType, int64_t addData);

protected:
	CC_SYNTHESIZE_READONLY(ui::Widget*, m_pCsbWidget, CsbWidget);
};

void MoneyAddHint(USER_MONEY_TYPE eType, int64_t addData);

#endif // end of _JPY_LAYER_LayerMoneyAddHint_H_