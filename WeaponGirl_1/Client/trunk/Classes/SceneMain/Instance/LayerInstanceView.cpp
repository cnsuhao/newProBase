////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerInstanceView.cpp
// Author: �½���(Chen Jianjun)
// Created: 2015-11-19
////////////////////////////////////////////////////////////////////////
#include "LayerInstanceView.h"
#include "Root.h"
#include "../SceneMain.h"
#include "WidgetInstanceViewInfo.h"
#include "Mgr\InstanceMgr.h"
#include "LayerInstanceMap.h"
#include "Mgr\ItemMgr.h"
#include "../Item/LayerItemList.h"
#include "MyCocosCommon/LayerHint.h"
#include "LayerInstanceSearchingResult.h"
#include "LayerInstanceDrop.h"
#include "MyCocosCommon\LoadingBarTo.h"
#include "Network\Instance\MsgGameInstanceInfo.h"
#include "Network\Comment\MsgCommentOpt.h"

//////////////////////////////////////////////////////////////////////////
LayerInstanceView::~LayerInstanceView()
{

}

//////////////////////////////////////////////////////////////////////////
bool LayerInstanceView::init() 
{
	this->setName("LayerInstanceView");
	this->setCascadeOpacityEnabled(true);

	// ����csb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerInstanceView.csb");
	this->addChild(m_pCsbWidget);
	ui::Helper::doLayout(m_pCsbWidget);

	// ���봥�����ȼ�
	if (this->initTouchPriority("LayerInstanceView", this))
	{
		m_pLayerTouchListener = EventListenerTouchOneByOne::create();
		m_pLayerTouchListener->setSwallowTouches(true);
		m_pLayerTouchListener->onTouchBegan = CC_CALLBACK_2(LayerInstanceView::onTouchBegan, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_pLayerTouchListener, this);
	}

	// ��ʼ������ؼ�
	// ��ͼ��ť
	CHECKF(this->initButtonListen("ImageViewMap", [=](Ref*){
		auto scene = Root::getInstance()->getSceneMain();
		CHECK_NOLOG(scene);
		scene->loadMainView("LayerInstanceMap");
	}));
	

	// �鿴���䰴ť
	CHECKF(this->initButtonListen("ImageViewDrop", [=](Ref*){
		auto sence = Root::getInstance()->getSceneMain();
		CHECK_NOLOG(sence);
		auto layer = LayerInstanceDrop::create();
		CHECK_NOLOG(layer);
		sence->addChild(layer);
		CHECK_NOLOG(m_pInstanceViewInfo);
		auto nChapter = m_pInstanceViewInfo->getSelectChapter();
		auto nMode = m_pInstanceViewInfo->getSelectMode();
		auto nPass = m_pInstanceViewInfo->getSelectPass();
		auto idInstance = InstanceMgr::getInstance()->getInstanceKey(nMode, nChapter, nPass);
		layer->updateDropInfo(idInstance);
	}));

	// �л��ѶȰ�ť
	CHECKF(this->initButtonListen("ImageViewEasy", [=](Ref*){ this->changeMode(E_INSTANCE_MODE_TYPE_EASY);}));
	CHECKF(this->initButtonListen("ImageViewNormal", [=](Ref*){ this->changeMode(E_INSTANCE_MODE_TYPE_NORMAL);}));
	CHECKF(this->initButtonListen("ImageViewDifficulty", [=](Ref*){ this->changeMode(E_INSTANCE_MODE_TYPE_DIFFICULTY);}));

	// �鿴�ؿ����԰�ť
	CHECKF(this->initButtonListen("ImageViewStrategy", [=](Ref*){
		CMsgCommentOpt msg;
		CHECK_NOLOG(msg.CreateCommentOpt(MSG_COMMENT_OPT_ACTION_querylist, InstanceMgr::getInstance()->getidCurInstance(), 0));
		NetworkServe::getInstance()->sendMsg(msg);
	}));

	// ̽�������ť
	CHECKF(this->initButtonListen("ImageViewSearching", [=](Ref*){
		// ��ѯ̽�����
		auto nSearchingCount = InstanceMgr::getInstance()->getSearchingCount();
		if (nSearchingCount > 0)
		{
			// ��ⱳ���Ƿ��㹻
			if (0 == ItemMgr::getInstance()->getLeftPackageSize())
			{
				AddHint(ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_PACKAGE_NOT_ENOUGH));
			}
			else
			{
				CMsgGameInstanceInfo msg;
				CHECK_NOLOG(msg.CreateMsg(EMSGINSTANCEA_SEARCHING_AWARD, EMSGINSTANCER_SUC, InstanceMgr::getInstance()->getidCurInstance()));
				NetworkServe::getInstance()->sendMsg(msg);
			}
			return;
		}

		// ���Բ鿴�յ�
		auto sence = Root::getInstance()->getSceneMain();
		CHECK_NOLOG(sence);
		auto layer = LayerInstanceSearchingResult::create();
		CHECK_NOLOG(layer);
		sence->addChild(layer);
	}));

	// ������ť
	CHECKF(this->initButtonListen("ImageViewPackageBack", [=](Ref*){
		auto sence = Root::getInstance()->getSceneMain();
		CHECK_NOLOG(sence);
		auto layer = LayerItemList::create();
		CHECK_NOLOG(layer);
		sence->addChild(layer);
	}, true));

	// ����ǿ����ť
	CHECKF(this->initButtonListen("ImageViewStrengthenBack", [=](Ref*){
		// ����ս��
		auto idInstance = InstanceMgr::getInstance()->getidCurInstance();
		CHECK_NOLOG(idInstance);
		if (0 == InstanceMgr::getInstance()->getFightLeftTime() && !InstanceMgr::getInstance()->isPass(idInstance))
		{
			CMsgGameInstanceInfo msg;
			CHECK_NOLOG(msg.CreateMsg(EMSGINSTANCEA_FIGHT, EMSGINSTANCER_SUC, idInstance));
			NetworkServe::getInstance()->sendMsg(msg);
		}
	}, true));

	// ����̽�������
	CHECKF(this->setSearchingMaxCount(InstanceMgr::getInstance()->getSearchingMaxCount()));

	// �����½ں͵�ͼ��Ϣ
	auto idInstance = InstanceMgr::getInstance()->getidCurInstance();
	CHECKF(idInstance);
	auto nChapter = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_instance, idInstance, INSTANCE_DATA_CHAPTER);
	CHECKF(ui::Helper::setStringText(m_pCsbWidget, "TextInstanceName", ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_instance, idInstance, INSTANCE_DATA_CHAPTER_NAME)));

	// ��ʼ������µ�ͼ
	auto LayoutChapterNode = dynamic_cast<ui::Layout*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "LayoutChapterNode"));
	CHECKF(LayoutChapterNode);
	m_pInstanceViewInfo = WidgetInstanceViewInfo::create(nChapter, ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_instance, idInstance, INSTANCE_DATA_CHAPTER_CSB_NAME));
	CHECKF(m_pInstanceViewInfo);
	LayoutChapterNode->addChild(m_pInstanceViewInfo);

	// �����Ѷ�
	CHECKF(this->updateMode(nChapter, E_INSTANCE_MODE_TYPE_EASY));
	CHECKF(this->updateMode(nChapter, E_INSTANCE_MODE_TYPE_NORMAL));
	CHECKF(this->updateMode(nChapter, E_INSTANCE_MODE_TYPE_DIFFICULTY));
	CHECKF(this->changeMode((E_INSTANCE_MODE_TYPE)ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_instance, idInstance, INSTANCE_DATA_MODE)));

	// ���ùؿ�
	CHECKF(this->changePass(ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_instance, idInstance, INSTANCE_DATA_PASS)));

	// ������ʱ
	this->scheduleUpdate();
	this->schedule([](float){ InstanceMgr::getInstance()->update(); }, 1.f, "updateSecond");
	return true;
}

// ��ʼ��������ť
bool LayerInstanceView::initButtonListen(const std::string& strName, const ui::Widget::ccWidgetClickCallback& callback, bool bLight/* = false*/)
{
	CHECKF(m_pCsbWidget);
	auto pImage = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(m_pCsbWidget, strName));
	CHECKF(pImage);
	pImage->setAutoTouchChangeRenderer(bLight);
	pImage->addClickEventListener(callback);
	pImage->setAutoTouchAction();
	pImage->setTouchEnabled(true);
	return true;
}

//////////////////////////////////////////////////////////////////////////
void LayerInstanceView::update(float delta)
{
	Layer::update(delta);
	float fSpeed = 8.f;
	float fDecX = 0.f;
	auto layoutWarning = dynamic_cast<ui::Layout*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "LayoutWarning"));
	CHECK(layoutWarning);
	auto warningSize = layoutWarning->getContentSize();

	// ��������ƾ���
	auto ImageViewWarningUp = dynamic_cast<ui::ImageView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ImageViewWarningUp"));
	CHECK(ImageViewWarningUp);
	auto ImageViewWarningUp_1 = dynamic_cast<ui::ImageView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ImageViewWarningUp_1"));
	CHECK(ImageViewWarningUp_1);
	auto fNewPositionX = ImageViewWarningUp->getPositionX() - fSpeed;
	fNewPositionX = (fNewPositionX + warningSize.width > 0) ? fNewPositionX : warningSize.width - fDecX;
	ImageViewWarningUp->setPositionX(fNewPositionX);
	fNewPositionX = ImageViewWarningUp_1->getPositionX() - fSpeed;
	fNewPositionX = (fNewPositionX + warningSize.width > 0) ? fNewPositionX : warningSize.width - fDecX;
	ImageViewWarningUp_1->setPositionX(fNewPositionX);

	// ��������ƾ���
	auto ImageViewWarningDown = dynamic_cast<ui::ImageView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ImageViewWarningDown"));
	CHECK(ImageViewWarningDown);
	auto ImageViewWarningDown_1 = dynamic_cast<ui::ImageView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ImageViewWarningDown_1"));
	CHECK(ImageViewWarningDown_1);
	fNewPositionX = ImageViewWarningDown->getPositionX() + fSpeed;
	fNewPositionX = (fNewPositionX > warningSize.width) ? fDecX - warningSize.width : fNewPositionX;
	ImageViewWarningDown->setPositionX(fNewPositionX);
	fNewPositionX = ImageViewWarningDown_1->getPositionX() + fSpeed;
	fNewPositionX = (fNewPositionX > warningSize.width) ? fDecX - warningSize.width : fNewPositionX;
	ImageViewWarningDown_1->setPositionX(fNewPositionX);
}

void LayerInstanceView::setVisible(bool bVisible)
{
	if (!bVisible)
	{
		this->checkMap();
	}
	Layer::setVisible(bVisible);
}

//////////////////////////////////////////////////////////////////////////
// ����ս��ʣ��ʱ��
void LayerInstanceView::updateFightTime(int nTime)
{
	CHECK(ui::Helper::setStringText(m_pCsbWidget, "TextFightTime", ::getMinuteTime(nTime)));
}

// ����̽��ʣ��ʱ��
void LayerInstanceView::updateSearchingTime(int nTime)
{
	CHECK(ui::Helper::setStringText(m_pCsbWidget, "TextSearchingTime", ::getMinuteTime(nTime)));
}

// ����������ʾ
void LayerInstanceView::openWarning()
{
	CHECK(ui::Helper::setVisable(m_pCsbWidget, "ImageViewWarningUp", true));
	CHECK(ui::Helper::setVisable(m_pCsbWidget, "ImageViewWarningUp_1", true));
	CHECK(ui::Helper::setVisable(m_pCsbWidget, "ImageViewWarningDown", true));
	CHECK(ui::Helper::setVisable(m_pCsbWidget, "ImageViewWarningDown_1", true));
}

// �رվ�����ʾ
void LayerInstanceView::closeWarning()
{
	CHECK(ui::Helper::setVisable(m_pCsbWidget, "ImageViewWarningUp", false));
	CHECK(ui::Helper::setVisable(m_pCsbWidget, "ImageViewWarningUp_1", false));
	CHECK(ui::Helper::setVisable(m_pCsbWidget, "ImageViewWarningDown", false));
	CHECK(ui::Helper::setVisable(m_pCsbWidget, "ImageViewWarningDown_1", false));
}

// ����SearchingMaxCount
bool LayerInstanceView::setSearchingMaxCount(int nCount)
{
	return ui::Helper::setDataText(m_pCsbWidget, "TextSearchingMaxCount", nCount);
}

// ����SearchingCount
bool LayerInstanceView::setSearchingCount(int nCount)
{
	CHECKF(ui::Helper::setDataText(m_pCsbWidget, "TextSearchingCount", nCount));
	CHECKF(ui::Helper::setVisable(m_pCsbWidget, "ImageViewMark", nCount > 0));
	return true;
}

// �����Ѷȵ�ǰѡ��Ч��
bool LayerInstanceView::selectMode(int nMode)
{
	switch ((E_INSTANCE_MODE_TYPE)nMode)
	{
	case E_INSTANCE_MODE_TYPE_EASY:			CHECKF(ui::Helper::setImageViewTexturePlist(m_pCsbWidget, "ImageViewEasy",			"res/Text/InstanceEasyChoose.png")); break;
	case E_INSTANCE_MODE_TYPE_NORMAL:		CHECKF(ui::Helper::setImageViewTexturePlist(m_pCsbWidget, "ImageViewNormal",		"res/Text/InstanceNormalChoose.png")); break;
	case E_INSTANCE_MODE_TYPE_DIFFICULTY:	CHECKF(ui::Helper::setImageViewTexturePlist(m_pCsbWidget, "ImageViewDifficulty",	"res/Text/InstanceDifficultyChoose.png")); break;
	default: break;
	}
	return true;
}

// �����Ѷȵ�ǰѡ��Ч��
bool LayerInstanceView::cancelMode(int nMode)
{
	switch ((E_INSTANCE_MODE_TYPE)nMode)
	{
	case E_INSTANCE_MODE_TYPE_EASY:			CHECKF(ui::Helper::setImageViewTexturePlist(m_pCsbWidget, "ImageViewEasy",			"res/Text/InstanceEasy.png")); break;
	case E_INSTANCE_MODE_TYPE_NORMAL:		CHECKF(ui::Helper::setImageViewTexturePlist(m_pCsbWidget, "ImageViewNormal",		"res/Text/InstanceNormal.png")); break;
	case E_INSTANCE_MODE_TYPE_DIFFICULTY:	CHECKF(ui::Helper::setImageViewTexturePlist(m_pCsbWidget, "ImageViewDifficulty",	"res/Text/InstanceDifficulty.png")); break;
	default: break;
	}
	return true;
}

// �����Ѷ�
bool LayerInstanceView::changeMode(int nMode, bool bForce/* = false*/)
{
	CHECKF(nMode);
	CHECKF(m_pInstanceViewInfo);
	auto nSelectMode = m_pInstanceViewInfo->getSelectMode();
	if (nSelectMode != nMode || bForce)
	{
		CHECKF(this->cancelMode(nSelectMode));
		CHECKF(this->selectMode(nMode));
		CHECKF(m_pInstanceViewInfo->changeMode(nMode));
	}
	return true;
}

// �����ؿ�
bool LayerInstanceView::changePass(int nPass)
{
	CHECKF(nPass);
	CHECKF(m_pInstanceViewInfo);
	auto idInstance = InstanceMgr::getInstance()->getidCurInstance();
	CHECKF1_NOLOG(idInstance && InstanceMgr::getInstance()->isSearching(idInstance));
	CHECKF(m_pInstanceViewInfo->changePass(nPass));

	// ���¹ؿ�����
	CHECKF(ui::Helper::setDataText(m_pCsbWidget, "TextChapterNum", ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_instance, idInstance, INSTANCE_DATA_CHAPTER)));
	CHECKF(ui::Helper::setDataText(m_pCsbWidget, "TextPassNum", nPass));

	// ����ÿ������ 
	CHECKF(ui::Helper::setDataText(m_pCsbWidget, "TextExp",		ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_instance, idInstance, INSTANCE_DATA_AUTO_ADD_EXP)));
	CHECKF(ui::Helper::setDataText(m_pCsbWidget, "TextMoney",	ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_instance, idInstance, INSTANCE_DATA_AUTO_ADD_MONEY)));

	// ����̽����
	CHECKF(this->setSearchingCount(InstanceMgr::getInstance()->getSearchingCount()));
	
	// ս��ʣ��ʱ�����������
	auto loadingBarFightTime = dynamic_cast<ui::LoadingBar*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "LoadingBarFightTime"));
	CHECKF(loadingBarFightTime);
	float fFightTime	 = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_instance, idInstance, INSTANCE_DATA_FIGHT_WAITING_TIME);
	float fFightLeftTime = InstanceMgr::getInstance()->getFightLeftTime();
	loadingBarFightTime->setPercent((fFightTime - fFightLeftTime) * 100.f / fFightTime);
	loadingBarFightTime->stopAllActions();
	if (fFightLeftTime > 0)
	{
		loadingBarFightTime->runAction(LoadingBarTo::create(fFightLeftTime, 100));
	}
	this->updateFightTime(fFightLeftTime);

	// ̽��ʣ��ʱ�����������
	auto loadingBarSearchingTime = dynamic_cast<ui::LoadingBar*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "LoadingBarSearchingTime"));
	CHECKF(loadingBarSearchingTime);
	float fSearchingTime = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_instance, idInstance, INSTANCE_DATA_SEARCHING_TIME);
	float fSearchingtLeftTime = InstanceMgr::getInstance()->getSearchingLeftTime();
	loadingBarSearchingTime->setPercent((fSearchingTime - fSearchingtLeftTime) * 100.f / fSearchingTime);
	loadingBarSearchingTime->stopAllActions();
	if (fSearchingtLeftTime > 0)
	{
		loadingBarSearchingTime->runAction(LoadingBarTo::create(fSearchingtLeftTime, 100));
	}
	this->updateSearchingTime(fSearchingtLeftTime);

	// ��⾯������
	if (0 == fFightLeftTime && !InstanceMgr::getInstance()->isPass(idInstance))
	{
		this->openWarning();
	}
	else
	{
		this->closeWarning();
	}

	// ��ȡ����
	CHECKF(ui::Helper::setDataText(m_pCsbWidget, "TextStrategyNum",	InstanceMgr::getInstance()->getCommentCount()));
	return true;
}

// ����ͼ
bool LayerInstanceView::checkMap()
{
	CHECKF(m_pInstanceViewInfo);
	auto idInstance = InstanceMgr::getInstance()->getidCurInstance();
	CHECKF(idInstance);
	auto nChapter = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_instance, idInstance, INSTANCE_DATA_CHAPTER);
	if (nChapter != m_pInstanceViewInfo->getSelectChapter())
	{
		CHECKF(this->updateMap(nChapter));
	}
	return true;
}

// �����½�
bool LayerInstanceView::updateMap(int nChapter)
{
	CHECKF(nChapter);
	CHECKF(m_pInstanceViewInfo);
	CHECKF1_NOLOG(nChapter != m_pInstanceViewInfo->getSelectChapter());

	// �����½���Ϣ
	auto idInstance = InstanceMgr::getInstance()->getidCurInstance();
	CHECKF(idInstance);
	if (nChapter != ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_instance, idInstance, INSTANCE_DATA_CHAPTER))
	{
		idInstance = InstanceMgr::getInstance()->getInstanceKey(E_INSTANCE_MODE_TYPE_EASY, nChapter, 1);
	}
	CHECKF(idInstance);
	CHECKF(ui::Helper::setStringText(m_pCsbWidget, "TextInstanceName", ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_instance, idInstance, INSTANCE_DATA_CHAPTER_NAME)));

	// ���µ�ͼ
	m_pInstanceViewInfo->updateMap(nChapter, ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_instance, idInstance, INSTANCE_DATA_CHAPTER_CSB_NAME));

	// �����Ѷ�
	CHECKF(this->updateMode(nChapter, E_INSTANCE_MODE_TYPE_EASY));
	CHECKF(this->updateMode(nChapter, E_INSTANCE_MODE_TYPE_NORMAL));
	CHECKF(this->updateMode(nChapter, E_INSTANCE_MODE_TYPE_DIFFICULTY));
	CHECKF(this->changeMode((E_INSTANCE_MODE_TYPE)ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_instance, idInstance, INSTANCE_DATA_MODE), true));

	// ����̽���ĵ�ͼ
	if (InstanceMgr::getInstance()->isSearching(idInstance))
	{
		CHECKF(this->changePass(ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_instance, idInstance, INSTANCE_DATA_PASS)));
	}
	return true;
}

bool LayerInstanceView::updateMode(int nChapter, int nMode)
{
	if (InstanceMgr::getInstance()->isModeThrough(nChapter, nMode))
	{
		switch ((E_INSTANCE_MODE_TYPE)nMode)
		{
		case E_INSTANCE_MODE_TYPE_EASY:	CHECKF(ui::Helper::setImageViewTexturePlist(this, "ImageViewStarEasy", "res/Instance/InstanceStarLight.png")); break;
		case E_INSTANCE_MODE_TYPE_NORMAL: CHECKF(ui::Helper::setImageViewTexturePlist(this, "ImageViewStarNormal", "res/Instance/InstanceStarLight.png")); break;
		case E_INSTANCE_MODE_TYPE_DIFFICULTY: CHECKF(ui::Helper::setImageViewTexturePlist(this, "ImageViewStarDifficulty", "res/Instance/InstanceStarLight.png")); break;
		default: break;
		}
	}
	else
	{
		switch ((E_INSTANCE_MODE_TYPE)nMode)
		{
		case E_INSTANCE_MODE_TYPE_EASY:	CHECKF(ui::Helper::setImageViewTexturePlist(this, "ImageViewStarEasy", "res/Instance/InstanceStar.png")); break;
		case E_INSTANCE_MODE_TYPE_NORMAL: CHECKF(ui::Helper::setImageViewTexturePlist(this, "ImageViewStarNormal", "res/Instance/InstanceStar.png")); break;
		case E_INSTANCE_MODE_TYPE_DIFFICULTY: CHECKF(ui::Helper::setImageViewTexturePlist(this, "ImageViewStarDifficulty", "res/Instance/InstanceStar.png")); break;
		default: break;
		}
	}
	return true;
}


// ս��ʤ��
bool LayerInstanceView::winFight()
{
	CHECKF(m_pInstanceViewInfo);
	CHECKF(this->updateMode(m_pInstanceViewInfo->getSelectChapter(), m_pInstanceViewInfo->getSelectMode()));
	CHECKF(m_pInstanceViewInfo->winFight(m_pInstanceViewInfo->getSelectPass(), true)); 
	this->closeWarning();
	return true;
}