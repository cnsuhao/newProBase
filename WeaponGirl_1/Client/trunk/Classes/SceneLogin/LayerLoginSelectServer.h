////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerLoginSelectServer.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/10/10
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_CONST_LayerLoginSelectServer_
#define _JYP_CONST_LayerLoginSelectServer_

#include "Global/Global.h"

class SceneLogin;
class LayerLoginSelectServer : public Layer, public TouchPriorityBase
{
public:
	virtual bool init();
	CREATE_FUNC(LayerLoginSelectServer);
protected:
	virtual ~LayerLoginSelectServer();

protected:
	void clickClose(Ref* pSender){ this->removeFromParent(); };
	void clickRecommond(Ref* pSender);
	void clickAll(Ref* pSender);
	void selectedServerListEvent(Ref* pSender, ui::ListView::EventType type);
	SceneLogin* getFather() const { return (SceneLogin*)_parent; }
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	Node* m_pCsbNodeServerSeparator;
	Node* m_pCsbNodeServerInfo;
};


#endif // end of _JYP_CONST_LayerLoginSelectServer_