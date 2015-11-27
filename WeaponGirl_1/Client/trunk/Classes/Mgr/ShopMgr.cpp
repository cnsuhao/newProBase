////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: ShopMgr.cpp
// Author: 陈建军(Chen Jianjun)
// Created: 2015-11-3
////////////////////////////////////////////////////////////////////////
#include "ShopMgr.h"
#include "Root.h"

ShopMgr* ShopMgr::m_pInstance = nullptr;
//////////////////////////////////////////////////////////////////////////
ShopMgr* ShopMgr::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new ShopMgr();
	}
	return m_pInstance;
}

//////////////////////////////////////////////////////////////////////////
void ShopMgr::destroyInstance()
{

}

//////////////////////////////////////////////////////////////////////////
ShopMgr::ShopMgr()
{

}

////////////////////////////////////////////////////////////////////////
// Description: 根据商店类型获取商品类型key
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value:  bool
////////////////////////////////////////////////////////////////////////
bool ShopMgr::getShopGoodsList(E_SHOP_TYPE eType, VEC_DB_KEY& vecGoodsList)
{
	vecGoodsList.clear();

	VEC_DB_KEY	vecKey;
	ConstTableMgr::getInstance()->EnumKey(CONST_TABLE_TYPE_shop_goods, vecKey);
	for (auto iterKey : vecKey)
	{
		if (eType == (E_SHOP_TYPE)ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_shop_goods, iterKey, SHOP_GOODS_DATA_SHOP_TYPE))
		{
			vecGoodsList.push_back(iterKey);
		}
	}
	return true;
}