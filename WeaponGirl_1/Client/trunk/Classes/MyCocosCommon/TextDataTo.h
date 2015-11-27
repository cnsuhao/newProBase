////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: TextDataTo.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/08/22
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_NODE_TEXT_DATA_TO_H_
#define _JYP_NODE_TEXT_DATA_TO_H_

#include "Global/Global.h"

class TextDataTo : public ActionInterval
{
public:
	/**
	* Creates and initializes with a duration and a percent
	* @param duration in seconds
	*/
	static TextDataTo* create(float duration, int nFrom, int nTo);

	//
	// Overrides
	//
	virtual TextDataTo* clone() const override;
	virtual TextDataTo* reverse() const override;
	virtual void startWithTarget(Node *target) override;
	/**
	* @param time in seconds
	*/
	virtual void update(float time) override;

CC_CONSTRUCTOR_ACCESS:
	TextDataTo() {}
	virtual ~TextDataTo() {}

	/**
	* Initializes with a duration and a percent
	* @param duration in seconds
	*/
	bool initWithDuration(float duration, int nFrom, int nTo);

protected:
	int _to;
	int _from;

private:
	CC_DISALLOW_COPY_AND_ASSIGN(TextDataTo);
};


#endif // end of _JYP_NODE_TEXT_DATA_TO_H_