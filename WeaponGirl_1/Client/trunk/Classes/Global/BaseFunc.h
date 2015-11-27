////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: BaseFunc.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2014-7-26
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_BASE_FUNC_H_
#define _JYP_BASE_FUNC_H_

#include <time.h>

#include "cocos2d.h"
#include "GlobalEnumDef.h"
#include "GlobalMacro.h"
#include "GlobalTypeDef.h"
#include "GlobalConstDef.h"

// 正则表达式
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
#include <regex>  
#endif  
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID||CC_TARGET_PLATFORM == CC_PLATFORM_IOS)  
#include <regex.h>  
#endif 

int64_t GetUtcMillisecond(void);
void	DateTime(char * buf20, time_t tInput = 0);		// 0 : curr time
bool	SafeCopy(char * pTarget, const char * pSource, int nBufLen = 0);

// 枚举名称请保持和服务器枚举相同, 不支持的枚举已删除
enum TIME_TYPE
{
	TIME_BEGIN,
	TIME_MILLISECOND=TIME_BEGIN, 
	TIME_SECOND, 
	TIME_MINUTE, 
	TIME_HOUR,
	TIME_DAY, 
	TIME_DAYTIME, 
	TIME_STAMP,
	YEAR_MONTH_DAY,
	TIME_DAYHOUR,//每天的时间 精确到小时
	TIME_DAYMIN,//每天的时间 精确到分钟
	TIME_DAY_START,
	TIME_DAY_END,
	TIME_MONTH_START,
	TIME_MONTH_END,
	TIME_END,
};

std::string getMinuteTime(int nTime);
std::string getCurTime();
uint32_t TimeGet(TIME_TYPE type=TIME_MILLISECOND);
uint32_t UtcSecondConvert(uint32_t unSecond, TIME_TYPE eType);
int		RandGet		(int nMax, bool bReset=false);
int		RandGetZT	(int nMax, double dRangeParamL=3.0, double dRangeParamR=3.0, bool bRest=false);
void	SpiltString(IN const std::string& srcString, IN const std::string& strSpiltFlag, OUT std::vector<std::string>& rVecSplitString, int nMaxSplits);

int ReplaceStdString(IN OUT std::string& str, const char* pszOld, const char* pszNew, bool bReplaceAll = true);	// 替换std::string中的字符

////////////////////////////////////////////////////////////////////////
// Description:  将值限定在合理范围内
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: class T
////////////////////////////////////////////////////////////////////////
template <class T>
T GetValueInRightRange(T value, T minValue, T maxValue)
{
	value = std::min(value, maxValue);
	value = std::max(value, minValue);
	return value;
}


template<class T>
bool CheckBetween(IN OUT T& nowVaule, T minVaule, T maxVaule, T defaultValue)
{
	bool bResult = false;
	if (nowVaule >= minVaule && nowVaule <= maxVaule)
	{
		bResult = true;
	}
	else
	{
		nowVaule = defaultValue;
	}

	return bResult;
}

class MyLock
{
public:
	MyLock(std::mutex* pMutex) : m_pMutex(pMutex)
	{
		if (m_pMutex)
		{
			m_pMutex->lock();
		}
	}
	~MyLock()
	{
		if (m_pMutex)
		{
			m_pMutex->unlock();
		}
	}
private:
	std::mutex*	m_pMutex;
};

bool FindRegularSubString(const std::string& rMainString, const std::string& rRegularSubString);

void AddBlurScreen(Layer* layer, bool bForceLowEffect = false);
void OnAddBlurScreen(Layer* layer, bool bForceLowEffect);

bool CheckName(const std::string& name);
bool CheckText(const std::string& text);
bool StrSqlCheck(const char* pszString);
SpriteFrame* getLookface(OBJID idLookface);
std::string getLookfaceFileName(OBJID idLookface);
SpriteFrame* getItemIcon(OBJID idItemtype);
std::string getItemIconFileName(OBJID idItemtype);
SpriteFrame* getMagicIcon(OBJID idMagicType);
std::string getMagicIconFileName(OBJID idMagicType);
SpriteFrame* getEquipMagicIcon(OBJID idMagicIcon);
std::string getEquipMagicIconFileName(OBJID idMagicIcon);

RepeatForever* createFrameLight(float fTime = 3.f);
Action* createTurnActionPart1();
Action* createTurnActionPart2();

#endif	// end of _JYP_BASE_FUNC_H_