////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: InstanceMgr.cpp
// Author: �½���(Chen Jianjun)
// Created: 2015-11-13
////////////////////////////////////////////////////////////////////////
#include "InstanceMgr.h"
#include "Root.h"
#include "SceneMain/SceneMain.h"
#include "MoneyMgr.h"
#include "UserAttrMgr.h"
#include "SceneMain/Instance/LayerInstanceView.h"
#include "SceneMain/Instance/LayerInstanceMap.h"
#include "SceneMain/Instance/LayerInstanceSearchingResult.h"
#include "SceneMain/Instance/LayerInstanceSearchingBuy.h"
#include "SceneMain/Instance/LayerInstanceStrategy.h"
#include "Network\NetworkServe.h"
#include "Network\Instance\MsgGameInstanceInfo.h"

InstanceMgr* InstanceMgr::m_pInstance = nullptr;
//////////////////////////////////////////////////////////////////////////
InstanceMgr* InstanceMgr::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new InstanceMgr();
	}
	return m_pInstance;
}

//////////////////////////////////////////////////////////////////////////
void InstanceMgr::destroyInstance()
{

}

//////////////////////////////////////////////////////////////////////////
InstanceMgr::InstanceMgr()
{
	m_idCurInstance = 10011;
	m_nFightLeftTime = 0;
	m_nFightCount = 0;
	m_nResetTime = 0;
	m_nSearchingLeftTime = 0;
	m_nSearchingCount = 0;
	m_mapInstanceInfo.clear();
}

////////////////////////////////////////////////////////////////////////
// Description: ��Ӹ����б���Ϣ
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool InstanceMgr::addInstanceInfo(ST_INSTANCE_LIST_INFO& stInfo)
{
	if (stInfo.sSearchingFlag > 0)
	{
		m_idCurInstance = stInfo.idInstance;
	}
	m_mapInstanceInfo[stInfo.idInstance] = stInfo;
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: �ؿ�ս��ʤ��
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
void InstanceMgr::winFight()
{
	CHECK(m_idCurInstance);
	CHECK(this->setPassFlag(m_idCurInstance));

	// ֪ͨview�������
	auto sceneMain = Root::getInstance()->getSceneMain();
	CHECK_NOLOG(sceneMain);
	auto layerInstanceView = (LayerInstanceView*)sceneMain->getChildByName("LayerInstanceView");
	CHECK_NOLOG(layerInstanceView);
	CHECK(layerInstanceView->winFight());

	// ֪ͨmap�������
	auto layerInstanceMap = (LayerInstanceMap*)sceneMain->getChildByName("LayerInstanceMap");
	CHECK_NOLOG(layerInstanceMap);
	CHECK(layerInstanceMap->updateMap(m_idCurInstance));
}

////////////////////////////////////////////////////////////////////////
// Description: �жϹؿ��Ƿ�ͨ��
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool InstanceMgr::isPass(OBJID idInstance)
{
	CHECKF(idInstance);
	auto iter = m_mapInstanceInfo.find(idInstance);
	if (iter != m_mapInstanceInfo.end())
	{
		return (iter->second.sPassFlag > 0);
	}
	return false;
}

////////////////////////////////////////////////////////////////////////
// Description: ����ͨ�ر��
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool InstanceMgr::setPassFlag(OBJID idInstance)
{
	CHECKF(idInstance);
	auto iter = m_mapInstanceInfo.find(idInstance);
	CHECKF(iter != m_mapInstanceInfo.end());
	iter->second.sPassFlag = 1;
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: �жϹؿ��Ƿ�����̽��
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool InstanceMgr::isSearching(OBJID idInstance)
{
	CHECKF(idInstance);
	auto iter = m_mapInstanceInfo.find(idInstance);
	if (iter != m_mapInstanceInfo.end())
	{
		return (iter->second.sSearchingFlag > 0);
	}
	return false;
}

////////////////////////////////////////////////////////////////////////
// Description: ����̽�����
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool InstanceMgr::setSearchingFlag(OBJID idInstance, int nFlag)
{
	CHECKF(idInstance);
	auto iter = m_mapInstanceInfo.find(idInstance);
	if (iter != m_mapInstanceInfo.end())
	{
		iter->second.sSearchingFlag = nFlag;
	}
	else
	{
		ST_INSTANCE_LIST_INFO stInfo = { 0 };
		stInfo.idInstance	  = idInstance;
		stInfo.sPassFlag	  = 0;
		stInfo.sSearchingFlag = nFlag;
		m_mapInstanceInfo[idInstance] = stInfo;
	}
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: ��ȡ���̽������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
int	InstanceMgr::getSearchingMaxCount()
{
	return (MoneyMgr::getInstance()->getMoney(USER_MONEY_TYPE_ExploreMaxBuy) + INSTANCE_SERACHING_INIT_COUNT);
}

////////////////////////////////////////////////////////////////////////
// Description: �жϸ�ģʽ�Ƿ�ͨ��
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool InstanceMgr::isModeThrough(int nChapter, int nMode)
{
	CHECKF(nChapter && nMode);
	VEC_DB_KEY vecKey;
	ConstTableMgr::getInstance()->EnumKey(CONST_TABLE_TYPE_instance, vecKey);
	bool bCheckResult = false;
	for (auto iter : vecKey)
	{
		CHECKC_NOLOG(nChapter == ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_instance, iter, INSTANCE_DATA_CHAPTER));
		CHECKC_NOLOG(nMode == ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_instance, iter, INSTANCE_DATA_MODE));
		if (!this->isPass(iter))
		{
			return false;
		}
		bCheckResult = true;
	}
	return bCheckResult;
}

////////////////////////////////////////////////////////////////////////
// Description: ����Ƿ��ܹ�̽���ùؿ�
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool InstanceMgr::checkSearching(OBJID idInstance)
{
	CHECKF(idInstance);
	CHECKF_NOLOG(idInstance != m_idCurInstance);
	
	// �Ѿ�̽����
	if (m_mapInstanceInfo.find(idInstance) != m_mapInstanceInfo.end())
	{
		return true;
	}

	// ���ؿ��Ƿ����
	if (!ConstTableMgr::getInstance()->IsExistSingle(CONST_TABLE_TYPE_instance, idInstance))
	{
		return false;
	}

	// �����һ�ؿ��Ƿ�ͨ��
	if (ConstTableMgr::getInstance()->IsExistSingle(CONST_TABLE_TYPE_instance, idInstance - 1))
	{
		return this->isPass(idInstance - 1);
	}

	// ����ѡ��Ĺؿ��Ѷ��ж�
	auto nChapter = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_instance, idInstance, INSTANCE_DATA_CHAPTER);
	auto nMode = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_instance, idInstance, INSTANCE_DATA_MODE);

	// �����һ�Ѷ��Ƿ�ͨ��
	if (nMode != E_INSTANCE_MODE_TYPE_EASY)
	{
		return this->isModeThrough(nChapter, nMode - 1);
	}

	// �����һ���Ƿ�ͨ��,ͨ�غ�����ս��
	if (nChapter > 1)
	{
		if (this->isModeThrough(nChapter - 1, nMode))
		{
			return (UserAttrMgr::getInstance()->getAttr(USER_ATTR_score_max) >= ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_instance, idInstance, INSTANCE_DATA_OPEN_SCORE));
		}
		return false;
	}
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: ��ʱ����
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
void InstanceMgr::update(void)
{
	auto sceneMain = Root::getInstance()->getSceneMain();
	CHECK_NOLOG(sceneMain);
	auto layerInstanceView = (LayerInstanceView*)sceneMain->getChildByName("LayerInstanceView");
	CHECK_NOLOG(layerInstanceView);

	// ����ս��ʣ��ʱ��
	if (m_nFightLeftTime > 0)
	{
		m_nFightLeftTime--;
		layerInstanceView->updateFightTime(m_nFightLeftTime);

		if (0 == m_nFightLeftTime)
		{
			layerInstanceView->openWarning();
		}
	}

	// ����̽��ʣ��ʱ��
	if (m_nSearchingLeftTime > 0)
	{
		m_nSearchingLeftTime--;
		if (0 == m_nSearchingLeftTime)
		{
			m_nSearchingLeftTime = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_instance, m_idCurInstance, INSTANCE_DATA_SEARCHING_TIME);
			if (m_nSearchingCount < this->getSearchingMaxCount())
			{
				m_nSearchingCount++;
				layerInstanceView->setSearchingCount(m_nSearchingCount);
			}
		}
		layerInstanceView->updateSearchingTime(m_nSearchingLeftTime);
	}
}

////////////////////////////////////////////////////////////////////////
// Description: ��������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool InstanceMgr::updateInstanceInfo(OBJID idInstance,
	int nFightLeftTime,
	int nFightCount,
	int nResetTime,
	int nSearchingLeftTime,
	int nSearchingCount,
	int nCommentCount)
{
	CHECKF(idInstance);
	CHECKF(this->setSearchingFlag(m_idCurInstance, 0));
	CHECKF(this->setSearchingFlag(idInstance, 1));
	m_idCurInstance		 = idInstance;
	m_nFightLeftTime	 = nFightLeftTime;
	m_nFightCount		 = nFightCount;
	m_nResetTime		 = nResetTime;
	m_nSearchingLeftTime = nSearchingLeftTime;
	m_nSearchingCount	 = nSearchingCount;
	m_nCommentCount		 = nCommentCount;
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: ����̽���ؿ�
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool InstanceMgr::updateSearchingPass(void)
{
	// ֪ͨ������������ؿ�
	auto sceneMain = Root::getInstance()->getSceneMain();
	CHECKF_NOLOG(sceneMain);
	auto layerInstanceView = (LayerInstanceView*)sceneMain->getChildByName("LayerInstanceView");
	CHECKF_NOLOG(layerInstanceView);
	layerInstanceView->changePass(ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_instance, m_idCurInstance, INSTANCE_DATA_PASS));
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: ����̽������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool InstanceMgr::updateSearchingCount(void)
{
	auto sceneMain = Root::getInstance()->getSceneMain();
	CHECKF_NOLOG(sceneMain);
	auto layerInstanceView = (LayerInstanceView*)sceneMain->getChildByName("LayerInstanceView");
	CHECKF_NOLOG(layerInstanceView);
	layerInstanceView->setSearchingCount(m_nSearchingCount);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: �������̽������
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool InstanceMgr::updateMaxSearchingCount(void)
{
	auto nSearchingMaxCount = this->getSearchingMaxCount();
	auto sceneMain = Root::getInstance()->getSceneMain();
	CHECKF_NOLOG(sceneMain);
	// ����view����
	auto layerInstanceView = (LayerInstanceView*)sceneMain->getChildByName("LayerInstanceView");
	if (layerInstanceView)
	{
		layerInstanceView->setSearchingMaxCount(nSearchingMaxCount);
	}

	// ����̽���������
	auto layerInstanceSearchingResult = (LayerInstanceSearchingResult*)sceneMain->getChildByName("LayerInstanceSearchingResult");
	if (layerInstanceSearchingResult)
	{
		layerInstanceSearchingResult->setSearchingMaxCount(nSearchingMaxCount);
	}

	// ���¹������
	auto layerInstanceSearchingBuy = (LayerInstanceSearchingBuy*)sceneMain->getChildByName("LayerInstanceSearchingBuy");
	if (layerInstanceSearchingBuy)
	{
		layerInstanceSearchingBuy->setSearchingMaxCount(nSearchingMaxCount);
	}
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: ����̽�����������Ϣ
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool InstanceMgr::updateSearchingResult(const std::vector<ST_AWARD_INFO>& vecInfo)
{
	CHECKF(vecInfo.size() > 0);
	auto sceneMain = Root::getInstance()->getSceneMain();
	CHECKF_NOLOG(sceneMain);
	auto layerInstanceSearchingResult = (LayerInstanceSearchingResult*)sceneMain->getChildByName("LayerInstanceSearchingResult");
	if (!layerInstanceSearchingResult)
	{
		layerInstanceSearchingResult = LayerInstanceSearchingResult::create();
		CHECKF_NOLOG(layerInstanceSearchingResult);
		sceneMain->addChild(layerInstanceSearchingResult);
	}
	layerInstanceSearchingResult->updateAwardInfo(vecInfo);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: ���¹�����Ϣ
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool InstanceMgr::updateStrategy(OBJID idCommentType)
{
	CHECKF(idCommentType);
	auto sceneMain = Root::getInstance()->getSceneMain();
	CHECKF_NOLOG(sceneMain);
	auto layerInstanceStrategy = (LayerInstanceStrategy*)sceneMain->getChildByName("LayerInstanceStrategy");
	if (!layerInstanceStrategy)
	{
		layerInstanceStrategy = LayerInstanceStrategy::create();
		CHECKF_NOLOG(layerInstanceStrategy);
		sceneMain->addChild(layerInstanceStrategy);
	}
	layerInstanceStrategy->updateStrategy(idCommentType);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: �����µĹ�����Ϣ
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool InstanceMgr::updateStrategyNew(OBJID idCommentType, const COMMENT_INFO& info)
{
	CHECKF(idCommentType);
	auto sceneMain = Root::getInstance()->getSceneMain();
	CHECKF_NOLOG(sceneMain);
	auto layerInstanceStrategy = (LayerInstanceStrategy*)sceneMain->getChildByName("LayerInstanceStrategy");
	if (!layerInstanceStrategy)
	{
		layerInstanceStrategy = LayerInstanceStrategy::create();
		CHECKF_NOLOG(layerInstanceStrategy);
		sceneMain->addChild(layerInstanceStrategy);
	}
	layerInstanceStrategy->updateStrategyNew(idCommentType, info);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: ���¹�����Ϣ
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool InstanceMgr::updateStrategyGood(OBJID idCommentType, const COMMENT_INFO& info)
{
	CHECKF(idCommentType);
	auto sceneMain = Root::getInstance()->getSceneMain();
	CHECKF_NOLOG(sceneMain);
	auto layerInstanceStrategy = (LayerInstanceStrategy*)sceneMain->getChildByName("LayerInstanceStrategy");
	if (!layerInstanceStrategy)
	{
		layerInstanceStrategy = LayerInstanceStrategy::create();
		CHECKF_NOLOG(layerInstanceStrategy);
		sceneMain->addChild(layerInstanceStrategy);
	}
	layerInstanceStrategy->updateStrategyGood(idCommentType, info);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: ��ø���key
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
OBJID InstanceMgr::getInstanceKey(int nMode, int nChapter, int nPass)
{
	CHECKF(nMode && nChapter && nPass);
	return (nMode * 10000 + nChapter * 10 + nPass);
}
////////////////////////////////////////////////////////////////////////