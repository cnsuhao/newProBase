////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerMyPoker.h
// Author: ������(Peng Wenqi)
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
	void	refreshPokerList();									// ���¿����б�
	void	popPokerSort(Ref* pSender);							// ���������
	void	selectPokerWidgetEvent(Ref* pSender);				// ѡ��ĳ������
	void	clickUpStar(Ref* pSender);							// �������
	void	clickUpStrengthen(Ref* pSender);					// ���ǿ��
	void	clickMagic1(Ref* pSender);							// �������1
	void	clickMagic2(Ref* pSender);							// �������2
	void	clickMagic3(Ref* pSender);							// �������3
	void	clickEquip(Ref* pSender);							// �������
	void	clickBossMagic(Ref* pSender);						// ������Ǽ���
	void	showMagic(OBJID idMagicType);						// ��ʾħ��˵��
	void	showEquip(OBJID idIcon, const std::string& name, const std::string& text);	// ��ʾ����˵��
	DB_KEY	getSelectPokerID() const;							// ���ѡ�п���id
	Poker*	getSelectPoker() const;								// ���ѡ�п�������

	// ���涨ʱ����
public:
	virtual void update(float delta) override;
protected:
	void updatePokerSort();			// ��������
	void updatePokerAttrDetail();	// ������ϸ����
private:
	POKER_SORT_TYPE	m_eUiSortType;
	OBJID			m_idShowMagicType;
};

#endif // end of _JPY_LayerMyPoker_H_