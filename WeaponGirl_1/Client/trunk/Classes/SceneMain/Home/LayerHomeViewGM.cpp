////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerHomeViewGM.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/11/25
////////////////////////////////////////////////////////////////////////
#include "LayerHomeView.h"
#include "Root.h"
#include "../SceneMain.h"
#include "network\AllMsg.h"
#include "Mgr\MoneyMgr.h"
#include "Mgr\LoginMgr.h"

#pragma warning (disable: 4996)

////////////////////////////////////////////////////////////////////////
// Description: 调试功能触发, 双端gm命令触发入口
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void LayerHomeView::editBoxReturn(ui::EditBox* editBox)
{
	CHECK(editBox);
	log(editBox->getText());
	std::string cmd = editBox->getText();

#ifdef COCOS2D_DEBUG
	if (cmd.size() > 0 && cmd[0] == '!')
	{
		ReplaceStdString(cmd, "!", "");
		this->processClientGmCmd(cmd);
		return;
	}
#endif // end of #ifdef COCOS2D_DEBUG

	CMsgGameDebug msg;
	msg.CreateString(cmd.c_str());
	NetworkServe::getInstance()->sendMsg(msg);
}

////////////////////////////////////////////////////////////////////////
// Description: 处理客户端gm命令
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void LayerHomeView::processClientGmCmd(const std::string& cmd)
{
	std::vector<std::string> vecCmd;
	::SpiltString(cmd, " ", vecCmd, 100);

	if (3 == vecCmd.size() && 0 == stricmp(vecCmd[0].c_str(), "comment"))
	{
		switch (vecCmd[1][0])
		{
		case '+':
			{
				CMsgCommentList msg;
				msg.CreateNewComment(123, vecCmd[2].c_str());
				NetworkServe::getInstance()->sendMsg(msg);
			}
			break;
		case 'q':
		case 'Q':
			{
				auto commentType = atoi(vecCmd[2].c_str());
				CMsgCommentOpt msg;
				msg.CreateCommentOpt(MSG_COMMENT_OPT_ACTION_querylist, commentType, 0);
				NetworkServe::getInstance()->sendMsg(msg);
			}
			break;
		case 'z':
		case 'Z':
			{
				auto commentID = atoi(vecCmd[2].c_str());
				CMsgCommentOpt msg;
				msg.CreateCommentOpt(MSG_COMMENT_OPT_ACTION_click_good, 0, commentID);
				NetworkServe::getInstance()->sendMsg(msg);
			}
			break;
		default:
			break;
		}
	}
	else if (3 == vecCmd.size() && 0 == stricmp(vecCmd[0].c_str(), "bbs"))
	{
		switch (vecCmd[1][0])
		{
		case 'l':
		case 'L':
			{
				CMsgGameBbs msg;
				msg.CreateBbsBase(MSG_BBS_ACTION_querylist);
				NetworkServe::getInstance()->sendMsg(msg);
			}
			break;
		case '+':
			{
				BBS_INFO info = { 0 };
				SafeCopy(info.szText, vecCmd[2].c_str(), sizeof(info.szText));
				CMsgGameBbs msg;
				msg.CreateBbsBase(MSG_BBS_ACTION_addnew);
				msg.AppendBbsInfo(info);
				NetworkServe::getInstance()->sendMsg(msg);
			}
			break;
		case 'r':
		case 'R':
			{
				auto idBBS = atoi(vecCmd[2].c_str());
				CMsgGameBbsReply msg;
				msg.CreateBbsReplyBase(MSG_BBS_REPLY_ACTION_querylist, idBBS);
				NetworkServe::getInstance()->sendMsg(msg);
			}
			break;
		case '*':
			{
				BBS_REPLY_INFO info = { 0 };
				SafeCopy(info.szText, vecCmd[2].c_str(), sizeof(info.szText));

				auto idBBS = atoi(vecCmd[2].c_str());
				CMsgGameBbsReply msg;
				msg.CreateBbsReplyBase(MSG_BBS_REPLY_ACTION_addnew, idBBS);
				msg.AppendBbsReplyInfo(info);
				NetworkServe::getInstance()->sendMsg(msg);
			}
			break;
		default:
			break;
		}
	}
	else if (3 == vecCmd.size() && 0 == stricmp(vecCmd[0].c_str(), "gift"))
	{
		switch (vecCmd[1][0])
		{
		case 'l':
		case 'L':
			{
				CMsgGameGift msg;
				msg.CreateGiftBase(MSG_GIFT_ACTION_querylist);
				NetworkServe::getInstance()->sendMsg(msg);
			}
			break;
		case 'g':
		case 'G':
			{
				GIFT_INFO info = { 0 };
				info.idGift = atoi(vecCmd[2].c_str());
				CMsgGameGift msg;
				msg.CreateGiftBase(MSG_GIFT_ACTION_getgift);
				msg.AppendGiftInfo(info);
				NetworkServe::getInstance()->sendMsg(msg);
			}
			break;
		default:
			break;
		}
	}
}
