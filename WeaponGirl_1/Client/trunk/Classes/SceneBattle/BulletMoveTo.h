////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: BulletMoveTo.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/08/13
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_NODE_BULLET_MOVE_TO_H_
#define _JYP_NODE_BULLET_MOVE_TO_H_

#include "Global/Global.h"

class BulletMoveTo : public BezierTo
{
public:
	static BulletMoveTo* create(float t, const Vec2& target);

	//
	// Overrides
	//
	virtual void startWithTarget(Node *target) override;
	virtual BulletMoveTo* clone() const override;

	/**
	* @param time in seconds
	*/
	virtual void update(float time) override;

protected:
	BulletMoveTo() {}
	virtual ~BulletMoveTo() {}
	/**
	* @param t in seconds
	*/
	bool initWithDuration(float t, const Vec2& target);

	Vec2	m_posTarget;
};
#endif // end of _JYP_NODE_BULLET_MOVE_TO_H_