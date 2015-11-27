////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-2016, WuHan GoodGame, All Rights Reserved
// Moudle: SpriteFrameAnimate.cpp
// Author: ������(MengSong Lee)
// Created: 2015-3-30
////////////////////////////////////////////////////////////////////////

#include "SpriteFrameAnimate.h"
#include "ConstTable\ConstTableMgr.h"
#include "2d\CCActionInterval.h"


//
// FrameAnimate
//
FrameAnimate* FrameAnimate::create(Animation *animation)
{
	FrameAnimate *animate = new (std::nothrow) FrameAnimate();
	animate->initWithAnimation(animation);
	animate->autorelease();

	return animate;
}

FrameAnimate::FrameAnimate()
	: _nextFrame(0)
	, _nextFrameTime(0.f)
	, _origFrame(nullptr)
	, _executedLoops(0)
	, _animation(nullptr)
	, _isLimitExecute(false)
	, _limitExecuteTimes(0.f)
	, _delayStart(0.f)
	, _callbackAnimateUpdate(nullptr)
	, _callbackAnimateStop(nullptr)
{

}

FrameAnimate::~FrameAnimate()
{
	CC_SAFE_RELEASE(_animation);
	CC_SAFE_RELEASE(_origFrame);
}

bool FrameAnimate::initWithAnimation(Animation* animation)
{
	CCASSERT(animation != nullptr, "FrameAnimate: argument Animation must be non-nullptr");

	float singleDuration = animation->getDuration();
	if (ActionInterval::initWithDuration(singleDuration * animation->getLoops() + _delayStart))
	{
		_nextFrame = 0;
		_nextFrameTime = 0.f;
		_animation = animation;
		_origFrame = nullptr;
		_executedLoops = 0;
		CC_SAFE_RETAIN(animation);
		return true;
	}
	return false;
}

void FrameAnimate::resetAnimate()
{
	CCASSERT(_animation != nullptr, "FrameAnimate: argument Animation must be exist");

	float singleDuration = _animation->getDuration();
	if (ActionInterval::initWithDuration(singleDuration * _animation->getLoops() + _delayStart))
	{
		CC_SAFE_RELEASE(_origFrame);
		_nextFrame = 0;
		_nextFrameTime = 0.f;
		_origFrame = nullptr;
		_executedLoops = 0;
	}
}

void FrameAnimate::setAnimation(cocos2d::Animation *animation)
{
	if (_animation != animation)
	{
		// ɾ���ϵĶ���
		CC_SAFE_RELEASE_NULL(_animation);
		// �����µĶ���
		this->initWithAnimation(animation);
	}
}

FrameAnimate* FrameAnimate::clone() const
{
	// no copy constructor
	auto a = new (std::nothrow) FrameAnimate();
	a->initWithAnimation(_animation->clone());
	a->setDelayStart(_delayStart);
	a->setLimitExecuteTimes(_limitExecuteTimes);
	a->setIsLimitExecute(_isLimitExecute);
	a->setAnimateStopCallback(_callbackAnimateUpdate);
	a->setAnimateStopCallback(_callbackAnimateStop);
	a->autorelease();
	return a;
}

void FrameAnimate::startWithTarget(Node *target)
{
	ActionInterval::startWithTarget(target);
	Sprite *sprite = static_cast<Sprite*>(target);

	CC_SAFE_RELEASE(_origFrame);

	if (_animation->getRestoreOriginalFrame())
	{
		_origFrame = sprite->getSpriteFrame();
		_origFrame->retain();
	}
	_nextFrame = 0;
	_nextFrameTime = 0.f;
	_executedLoops = 0;
}

void FrameAnimate::stop()
{
	if (_animation->getRestoreOriginalFrame() && _target)
	{
		static_cast<Sprite*>(_target)->setSpriteFrame(_origFrame);
	}
	ActionInterval::stop();
	if (_callbackAnimateStop)
	{
		_callbackAnimateStop(this);
	}
}

void FrameAnimate::update(float t)
{
	CHECK_NOLOG(_animation);
	// ��ȡ�����Ѳ��ŵľ���ʱ��
	float fTotalPlayTimes = _elapsed;
	float fRelativePlayTimes = 0.f;
	// if t==1, ignore. Animation should finish with t==1
	float singleDuration = _animation->getDuration();
	_duration = singleDuration * _animation->getLoops() + _delayStart;
	
	// �������������Ʋ���ʱ��, ��������
	if (_isLimitExecute && fTotalPlayTimes >= (_limitExecuteTimes + _delayStart))
	{
		_elapsed = _duration;
		return;
	}
	if (fTotalPlayTimes < _delayStart)
	{
		// ��ʱ�ڼ䲻���Ŷ���
		return;
	}
	
	auto& frames = _animation->getFrames();
	auto numberOfFrames = frames.size();
	SpriteFrame *frameToDisplay = nullptr;
	for (int i = _nextFrame; i < numberOfFrames; i++) {
		// ������֡�Ŀ�ʼʱ��ʱ, ����֡ͼ��
		if (_nextFrameTime <= fTotalPlayTimes) {
			AnimationFrame* frame = frames.at(i);
			frameToDisplay = frame->getSpriteFrame();
			if (frameToDisplay)
			{
				static_cast<Sprite*>(_target)->setSpriteFrame(frameToDisplay);
			}
			_nextFrame = i + 1;
			_nextFrameTime = fTotalPlayTimes + _animation->getDelayPerUnit();
			if (_nextFrame == numberOfFrames)
			{
				// ���������������һ֡ʱ, ��������ʼ֡, ���Ҳ��Ŵ���+1
				_nextFrame = 0;
				_executedLoops++;
			}
			if (_callbackAnimateUpdate)
			{
				_callbackAnimateUpdate(this);
			}
		}
		// Issue 1438. Could be more than one frame per tick, due to low frame rate or frame delta < 1/FPS
		else {
			break;
		}
	}
}

FrameAnimate* FrameAnimate::reverse() const
{
	auto& oldArray = _animation->getFrames();
	Vector<AnimationFrame*> newArray(oldArray.size());

	if (oldArray.size() > 0)
	{
		for (auto iter = oldArray.crbegin(); iter != oldArray.crend(); ++iter)
		{
			AnimationFrame* animFrame = *iter;
			if (!animFrame)
			{
				break;
			}

			newArray.pushBack(animFrame->clone());
		}
	}
	Animation *newAnim = Animation::create(newArray, _animation->getDelayPerUnit(), _animation->getLoops());
	newAnim->setRestoreOriginalFrame(_animation->getRestoreOriginalFrame());
	return FrameAnimate::create(newAnim);
}




SpriteFrameAnimate::SpriteFrameAnimate()
	: m_idAnimate(ID_NONE)
	, m_animationCfg(nullptr)
	, m_fPlayScale(1.0f)
	, m_bIsLimitExecute(false)
	, m_fLimitExecuteTimes(0.f)
	, m_fDelayStart(0.f)
	, m_callbackAnimateUpdate(nullptr)
	, m_callbackAnimateStop(nullptr)
{

}

SpriteFrameAnimate::~SpriteFrameAnimate()
{
	CC_SAFE_RELEASE_NULL(m_animationCfg);
}

SpriteFrameAnimate* SpriteFrameAnimate::createWithId(DB_KEY idAnimation)
{
	// ����һ��Node
	auto pAnimation = new(std::nothrow) SpriteFrameAnimate();
	if (pAnimation && pAnimation->initWithId(idAnimation))
	{
		pAnimation->autorelease();
		return pAnimation;
	}
	else
	{
		delete pAnimation;
		pAnimation = NULL;
		return NULL;
	}
}

////////////////////////////////////////////////////////////////////////
// Description: ����������һ������֡��Ч
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: FrameAnimateSprite*
////////////////////////////////////////////////////////////////////////
SpriteFrameAnimate* SpriteFrameAnimate::createAndPlay(DB_KEY idAnimation, const SpriteFrameAnimateListener& updateListener /*= nullptr*/, const SpriteFrameAnimateListener& stopListener /*= nullptr*/)
{
	auto pAnimation = new(std::nothrow) SpriteFrameAnimate();
	if (pAnimation && pAnimation->initWithId(idAnimation))
	{
		pAnimation->autorelease();
		pAnimation->setAnimateUpdateCallback(updateListener);
		pAnimation->setAnimateStopCallback(stopListener);
		pAnimation->playAnimate();
		return pAnimation;
	}
	else
	{
		delete pAnimation;
		pAnimation = NULL;
		return NULL;
	}
}

bool SpriteFrameAnimate::initWithId(DB_KEY idAnimation)
{
	CHECKF(Sprite::init());
	m_idAnimate = idAnimation;
	// ��ȡ������Ϣ
	auto strFrameName = ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_frame_animate, idAnimation, FRAME_ANIMATE_DATA_frame_name);
	auto nFrameBeg = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_frame_animate, idAnimation, FRAME_ANIMATE_DATA_frame_beg);
	auto nFrameEnd = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_frame_animate, idAnimation, FRAME_ANIMATE_DATA_frame_end);
	CHECKF(nFrameEnd > nFrameBeg);
	auto fFrameTime = (float)(ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_frame_animate, idAnimation, FRAME_ANIMATE_DATA_frame_time)) / 1000.f;
	CHECKF(fFrameTime > 0.f);
	auto nAnimateLoops = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_frame_animate, idAnimation, FRAME_ANIMATE_DATA_loops);
	auto bEndRestore = (ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_frame_animate, idAnimation, FRAME_ANIMATE_DATA_end_restore) > 0);
	m_fPlayScale = (float)(ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_frame_animate, idAnimation, FRAME_ANIMATE_DATA_scale)) / 10000.f;
	m_fDelayStart = (float)(ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_frame_animate, idAnimation, FRAME_ANIMATE_DATA_delay_start)) / 1000.f;
	auto nLimitExecute = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_frame_animate, idAnimation, FRAME_ANIMATE_DATA_limit_execute);
	if (nLimitExecute > 0)
	{
		m_bIsLimitExecute = true;
		m_fLimitExecuteTimes = (float)nLimitExecute;
	}
	else
	{
		m_bIsLimitExecute = false;
		m_fLimitExecuteTimes = 0.f;
	}
	//����һ���հ׵�����֡������Ϣ��  
	Animation* animation = Animation::create();
	CHECKF(animation);
	// �������õ�����ͼ���뵽�����С�  
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(StringUtils::format("frameAnimate/%s.plist", strFrameName.c_str()));
	for (int i = nFrameBeg; i <= nFrameEnd; i++)
	{
		auto szFrameFile = StringUtils::format("%s_%02d.png", strFrameName.c_str(), i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szFrameFile));
	}
	// ����ÿ��֡��ʱ������  
	animation->setDelayPerUnit(fFrameTime);
	// ���ö������Ŵ�����  
	if (nAnimateLoops <= 0)
	{
		animation->setLoops(-1);
	}
	else
	{
		animation->setLoops(nAnimateLoops);
	}
	// ���ö����������Ƿ�ص���ʼ֡��  
	animation->setRestoreOriginalFrame(bEndRestore);
	
	// ���ö����Ĵ������á�  
	this->setAnimation(animation);
	return (true);
}

////////////////////////////////////////////////////////////////////////
// Description: ��ò�����ʱ��
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: float
////////////////////////////////////////////////////////////////////////
float SpriteFrameAnimate::getPlayTime() const
{
	auto nFrameBeg = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_frame_animate, m_idAnimate, FRAME_ANIMATE_DATA_frame_beg);
	auto nFrameEnd = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_frame_animate, m_idAnimate, FRAME_ANIMATE_DATA_frame_end);
	auto fFrameTime = (float)(ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_frame_animate, m_idAnimate, FRAME_ANIMATE_DATA_frame_time)) / 1000.f;
	float fTotalTime = fFrameTime * (nFrameEnd - nFrameBeg);

	auto nAnimateLoops = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_frame_animate, m_idAnimate, FRAME_ANIMATE_DATA_loops);
	if (nAnimateLoops <= 0)
	{
		fTotalTime = 999999999.f;
	}
	else
	{
		fTotalTime *= nAnimateLoops;
	}

	if (m_bIsLimitExecute)
	{
		fTotalTime = std::min(fTotalTime, m_fLimitExecuteTimes);
	}
	return fTotalTime + m_fDelayStart;
}

bool SpriteFrameAnimate::setAnimation(Animation* animation)
{
	CHECKF(animation);
	CHECKF(m_animationCfg == nullptr);
	m_animationCfg = animation;
	CC_SAFE_RETAIN(animation);
	return (true);
}

FrameAnimate* SpriteFrameAnimate::createFrameAnimate()
{
	CHECKF(m_animationCfg);
	auto animateFrame = FrameAnimate::create(m_animationCfg);
	CHECKF(animateFrame);
	animateFrame->setDelayStart(m_fDelayStart);
	animateFrame->setAnimateUpdateCallback(CC_CALLBACK_1(SpriteFrameAnimate::callbackAnimateUpdate, this));
	animateFrame->setAnimateStopCallback(CC_CALLBACK_1(SpriteFrameAnimate::callbackAnimateStop, this));
	animateFrame->setIsLimitExecute(m_bIsLimitExecute);
	animateFrame->setLimitExecuteTimes(m_fLimitExecuteTimes);
	this->setScale(m_fPlayScale);
	return (animateFrame);
}

void SpriteFrameAnimate::playAnimate()
{
	CHECK(m_animationCfg);
	// �����������Ϣ����һ������֡������  
	auto animateFrame = this->createFrameAnimate();
	CHECK(animateFrame);
	this->stopAllActions();
	this->runAction(animateFrame);
}

void SpriteFrameAnimate::callbackAnimateUpdate(FrameAnimate* animate)
{
	if (m_callbackAnimateUpdate)
	{
		m_callbackAnimateUpdate(this, animate);
	}
}

void SpriteFrameAnimate::callbackAnimateStop(FrameAnimate* animate)
{
	if (m_callbackAnimateStop)
	{
		m_callbackAnimateStop(this, animate);
	}
	this->removeFromParent();
}


