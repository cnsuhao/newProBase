////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-2016, WuHan GoodGame, All Rights Reserved
// Moudle: SpriteFrameAnimate.h
// Author: ¿Ó√ŒÀ…(MengSong Lee)
// Created: 2015-3-30
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_FRAME_ANIMATE_SPRITE_H_
#define _JPY_FRAME_ANIMATE_SPRITE_H_

#include "Global/Global.h"

class FrameAnimate;
typedef std::function<void(FrameAnimate* animate)> FrameAnimateListener;

/** @brief Animates a sprite given the name of an Animation */
class FrameAnimate : public ActionInterval
{
public:
    /** creates the action with an Animation and will restore the original frame when the animation is over */
    static FrameAnimate* create(Animation *animation);

    /** sets the Animation object to be animated */
    void setAnimation( Animation* animation );
    /** returns the Animation object that is being animated */
    Animation* getAnimation() { return _animation; }
    const Animation* getAnimation() const { return _animation; }

    //
    // Overrides
    //
    virtual FrameAnimate* clone() const override;
    virtual FrameAnimate* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    /**
     * @param t in seconds
     */
    virtual void update(float t) override;
	void resetAnimate();

CC_CONSTRUCTOR_ACCESS:
    FrameAnimate();
    virtual ~FrameAnimate();

    /** initializes the action with an Animation and will restore the original frame when the animation is over */
    bool initWithAnimation(Animation *animation);

protected:
	CC_SYNTHESIZE_READONLY(int, _nextFrame, NextFrame);
	CC_SYNTHESIZE_READONLY(float, _nextFrameTime, NextFrameTime);
	CC_SYNTHESIZE_READONLY(unsigned int, _executedLoops, ExecutedLoops);
	CC_SYNTHESIZE(bool, _isLimitExecute, IsLimitExecute);
	CC_SYNTHESIZE(float, _limitExecuteTimes, LimitExecuteTimes);
	CC_SYNTHESIZE(float, _delayStart, DelayStart);
	CC_SYNTHESIZE(FrameAnimateListener, _callbackAnimateUpdate, AnimateUpdateCallback);
	CC_SYNTHESIZE(FrameAnimateListener, _callbackAnimateStop, AnimateStopCallback);
protected:
    SpriteFrame*    _origFrame;
    Animation*      _animation;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(FrameAnimate);
};

class SpriteFrameAnimate;
typedef std::function<void(SpriteFrameAnimate* animateSprite, FrameAnimate* animate)> SpriteFrameAnimateListener;

class SpriteFrameAnimate : public Sprite
{
public:
	SpriteFrameAnimate();
	~SpriteFrameAnimate();

public:
	static SpriteFrameAnimate* createWithId(DB_KEY idAnimation);
	static SpriteFrameAnimate* createAndPlay(DB_KEY idAnimation, const SpriteFrameAnimateListener& updateListener = nullptr, const SpriteFrameAnimateListener& stopListener = nullptr);
	bool initWithId(DB_KEY idAnimation);
	Animation* getAnimation() {return m_animationCfg;}
	const Animation* getAnimation() const {return m_animationCfg;}
	float getPlayTime() const;

protected:
	bool setAnimation(Animation* animation);
	FrameAnimate* createFrameAnimate();

public:
	void playAnimate();
	void callbackAnimateUpdate(FrameAnimate* animate);
	void callbackAnimateStop(FrameAnimate* animate);



protected:
	CC_SYNTHESIZE_READONLY(DB_KEY,			m_idAnimate,				AnimateId);
	CC_SYNTHESIZE_READONLY(Animation*,		m_animationCfg,				AnimationCfg);
	CC_SYNTHESIZE_READONLY(float,			m_fPlayScale,				PlayScale);
	CC_SYNTHESIZE(bool,		m_bIsLimitExecute,		IsLimitExecute);
	CC_SYNTHESIZE(float,	m_fLimitExecuteTimes,	LimitExecuteTimes);
	CC_SYNTHESIZE(float,	m_fDelayStart,			DelayStart);
	CC_SYNTHESIZE(SpriteFrameAnimateListener, m_callbackAnimateUpdate, AnimateUpdateCallback);
	CC_SYNTHESIZE(SpriteFrameAnimateListener, m_callbackAnimateStop, AnimateStopCallback);
};

#endif