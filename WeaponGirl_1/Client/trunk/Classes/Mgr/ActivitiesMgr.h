////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: ActivitiesMgr.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/11/05
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_ActivitiesMgr_H_
#define _JYP_ActivitiesMgr_H_

#include "Global/Global.h"

class ActivitiesMgr : public Ref
{
public:
	static ActivitiesMgr*	getInstance();
	static void			destroyInstance();
private:
	ActivitiesMgr();
	static ActivitiesMgr*	m_pInstance;

public:
	void updateActivity(const Activity_Info& info);
	void deleteActivity(ACTIVITY_CONFIG_TYPE eType);
	bool isActivityRunning(ACTIVITY_CONFIG_TYPE eType) const;

protected:
	std::map<ACTIVITY_CONFIG_TYPE, Activity_Info> m_mapData;
};

#endif // end of _JYP_ActivitiesMgr_H_