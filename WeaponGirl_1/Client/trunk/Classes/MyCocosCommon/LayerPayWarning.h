////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerPayWarning.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/07/07
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_LAYER_PAY_WARNING_H_
#define _JPY_LAYER_PAY_WARNING_H_

#include "Global/Global.h"


class LayerPayWarning : public Layer, public TouchPriorityBase
{
public:
	static LayerPayWarning* create(OBJID idItemType, int nNeedCount, const std::string& strDetail, PayWarningCallback callbackOK, PayWarningCallback callbackCancel);
	virtual bool init(OBJID idItemType, int nNeedCount, const std::string& strDetail, PayWarningCallback callbackOK, PayWarningCallback callbackCancel);
	static LayerPayWarning* createWithHint(const std::string& strHint, const std::string& strDetail, PayWarningCallback callbackOK, PayWarningCallback callbackCancel);
	bool initWithHint(const std::string& strHint, const std::string& strDetail, PayWarningCallback callbackOK, PayWarningCallback callbackCancel);
	

protected:
	LayerPayWarning();
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
	virtual void onTouchCancelled(Touch *touch, Event *unused_event);

protected:
	void clickBtnOK(Ref* pSender);
	void clickBtnCancel(Ref* pSender);

protected:
	PayWarningCallback	m_callbackOK;
	PayWarningCallback	m_callbackCancel;
};


#endif // end of _JPY_LAYER_PAY_WARNING_H_