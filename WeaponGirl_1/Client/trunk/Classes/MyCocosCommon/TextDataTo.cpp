////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: TextDataTo.cpp
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/08/22
////////////////////////////////////////////////////////////////////////
#include "TextDataTo.h"

//////////////////////////////////////////////////////////////////////////
TextDataTo* TextDataTo::create(float duration, int nFrom, int nTo)
{
	TextDataTo *progressTo = new (std::nothrow) TextDataTo();
	progressTo->initWithDuration(duration, nFrom, nTo);
	progressTo->autorelease();

	return progressTo;
}

//////////////////////////////////////////////////////////////////////////
TextDataTo* TextDataTo::clone() const
{
	// no copy constructor    
	auto a = new (std::nothrow) TextDataTo();
	a->initWithDuration(_duration, _from, _to);
	a->autorelease();
	return a;
}

//////////////////////////////////////////////////////////////////////////
TextDataTo* TextDataTo::reverse() const
{
	// no copy constructor    
	auto a = new (std::nothrow) TextDataTo();
	a->initWithDuration(_duration, _to, _from);
	a->autorelease();
	return a;
}

//////////////////////////////////////////////////////////////////////////
void TextDataTo::startWithTarget(Node *target)
{
	ActionInterval::startWithTarget(target);
}

//////////////////////////////////////////////////////////////////////////
void TextDataTo::update(float time)
{
	auto text = dynamic_cast<ui::Text*>(_target);
	if (text)
	{
		int nData = _from + (_to - _from) * time;
		text->setString(StringUtils::format("%d", nData));
	}
}

//////////////////////////////////////////////////////////////////////////
bool TextDataTo::initWithDuration(float duration, int nFrom, int nTo)
{
	if (ActionInterval::initWithDuration(duration))
	{
		_from = nFrom;
		_to = nTo;

		return true;
	}

	return false;
}
