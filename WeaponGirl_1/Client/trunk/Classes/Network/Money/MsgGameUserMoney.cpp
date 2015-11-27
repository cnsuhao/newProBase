#include "./MsgGameUserMoney.h"
#include "Mgr/MoneyMgr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMsgGameUserMoney::CMsgGameUserMoney()
{
	Init();
	m_pInfo = (MSG_Info*)m_bufMsg;
	m_head.usType = _MSG_GAME_USER_MONEY;
	m_head.usSize = sizeof(MSG_Info);
}

CMsgGameUserMoney::~CMsgGameUserMoney()
{

}


//////////////////////////////////////////////////////////////////////////
void CMsgGameUserMoney::Process()
{
	switch (m_pInfo->sAction)
	{
	case MSG_USER_MONEY_ACTION_UPDATE:
	case MSG_USER_MONEY_ACTION_QUERY_ALL:
		{
			for (int i = 0; i < m_pInfo->sCount; i++)
			{
				MSG_USER_MONEY&	stInfo = m_pInfo->stInfo[i];
				MoneyMgr::getInstance()->updateMoneyData((USER_MONEY_TYPE)m_pInfo->stInfo[i].nType, m_pInfo->stInfo[i].i64Data, m_pInfo->stInfo[i].unTimeStart, m_pInfo->stInfo[i].unAddSpeed);
			}
		}
		break;
	default:
		break;
	}
}

bool CMsgGameUserMoney::CreateUserMoneyBase(short sAction /*= MSG_USER_MONEY_ACTION_UPDATE*/)
{
	this->Init();
	m_head.usType = _MSG_GAME_USER_MONEY;
	m_head.usSize = sizeof(MSG_Info) - sizeof(MSG_USER_MONEY);

	m_pInfo->sAction = sAction;
	m_pInfo->sCount = 0;

	return true;
}

bool CMsgGameUserMoney::AppendMoneyInfo(int nType, int64_t i64Data)
{
	CHECKF(sizeof(MSG_Info) + sizeof(MSG_USER_MONEY) * m_pInfo->sCount < MAX_PACKETSIZE);
	m_pInfo->stInfo[m_pInfo->sCount].nType = nType;
	m_pInfo->stInfo[m_pInfo->sCount].i64Data = i64Data;
	m_head.usSize = sizeof(MSG_Info) + sizeof(MSG_USER_MONEY) * m_pInfo->sCount;
	m_pInfo->sCount++;
	return true;
}