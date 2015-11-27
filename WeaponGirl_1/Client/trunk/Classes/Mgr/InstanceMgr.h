////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: InstanceMgr.h
// Author: 陈建军(Chen Jianjun)
// Created: 2015-11-13
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_INSTANCE_MGR_H_
#define _JYP_INSTANCE_MGR_H_

#include "Global/Global.h"
class InstanceMgr : public Ref
{
public:
	static InstanceMgr*	getInstance();
	static void			destroyInstance();
private:
	InstanceMgr();
	static InstanceMgr*	m_pInstance;

public:
	void	update				(void);

	bool	addInstanceInfo		(ST_INSTANCE_LIST_INFO& stInfo);
	const std::map<OBJID, ST_INSTANCE_LIST_INFO>* getInstanceInfo() { return &m_mapInstanceInfo; }
	bool	isPass				(OBJID idInstance);
	bool	setPassFlag			(OBJID idInstance);
	bool	isSearching			(OBJID idInstance);
	bool	setSearchingFlag	(OBJID idInstance, int nFlag);
	int		getSearchingMaxCount(void);
	bool	isModeThrough		(int nChapter, int nMode);
	bool	checkSearching		(OBJID idInstance);

	void	winFight				(void);
	bool	updateInstanceInfo		(	OBJID idInstance,
										int nFightLeftTime,
										int nFightCount,
										int nResetTime,
										int nSearchingLeftTime,
										int nSearchingCount,
										int nCommentCount);

	bool	updateSearchingPass		(void);
	bool	updateSearchingCount	(void);
	bool	updateMaxSearchingCount	(void);
	bool	updateSearchingResult	(const std::vector<ST_AWARD_INFO>& vecInfo);
	bool	updateStrategy			(OBJID idCommentType);
	bool	updateStrategyNew		(OBJID idCommentType, const COMMENT_INFO& info);
	bool	updateStrategyGood		(OBJID idCommentType, const COMMENT_INFO& info);

	OBJID	getInstanceKey		(int nMode, int nChapter, int nPass);

protected:
	CC_SYNTHESIZE_READONLY(OBJID,	m_idCurInstance,		idCurInstance);		// 当前选中的副本id
	CC_SYNTHESIZE_READONLY(int,		m_nFightLeftTime,		FightLeftTime);		// 战斗剩余时间
	CC_SYNTHESIZE_READONLY(int,		m_nFightCount,			FightCount);		// 战斗次数
	CC_SYNTHESIZE_READONLY(int,		m_nResetTime,			ResetTime);			// 消耗重置时间
	CC_SYNTHESIZE_READONLY(int,		m_nSearchingLeftTime,	SearchingLeftTime);	// 探索剩余时间
	CC_SYNTHESIZE_READONLY(int,		m_nSearchingCount,		SearchingCount);	// 探索次数
	CC_SYNTHESIZE_READONLY(int,		m_nCommentCount,		CommentCount);		// 攻略数
	std::map<OBJID, ST_INSTANCE_LIST_INFO>	m_mapInstanceInfo;		// 副本信息

	CC_SYNTHESIZE(std::string,		m_strStrategyText,		StrategyText);		// 缓存准备发布的攻略内容
};

#endif // end of _JYP_INSTANCE_MGR_H_