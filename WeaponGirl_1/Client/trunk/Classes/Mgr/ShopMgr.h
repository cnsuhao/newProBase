////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: ShopMgr.h
// Author: ³Â½¨¾ü(Chen Jianjun)
// Created: 2015-11-3
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_SHOP_MGR_H_
#define _JYP_SHOP_MGR_H_

#include "Global/Global.h"

class ShopMgr : public Ref
{
public:
	static ShopMgr*	getInstance();
	static void		destroyInstance();
private:
	ShopMgr();
	static ShopMgr*	m_pInstance;

public:
	bool	getShopGoodsList(E_SHOP_TYPE eType, VEC_DB_KEY& vecGoodsList);

};

#endif // end of _JYP_SHOP_MGR_H_