////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MoneyMgr.cpp
// Author: ������(Peng Wenqi)
// Created: 2015/10/16
////////////////////////////////////////////////////////////////////////
#include "MoneyMgr.h"
#include "LoginMgr.h"

MoneyMgr* MoneyMgr::m_pInstance = nullptr;
//////////////////////////////////////////////////////////////////////////
MoneyMgr* MoneyMgr::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new MoneyMgr();
	}
	return m_pInstance;
}

//////////////////////////////////////////////////////////////////////////
void MoneyMgr::destroyInstance()
{

}

//////////////////////////////////////////////////////////////////////////
MoneyMgr::MoneyMgr()
{

}

////////////////////////////////////////////////////////////////////////
// Description: ���һ���������ַ���
// Arguments:	֧�� �� �� ����
// Author: ������(Peng Wenqi)
// Return Value: std::string
////////////////////////////////////////////////////////////////////////
std::string MoneyMgr::getBigForamt(int64_t data)
{
	if (data >= 100000000000i64)	// ����1000��, ����ʾС�� 
	{
		return StringUtils::format("%lldE", data / 100000000i64);
	}
	else if (data >= 10000000000i64)	// ����100��, ��ʾ1λС�� 
	{
		int xiaoshu = (data % 100000000i64) / 10000000;
		while (xiaoshu >= 10 && xiaoshu % 10 == 0){ xiaoshu /= 10; }	// С��β���Ƴ�
		if (xiaoshu > 0)
		{
			return StringUtils::format("%lld.%dE", data / 100000000i64, xiaoshu);
		}
		else
		{
			return StringUtils::format("%lldE", data / 100000000i64);
		}
	}
	else if (data >= 1000000000i64)	// ����10��, ��ʾ2λС�� 
	{
		int xiaoshu = (data % 100000000i64) / 1000000;
		while (xiaoshu >= 10 && xiaoshu % 10 == 0){ xiaoshu /= 10; }	// С��β���Ƴ�
		if (xiaoshu > 0)
		{
			return StringUtils::format("%lld.%dE", data / 100000000i64, xiaoshu);
		}
		else
		{
			return StringUtils::format("%lldE", data / 100000000i64);
		}
	}
	else if (data >= 100000000i64)	// ����1��, ��ʾ3λС�� 
	{
		int xiaoshu = (data % 100000000i64) / 100000;
		while (xiaoshu >= 10 && xiaoshu % 10 == 0){ xiaoshu /= 10; }	// С��β���Ƴ�
		if (xiaoshu > 0)
		{
			return StringUtils::format("%lld.%dE", data / 100000000i64, xiaoshu);
		}
		else
		{
			return StringUtils::format("%lldE", data / 100000000i64);
		}
	}
	else if (data >= 10000000)	// ����1000��, ����ʾС�� 
	{
		return StringUtils::format("%lldW", data / 10000);
	}
	else if (data >= 1000000)	// ����100��, ��ʾ1λС�� 
	{
		int xiaoshu = (data % 10000) / 1000;
		while (xiaoshu >= 10 && xiaoshu % 10 == 0){ xiaoshu /= 10; }	// С��β���Ƴ�
		if (xiaoshu > 0)
		{
			return StringUtils::format("%lld.%dW", data / 10000, xiaoshu);
		}
		else
		{
			return StringUtils::format("%lldW", data / 10000);
		}
	}
	else if (data >= 100000)	// ����10��, ��ʾ2λС�� 
	{
		int xiaoshu = (data % 10000) / 100;
		while (xiaoshu >= 10 && xiaoshu % 10 == 0){ xiaoshu /= 10; }	// С��β���Ƴ�
		if (xiaoshu > 0)
		{
			return StringUtils::format("%lld.%dW", data / 10000, xiaoshu);
		}
		else
		{
			return StringUtils::format("%lldW", data / 10000);
		}
	}
	else if (data >= 10000)	// ����1��, ��ʾ3λС�� 
	{
		int xiaoshu = (data % 10000) / 10;
		while (xiaoshu >= 10 && xiaoshu % 10 == 0){ xiaoshu /= 10; }	// С��β���Ƴ�
		if (xiaoshu > 0)
		{
			return StringUtils::format("%lld.%dW", data / 10000, xiaoshu);
		}
		else
		{
			return StringUtils::format("%lldW", data / 10000);
		}
	}
	else
	{
		return StringUtils::format("%lld", data);
	}
}

////////////////////////////////////////////////////////////////////////
// Description: ÿ��λ�ö��Ÿ���
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: std::string
////////////////////////////////////////////////////////////////////////
std::string MoneyMgr::getDivisionForamt(int64_t data)
{
	std::string result = "";
	if (data >= 100000000i64)	// ����1��
	{
		result += StringUtils::format("%lld,", data / 100000000i64);
	}

	if (data >= 10000i64)	// ����1��
	{
		auto temp = data % 100000000i64;
		result += StringUtils::format("%lld,", temp / 10000i64);
	}

	result += StringUtils::format("%lld", data % 10000i64);
	return result;
}

/*
��������
LogSave("%s", MoneyMgr::getBigForamt(1).c_str());
LogSave("%s", MoneyMgr::getBigForamt(12).c_str());
LogSave("%s", MoneyMgr::getBigForamt(123).c_str());
LogSave("%s", MoneyMgr::getBigForamt(1234).c_str());
LogSave("%s", MoneyMgr::getBigForamt(12345).c_str());
LogSave("%s", MoneyMgr::getBigForamt(123456).c_str());
LogSave("%s", MoneyMgr::getBigForamt(1234567).c_str());
LogSave("%s", MoneyMgr::getBigForamt(12345678).c_str());
LogSave("%s", MoneyMgr::getBigForamt(123456789).c_str());
LogSave("%s", MoneyMgr::getBigForamt(1234567890).c_str());
LogSave("%s", MoneyMgr::getBigForamt(12345678901).c_str());
LogSave("%s", MoneyMgr::getBigForamt(123456789012).c_str());
LogSave("%s", MoneyMgr::getBigForamt(1234567890123).c_str());
LogSave("%s", MoneyMgr::getBigForamt(12345678901234).c_str());


LogSave("%s", MoneyMgr::getBigForamt(12000).c_str());
LogSave("%s", MoneyMgr::getBigForamt(102000).c_str());
LogSave("%s", MoneyMgr::getBigForamt(120000000).c_str());
LogSave("%s", MoneyMgr::getBigForamt(1300000000).c_str());
*/

//////////////////////////////////////////////////////////////////////////
void MoneyMgr::clearMoneyData()
{
	m_mapData.clear();
}

//////////////////////////////////////////////////////////////////////////
void MoneyMgr::updateMoneyData(USER_MONEY_TYPE moneyType, int64_t moneyData, uint32_t timestart, uint32_t addspeed)
{
	auto iter = m_mapData.find(moneyType);
	if (iter != m_mapData.end())
	{
		iter->second.data = moneyData;
		iter->second.timestart = timestart;
		iter->second.addspeed = addspeed;
	}
	else
	{
		MONEY_INFO info = { 0 };
		info.data = moneyData;
		info.timestart = timestart;
		info.addspeed = addspeed;
		m_mapData[moneyType] = info;
	}	
}			

//////////////////////////////////////////////////////////////////////////
int64_t MoneyMgr::getMoney(USER_MONEY_TYPE moneyType) const
{
	auto iter = m_mapData.find(moneyType);
	if (iter == m_mapData.end())
	{
		return 0;
	}

	uint32_t nowtime = LoginMgr::getInstance()->getHeartbeat();

	int64_t moneydata = iter->second.data;
	int64_t timestart = iter->second.timestart;
	int64_t addspeed = iter->second.addspeed;

	int64_t addmoney = 0;
	if (timestart < nowtime && addspeed > 0)
	{
		addmoney = addspeed * (nowtime - timestart);
	}
	return moneydata + addmoney;
}

//////////////////////////////////////////////////////////////////////////
std::string MoneyMgr::getMoneyBigFormat(USER_MONEY_TYPE moneyType) const
{
	int64_t data = this->getMoney(moneyType);
	return MoneyMgr::getBigForamt(data);
}

//////////////////////////////////////////////////////////////////////////
std::string MoneyMgr::getMoneyDivisionForamt(USER_MONEY_TYPE moneyType) const
{
	int64_t data = this->getMoney(moneyType);
	return MoneyMgr::getDivisionForamt(data);
}

////////////////////////////////////////////////////////////////////////
// Description: ��û���SpriteFrame����
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: std::string 
////////////////////////////////////////////////////////////////////////
std::string MoneyMgr::getMoneySpriteFrameName(USER_MONEY_TYPE moneyType) const
{
	return StringUtils::format("money/%d.png", moneyType);
}


