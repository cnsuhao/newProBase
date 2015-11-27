////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameShop.h
// Author: �½���(Chen Jianjun)
// Created: 2015-11-3
////////////////////////////////////////////////////////////////////////
#ifndef _GAMEKERNEL_MSG_GAME_SHOP_H_
#define _GAMEKERNEL_MSG_GAME_SHOP_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "./Network/NetMsg.h"

enum EMSGSHOPACTION				// ��Ϣ����
{
	EMSHOPA_NONE		= 0,
	EMSHOPA_BUY			= 1,	// ������Ʒ
};

enum EMSGSHOPRESULT				// ��Ϣ�������
{
	EMSHOPR_SUC			= 0,	// ǩ���ɹ�
	EMSHOPR_FAILD		= 1,	// ͨ��ʧ��
	EMSHOPR_PACKFULL	= 2,	// ��������
};

class CMsgGameShop : public CNetMsg
{
public:
	CMsgGameShop();
	virtual ~CMsgGameShop();

protected:
	virtual void Process();

public:
	bool	CreateMsg(MSG_NUM_2BIT sAction, MSG_NUM_2BIT sResult, MSG_NUM_4BIT idShopGoods);

private:
	typedef struct{
		MSG_NUM_2BIT	sAction;
		MSG_NUM_2BIT	sResult;
		MSG_NUM_4BIT	idShopGoods;
	}MSG_Info;

	MSG_Info*			m_pInfo;
};

#endif // !defined _GAMEKERNEL_MSG_GAME_SHOP_H_
