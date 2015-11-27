////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: ItemMgr.h
// Author: 陈建军(Chen Jianjun)
// Created: 2015-10-27
////////////////////////////////////////////////////////////////////////
#include "ItemMgr.h"
#include "Root.h"
#include "SceneMain\SceneMain.h"
#include "SceneMain/Item/LayerItemList.h"
#include "MoneyMgr.h"

//////////////////////////////////////////////////////////////////////////
// ItemInfo：物品信息类

////////////////////////////////////////////////////////////////////////
// Description: 创建物品信息
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value: ItemInfo*
////////////////////////////////////////////////////////////////////////
ItemInfo* ItemInfo::createWithMsg(const ITEM_INFO& info)
{
	// 创建一个Node
	auto pItemInfo = new(std::nothrow) ItemInfo();
	if (pItemInfo && pItemInfo->initWithMsg(info))
	{
		return pItemInfo;
	}
	else
	{
		delete pItemInfo;
		pItemInfo = NULL;
		return NULL;
	}
	return pItemInfo;
}

////////////////////////////////////////////////////////////////////////
// Description: 初始化物品信息
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool ItemInfo::initWithMsg(const ITEM_INFO& info)
{
	CHECKF(info.i64ID);
	CHECKF(info.idItemType);

	// 必须存在该物品
	//CHECKF(ConstTableMgr::getInstance()->IsExistSingle(CONST_TABLE_TYPE_item_type, info.idItemType));

	// 保存物品信息
	m_i64ID = info.i64ID;
	this->setData(ITEM_DATA_ID,			info.i64ID);
	this->setData(ITEM_DATA_TYPE,		info.idItemType);
	this->setData(ITEM_DATA_OWNER_ID,	info.idUser);
	this->setData(ITEM_DATA_PARAM,		info.nParam);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 获取物品指定数据
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value: DB_KEY
////////////////////////////////////////////////////////////////////////
DB_KEY ItemInfo::getData(ITEM_DATA eIndex)
{
	auto iter = m_mapData.find(eIndex);
	CHECKF(iter != m_mapData.end());
	return (iter->second);
}

////////////////////////////////////////////////////////////////////////
// Description: 设置物品指定数据
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void ItemInfo::setData(ITEM_DATA eIndex, const DB_KEY& data)
{
	m_mapData[eIndex] = data;
}

//////////////////////////////////////////////////////////////////////////
// ItemMgr：物品信息管理类
//////////////////////////////////////////////////////////////////////////
ItemMgr* ItemMgr::m_pInstance = nullptr;

//////////////////////////////////////////////////////////////////////////
ItemMgr::~ItemMgr()
{
	this->clearItem();
}

//////////////////////////////////////////////////////////////////////////
ItemMgr* ItemMgr::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new ItemMgr();
	}
	return m_pInstance;
}

//////////////////////////////////////////////////////////////////////////
void ItemMgr::destroyInstance()
{
	CC_SAFE_DELETE(m_pInstance);
}

////////////////////////////////////////////////////////////////////////
// Description: 判断物品类型是否正确
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool ItemMgr::IsExistItemType(uint32_t unItemType) const
{
	return (ConstTableMgr::getInstance()->IsExistSingle(CONST_TABLE_TYPE_item_type, unItemType));
}

////////////////////////////////////////////////////////////////////////
// Description: 获取物品的配置信息
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value: DB_KEY
////////////////////////////////////////////////////////////////////////
DB_KEY ItemMgr::getDataByType(uint32_t unItemType, ITEM_TYPE_DATA eIndex) const
{
	CHECKF(eIndex != ITEM_TYPE_DATA_NAME && eIndex != ITEM_TYPE_DATA_DETAIL);
	CHECKF_NOLOG(this->IsExistItemType(unItemType));
	return (ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_item_type, unItemType, eIndex));
}

////////////////////////////////////////////////////////////////////////
// Description: 获取物品的配置字符信息
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value: DB_KEY
////////////////////////////////////////////////////////////////////////
bool ItemMgr::getDataStrByType(uint32_t unItemType, ITEM_TYPE_DATA eIndex, std::string& szDataStr) const
{
	CHECKF(eIndex == ITEM_TYPE_DATA_NAME || eIndex == ITEM_TYPE_DATA_DETAIL);
	szDataStr.assign(ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_item_type, unItemType, eIndex));
	return (true);
}

////////////////////////////////////////////////////////////////////////
// Description: 清空管理器的所有数据
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void ItemMgr::clearItem()
{
	for (auto iter : m_mapItem)
	{
		CC_SAFE_DELETE(iter.second);
	}
	m_mapItem.clear();
}

////////////////////////////////////////////////////////////////////////
// Description: 新增一个物品
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value:  bool
////////////////////////////////////////////////////////////////////////
bool ItemMgr::addItem(const ITEM_INFO& info)
{
	CHECKF(info.i64ID);
	CHECKF(getLeftPackageSize() > 0);

	auto iter = m_mapItem.find(info.i64ID);
	CHECKF(iter == m_mapItem.end());

	auto pItemInfo = ItemInfo::createWithMsg(info);
	CHECKF(pItemInfo);

	// 必须先将数据放入数据池
	m_mapItem.insert(std::make_pair(info.i64ID, pItemInfo));

	// 通知背包界面新增物品
	auto sceneMain = Root::getInstance()->getSceneMain();
	CHECKF_NOLOG(sceneMain);
	auto layerItemList = (LayerItemList*)sceneMain->getChildByName("LayerItemList");
	CHECKF_NOLOG(layerItemList);
	layerItemList->addItem(info.i64ID);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 删除一个物品
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value:  bool
////////////////////////////////////////////////////////////////////////
bool ItemMgr::delItem(OBJID idItem)
{
	CHECKF(idItem);
	auto iter = m_mapItem.find(idItem);
	CHECKF(iter != m_mapItem.end());
	CC_SAFE_DELETE(iter->second);
	
	// 先将数据从数据池中删除
	m_mapItem.erase(idItem);

	// 通知背包界面删除物品
	auto sceneMain = Root::getInstance()->getSceneMain();
	CHECKF_NOLOG(sceneMain);
	auto layerItemList = (LayerItemList*)sceneMain->getChildByName("LayerItemList");
	CHECKF_NOLOG(layerItemList);
	layerItemList->delItem(idItem);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 解锁背包格子
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value:  bool
////////////////////////////////////////////////////////////////////////
bool ItemMgr::expansionPackage()
{
	// 通知背包界面解锁格子
	auto sceneMain = Root::getInstance()->getSceneMain();
	CHECKF_NOLOG(sceneMain);
	auto layerItemList = (LayerItemList*)sceneMain->getChildByName("LayerItemList");
	CHECKF_NOLOG(layerItemList);
	layerItemList->expansionPackage();
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 判断背包是否还能够扩展
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value:  int
////////////////////////////////////////////////////////////////////////
bool ItemMgr::isLockExpansion()
{
	return ((MoneyMgr::getInstance()->getMoney(USER_MONEY_TYPE_ItemMaxBuy) / PACKAGE_EXPANSION_SIZE) >= PACKAGE_EXPANSION_MAX_COUNT);
}

////////////////////////////////////////////////////////////////////////
// Description: 获取背包格子数
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value:  int
////////////////////////////////////////////////////////////////////////
int	ItemMgr::getPackageSize()
{
	return (MoneyMgr::getInstance()->getMoney(USER_MONEY_TYPE_ItemMaxBuy) + PACKAGE_INIT_SIZE);
}

////////////////////////////////////////////////////////////////////////
// Description: 获取剩余格子数量
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value:  int
////////////////////////////////////////////////////////////////////////
int	ItemMgr::getLeftPackageSize()
{
	return (MoneyMgr::getInstance()->getMoney(USER_MONEY_TYPE_ItemMaxBuy) + PACKAGE_INIT_SIZE - m_mapItem.size());
}

////////////////////////////////////////////////////////////////////////
// Description: 获取物品
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value:  ItemInfo* 
////////////////////////////////////////////////////////////////////////
ItemInfo* ItemMgr::getItem(DB_KEY idItem)
{
	CHECKF_NOLOG(idItem);
	auto iter = m_mapItem.find(idItem);
	CHECKF_NOLOG(iter != m_mapItem.end());
	return (iter->second);
}

////////////////////////////////////////////////////////////////////////
// Description: 获取物品容器
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value: const std::map<DB_KEY, ItemInfo*>* 
////////////////////////////////////////////////////////////////////////
const std::map<DB_KEY, ItemInfo*>* ItemMgr::getItems()
{
	return (&m_mapItem);
}

////////////////////////////////////////////////////////////////////////
// Description: 获取所有物品ID
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value:  bool
////////////////////////////////////////////////////////////////////////
void ItemMgr::queryItemKeyVector(OUT VEC_DB_KEY& vecKey)
{
	for (auto i : m_mapItem)
	{
		vecKey.push_back(i.first);
	}
}