////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-2016, WuHan GoodGame, All Rights Reserved
// Moudle: LayerMessageBox.h
// Author: ¿Ó√ŒÀ…(MengSong Lee)
// Created: 2015-3-30
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_LAYER_MESSAGEBOX_H_
#define _JPY_LAYER_MESSAGEBOX_H_

#include "Global/Global.h"

class LayerMessageBox : public Layer
{
protected:
	LayerMessageBox();
	~LayerMessageBox();

public:
	static LayerMessageBox* createWithMessage(const std::string& message, const std::string& title = "", MESSAGE_BOX_MODE mode = MESSAGE_BOX_MODE_OK, bool bCloseByBg = false,
											  MessageBoxClickCallback callback = nullptr, Ref* pRef = nullptr);
	bool initWithMessage(const std::string& message, const std::string& title, MESSAGE_BOX_MODE mode, bool bCloseByBg, MessageBoxClickCallback callback , Ref* pRef);

protected:
	void setClickCallback(MessageBoxClickCallback callback, Ref* pRef);
protected:
	MessageBoxClickCallback m_callbackMessageBoxClick;
	Ref* m_pClickCallBackRef;
	EventListenerTouchOneByOne* m_pLayerTouchListener;
	CC_SYNTHESIZE(ui::Widget*, m_pWidget, Widget);
	CC_SYNTHESIZE(bool, m_bCloseByBg, IsCloseByBg);
	CC_SYNTHESIZE(std::string, m_strMessage, Message);
		
protected:
	void clickMessageBoxBtnOK(Ref* pSender);
	void clickMessageBoxBtnCancel(Ref* pSender);
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
};

#endif // end of _JPY_LAYER_COMMON_H_
