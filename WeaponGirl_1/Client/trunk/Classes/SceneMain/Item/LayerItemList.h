////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerItemList.h
// Author: 陈建军(Chen Jianjun)
// Created: 2015-10-27
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_LAYER_ITEM_LIST_H_
#define _JPY_LAYER_ITEM_LIST_H_

#include "Global/Global.h"

struct ST_SORT_ITEM_INFO	// 物品排序结构体
{
	DB_KEY idItem;
	int	   nCellType;
	int	   nIndex;
};

class SceneMain;
class WidgetItemListInfo;
class LayerItemList : public Layer, public TouchPriorityBase
{
protected:
	virtual ~LayerItemList();
public:
	virtual bool init();
	CREATE_FUNC(LayerItemList);

	bool	addItem(DB_KEY idItem);
	bool	delItem(DB_KEY idItem);
	bool	expansionPackage();

protected:
	DB_KEY	m_selectId;
	Node*	m_pItemCsbNode;
	std::vector<WidgetItemListInfo*> m_pItemListInfo;
	SceneMain* getFather() const { return (SceneMain*)_parent; }
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
	void	selectedItemListEvent(Ref* pSender);
	bool	selectItem(DB_KEY idItem);
	void	refreshUIAttr(DB_KEY idItem);
	void	popItemListExpansion();
	void	sortItem();
	bool	addPakageCell();
	bool	initItem(DB_KEY idItem);
	bool	initExpansionButton();
	void	initScrollInnerContainerSize();
};

#endif // end of _JPY_LAYER_ITEM_LIST_H_
