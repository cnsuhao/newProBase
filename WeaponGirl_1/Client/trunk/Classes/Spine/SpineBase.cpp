////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2015, WuHan GoodGame, All Rights Reserved
// Moudle: SpineBase.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015-2-2
////////////////////////////////////////////////////////////////////////
#include "SpineBase.h"
#include "SpineCache.h"
#include "ConstTable\ConstTableMgr.h"

//////////////////////////////////////////////////////////////////////////
SpineBase::SpineBase()
{
	m_pAtlas = nullptr;
	m_bOwner = false;
	m_idSpineType = ID_NONE;
	m_eAnimation = SPINE_ANIMATION_NONE;
	m_eShaderEffect = MY_SHADER_EFFECT_NONE;
	m_bCanNotSetupPose = false;
}

//////////////////////////////////////////////////////////////////////////
SpineBase::~SpineBase()
{
	if (m_bOwner && m_pAtlas) 
	{
		spAtlas_dispose(m_pAtlas);
	}
}

////////////////////////////////////////////////////////////////////////
// Description: 初始化spine资源
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool SpineBase::initSpine(OBJID idSpineType, BORN_FROM bBornFrom /*= BORN_FROM_LEFT*/)
{
	ST_SPINE_DATA stData = { 0 };
	CHECKF(SpineCache::getInstance()->getSkeletonInfo(idSpineType, stData));

	// 骨骼类属性
	m_idSpineType = idSpineType;
	m_pAtlas = stData.pAtlas;
	_skeleton = spSkeleton_create(stData.pData);
	_ownsSkeletonData = stData.bOwner;
	m_bOwner = stData.bOwner;
	SkeletonAnimation::initialize();
	this->setBornFrom(bBornFrom);

	this->setEventListener([=](int trackIndex, spEvent* event)
	{
		if (event && event->data)
		{
			this->onEvent(trackIndex, event->data->name, event->data->intValue, event->data->floatValue);
		}
	});
	
	// 特效初始化
	for (int i = 0; i < 2; i++)
	{
		auto strEffectFile = ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_spine_type, idSpineType, SPINE_TYPE_effect1 + i * 3);
		int nEffectLocalOrder = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_spine_type, idSpineType, SPINE_TYPE_effect1_order + i * 3) - 10;
		int nEffectScale = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_spine_type, idSpineType, SPINE_TYPE_effect1_scale + i * 3);
		if (strEffectFile.size() > 0)
		{
			auto pEffect = ParticleSystemQuad::create(strEffectFile);
			if (pEffect)
			{
				pEffect->setName(StringUtils::format("effect_%d", i + 1));
				pEffect->setVisible(false);
				pEffect->setScale(nEffectScale / 10000.f);
				this->addChild(pEffect, nEffectLocalOrder);
			}
		}
	}

	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 设置出生方向
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void SpineBase::setBornFrom(BORN_FROM eBornFrom)
{
	CHECK(BORN_FROM_NONE != eBornFrom);
	auto sk = this->getSkeleton();
	CHECK(sk);
	sk->flipX = (eBornFrom == BORN_FROM_LEFT) ? 1 : 0;
}

////////////////////////////////////////////////////////////////////////
// Description: 获得出生方向
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: SPINE_FACE
////////////////////////////////////////////////////////////////////////
BORN_FROM SpineBase::getBornFrom() const
{
	IF_OK(_skeleton)
	{
		if (_skeleton->flipX != 0)
		{
			return BORN_FROM_LEFT;
		}
		else
		{
			return BORN_FROM_RIGHT;
		}
	}
	return BORN_FROM_LEFT;
}

////////////////////////////////////////////////////////////////////////
// Description: 执行动画
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void SpineBase::doAnimation(SPINE_ANIMATION eAnimation, bool bLoop /*= false*/, const CompleteListener& listener /*= nullptr*/)
{
	if (eAnimation == m_eAnimation)
	{
		_completeListener = nullptr;
		return;
	}

	if (eAnimation == SPINE_ANIMATION_NONE)
	{
		this->clearTracks();
		m_eAnimation = SPINE_ANIMATION_NONE;
		return;
	}

	int nSpineTypeActionNow = SPINE_TYPE_action_idle + m_eAnimation - 1;
	int nSpineTypeActionNew = SPINE_TYPE_action_idle + eAnimation - 1;
	auto strNowAnimation = SPINE_ANIMATION_NONE == m_eAnimation ? "" : ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_spine_type, m_idSpineType, nSpineTypeActionNow);
	auto strNewAnimation = ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_spine_type, m_idSpineType, nSpineTypeActionNew);

	// 受击动作融合
// 	if (SPINE_ANIMATION_BE_ATK == eAnimation)
// 	{
// 		if (strlen(pszNowAnimation) > 0 && strlen(pszNewAnimation) > 0)
// 		{
// 			const float MIX_DEFAULT_SECOND = 0.1f;	// 默认动作融合时间
// 			this->setMix(pszNowAnimation, pszNewAnimation, MIX_DEFAULT_SECOND);
// 		}
// 	}

	this->setToSetupPose();

	auto oldAnimation = m_eAnimation;
	m_eAnimation = eAnimation;
	_completeListener = nullptr;

	// 受击动作单独处理
// 	if (SPINE_ANIMATION_BE_ATK == eAnimation ||
// 		SPINE_ANIMATION_DEFENSE_BE_ATK == eAnimation)
// 	{
// 		CHECK(this->setAnimation(0, pszNewAnimation, true));
// 
// 		const float fBeAttackTime = 0.35f;
// 		const float fShakestrength = 8.f;
// 		auto nowShaderEffect = m_eShaderEffect;
// 		auto bornFrom = this->getBornFrom();
// 
// 		auto actionShake = Shake::create(fBeAttackTime, fShakestrength);
// 
// 		Vector<FiniteTimeAction*> vecAction;
// 		for (int i = 0; i < 3; i++)
// 		{
// 			vecAction.pushBack(DelayTime::create(fBeAttackTime / 6.f));
// 			vecAction.pushBack(CallFunc::create([=](){this->setShaderEffect(MY_SHADER_EFFECT_HIDDEN); }));
// 			vecAction.pushBack(DelayTime::create(fBeAttackTime / 6.f));
// 			vecAction.pushBack(CallFunc::create([=](){this->setShaderEffect(MY_SHADER_EFFECT_NONE); }));
// 		}
// 
// 		vecAction.pushBack(CallFunc::create([=](){
// 			this->setShaderEffect(nowShaderEffect); 
// 			if (strlen(pszNowAnimation) > 0)
// 			{
// 				this->setAnimation(0, pszNowAnimation, true);
// 				m_eAnimation = oldAnimation;
// 			}
// 
// 			if (compFunc)
// 			{
// 				compFunc(this, eAnimation);
// 			}
// 		}));
// 
// 		auto beAtk = Spawn::create(actionShake, Sequence::create(vecAction), nullptr);
// 		beAtk->setTag(997);
// 		if (!this->getActionByTag(997))
// 		{
// 			this->runAction(beAtk);
// 		}
// 
// 		return;
// 	}
	

	CHECK(this->setAnimation(0, strNewAnimation, bLoop));
	if (listener)
	{
		_completeListener = listener;
	}
}

////////////////////////////////////////////////////////////////////////
// Description: 设置特效
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void SpineBase::setShaderEffect(MY_SHADER_EFFECT eShaderEffect)
{
	CHECK(eShaderEffect >= MY_SHADER_EFFECT_NONE && eShaderEffect < MY_SHADER_EFFECT_END);
	if (eShaderEffect == m_eShaderEffect)
	{
		return;
	}

	m_eShaderEffect = eShaderEffect;
	auto opacity = this->getOpacity();
	float fBaseData[16] = { 0.f };
	for (int i = 0; i < 16; i++)
	{
		fBaseData[i] = (opacity / 255.f) * MY_SHADER_EFFECT_MAT[m_eShaderEffect][i];
	}

	auto glState = getGLProgramState();
	CHECK(glState);
	glState->setUniformMat4("matrixEffect", Mat4(fBaseData));
}

////////////////////////////////////////////////////////////////////////
// Description: 获得骨骼坐标
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: Vec2
////////////////////////////////////////////////////////////////////////
cocos2d::Vec2 SpineBase::getBonePosition(const std::string& rBoneName) const
{
	Vec2 result = Vec2::ZERO;

	auto bone = this->findBone(rBoneName);
	if (!bone)
	{
		LogSave("can not find bone[%s] idSpineType[%u]", rBoneName.c_str(), m_idSpineType);
		return result;
	}

	result.x += bone->worldX;
	result.y += bone->worldY;
	return result;
}

////////////////////////////////////////////////////////////////////////
// Description: 获得骨骼的坐标
// Arguments:	不存在的骨骼为0,0
// Author: 彭文奇(Peng Wenqi)
// Return Value: Vec2
////////////////////////////////////////////////////////////////////////
cocos2d::Vec2 SpineBase::getBoneWorldPosition(const std::string& rBoneName) const
{
	Vec2 result = this->getPosition();

	auto bone = this->findBone(rBoneName);
	if (!bone)
	{
		LogSave("can not find bone[%s] idSpineType[%u]", rBoneName.c_str(), m_idSpineType);
		return result;
	}
	
	result.x += bone->worldX;
	result.y += bone->worldY;
	return result;
}

////////////////////////////////////////////////////////////////////////
// Description: 获得槽坐标
// Arguments:	不存在的槽为0,0
// Author: 彭文奇(Peng Wenqi)
// Return Value: Vec2
////////////////////////////////////////////////////////////////////////
Vec2 SpineBase::getSlotWorldPosition(const std::string& rSlotName) const
{
	auto slot = this->findSlot(rSlotName);
	IF_NOT(slot)
	{
		return Vec2::ZERO;
	}

	IF_NOT(slot->bone)
	{
		return Vec2::ZERO;
	}

	Vec2 result = this->getPosition();
	result.x += slot->bone->worldX;
	result.y += slot->bone->worldY;
	return result;
}

////////////////////////////////////////////////////////////////////////
// Description: 事件传回触发
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void SpineBase::onEvent(int trackIndex, const char* pszEventName, int nData, float fData)
{
	CHECK(pszEventName);

#ifdef _DEBUG
	CCLOG("SpineBase::onEvent m_idSpineType[%u] EventName[%s] nData[%d] fData[%f]", m_idSpineType, pszEventName, nData, fData);
#endif

	// 提前结束攻击动作完成触发
	if (0 == strcmp(pszEventName, "attack") && 
		m_eAnimation >= SPINE_ANIMATION_ATTACK1 &&
		m_eAnimation <= SPINE_ANIMATION_ATTACK2 &&
		_completeListener != nullptr)
	{
		_completeListener(trackIndex, 0);
		_completeListener = nullptr;
	}
}

////////////////////////////////////////////////////////////////////////
// Description: 更新透明度
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void SpineBase::updateColor()
{
	float fBaseData[16] = { 0.f };
	for (int i = 0; i < 16; i++)
	{
		fBaseData[i] = (_displayedOpacity / 255.f) * MY_SHADER_EFFECT_MAT[m_eShaderEffect][i];
	}

	auto glState = getGLProgramState();
	CHECK(glState);
	glState->setUniformMat4("matrixEffect", Mat4(fBaseData));
}

////////////////////////////////////////////////////////////////////////
// Description: 
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void SpineBase::onAnimationStateEvent(int trackIndex, spEventType type, spEvent* event, int loopCount)
{
	// 攻击动作后一定还原休闲动作
	if (SP_ANIMATION_COMPLETE == type)
	{
		if (m_eAnimation >= SPINE_ANIMATION_ATTACK1 &&
			m_eAnimation <= SPINE_ANIMATION_ATTACK2)
		{
			this->doAnimation(SPINE_ANIMATION_IDLE, true);
		}
	}

	SkeletonAnimation::onAnimationStateEvent(trackIndex, type, event, loopCount);
}


