////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2015, WuHan GoodGame, All Rights Reserved
// Moudle: NetMsg.cpp
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015-1-19
////////////////////////////////////////////////////////////////////////
#include "NetMsg.h"
#include "Global/Global.h"
#include "Network/AllMsg.h"

//////////////////////////////////////////////////////////////////////////
void CNetMsg::Init( void )
{
	memset(m_bufMsg, 0, sizeof(m_bufMsg));
	m_head.usType = _MSG_NONE;
	m_head.usSize = 0;
}

//////////////////////////////////////////////////////////////////////////
bool CNetMsg::IsVaild() const
{
	if(_MSG_NONE == this->GetType())
		return false;

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool CNetMsg::Create( const char* pMsgBuffer, unsigned short usSize, unsigned short usType )
{
	if(!pMsgBuffer)
		return false;

	m_head.usType = usType;
	m_head.usSize = usSize;

	memcpy(m_bufMsg, pMsgBuffer, usSize);
	return true;
}



//////////////////////////////////////////////////////////////////////////
CNetMsg* CNetMsg::CreateMsg(int nMsgSize, unsigned short usMsgType, const char* pbufMsg)
{
	// check it...
	if(usMsgType == _MSG_NONE || !pbufMsg || nMsgSize > MESSAGE_MAX_SIZE)
		return nullptr;

	CNetMsg* pMsg = CNetMsg::RegisterMsg(usMsgType);
	if (!pMsg)
	{
		return nullptr;
	}

	if(!pMsg->Create((char*)pbufMsg, nMsgSize, usMsgType))
	{
		CC_SAFE_DELETE(pMsg);
		return nullptr;
	}
	else
	{
		return pMsg;
	}

	return nullptr;
}

//////////////////////////////////////////////////////////////////////////
CNetMsg* CNetMsg::RegisterMsg( unsigned short usMsgType )
{
	CNetMsg* pMsg = nullptr;
	switch (usMsgType)
	{
	case _MSG_RL_SERVER_REQ_LOGIN:
		pMsg = new (std::nothrow) CMsgReqLogin();
		break;
	case _MSG_LOGIN_CONNECT:
		pMsg = new (std::nothrow) CMsgLoginConnect();
		break;
	case _MSG_LOGIN_USER_LIST:
		pMsg = new (std::nothrow) CMsgLoginUserList();
		break;
	case _MSG_LOGIN_CONNECT_ACTION:
		pMsg = new (std::nothrow) CMsgLoginAction();
		break;
	case _MSG_GAME_USER_INFO:
		pMsg = new (std::nothrow) CMsgGameUserInfo();
		break;
	case _MSG_LOGIN_KICK_REASON:
	case _MSG_GAME_KICK_REASON:
		pMsg = new (std::nothrow) CMsgKickReason();
		break;
	case _MSG_LOGIN_CREATE_NEW_USER:
		pMsg = new (std::nothrow) CMsgLoginCreateNewUser();
		break;
	case _MSG_GAME_LOGIN_QUERY:
		pMsg = new (std::nothrow) CMsgGameLoginQuery();
		break;
	case _MSG_GAME_SMALLACTION:
		pMsg = new (std::nothrow) CMsgGameSmallAction();
		break;
	case _MSG_GAME_USER_MONEY:
		pMsg = new (std::nothrow) CMsgGameUserMoney();
		break;	
	case _MSG_GAME_VAS_INFO:
		pMsg = new (std::nothrow) CMsgGameVasInfo();
		break;
	case _MSG_GAME_DEBUG:
		pMsg = new (std::nothrow) CMsgGameDebug();
		break;
	case _MSG_GAME_USER_ATTR:
		pMsg = new (std::nothrow) CMsgGameUserAttr();
		break;
	case _MSG_GAME_USER_MONEY_HINT:
		pMsg = new (std::nothrow) CMsgGameMoneyHint();
		break;
	case _MSG_GAME_ITEM:
		pMsg = new (std::nothrow) CMsgGameItem();
		break;
	case _MSG_GAME_POKER_LIST:
		pMsg = new (std::nothrow) CMsgGamePokerList();
		break;
	case _MSG_GAME_POKER_OPT:
		pMsg = new (std::nothrow) CMsgGamePokerOpt();
		break;
	case _MSG_GAME_POKER_BOOK_LIST:
		pMsg = new (std::nothrow) CMsgGamePokerBookList();
		break;
	case _MSG_GAME_POKER_HOLY:
		pMsg = new (std::nothrow) CMsgGamePokerHoly;
		break;
	case _MSG_GAME_SIGN:
		pMsg = new (std::nothrow) CMsgGameSign();
		break;
	case _MSG_GAME_FRIEND:
		pMsg = new (std::nothrow) CMsgGameFriend();
		break;
	case _MSG_GAME_SHOP:
		pMsg = new (std::nothrow) CMsgGameShop();
		break;
	case _MSG_COMMENT_OPT:
		pMsg = new (std::nothrow) CMsgCommentOpt();
		break;
	case _MSG_COMMENT_LIST:
		pMsg = new (std::nothrow) CMsgCommentList();
		break;
	case _MSG_GAME_BBS:
		pMsg = new (std::nothrow) CMsgGameBbs();
		break;
	case _MSG_GAME_BBS_REPLY:
		pMsg = new (std::nothrow) CMsgGameBbsReply();
		break;
	case _MSG_GAME_GIFT:
		pMsg = new (std::nothrow) CMsgGameGift();
		break;
	case _MSG_GAME_SMELT:
		pMsg = new (std::nothrow) CMsgGameSmelt();
		break;
	case _MSG_GAME_SMELT_MONSTER:
		pMsg = new (std::nothrow) CMsgGameSmeltMonster();
		break;
	case _MSG_GAME_BATTLE_INFO:
		pMsg = new (std::nothrow) CMsgGameBattleInfo();
		break;
	case _MSG_GAME_BATTLE_RESULT:
		pMsg = new (std::nothrow) CMsgGameBattleResult();
		break;
	case _MSG_GAME_CHALLENGE:
		pMsg = new (std::nothrow) CMsgGameChallenge();
		break;
	case _MSG_GAME_INSTANCE_INFO:
		pMsg = new (std::nothrow) CMsgGameInstanceInfo();
		break;
	case _MSG_GAME_INSTANCE_LIST:
		pMsg = new (std::nothrow) CMsgGameInstanceList();
		break;
	case _MSG_GAME_AWARD_HINT:
		pMsg = new (std::nothrow) CMsgGameAwardHint();
		break;
	default:
		cocos2d::log("========= usMsgType[%d] not CNetMsg::Register =========", usMsgType);
		break;
	}

	return pMsg;
}

//////////////////////////////////////////////////////////////////////////
void CNetMsg::Process()
{
	cocos2d::log("CNetMsg::Process type[%d] size[%d]", m_head.usType, m_head.usSize);
}
