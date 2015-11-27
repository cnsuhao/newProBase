////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: ItemMgr.h
// Author: �½���(Chen Jianjun)
// Created: 2015-10-27
////////////////////////////////////////////////////////////////////////
#include "ItemMgr.h"
#include "Root.h"
#include "SceneMain\SceneMain.h"
#include "SceneMain/Item/LayerItemList.h"
#include "MoneyMgr.h"

//////////////////////////////////////////////////////////////////////////
// ItemInfo����Ʒ��Ϣ��

////////////////////////////////////////////////////////////////////////
// Description: ������Ʒ��Ϣ
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: ItemInfo*
////////////////////////////////////////////////////////////////////////
ItemInfo* ItemInfo::createWithMsg(const ITEM_INFO& info)
{
	// ����һ��Node
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
// Description: ��ʼ����Ʒ��Ϣ
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool ItemInfo::initWithMsg(const ITEM_INFO& info)
{
	CHECKF(info.i64ID);
	CHECKF(info.idItemType);

	// ������ڸ���Ʒ
	//CHECKF(ConstTableMgr::getInstance()->IsExistSingle(CONST_TABLE_TYPE_item_type, info.idItemType));

	// ������Ʒ��Ϣ
	m_i64ID = info.i64ID;
	this->setData(ITEM_DATA_ID,			info.i64ID);
	this->setData(ITEM_DATA_TYPE,		info.idItemType);
	this->setData(ITEM_DATA_OWNER_ID,	info.idUser);
	this->setData(ITEM_DATA_PARAM,		info.nParam);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: ��ȡ��Ʒָ������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: DB_KEY
////////////////////////////////////////////////////////////////////////
DB_KEY ItemInfo::getData(ITEM_DATA eIndex)
{
	auto iter = m_mapData.find(eIndex);
	CHECKF(iter != m_mapData.end());
	return (iter->second);
}

////////////////////////////////////////////////////////////////////////
// Description: ������Ʒָ������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void ItemInfo::setData(ITEM_DATA eIndex, const DB_KEY& data)
{
	m_mapData[eIndex] = data;
}

//////////////////////////////////////////////////////////////////////////
// ItemMgr����Ʒ��Ϣ������
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
// Description: �ж���Ʒ�����Ƿ���ȷ
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool ItemMgr::IsExistItemType(uint32_t unItemType) const
{
	return (ConstTableMgr::getInstance()->IsExistSingle(CONST_TABLE_TYPE_item_type, unItemType));
}

////////////////////////////////////////////////////////////////////////
// Description: ��ȡ��Ʒ��������Ϣ
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: DB_KEY
////////////////////////////////////////////////////////////////////////
DB_KEY ItemMgr::getDataByType(uint32_t unItemType, ITEM_TYPE_DATA eIndex) const
{
	CHECKF(eIndex != ITEM_TYPE_DATA_NAME && eIndex != ITEM_TYPE_DATA_DETAIL);
	CHECKF_NOLOG(this->IsExistItemType(unItemType));
	return (ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_item_type, unItemType, eIndex));
}

////////////////////////////////////////////////////////////////////////
// Description: ��ȡ��Ʒ�������ַ���Ϣ
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: DB_KEY
////////////////////////////////////////////////////////////////////////
bool ItemMgr::getDataStrByType(uint32_t unItemType, ITEM_TYPE_DATA eIndex, std::string& szDataStr) const
{
	CHECKF(eIndex == ITEM_TYPE_DATA_NAME || eIndex == ITEM_TYPE_DATA_DETAIL);
	szDataStr.assign(ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_item_type, unItemType, eIndex));
	return (true);
}

////////////////////////////////////////////////////////////////////////
// Description: ��չ���������������
// Arguments:
// Author: �½���(Chen Jianjun)
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
// Description: ����һ����Ʒ
// Arguments:
// Author: �½���(Chen Jianjun)
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

	// �����Ƚ����ݷ������ݳ�
	m_mapItem.insert(std::make_pair(info.i64ID, pItemInfo));

	// ֪ͨ��������������Ʒ
	auto sceneMain = Root::getInstance()->getSceneMain();
	CHECKF_NOLOG(sceneMain);
	auto layerItemList = (LayerItemList*)sceneMain->getChildByName("LayerItemList");
	CHECKF_NOLOG(layerItemList);
	layerItemList->addItem(info.i64ID);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: ɾ��һ����Ʒ
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value:  bool
////////////////////////////////////////////////////////////////////////
bool ItemMgr::delItem(OBJID idItem)
{
	CHECKF(idItem);
	auto iter = m_mapItem.find(idItem);
	CHECKF(iter != m_mapItem.end());
	CC_SAFE_DELETE(iter->second);
	
	// �Ƚ����ݴ����ݳ���ɾ��
	m_mapItem.erase(idItem);

	// ֪ͨ��������ɾ����Ʒ
	auto sceneMain = Root::getInstance()->getSceneMain();
	CHECKF_NOLOG(sceneMain);
	auto layerItemList = (LayerItemList*)sceneMain->getChildByName("LayerItemList");
	CHECKF_NOLOG(layerItemList);
	layerItemList->delItem(idItem);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: ������������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value:  bool
////////////////////////////////////////////////////////////////////////
bool ItemMgr::expansionPackage()
{
	// ֪ͨ���������������
	auto sceneMain = Root::getInstance()->getSceneMain();
	CHECKF_NOLOG(sceneMain);
	auto layerItemList = (LayerItemList*)sceneMain->getChildByName("LayerItemList");
	CHECKF_NOLOG(layerItemList);
	layerItemList->expansionPackage();
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: �жϱ����Ƿ��ܹ���չ
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value:  int
////////////////////////////////////////////////////////////////////////
bool ItemMgr::isLockExpansion()
{
	return ((MoneyMgr::getInstance()->getMoney(USER_MONEY_TYPE_ItemMaxBuy) / PACKAGE_EXPANSION_SIZE) >= PACKAGE_EXPANSION_MAX_COUNT);
}

////////////////////////////////////////////////////////////////////////
// Description: ��ȡ����������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value:  int
////////////////////////////////////////////////////////////////////////
int	ItemMgr::getPackageSize()
{
	return (MoneyMgr::getInstance()->getMoney(USER_MONEY_TYPE_ItemMaxBuy) + PACKAGE_INIT_SIZE);
}

////////////////////////////////////////////////////////////////////////
// Description: ��ȡʣ���������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value:  int
////////////////////////////////////////////////////////////////////////
int	ItemMgr::getLeftPackageSize()
{
	return (MoneyMgr::getInstance()->getMoney(USER_MONEY_TYPE_ItemMaxBuy) + PACKAGE_INIT_SIZE - m_mapItem.size());
}

////////////////////////////////////////////////////////////////////////
// Description: ��ȡ��Ʒ
// Arguments:
// Author: �½���(Chen Jianjun)
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
// Description: ��ȡ��Ʒ����
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: const std::map<DB_KEY, ItemInfo*>* 
////////////////////////////////////////////////////////////////////////
const std::map<DB_KEY, ItemInfo*>* ItemMgr::getItems()
{
	return (&m_mapItem);
}

////////////////////////////////////////////////////////////////////////
// Description: ��ȡ������ƷID
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value:  bool
////////////////////////////////////////////////////////////////////////
void ItemMgr::queryItemKeyVector(OUT VEC_DB_KEY& vecKey)
{
	for (auto i : m_mapItem)
	{
		vecKey.push_back(i.first);
	}
}