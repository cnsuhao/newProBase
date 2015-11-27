////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: BulletMoveTo.cpp
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/08/13
////////////////////////////////////////////////////////////////////////
#include "BulletMoveTo.h"

//////////////////////////////////////////////////////////////////////////
BulletMoveTo* BulletMoveTo::create(float t, const Vec2& target)
{
	BulletMoveTo *bulletMove = new (std::nothrow) BulletMoveTo();
	bulletMove->initWithDuration(t, target);
	bulletMove->autorelease();
	return bulletMove;
}

//////////////////////////////////////////////////////////////////////////
void BulletMoveTo::startWithTarget(Node *target)
{
	int nModifyY = 175 + ::RandGet(50);
	_toConfig.endPosition = m_posTarget;
	_toConfig.controlPoint_1.x = (target->getPositionX() + m_posTarget.x) / 2.f;
	_toConfig.controlPoint_1.y = nModifyY + (target->getPositionY() + m_posTarget.y) / 2.f;

	_toConfig.controlPoint_2.x = (target->getPositionX() + m_posTarget.x) / 2.f;
	_toConfig.controlPoint_2.y = nModifyY + (target->getPositionY() + m_posTarget.y) / 2.f;

// 	if (target->getPositionX() > m_posTarget.x)
// 	{
// 		_toConfig.controlPoint_2.x = (target->getPositionX() + m_posTarget.x) * 0.75f;
// 	}
// 	else
// 	{
// 		_toConfig.controlPoint_2.x = (target->getPositionX() + m_posTarget.x) * 0.25f;
// 	}
// 	_toConfig.controlPoint_2.y = 160 + (target->getPositionY() + m_posTarget.y) / 2.f;

	BezierTo::startWithTarget(target);
}

//////////////////////////////////////////////////////////////////////////
BulletMoveTo* BulletMoveTo::clone() const
{
	// no copy constructor
	auto a = new (std::nothrow) BulletMoveTo();
	a->initWithDuration(_duration, m_posTarget);
	a->autorelease();
	return a;
}

//////////////////////////////////////////////////////////////////////////
void BulletMoveTo::update(float time)
{
	BezierTo::update(time);
	const float HALF_TIME = 0.55f;
	
	if (_target && _duration > 0.1f)
	{
		if (_startPosition.x < _toConfig.endPosition.x)
		{
			if (time < HALF_TIME)
			{
				float fPercent = 1.f - time / HALF_TIME;
				_target->setRotation(-30 * fPercent);
//				CCLOG("a: %f - %f  [%f]", fPercent, _target->getRotation(), time);
			}
			else
			{
				float fPercent = (time - HALF_TIME) / (1.f - HALF_TIME);
				_target->setRotation(30 * fPercent);
//				CCLOG("b: %f - %f  [%f]", fPercent, _target->getRotation(), time);
			}
		}
		else
		{
			if (time < HALF_TIME)
			{
				float fPercent = 1.f - time / HALF_TIME;
				_target->setRotation(30 * fPercent);
//				CCLOG("c: %f - %f  [%f]", fPercent, _target->getRotation(), time);
			}
			else
			{
				float fPercent = (time - HALF_TIME) / (1.f - HALF_TIME);
				_target->setRotation(-30 * fPercent);
//				CCLOG("d: %f - %f  [%f]", fPercent, _target->getRotation(), time);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
bool BulletMoveTo::initWithDuration(float t, const Vec2& target)
{
	if (ActionInterval::initWithDuration(t))
	{
		m_posTarget = target;
		return true;
	}

	return false;
}
