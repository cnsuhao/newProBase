////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: BaseFunc.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2014-7-26
////////////////////////////////////////////////////////////////////////
#include "BaseFunc.h"

#include <fstream>
#include <sstream>
#include <set>
#include "MyShader.h"
#include "StackBlur.h"
#include "ConstTable\ConstTableMgr.h"
#include <stdint.h>

using namespace cocos2d;
const char SZ_UTF8_FILE_HEADER[3] = {(char)0xEF, (char)0xBB, (char)0xBF};	// utf8文件头

int64_t GetUtcMillisecond( void )
{
	struct timeval tv;     
	gettimeofday(&tv,NULL);     
	return (int64_t)(tv.tv_sec) * 1000 + (int64_t)(tv.tv_usec) / 1000;     
}

/////////////////////////////////////////////////////////////////////////////
// szFormat: "%04d-%02d-%02d %02d:%02d:%02d"
// 格式化日期时间串
void	DateTime(char * buf20, time_t tInput /*= 0*/)	// 填入buf20中
{
	if(!buf20)
		return;

	if(tInput == 0)
		tInput = time(NULL);

	tm * pTm = localtime(&tInput);
	if(buf20)
		sprintf(buf20, "%04d-%02d-%02d %02d:%02d:%02d", 
		pTm->tm_year+1900, pTm->tm_mon+1, pTm->tm_mday, pTm->tm_hour, pTm->tm_min, pTm->tm_sec);
}


//////////////////////////////////////////////////////////////////////////
bool SafeCopy(char * pTarget, const char * pSource, int nBufLen /*= 0*/)
{
	if(pTarget)
	{
		pTarget[0] = 0;
		if(pSource)
		{
			if(nBufLen && (int)strlen(pSource) >= nBufLen)
			{
				strncpy(pTarget, pSource, nBufLen-1);
				pTarget[nBufLen-1] = 0;
				return false;
			}
			strcpy(pTarget, pSource);
			return true;
		}
	}
	return false;
}

std::string getMinuteTime(int nTime)
{
	int nMinute = nTime / 60;
	std::string strMinute = "";
	if (nMinute < 10)
	{
		strMinute = StringUtils::format("0%d", nMinute);
	}
	else
	{
		strMinute = StringUtils::format("%d", nMinute);
	}

	int nSecond = nTime % 60;
	std::string strSecond = "";
	if (nSecond < 10)
	{
		strSecond = StringUtils::format("0%d", nSecond);
	}
	else
	{
		strSecond = StringUtils::format("%d", nSecond);
	}
	return StringUtils::format("%s:%s", strMinute.c_str(), strSecond.c_str());
}

std::string getCurTime()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	struct timeval now;
	gettimeofday(&now, NULL);

	struct tm* time;
	time = localtime(&now.tv_sec);
	return StringUtils::format("%d-%02d-%02d %02d:%02d:%02d", time->tm_year + 1900, time->tm_mon + 1, time->tm_mday, time->tm_hour, time->tm_min, time->tm_sec);

#endif

#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	time_t timep;
	time(&timep);
	
	struct tm* tm;
	tm = localtime(&timep);
	return StringUtils::format("%d-%02d-%02d %02d:%02d:%02d", tm->tm_year + 1900,tm->tm_mon + 1,tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
#endif
}

uint32_t TimeGet( TIME_TYPE type/*=TIME_MILLISECOND*/ )
{
	uint32_t unTime = 0;
	switch(type)
	{
	case TIME_SECOND:
		unTime = (uint32_t)::time(nullptr);
		break;

	case TIME_MINUTE:
		{
			time_t long_time;
			time( &long_time );                /* Get time as long integer. */

			struct tm *pTime;
			pTime = localtime( &long_time ); /* Convert to local time. */

			unTime	=	pTime->tm_year%100*100000000 +
				(pTime->tm_mon+1)*1000000 +
				pTime->tm_mday*10000 +
				pTime->tm_hour*100 + 
				pTime->tm_min;
		}
		break;
	case TIME_HOUR:
		{
			time_t long_time;
			time( &long_time );                /* Get time as long integer. */

			struct tm *pTime;
			pTime = localtime( &long_time ); /* Convert to local time. */

			unTime	=	pTime->tm_year%100*1000000 +
				(pTime->tm_mon+1)*10000 +
				pTime->tm_mday*100 +
				pTime->tm_hour; 
		}
		break;

	case TIME_DAY:
		{
			time_t long_time;
			time( &long_time );                /* Get time as long integer. */

			struct tm *pTime;
			pTime = localtime( &long_time ); /* Convert to local time. */

			unTime	=	pTime->tm_year*10000 +
				(pTime->tm_mon+1)*100 +
				pTime->tm_mday;
		}
		break;

	case TIME_DAYTIME: 
		{
			time_t long_time;
			time( &long_time );                /* Get time as long integer. */

			struct tm *pTime;
			pTime = localtime( &long_time ); /* Convert to local time. */

			unTime	=	pTime->tm_hour*10000 + 
				pTime->tm_min *100 +
				pTime->tm_sec;
		}
		break;
	case TIME_DAYHOUR: 
		{
			time_t long_time;
			time( &long_time );                /* Get time as long integer. */

			struct tm *pTime;
			pTime = localtime( &long_time ); /* Convert to local time. */

			unTime	=	pTime->tm_hour;		
		}
		break;
	case TIME_DAYMIN: 
		{
			time_t long_time;
			time( &long_time );                /* Get time as long integer. */

			struct tm *pTime;
			pTime = localtime( &long_time ); /* Convert to local time. */

			unTime = pTime->tm_hour*100 + pTime->tm_min;	
		}
		break;
	case TIME_STAMP: 
		{
			time_t long_time;
			time( &long_time );                /* Get time as long integer. */

			struct tm *pTime;
			pTime = localtime( &long_time ); /* Convert to local time. */

			unTime	=	(pTime->tm_mon+1)*100000000 +
				pTime->tm_mday*1000000 +
				pTime->tm_hour*10000 + 
				pTime->tm_min *100 +
				pTime->tm_sec;
		}
		break;
	case YEAR_MONTH_DAY:
		{
			time_t long_time = 0;
			time( &long_time );                /* Get time as long integer. */

			struct tm *pTime = nullptr;
			pTime = localtime( &long_time ); /* Convert to local time. */

			unTime	=	(pTime->tm_year+1900)*10000 +
				(pTime->tm_mon+1)*100 +
				pTime->tm_mday;
		}
		break;
	case TIME_DAY_START:	// 今天的第一秒
		{
			time_t long_time = 0;
			time( &long_time );                /* Get time as long integer. */

			struct tm *pTime = nullptr;
			pTime = localtime( &long_time ); /* Convert to local time. */
			pTime->tm_hour	= 0;
			pTime->tm_min	= 0;
			pTime->tm_sec	= 0;

			unTime = ::mktime(pTime);
		}
		break;
	case TIME_DAY_END:	// 今天最后一秒
		{
			time_t long_time = 0;
			time( &long_time );                /* Get time as long integer. */

			struct tm *pTime = nullptr;
			pTime = localtime( &long_time ); /* Convert to local time. */
			pTime->tm_hour	= 23;
			pTime->tm_min	= 59;
			pTime->tm_sec	= 59;

			unTime = ::mktime(pTime);
		}
		break;
	case TIME_MONTH_START:	// 本月第一秒
		{
			time_t long_time = 0;
			time( &long_time );                /* Get time as long integer. */

			struct tm *pTime = nullptr;
			pTime = localtime( &long_time ); /* Convert to local time. */
			pTime->tm_mday	= 1;
			pTime->tm_hour	= 0;
			pTime->tm_min	= 0;
			pTime->tm_sec	= 0;

			unTime = ::mktime(pTime);
		}
		break;
	case TIME_MONTH_END:
		{
			time_t long_time = 0;
			time( &long_time );                /* Get time as long integer. */

			struct tm *pTime = nullptr;
			pTime = localtime( &long_time ); /* Convert to local time. */

			switch (pTime->tm_mon)
			{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				{
					pTime->tm_mday	= 31;
				}
				break;
			case 4:
			case 6:
			case 9:
			case 11:
				{
					pTime->tm_mday	= 30;
				}
				break;
			case 2:
				{
					int nYear = pTime->tm_year + 1900;
					if(  ((0 == nYear%4) &&(0 != nYear % 100)) ||(0 == nYear %400) )
					{
						pTime->tm_mday = 29;
					}
					else
					{
						pTime->tm_mday = 28;
					}
				}
				break;
			default:
				break;
			}

			pTime->tm_hour	= 23;
			pTime->tm_min	= 59;
			pTime->tm_sec	= 59;

			unTime = ::mktime(pTime);
		}
		break;
	default:
		unTime = ::GetUtcMillisecond() & 0xFFFFFFFF;
		break;
	}

	return unTime;
}

uint32_t UtcSecondConvert(uint32_t unSecond, TIME_TYPE eType)
{
	time_t tTime = 0;
	uint32_t unTime = 0;
	tTime = unSecond;
	struct tm *pTime;
	pTime = localtime(&tTime);
	switch (eType)
	{
	case TIME_SECOND:
		unTime = unSecond;
		break;

	case TIME_MINUTE:
		{
			unTime	=	pTime->tm_year%100*100000000 +
				(pTime->tm_mon+1)*1000000 +
				pTime->tm_mday*10000 +
				pTime->tm_hour*100 + 
				pTime->tm_min;
		}
		break;
	case TIME_HOUR:
		{
			unTime	=	pTime->tm_year%100*1000000 +
				(pTime->tm_mon+1)*10000 +
				pTime->tm_mday*100 +
				pTime->tm_hour; 
		}
		break;

	case TIME_DAY:
		{
			unTime	=	pTime->tm_year*10000 +
				(pTime->tm_mon+1)*100 +
				pTime->tm_mday;
		}
		break;

	case TIME_DAYTIME: 
		{
			unTime	=	pTime->tm_hour*10000 + 
				pTime->tm_min *100 +
				pTime->tm_sec;
		}
		break;
	case TIME_DAYHOUR: 
		{
			unTime	=	pTime->tm_hour;		
		}
		break;
	case TIME_DAYMIN: 
		{
			unTime = pTime->tm_hour*100 + pTime->tm_min;	
		}
		break;
	case TIME_STAMP: 
		{
			unTime	=	(pTime->tm_mon+1)*100000000 +
				pTime->tm_mday*1000000 +
				pTime->tm_hour*10000 + 
				pTime->tm_min *100 +
				pTime->tm_sec;
		}
		break;
	case YEAR_MONTH_DAY:
		{
			unTime	=	(pTime->tm_year+1900)*10000 +
				(pTime->tm_mon+1)*100 +
				pTime->tm_mday;
		}
		break;
	case TIME_DAY_START:	// 今天的第一秒
		{
			unTime = ::mktime(pTime);
		}
		break;
	case TIME_DAY_END:	// 今天最后一秒
		{
			unTime = ::mktime(pTime);
		}
		break;
	case TIME_MONTH_START:	// 本月第一秒
		{
			unTime = ::mktime(pTime);
		}
		break;
	case TIME_MONTH_END:
		{
			switch (pTime->tm_mon)
			{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				{
					pTime->tm_mday	= 31;
				}
				break;
			case 4:
			case 6:
			case 9:
			case 11:
				{
					pTime->tm_mday	= 30;
				}
				break;
			case 2:
				{
					int nYear = pTime->tm_year + 1900;
					if(  ((0 == nYear%4) &&(0 != nYear % 100)) ||(0 == nYear %400) )
					{
						pTime->tm_mday = 29;
					}
					else
					{
						pTime->tm_mday = 28;
					}
				}
				break;
			default:
				break;
			}

			pTime->tm_hour	= 23;
			pTime->tm_min	= 59;
			pTime->tm_sec	= 59;

			unTime = ::mktime(pTime);
		}
		break;
	default:
		unTime = ::GetUtcMillisecond() & 0xFFFFFFFF;
		break;
	}

	return unTime;
}

//////////////////////////////////////////////////////////////////////
int RandGet(int nMax, bool bReset)
{
	static int64_t RandSeed = (uint32_t)::TimeGet();
	if (bReset)
		RandSeed = (uint32_t)::TimeGet();

	if (RandSeed < 0)
	{
		RandSeed *= (-1);
	}

	int64_t x;
	double i;
	uint32_t final;
	x = 0xffffffff;
	x += 1;

	RandSeed *= ((int64_t)134775813);
	RandSeed += 1;
	RandSeed = RandSeed % x;
	i = ((double)RandSeed) / (double)x;
	final = (uint32_t) (nMax * i);

	return (int)final;
}

////////////////////////////////////////////////////////////////////////
// Description: 正态分布随机函数 取[0, nMax)的正态分布
//				随机产生μ = 0, σ = 1的标准正态分布, 
//				默认在正负3σ内取值, 其余部分按照平均概率返回RandGet(nMax)
//
// Arguments:	dRangeParam 表示取值范围, 默认3.0. 即正负3σ内取值, 
//				剩余部分均按照平均概率返回RandGet(nMax)返回, 保证正态分布图形不突兀
//				1σ包含68.268949% 概率面积
//				2σ包含95.449974% 概率面积
//				3σ包含99.730020% 概率面积
//				4σ包含99.993666% 概率面积
//				dRangeParam如果小于0.1则取值0.1
//				dRangeParam越小则中位数两边取值越平缓, 越大则陡峭, 所有正态分布均可调整此参数产生, 一般取3.0即可
//
//				数学原理为Box-Muller方法, 即:		
//				产生两个x,y随机数, 服从(0,1]平均分布, 
//				那么 (-2 * log(x))^0.5 * cos(2 * pi * y) 或 (-2 * log(x))^0.5 * sin(2 * pi * y) 均服从(0,1)正态分布
//				代码中采用cos这种方法
// 
// Author: 彭文奇(Peng Wenqi)
// Return Value: INT
////////////////////////////////////////////////////////////////////////
int	RandGetZT(int nMax, double dRangeParamL/*=3.0*/, double dRangeParamR/*=3.0*/, bool bRest/*=false*/)
{
	if (nMax < 0)
	{
		return 0;
	}

	if (dRangeParamL < 0.1)
	{
		dRangeParamL = 0.1;
	}

	if (dRangeParamR < 0.1)
	{
		dRangeParamR = 0.1;
	}

	const double dSigma			= 1.0;						// 不要修改σ, 调整范围用RangeParam
	const double dPi			= 3.1415926535897932;	
	const int64_t i64RandBase	= 0x7fffffff;				// 产生平均分布基数,

	// 让 dRandGet_X, dRandGet_Y 服从(0,1]平均分布, 因为半开半闭区间, 所以有 +1
	int64_t i64RandGet_X = RandGet(i64RandBase, bRest) + 1;
	int64_t i64RandGet_Y = RandGet(i64RandBase, false) + 1;

	double dRandGet_X = (double)i64RandGet_X / (double)i64RandBase;	
	double dRandGet_Y = (double)i64RandGet_Y / (double)i64RandBase;

	double dParam	= -2.0 * ::log(dRandGet_X);
	if (dParam < 0.0)
	{
		return 0;
	}

	double dResultZT = ::sqrt(dParam) * ::cos(2.0 * dPi * dRandGet_Y);

	// 调整中位数为3σ
	dResultZT += (dRangeParamL * dSigma);

	// 将正负3σ以外的数据进行边界处理
	if (dResultZT < 0.0 || dResultZT > (dRangeParamL + dRangeParamR) * dSigma)
	{
		return RandGet(nMax);
	}

	// 调整为0-1之间取值
	dResultZT /= ((dRangeParamL + dRangeParamR) * dSigma);

	int nResultZT = (int)(dResultZT * nMax);

	// 防止越界
	if (nResultZT < 0 || nResultZT >= nMax)
	{
		return RandGet(nMax);
	}

	return nResultZT;
}

////////////////////////////////////////////////////////////////////////
// Description: 字符串分割
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void SpiltString(IN const std::string& srcString, IN const std::string& strSpiltFlag, OUT std::vector<std::string>& rVecSplitString, int nMaxSplits)
{
	int nSplitLength = strSpiltFlag.size();
	if (0 == nSplitLength)
	{
		return;
	}

	int nStartPos = 0;
	int nBreakCount = 0;
	while (true)
	{
		int nEndPos = srcString.find_first_of(strSpiltFlag, nStartPos);
		if (nEndPos == std::string::npos)
		{
			nEndPos = srcString.size();
		}
		auto strSplit = srcString.substr(nStartPos, nEndPos - nStartPos);
		rVecSplitString.push_back(strSplit);

		DEAD_LOOP_BREAK(nBreakCount, nMaxSplits);
		nStartPos = nEndPos + nSplitLength;
		if (nStartPos > (int)(srcString.size()))
		{
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////
// Description:  替换std::string中的字符
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
int ReplaceStdString(IN OUT std::string& str, const char* pszOld, const char* pszNew, bool bReplaceAll/* = true*/)
{
	CHECKF(pszOld && ::strlen(pszOld) > 0);
	CHECKF(pszNew && ::strlen(pszNew) >= 0);
	if (str.empty())
	{
		return 0;
	}

	std::string::size_type unOldSize = ::strlen(pszOld);
	std::string::size_type unNewSize = ::strlen(pszNew);

	int nReplaceCount = 0;
	std::string::size_type unPos = 0;
	while ((unPos = str.find(pszOld, unPos)) != str.npos)
	{
		nReplaceCount++;
		str.replace(unPos, unOldSize, pszNew);
		unPos += unNewSize;
		if (!bReplaceAll)
		{
			break;
		}
	}

	return nReplaceCount;
}

////////////////////////////////////////////////////////////////////////
// Description: 寻找正则表达式字串
// Arguments:	邮箱合法参考串  "([0-9A-Za-z\\-_\\.]+)@([0-9a-z]+\\.[a-z]{2,3}(\\.[a-z]{2})?)"
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool FindRegularSubString(const std::string& rMainString, const std::string& rRegularSubString)
{
#if		(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
	std::regex pattern(rRegularSubString.c_str());
	if (regex_match(rMainString, pattern))
	{
		return true;
	}
	return false;
#elif	(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID||CC_TARGET_PLATFORM == CC_PLATFORM_IOS)  
	char ss[1024] = "";
	sprintf(ss, "%s", rMainString.c_str());
	regmatch_t pmatch[4];
	regex_t match_regex;
	regcomp(&match_regex, rRegularSubString.c_str(), REG_EXTENDED);
	if (regexec(&match_regex, ss, 4, pmatch, 0) != 0)
	{
		regfree(&match_regex);
		return false;
	}
	else
	{
		regfree(&match_regex);
		return true;
	}
	regfree(&match_regex);
#endif 
	return false;
};

struct RGBA32      //32 bit color
{
	GLubyte  B, G, R, A;          // A is alpha
};

struct ImageRegion  //一块颜色数据区的描述，便于参数传递
{
	RGBA32*	pdata;			//颜色数据首地址
	int     byte_width;		//一行数据的物理宽度(字节宽度)；
							//abs(byte_width) 有可能大于等于width*sizeof(TARGB32);
	int    width;			//像素宽度
	int    height;			//像素高度
};

void ImageZoom(const ImageRegion& Dst, const ImageRegion& Src)
{
	if ((0 == Dst.width) || (0 == Dst.height)
		|| (0 == Src.width) || (0 == Src.height)) return;
	uint32_t xrIntFloat_16 = (Src.width << 16) / Dst.width + 1;
	uint32_t yrIntFloat_16 = (Src.height << 16) / Dst.height + 1;
	uint32_t dst_width = Dst.width;
	RGBA32* pDstLine = Dst.pdata;
	uint32_t srcy_16 = 0;
	for (uint32_t y = 0; y < Dst.height; ++y)
	{
		RGBA32* pSrcLine = ((RGBA32*)((GLubyte*)Src.pdata + Src.byte_width*(srcy_16 >> 16)));
		uint32_t srcx_16 = 0;
		for (uint32_t x = 0; x < dst_width; ++x)
		{
			pDstLine[x] = pSrcLine[srcx_16 >> 16];
			srcx_16 += xrIntFloat_16;
		}
		srcy_16 += yrIntFloat_16;
		((GLubyte*&)pDstLine) += Dst.byte_width;
	}
}

////////////////////////////////////////////////////////////////////////
// Description: 创建虚化屏幕
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void AddBlurScreen(Layer* layer, bool bForceLowEffect /*= false*/)
{
	static CustomCommand addBlurScreenCommand;
	addBlurScreenCommand.init(std::numeric_limits<float>::max());
	addBlurScreenCommand.func = std::bind(OnAddBlurScreen, layer, bForceLowEffect);
	Director::getInstance()->getRenderer()->addCommand(&addBlurScreenCommand);
}

////////////////////////////////////////////////////////////////////////
// Description: 虚化屏幕回调
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void OnAddBlurScreen(Layer* layer, bool bForceLowEffect)
{
	CHECK(layer);

#pragma message(PRAGMAMSG(低特效虚化用半透灰色代替))
	if (bForceLowEffect || false)
	{
		auto color = LayerColor::create(Color4B(0, 0, 0, 192));
		color->setLocalZOrder(-1);
		layer->addChild(color);
		return;
	}

	auto glView = Director::getInstance()->getOpenGLView();
	auto frameSize = glView->getFrameSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
	frameSize = frameSize * glView->getFrameZoomFactor() * glView->getRetinaFactor();
#endif

	int width = static_cast<int>(frameSize.width);
	int height = static_cast<int>(frameSize.height);
	
	auto time_begin = ::GetUtcMillisecond();

	do
	{
		std::shared_ptr<GLubyte> buffer(new GLubyte[width * height * 4], [](GLubyte* p){ CC_SAFE_DELETE_ARRAY(p); });
		if (!buffer)
		{
			break;
		}
		
		glPixelStorei(GL_PACK_ALIGNMENT, 1);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
		// The frame buffer is always created with portrait orientation on WP8. 
		// So if the current device orientation is landscape, we need to rotate the frame buffer.  
		auto renderTargetSize = glView->getRenerTargetSize();
		CCASSERT(width * height == static_cast<int>(renderTargetSize.width * renderTargetSize.height), "The frame size is not matched");
		glReadPixels(0, 0, (int)renderTargetSize.width, (int)renderTargetSize.height, GL_RGBA, GL_UNSIGNED_BYTE, buffer.get());
#else
		glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer.get());
#endif

		auto time1 = ::GetUtcMillisecond() - time_begin;
		std::shared_ptr<GLubyte> flippedBuffer(new GLubyte[width * height * 4], [](GLubyte* p) { CC_SAFE_DELETE_ARRAY(p); });
		std::shared_ptr<GLubyte> flippedZipBuffer(new GLubyte[width * height / 4], [](GLubyte* p) { CC_SAFE_DELETE_ARRAY(p); });
		if (!flippedBuffer || !flippedZipBuffer)
		{
			break;
		}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
		if (width == static_cast<int>(renderTargetSize.width))
		{
			// The current device orientation is portrait.
			for (int row = 0; row < height; ++row)
			{
				memcpy(flippedBuffer.get() + (height - row - 1) * width * 4, buffer.get() + row * width * 4, width * 4);
			}
		}
		else
		{
			// The current device orientation is landscape.
			for (int row = 0; row < width; ++row)
			{
				for (int col = 0; col < height; ++col)
				{
					*(int*)(flippedBuffer.get() + (height - col - 1) * width * 4 + row * 4) = *(int*)(buffer.get() + row * height * 4 + col * 4);
				}
			}
		}
#else
		for (int row = 0; row < height; ++row)
		{
			memcpy(flippedBuffer.get() + (height - row - 1) * width * 4, buffer.get() + row * width * 4, width * 4);
		}
#endif

		ImageRegion src = { 0 };
		src.pdata = (RGBA32*)flippedBuffer.get();
		src.byte_width = width * sizeof(RGBA32);
		src.width = width;
		src.height = height;
		
		ImageRegion target = { 0 };
		target.pdata = (RGBA32*)flippedZipBuffer.get();
		target.byte_width = width * sizeof(RGBA32) / 4;
		target.width = width / 4;
		target.height = height / 4;

		auto time2 = ::GetUtcMillisecond() - time_begin;
		ImageZoom(target, src);
		auto time3 = ::GetUtcMillisecond() - time_begin;
		stackblur(flippedZipBuffer.get(), width / 4, height / 4, 4);
		auto time4 = ::GetUtcMillisecond() - time_begin;

		auto image = new (std::nothrow) Image();
		if (image && image->initWithRawData(flippedZipBuffer.get(), width * height / 4, width / 4, height / 4, 8))
		{
			auto texture2D = new (std::nothrow) Texture2D();
			if (texture2D && texture2D->initWithImage(image, Texture2D::PixelFormat::RGB565))
			{
				auto sprite = Sprite::createWithTexture(texture2D);
				CHECK(sprite);
				sprite->setAnchorPoint(Vec2::ZERO);
				sprite->setPosition(Vec2::ZERO);

				auto size = sprite->getContentSize();
				CHECK(size.width > 10);
				auto scaleX = APP_DESIGN_WIDTH / size.width;
				auto scaleY = APP_DESIGN_HEIGHT / size.height;
				sprite->setLocalZOrder(-1);
				sprite->setScale(scaleX, scaleY);
				layer->addChild(sprite);
			}
			CC_SAFE_DELETE(image);
		}
		auto time5 = ::GetUtcMillisecond() - time_begin;

		LogSave("BlurTimeCost: %d/%d/%d/%d/%d", (int)time1, (int)time2, (int)time3, (int)time4, (int)time5);
	} while (0);
}

////////////////////////////////////////////////////////////////////////
// Description: 检查名字
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CheckName(const std::string& name)
{
	int nStringSize = name.size();
	if (nStringSize == 0)
	{
		return false;
	}

	// 10个字节以下字节直接允许
	if (nStringSize < 10)
	{
		return true;
	}

	if (nStringSize >= 32)
	{
		return false;
	}

	int nUtf8Len = StringUtils::getCharacterCountInUTF8String(name);
	if (nUtf8Len > 7)
	{
		return false;
	}

	if (!StrSqlCheck(name.c_str()))
	{
		return false;
	}

#pragma message(PRAGMAMSG(此处需要加入客户端敏感词过滤检查))
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 检查字符串是否合法
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CheckText(const std::string& text)
{
	int nStringSize = text.size();
	if (nStringSize >= 256)
	{
		return false;
	}

	if (!StrSqlCheck(text.c_str()))
	{
		return false;
	}

#pragma message(PRAGMAMSG(此处需要加入客户端敏感词过滤检查))
	return true;
}


////////////////////////////////////////////////////////////////////////
// Description:  检查字符串是否包含sql语句
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool StrSqlCheck(const char* pszString)
{
	if (!pszString)
		return false;

	int nLen = strlen(pszString);
	wchar_t c = '\0';
	for (int i = 0; i < nLen; i++)
	{
		c = pszString[i];
		if (c < ' ')
			return false;
		switch (c)
		{
		case ';':
		case ',':
		case '/':
		case '\\':
		case '=':
		case '%':
		case '@':
		case '\'':
		case '"':
		case '[':
		case ']':
		case '#':
		case '?':
		case '*':
		case '!':
		case '<':
		case '>':
			return false;
		}
	}

	return true;
}


////////////////////////////////////////////////////////////////////////
// Description: 获得lookface
// Arguments:	
// Author: 彭文奇(Peng Wenqi)
// Return Value: SpriteFrame*
////////////////////////////////////////////////////////////////////////
SpriteFrame* getLookface(OBJID idLookface)
{
	SpriteFrame* result = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("lookface/%u.png", idLookface));
	if (nullptr == result)
	{
		result = SpriteFrameCache::getInstance()->getSpriteFrameByName("lookface/1001.png");
	}
	return result;
}

////////////////////////////////////////////////////////////////////////
// Description: 获得lookface
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: std::string
////////////////////////////////////////////////////////////////////////
std::string getLookfaceFileName(OBJID idLookface)
{
	SpriteFrame* pSpriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("lookface/%u.png", idLookface));
	if (nullptr == pSpriteFrame)
	{
		return "lookface/1001.png";
	}
	return StringUtils::format("lookface/%u.png", idLookface);
}

////////////////////////////////////////////////////////////////////////
// Description: 获得物品icon
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: SpriteFrame*
////////////////////////////////////////////////////////////////////////
SpriteFrame* getItemIcon(OBJID idItemtype)
{
	if (!ConstTableMgr::getInstance()->IsExistSingle(CONST_TABLE_TYPE_item_type, idItemtype))
	{
		return  SpriteFrameCache::getInstance()->getSpriteFrameByName("item/100001.png");
	}

	uint32_t unIcon = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_item_type, idItemtype, ITEM_TYPE_DATA_ICON);
	SpriteFrame* result = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("item/%u.png", unIcon));
	if (nullptr == result)
	{
		result = SpriteFrameCache::getInstance()->getSpriteFrameByName("item/100001.png");
	}
	return result;
}

////////////////////////////////////////////////////////////////////////
// Description: 获得物品icon
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: std::string
////////////////////////////////////////////////////////////////////////
std::string getItemIconFileName(OBJID idItemtype)
{
	if (!ConstTableMgr::getInstance()->IsExistSingle(CONST_TABLE_TYPE_item_type, idItemtype))
	{
		return  "item/100001.png";
	}
	OBJID idIcon = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_item_type, idItemtype, ITEM_TYPE_DATA_ICON);
	SpriteFrame* result = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("item/%u.png", idIcon));
	if (nullptr == result)
	{
		return  "item/100001.png";
	}
	return StringUtils::format("item/%u.png", idIcon);
}

////////////////////////////////////////////////////////////////////////
// Description: 获得魔法icon
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: SpriteFrame*
////////////////////////////////////////////////////////////////////////
SpriteFrame* getMagicIcon(OBJID idMagicType)
{
	if (!ConstTableMgr::getInstance()->IsExistSingle(CONST_TABLE_TYPE_magic_type, idMagicType))
	{
		return  SpriteFrameCache::getInstance()->getSpriteFrameByName("magic/1.png");
	}

	uint32_t unIcon = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_magic_type, idMagicType, MAGIC_TYPE_DATA_icon);
	SpriteFrame* result = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("magic/%u.png", unIcon));
	if (nullptr == result)
	{
		result = SpriteFrameCache::getInstance()->getSpriteFrameByName("magic/1.png");
	}
	return result;
}

////////////////////////////////////////////////////////////////////////
// Description: 获得魔法icon
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: std::string
////////////////////////////////////////////////////////////////////////
std::string getMagicIconFileName(OBJID idMagicType)
{
	if (!ConstTableMgr::getInstance()->IsExistSingle(CONST_TABLE_TYPE_magic_type, idMagicType))
	{
		return  "magic/1.png";
	}
	OBJID idIcon = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_magic_type, idMagicType, MAGIC_TYPE_DATA_icon);
	SpriteFrame* result = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("magic/%u.png", idIcon));
	if (nullptr == result)
	{
		return  "magic/1.png";
	}
	return StringUtils::format("magic/%u.png", idIcon);
}

////////////////////////////////////////////////////////////////////////
// Description: 获得宝具icon
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: SpriteFrame*
////////////////////////////////////////////////////////////////////////
SpriteFrame* getEquipMagicIcon(OBJID idMagicIcon)
{
	SpriteFrame* result = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("magic/%u.png", idMagicIcon));
	if (nullptr == result)
	{
		result = SpriteFrameCache::getInstance()->getSpriteFrameByName("magic/5001.png");
	}
	return result;
}

////////////////////////////////////////////////////////////////////////
// Description: 获得宝具icon
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: std::string
////////////////////////////////////////////////////////////////////////
std::string getEquipMagicIconFileName(OBJID idMagicIcon)
{
	SpriteFrame* result = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("magic/%u.png", idMagicIcon));
	if (nullptr == result)
	{
		return  "magic/5001.png";
	}
	return StringUtils::format("magic/%u.png", idMagicIcon);
}

////////////////////////////////////////////////////////////////////////
// Description: 创建边框发亮动作
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: RepeatForever* 
////////////////////////////////////////////////////////////////////////
RepeatForever* createFrameLight(float fTime /*= 3.f*/)
{
	auto fadeAction1 = FadeTo::create(fTime * 0.666f, 0);
	auto fadeAction2 = FadeTo::create(fTime * 0.333f, 255);
	auto seqAction = Sequence::create(fadeAction1, fadeAction2, NULL);
	return RepeatForever::create(seqAction);
}

////////////////////////////////////////////////////////////////////////
// Description: 创建悬浮动画第一部分
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: Action*
////////////////////////////////////////////////////////////////////////
Action* createTurnActionPart1()
{
	Vector<FiniteTimeAction*> vecAction;
	vecAction.pushBack(DelayTime::create(RandGet(50) / 100.f));
	auto stda = OrbitCamera::create(0.5f, 1, 0, 0, -8, 0, 0);
	vecAction.pushBack(stda);
	vecAction.pushBack(stda->reverse());
	auto stdb = OrbitCamera::create(0.5f, 1, 0, 0, 8, 0, 0);
	vecAction.pushBack(stdb);
	vecAction.pushBack(stdb->reverse());
	return Speed::create(RepeatForever::create(Sequence::create(vecAction)), 1.f);
}

////////////////////////////////////////////////////////////////////////
// Description: 创建悬浮动画第二部分
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: Speed*
////////////////////////////////////////////////////////////////////////
Action* createTurnActionPart2()
{
	Vector<FiniteTimeAction*> vecAction;
	vecAction.pushBack(DelayTime::create(RandGet(50) / 100.f));
	vecAction.pushBack(RotateTo::create(0.5f, 4));
	vecAction.pushBack(DelayTime::create(0.3f));
	vecAction.pushBack(RotateTo::create(1.0f, -8));
	vecAction.pushBack(DelayTime::create(0.3f));
	vecAction.pushBack(RotateTo::create(0.5f, 4));
	vecAction.pushBack(DelayTime::create(0.3f));
	return Speed::create(RepeatForever::create(Sequence::create(vecAction)), 1.f);
}

