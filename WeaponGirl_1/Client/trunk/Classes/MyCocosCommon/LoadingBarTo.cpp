////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LoadingBarTo.cpp
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/08/21
////////////////////////////////////////////////////////////////////////
#include "LoadingBarTo.h"

//////////////////////////////////////////////////////////////////////////
LoadingBarTo* LoadingBarTo::create(float duration, float percent)
{
	LoadingBarTo *progressTo = new (std::nothrow) LoadingBarTo();
	progressTo->initWithDuration(duration, percent);
	progressTo->autorelease();

	return progressTo;
}

//////////////////////////////////////////////////////////////////////////
LoadingBarTo* LoadingBarTo::clone() const
{
	// no copy constructor    
	auto a = new (std::nothrow) LoadingBarTo();
	a->initWithDuration(_duration, _to);
	a->autorelease();
	return a;
}

//////////////////////////////////////////////////////////////////////////
LoadingBarTo* LoadingBarTo::reverse() const
{
	CCASSERT(false, "reverse() not supported in LoadingBarTo");
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////
void LoadingBarTo::startWithTarget(Node *target)
{
	ActionInterval::startWithTarget(target);
	auto loadingBar = dynamic_cast<ui::LoadingBar*>(target);
	if (loadingBar)
	{
		_from = loadingBar->getPercent();
	}
	
}

//////////////////////////////////////////////////////////////////////////
void LoadingBarTo::update(float time)
{
	auto loadingBar = dynamic_cast<ui::LoadingBar*>(_target);
	loadingBar->setPercent(_from + (_to - _from) * time);
}

//////////////////////////////////////////////////////////////////////////
bool LoadingBarTo::initWithDuration(float duration, float percent)
{
	if (ActionInterval::initWithDuration(duration))
	{
		_to = percent;

		return true;
	}

	return false;
}
