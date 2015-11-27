////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerMyPoker.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/11/24
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_LayerMyPoker_H_
#define _JPY_LayerMyPoker_H_

#include "Global/Global.h"

class Poker;
class SceneMain;
class LayerMyPoker : public Layer, public TouchPriorityBase
{
public:
	virtual bool init();
	CREATE_FUNC(LayerMyPoker);

protected:
	SceneMain* getFather() const { return (SceneMain*)_parent; }
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
	virtual ~LayerMyPoker();
	Node* m_pPokerCsbNode;

public:
	void	refreshPokerList();									// 更新卡牌列表
	void	popPokerSort(Ref* pSender);							// 弹出排序层
	void	selectPokerWidgetEvent(Ref* pSender);				// 选中某个卡牌
	void	clickUpStar(Ref* pSender);							// 点击升星
	void	clickUpStrengthen(Ref* pSender);					// 点击强化
	void	clickMagic1(Ref* pSender);							// 点击技能1
	void	clickMagic2(Ref* pSender);							// 点击技能2
	void	clickMagic3(Ref* pSender);							// 点击技能3
	void	clickEquip(Ref* pSender);							// 点击宝具
	void	clickBossMagic(Ref* pSender);						// 点击主角技能
	void	showMagic(OBJID idMagicType);						// 显示魔法说明
	void	showEquip(OBJID idIcon, const std::string& name, const std::string& text);	// 显示宝具说明
	DB_KEY	getSelectPokerID() const;							// 获得选中卡牌id
	Poker*	getSelectPoker() const;								// 获得选中卡牌数据

	// 界面定时更新
public:
	virtual void update(float delta) override;
protected:
	void updatePokerSort();			// 卡牌排序
	void updatePokerAttrDetail();	// 卡牌详细描述
private:
	POKER_SORT_TYPE	m_eUiSortType;
	OBJID			m_idShowMagicType;
};

#endif // end of _JPY_LayerMyPoker_H_