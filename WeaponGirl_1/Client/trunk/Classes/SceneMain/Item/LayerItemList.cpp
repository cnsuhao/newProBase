////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerItemList.cpp
// Author: �½���(Chen Jianjun)
// Created: 2015-10-27
////////////////////////////////////////////////////////////////////////
#include "LayerItemList.h"
#include "Root.h"
#include "../SceneMain.h"
#include "WidgetItemListInfo.h"
#include "Mgr\ItemMgr.h"
#include "LayerItemExpansion.h"
#include "Network\Item\MsgGameItem.h"

//////////////////////////////////////////////////////////////////////////
LayerItemList::~LayerItemList()
{
	CC_SAFE_RELEASE(m_pItemCsbNode);
}

//////////////////////////////////////////////////////////////////////////
bool LayerItemList::init()
{
	this->setName("LayerItemList");
	this->setCascadeOpacityEnabled(true);

	// ����csb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerItemList.csb");
	this->addChild(m_pCsbWidget);
	ui::Helper::doLayout(m_pCsbWidget);

	m_pItemCsbNode = CSLoader::createNode("NodeItemListInfo.csb");
	CHECKF(m_pItemCsbNode);
	m_pItemCsbNode->retain();

	// ���봥�����ȼ�
	if (this->initTouchPriority("LayerItemList", this))
	{
		m_pLayerTouchListener = EventListenerTouchOneByOne::create();
		m_pLayerTouchListener->setSwallowTouches(true);
		m_pLayerTouchListener->onTouchBegan = CC_CALLBACK_2(LayerItemList::onTouchBegan, this);
		m_pLayerTouchListener->onTouchEnded = CC_CALLBACK_2(LayerItemList::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_pLayerTouchListener, this);
	}

	auto scrollViewItem = dynamic_cast<ui::ScrollView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ScrollViewItem"));
	CHECKF(scrollViewItem);
	scrollViewItem->setScrollBarWidth(4);
	scrollViewItem->setScrollBarPositionFromCorner(Vec2(2, 2));
	scrollViewItem->setScrollBarColor(Color3B::WHITE);
	scrollViewItem->setScrollBarEnabled(true);
	scrollViewItem->removeAllChildren();
	this->initScrollInnerContainerSize();

	// ��ʼ����Ʒ�б�
	VEC_DB_KEY vecItemID;
	ItemMgr::getInstance()->queryItemKeyVector(vecItemID);
	auto nItemPosionIndex = 0;
	for (auto iter : vecItemID)
	{
		this->initItem(iter);
	}

	// ��ʼ����������
	auto nLeftPackageCount = ItemMgr::getInstance()->getLeftPackageSize();
	for (int i = 0; i < nLeftPackageCount; i++)
	{
		this->addPakageCell();
	}
	this->initExpansionButton();
	this->sortItem();
	this->selectItem(m_pItemListInfo[0]->getID());

	// ��ʼ���ؼ�
	auto imageViewUse = dynamic_cast<ui::ImageView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ImageViewUse"));
	CHECKF(imageViewUse);
	imageViewUse->addClickEventListener([=](Ref*){
		CHECK(m_selectId);
		CMsgGameItem msg;
		CHECK(msg.CreateMsgItem(MSG_ITEM_ACTION_USE, MSG_ITEM_RESULT_SUCC,  0, m_selectId));
		NetworkServe::getInstance()->sendMsg(msg);
	});

	auto imageViewClose = dynamic_cast<ui::ImageView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ImageViewClose"));
	CHECKF(imageViewClose);
	imageViewClose->addClickEventListener([=](Ref*){
		this->removeFromParent();
	});

	// ������͸����
	::AddBlurScreen(this, true);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: ������Ʒ�б��¼�
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void LayerItemList::selectedItemListEvent(Ref* pSender)
{
	WidgetItemListInfo* info = dynamic_cast<WidgetItemListInfo*>(pSender);
	CHECK(info);
	if (info->isNone())
	{
		return;
	}
	else if (info->isExpasionButton())
	{
		// ѡ�н������������������˵�
		this->popItemListExpansion();
	}
	else if(info->isItem())
	{
		this->selectItem(info->getID());
	}
}

////////////////////////////////////////////////////////////////////////
// Description:  ѡ����Ʒ
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool LayerItemList::selectItem(DB_KEY idItem)
{
	m_selectId = idItem;

	CHECKF(m_pCsbWidget);
	auto scrollViewItem = dynamic_cast<ui::ScrollView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ScrollViewItem"));
	CHECKF(scrollViewItem);

	for (auto i : scrollViewItem->getChildren())
	{
		WidgetItemListInfo* info = (WidgetItemListInfo*)i;
		CHECKC(info);
		if (info->getID() == idItem)
		{
			if (info->isItem())
			{
				// ѡ�б��
				info->setSelected(true);

				// ������Ʒ���ܽ���
				this->refreshUIAttr(idItem);
			}
		}
		else if (info->isSelected())
		{
			info->setSelected(false);
		}
	}

	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: �������������������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void LayerItemList::popItemListExpansion()
{
	LogSave("LayerItemList::popItemListExpansion");

	auto node = LayerItemExpansion::create();
	CHECK(node);
	this->getFather()->addChild(node);
}

////////////////////////////////////////////////////////////////////////
// Description: ��ʼ�����������С
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void LayerItemList::initScrollInnerContainerSize()
{
	CHECK(m_pCsbWidget);
	auto scrollViewItem = dynamic_cast<ui::ScrollView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ScrollViewItem"));
	CHECK(scrollViewItem);
	auto autoInnerContainerSize = scrollViewItem->getContentSize();

	// ����������Ʒ��ؼ�����
	int allNodeCount = ItemMgr::getInstance()->getPackageSize();
	if (!ItemMgr::getInstance()->isLockExpansion())
	{
		allNodeCount += 1;
	}

	// ��������
	int colCount = allNodeCount / 6;
	if (allNodeCount % 6 > 0)
	{
		colCount++;
	}

	// �����ۼƸ߶�
	auto csbLayout = (ui::Widget*)m_pItemCsbNode->getChildByName("Layout");
	if (csbLayout)
	{
		autoInnerContainerSize.height = csbLayout->getContentSize().height * colCount;
	}

	// �����趨���������С
	if (autoInnerContainerSize.height < scrollViewItem->getContentSize().height)
	{
		autoInnerContainerSize.height = scrollViewItem->getContentSize().height;
	}
	scrollViewItem->setInnerContainerSize(autoInnerContainerSize);
}

////////////////////////////////////////////////////////////////////////
// Description: ������Ʒ�������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void LayerItemList::refreshUIAttr(DB_KEY idItem)
{
	auto nodeAttr = ui::Helper::seekNodeByName(m_pCsbWidget, "LayerItemConnext");
	CHECK(nodeAttr);
	auto pItemInfo = ItemMgr::getInstance()->getItem(idItem);
	CHECK(pItemInfo);

	auto imageViewItemSelect = (ui::ImageView*)(ui::Helper::seekWidgetByName(m_pCsbWidget, "ImageViewItemSelect"));
	CHECKB(imageViewItemSelect);
	imageViewItemSelect->loadTexture(::getItemIconFileName(pItemInfo->getData(ITEM_DATA_TYPE)), ui::Widget::TextureResType::PLIST);

	std::string strItemConnext = "";
	CHECKB(ItemMgr::getInstance()->getDataStrByType(pItemInfo->getData(ITEM_DATA_TYPE), ITEM_TYPE_DATA_NAME, strItemConnext));
	CHECKB(ui::Helper::setStringText(nodeAttr, "TextItemName", strItemConnext));
	CHECKB(ItemMgr::getInstance()->getDataStrByType(pItemInfo->getData(ITEM_DATA_TYPE), ITEM_TYPE_DATA_DETAIL, strItemConnext));
	CHECKB(ui::Helper::setStringText(nodeAttr, "TextItemConnext", strItemConnext));

}

//////////////////////////////////////////////////////////////////////////
bool LayerItemList::onTouchBegan(Touch *touch, Event *unused_event)
{
	// �̵����ٴ��������е��¼�
	if (!this->isInTouchRect(touch->getLocation()))
	{
		return true;
	}
	
	return false;
}

//////////////////////////////////////////////////////////////////////////
void LayerItemList::onTouchEnded(Touch *touch, Event *unused_event)
{
	// �����������˳�
	if (!this->isInTouchRect(touch->getStartLocation()) && !this->isInTouchRect(touch->getLocation()))
	{
		this->removeFromParent();
		return;
	}
}

////////////////////////////////////////////////////////////////////////
// Description: ��Ʒ������(1���Ƚ�id��С��2���ȽϿؼ�������Ʒ>�ո�>����)
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value:  bool
////////////////////////////////////////////////////////////////////////
bool GetBatterItemSort(ST_SORT_ITEM_INFO& info1, ST_SORT_ITEM_INFO& info2)
{
	if (info1.idItem != info2.idItem)
	{
		return info1.idItem > info2.idItem;
	}
	else if (info1.nCellType != info2.nCellType)
	{
		return info1.nCellType > info2.nCellType;
	}
	else if (info1.nIndex != info2.nIndex)
	{
		return info1.nIndex < info2.nIndex;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////
// Description: ��Ʒ����
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value:  bool
////////////////////////////////////////////////////////////////////////
void LayerItemList::sortItem()
{
	auto scrollViewItem = dynamic_cast<ui::ScrollView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ScrollViewItem"));
	CHECK(scrollViewItem);
	auto fInnerHeight =  scrollViewItem->getInnerContainerSize().height;

	std::vector<ST_SORT_ITEM_INFO> vecSortInfo;
	for (int i = 0; i < m_pItemListInfo.size(); i++)
	{
		ST_SORT_ITEM_INFO stInfo = {};
		stInfo.idItem = m_pItemListInfo[i]->getID();
		stInfo.nCellType = m_pItemListInfo[i]->getType();
		stInfo.nIndex = i;
		vecSortInfo.push_back(stInfo);
	}
	std::sort(vecSortInfo.begin(), vecSortInfo.end(), GetBatterItemSort);
	
	std::vector<WidgetItemListInfo*> vecTmpSort;
	auto csbLayout = (ui::Widget*)m_pItemCsbNode->getChildByName("Layout");
	auto itemSize = csbLayout->getContentSize();
	for (int i = 0; i < vecSortInfo.size(); i++)
	{
		int nIndex = vecSortInfo[i].nIndex;
		m_pItemListInfo[nIndex]->setPosition(Vec2((i % 6 + 0.5f) * itemSize.width, fInnerHeight - (i / 6 + 0.5f) * itemSize.height));
		vecTmpSort.push_back(m_pItemListInfo[nIndex]);
	}
	m_pItemListInfo.swap(vecTmpSort);
}

////////////////////////////////////////////////////////////////////////
// Description: ��ӱ�������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value:  bool
////////////////////////////////////////////////////////////////////////
bool LayerItemList::addPakageCell()
{
	auto scrollViewItem = dynamic_cast<ui::ScrollView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ScrollViewItem"));
	CHECKF(scrollViewItem);
	auto info = WidgetItemListInfo::create(m_pItemCsbNode, WIDGET_ITEM_TYPE_NONE, 0);
	CHECKF(info);
	auto nViewItemCount = scrollViewItem->getChildrenCount();
	auto innerSize = scrollViewItem->getInnerContainerSize();
	auto infoSize = info->getContentSize();
	auto nInfoWidth = (nViewItemCount % 6 + 0.5f) * infoSize.width;
	auto nInfoheight = (nViewItemCount / 6 + 0.5f) * infoSize.height;
	info->setPosition(Vec2(nInfoWidth, innerSize.height - nInfoheight));
	info->addClickEventListener(CC_CALLBACK_1(LayerItemList::selectedItemListEvent, this));
	scrollViewItem->addChild(info);
	m_pItemListInfo.push_back(info);

	// ����Ƿ���Ҫ�������������б�
	if (nInfoheight > innerSize.height)
	{
		// �������ù��������С
		auto fNewInnerHeight = innerSize.height + infoSize.height;
		scrollViewItem->setInnerContainerSize(Size(innerSize.width, fNewInnerHeight));

		// �����趨���пؼ�λ��
		for (int i = 0; i < m_pItemListInfo.size(); i++)
		{
			m_pItemListInfo[i]->setPosition(Vec2((i % 6 + 0.5f) * infoSize.width, fNewInnerHeight - (i / 6 + 0.5f) * infoSize.height));
		}
	}

	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: ��ӱ�������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value:  bool
////////////////////////////////////////////////////////////////////////
bool LayerItemList::initExpansionButton()
{
	// �Ѵ����޲�������չ
	if (ItemMgr::getInstance()->isLockExpansion())
	{
		return true;
	}

	auto scrollViewItem = dynamic_cast<ui::ScrollView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ScrollViewItem"));
	CHECKF(scrollViewItem);
	auto info = WidgetItemListInfo::create(m_pItemCsbNode, WIDGET_ITEM_TYPE_EXPASION, 0);
	CHECKF(info);
	auto nViewItemCount = scrollViewItem->getChildrenCount();
	float innerWidth	= scrollViewItem->getInnerContainerSize().width;
	float innerHeight	= scrollViewItem->getInnerContainerSize().height;
	float nInfoWidth	= (nViewItemCount % 6 + 0.5f) * info->getContentSize().width;
	float nInfoheight	= (nViewItemCount / 6 + 0.5f) * info->getContentSize().height;
	info->setPosition(Vec2(nInfoWidth, innerHeight - nInfoheight));
	info->addClickEventListener(CC_CALLBACK_1(LayerItemList::selectedItemListEvent, this));
	scrollViewItem->addChild(info);
	m_pItemListInfo.push_back(info);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: ��ʼ����Ʒ����
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value:  bool
////////////////////////////////////////////////////////////////////////
bool LayerItemList::initItem(DB_KEY idItem)
{
	CHECKF(idItem);
	auto scrollViewItem = dynamic_cast<ui::ScrollView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ScrollViewItem"));
	CHECKF(scrollViewItem);
	auto info = WidgetItemListInfo::create(m_pItemCsbNode, WIDGET_ITEM_TYPE_ITEM, idItem);
	CHECKF(info);
	auto nViewItemCount = scrollViewItem->getChildrenCount();
	float innerWidth = scrollViewItem->getInnerContainerSize().width;
	float innerHeight = scrollViewItem->getInnerContainerSize().height;
	float nInfoWidth = (nViewItemCount % 6 + 0.5f) * info->getContentSize().width;
	float nInfoheight = (nViewItemCount / 6 + 0.5f) * info->getContentSize().height;
	info->setPosition(Vec2(nInfoWidth, innerHeight - nInfoheight));
	info->addClickEventListener(CC_CALLBACK_1(LayerItemList::selectedItemListEvent, this));
	scrollViewItem->addChild(info);
	m_pItemListInfo.push_back(info);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: �����Ʒ(�ⲿ�ӿ�)
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value:  bool
////////////////////////////////////////////////////////////////////////
bool LayerItemList::addItem(DB_KEY idItem)
{
	CHECKF(idItem);

	// ����һ���ո�
	for (int i = 0; i < m_pItemListInfo.size(); i++)
	{
		if (m_pItemListInfo[i]->isNone())
		{
			m_pItemListInfo[i]->setItemData(WIDGET_ITEM_TYPE_ITEM, idItem);
			break;
		}
	}

	// �����趨ѡ����
	this->selectItem(idItem);

	// ��������
	this->sortItem();
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: ɾ����Ʒ(�ⲿ�ӿ�)
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value:  bool
////////////////////////////////////////////////////////////////////////
bool LayerItemList::delItem(DB_KEY idItem)
{
	CHECKF(idItem);
	// �ȴ�������ɾ������
	auto nDelItemIndex = 0;
	for (int i = 0; i < m_pItemListInfo.size(); i++)
	{
		if (idItem == m_pItemListInfo[i]->getID())
		{
			m_pItemListInfo[i]->setItemData(WIDGET_ITEM_TYPE_NONE, 0);
			nDelItemIndex = i + 1;
			break;
		}
	}

	// �����趨ѡ����
	if (m_pItemListInfo.size() > nDelItemIndex)
	{
		this->selectItem(m_pItemListInfo[nDelItemIndex]->getID());
	}

	// ��������
	this->sortItem();
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: ������������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value:  bool
////////////////////////////////////////////////////////////////////////
bool LayerItemList::expansionPackage()
{
	for (int i = 0; i < PACKAGE_EXPANSION_SIZE - 1; i++)
	{
		this->addPakageCell();
	}

	// ��չ���һ��ʱ����Ƿ��ѵ�������
	if (ItemMgr::getInstance()->isLockExpansion())
	{
		// ���½�����ťΪ�ո�
		for (int i = 0; i < m_pItemListInfo.size(); i++)
		{
			if (m_pItemListInfo[i]->isExpasionButton())
			{
				m_pItemListInfo[i]->setItemData(WIDGET_ITEM_TYPE_NONE, 0);
				break;
			}
		}
	}
	else
	{
		this->addPakageCell();
	}
	this->sortItem();
	return true;
}
