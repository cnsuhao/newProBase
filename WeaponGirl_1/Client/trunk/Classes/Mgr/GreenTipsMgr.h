////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: GreenTipsMgr.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/11/20
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_GreenTipsMgr_H_
#define _JYP_GreenTipsMgr_H_

#include "Global/Global.h"

class GreenTipsMgr : public Ref
{
public:
	static GreenTipsMgr*	getInstance();
	static void		destroyInstance();
private:
	GreenTipsMgr();
	static GreenTipsMgr*	m_pInstance;

public:
	bool isHaveTips(GREEN_TIPS_TYPE eType) const;

protected:


};

#endif // end of _JYP_GreenTipsMgr_H_