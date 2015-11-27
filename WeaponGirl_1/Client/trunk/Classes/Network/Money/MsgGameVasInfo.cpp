#include "./MsgGameVasInfo.h"
#include "Mgr/MoneyMgr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMsgGameVasInfo::CMsgGameVasInfo()
{
	Init();
	m_pInfo = (MSG_Info*)m_bufMsg;
	m_head.usType = _MSG_GAME_VAS_INFO;
	m_head.usSize = sizeof(MSG_Info);
}

CMsgGameVasInfo::~CMsgGameVasInfo()
{

}


//////////////////////////////////////////////////////////////////////////
void CMsgGameVasInfo::Process()
{
	MoneyMgr::getInstance()->updateMoneyData(USER_MONEY_TYPE_VAS, m_pInfo->i64Vas, 0, 0);

	MoneyMgr::getInstance()->setVasFirstMask(m_pInfo->nFirstMask);
	MoneyMgr::getInstance()->setMonthCardID(m_pInfo->nMonthCardID);
	MoneyMgr::getInstance()->setMonthCardTodayCanGet(!!m_pInfo->sMonthCardTodayCanGet);
	MoneyMgr::getInstance()->setMonthCardLeftCount(m_pInfo->sMonthCardLeftCount);

}