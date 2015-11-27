////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2015, WuHan GoodGame, All Rights Reserved
// Moudle: Root.h
// Author: 彭文奇(Peng Wenqi)
//	全局单例根节点
// Created: 2015-1-20
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_ROOT_H_
#define _JYP_ROOT_H_

#include "Global/Global.h"
#include "ConstTable/ConstTableMgr.h"
#include "Audio/Audio.h"
#include "Network/NetworkServe.h"
#include "SaveData/SaveData.h"
#include "Spine/SpineCache.h"
#include "Mgr/LogicDataMgr.h"
#include "Mgr/BattleDataMgr.h"

class SceneBattle;
class SceneMain;
class SceneLogin;
class Root : public Ref, public SceneNetworkProtocol
{
public:
	static Root*	getInstance();
	static void		destroyInstance();
private:
	static Root*	m_pInstance;

public:
	bool init();
	void release();

public:
	virtual void OnConnectOK();
	virtual void OnConnectBreak();

public:
	bool isNeedReconnectBreakCode(int nBreakCode);

protected:
	CC_SYNTHESIZE(SceneLogin*,	m_pSceneLogin,		SceneLogin);
	CC_SYNTHESIZE(SceneMain*,	m_pSceneMain,		SceneMain);
	CC_SYNTHESIZE(SceneBattle*, m_pSceneBattle,		SceneBattle);

protected:
	void onTimerFastest(float dt);
	void onTimerSecond(float dt);
	void onTimerMinute(float dt);

public:
	void autoClearCache();
	void popMessageBox(const std::string& message, const std::string& title = "", MESSAGE_BOX_MODE mode = MESSAGE_BOX_MODE_OK, bool bCloseByBg = false,
		MessageBoxClickCallback callback = nullptr, Ref* pRef = nullptr);
	void processConnectFailed();
};

#endif // end of _JYP_ROOT_H_