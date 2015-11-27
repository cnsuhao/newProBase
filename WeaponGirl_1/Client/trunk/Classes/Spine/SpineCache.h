////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2015, WuHan GoodGame, All Rights Reserved
// Moudle: SpineCache.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015-1-29
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_SPINE_CACHE_H_
#define _JYP_SPINE_CACHE_H_

#include "Global/Global.h"

struct ST_SPINE_DATA
{
	float			fScale;
	bool			bOwner;
	spSkeletonData*	pData;
	spAtlas*		pAtlas;
};

class SpineBase;
class SpineCache : public Ref
{
public:
	static SpineCache*	getInstance();
	static void			destroyInstance();
private:
	static SpineCache*	m_pInstance;
	SpineCache();
	~SpineCache();

public:
	bool			proloadCache(void);
	bool			getSkeletonInfo(OBJID idSpineType, OUT ST_SPINE_DATA& rData);
	void			onTimerProloadCache(void);

private:
	bool			loadCacheData(OBJID idSpineType, OUT ST_SPINE_DATA& rData);


private:
	std::map<OBJID, ST_SPINE_DATA>	m_mapData;
	SET_OBJID						m_setProloadType;
};

#endif