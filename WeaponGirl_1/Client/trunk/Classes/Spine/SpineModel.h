////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: SpineModel.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/10/19
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_SPINE_MODEL_H_
#define _JYP_SPINE_MODEL_H_

#include "Global/Global.h"
#include "Spine/SpineBase.h"

class SpineModel : public SpineBase
{
public:
	static SpineModel* createWithPokerType(OBJID idPokerType);

protected:
	bool initWithPokerType(OBJID idPokerType);

	SpineModel();
	virtual ~SpineModel();


protected:
	CC_SYNTHESIZE_READONLY(OBJID, m_idPokerType, PokerType);
};

#endif // end of _JYP_SPINE_MODEL_H_