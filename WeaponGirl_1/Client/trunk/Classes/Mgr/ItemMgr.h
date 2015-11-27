////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: ItemMgr.h
// Author: 陈建军(Chen Jianjun)
// Created: 2015-10-27
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_MGR_ITEM_MGR_H_
#define _JYP_MGR_ITEM_MGR_H_

#include "Global/Global.h"
#include "ConstTable/ConstTableDefine.h"

// 物品表
enum ITEM_DATA
{
	ITEM_DATA_ID = 0,			// 物品id		bigint
	ITEM_DATA_TYPE,				// 物品类型		uint
	ITEM_DATA_OWNER_ID,			// 归属者id		uint
	ITEM_DATA_PARAM,			// 参数			uint
	ITEM_DATA_END,
};

class ItemInfo
{
protected:
	ItemInfo() : m_i64ID(0) {}

public:
	~ItemInfo() {};
	static ItemInfo* createWithMsg(const ITEM_INFO& info);
	bool	initWithMsg	(const ITEM_INFO& info);

public:
	DB_KEY	getData		(ITEM_DATA eIndex);

protected:
	void	setData		(ITEM_DATA eIndex, const DB_KEY& data);

protected:
	std::map<ITEM_DATA, DB_KEY>			m_mapData;
	CC_SYNTHESIZE_READONLY(int64_t,		m_i64ID,	ID);
};

typedef std::vector<ItemInfo*>		VEC_ITEMINFO_LIST;
typedef std::function<void(DB_KEY)> CallbackItemDataChange;

class ItemMgr : public Ref
{
public:
	static ItemMgr*	getInstance();
	static void		destroyInstance();
	virtual ~ItemMgr();
private:
	ItemMgr() {}
	static ItemMgr*	m_pInstance;

public:
	ui::Widget* getNodeItemIconWidget();
	ui::Widget* getNodeItemBlankWidget();

public:
	bool	IsExistItemType		(uint32_t unItemType) const;
	DB_KEY	getDataByType		(uint32_t unItemType, ITEM_TYPE_DATA eIndex) const;
	bool	getDataStrByType	(uint32_t unItemType, ITEM_TYPE_DATA eIndex, std::string& szDataStr) const;

	void	clearItem			();
	bool	addItem				(const ITEM_INFO& info);
	bool	delItem				(OBJID idItem);
	bool	expansionPackage	();
	bool	isLockExpansion		();
	int		getPackageSize		();
	int		getLeftPackageSize	();
	int		getItemCount() { return m_mapItem.size(); }

	ItemInfo* getItem(DB_KEY idItem);
	const std::map<DB_KEY, ItemInfo*>* getItems();
	void	queryItemKeyVector	(OUT VEC_DB_KEY& vecKey);

protected:
	std::map<DB_KEY, ItemInfo*> m_mapItem;
};

#endif // end of _JYP_MGR_ITEM_MGR_H_