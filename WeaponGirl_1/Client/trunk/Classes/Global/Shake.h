/**
desc:��ָ���ؼ�����
һ��CCNodeͬʱִ�ж��CCShake����,����һ��CCShakeû������ִ��һ��CCShake�Ļ��ͻ��������,�����ƫ�Ƶ�����!

�������:
1).��Ҫͬʱִ�ж��CCShake����.
2.�Լ��ⲿ��¼���CCNode��λ��,ִ����ɺ��ֶ�setPosition();
*/
#ifndef __SHAKE_H__  
#define __SHAKE_H__  

#include "cocos2d.h"  

/**
* ��ָ��Ƶ�ȷ�Χ�ڶ���[-strength_x,strength_x][-strength_y, strength_y]
*/
class Shake : public cocos2d::ActionInterval
{
public:
	Shake();

	// Create the action with a time and a strength (same in x and y)  
	static Shake* create(float d, float strength);
	// Create the action with a time and strengths (different in x and y)  
	static Shake* createWithStrength(float d, float strength_x, float strength_y);
	bool initWithDuration(float d, float strength_x, float strength_y);

protected:

	virtual void startWithTarget(cocos2d::Node *pTarget);
	virtual void update(float time);
	virtual void stop(void);


	// Initial position of the shaked node  
	float m_initial_x, m_initial_y;
	// Strength of the action  
	float m_strength_x, m_strength_y;
};


/**
* ���Զ���(ʣ��ʱ��Խ�̣�������ΧԽС)
*/
class FallOffShake : public Shake
{
public:
	FallOffShake();

	// Create the action with a time and a strength (same in x and y)  
	static FallOffShake* create(float d, float strength);
	// Create the action with a time and strengths (different in x and y)  
	static FallOffShake* createWithStrength(float d, float strength_x, float strength_y);

protected:
	virtual void update(float time);
};

#endif //__SHAKE_H__  