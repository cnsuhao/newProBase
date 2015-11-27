////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: UserAttrMgr.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/10/16
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_UserAttrMgr_H_
#define _JYP_UserAttrMgr_H_

#include "Global/Global.h"

class UserAttrMgr : public Ref
{
public:
	static UserAttrMgr*	getInstance();
	static void			destroyInstance();
private:
	UserAttrMgr();
	static UserAttrMgr*	m_pInstance;

public:
	int64_t	getAttr(USER_ATTR eAttr) const;
	void updateAttr(USER_ATTR eAttr, int64_t data);

protected:
	std::map<USER_ATTR, int64_t> m_mapData;
};

#endif // end of _JYP_UserAttrMgr_H_