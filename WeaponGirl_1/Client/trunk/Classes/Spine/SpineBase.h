////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2015, WuHan GoodGame, All Rights Reserved
// Moudle: SpineBase.h
//			该类不得直接初始化, init函数提供给子类使用
// Author: 彭文奇(Peng Wenqi)
// Created: 2015-2-2
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_SPINE_BASE_H_
#define _JYP_SPINE_BASE_H_

#include "Global/Global.h"
#include "SpineCache.h"

enum SPINE_ANIMATION
{
	SPINE_ANIMATION_NONE = 0,		// 没动作
	SPINE_ANIMATION_IDLE,			// 休闲
	SPINE_ANIMATION_ATTACK1,		// 攻击1
	SPINE_ANIMATION_ATTACK2,		// 攻击2
};

class SpineBase : public SkeletonAnimation
{
protected:
	SpineBase();
	virtual ~SpineBase();

protected:
	bool		initSpine(OBJID idSpineType, BORN_FROM bBornFrom = BORN_FROM_LEFT);

public:
	void		setBornFrom(BORN_FROM eBornFrom);
	BORN_FROM	getBornFrom() const;
	virtual void updateColor();
	virtual void onAnimationStateEvent(int trackIndex, spEventType type, spEvent* event, int loopCount);

	void		doAnimation(SPINE_ANIMATION eAnimation, bool bLoop = false, const CompleteListener& listener = nullptr);
	void		setShaderEffect(MY_SHADER_EFFECT eEffect);

	Vec2		getBonePosition(const std::string& rBoneName) const;
	Vec2		getBoneWorldPosition(const std::string& rBoneName) const;
	Vec2		getSlotWorldPosition(const std::string& rSlotName) const;

	void		onEvent(int trackIndex, const char* pszEventName, int nData, float fData);


	//////////////////////////////////////////////////////////////////////////
	CC_SYNTHESIZE_READONLY(OBJID,			m_idSpineType,		SpineType);
	CC_SYNTHESIZE_READONLY(bool,			m_bOwner,			Owner);
	CC_SYNTHESIZE_READONLY(spAtlas*,		m_pAtlas,			Atlas);
	CC_SYNTHESIZE_READONLY(SPINE_ANIMATION, m_eAnimation,		Animation);
	CC_SYNTHESIZE_READONLY(MY_SHADER_EFFECT,m_eShaderEffect,	ShaderEffect);
	CC_SYNTHESIZE_READONLY(bool,			m_bAttackOverDelay, AttackOverDelay);
	CC_SYNTHESIZE_READONLY(bool,			m_bCanNotSetupPose, CanNotSetupPose);
};

#endif // end of _JYP_SPINE_BASE_H_