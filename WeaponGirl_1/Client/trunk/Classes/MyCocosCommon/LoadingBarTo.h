////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LoadingBarTo.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/08/21
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_NODE_LOADING_BAR_TO_H_
#define _JYP_NODE_LOADING_BAR_TO_H_

#include "Global/Global.h"

class LoadingBarTo : public ActionInterval
{
public:
	/**
	* Creates and initializes with a duration and a percent
	* @param duration in seconds
	*/
	static LoadingBarTo* create(float duration, float percent);

	//
	// Overrides
	//
	virtual LoadingBarTo* clone() const override;
	virtual LoadingBarTo* reverse() const override;
	virtual void startWithTarget(Node *target) override;
	/**
	* @param time in seconds
	*/
	virtual void update(float time) override;

CC_CONSTRUCTOR_ACCESS:
	LoadingBarTo() {}
	virtual ~LoadingBarTo() {}

	/**
	* Initializes with a duration and a percent
	* @param duration in seconds
	*/
	bool initWithDuration(float duration, float percent);

protected:
	float _to;
	float _from;
	 
private:
	CC_DISALLOW_COPY_AND_ASSIGN(LoadingBarTo);
};


#endif // end of _JYP_NODE_LOADING_BAR_TO_H_