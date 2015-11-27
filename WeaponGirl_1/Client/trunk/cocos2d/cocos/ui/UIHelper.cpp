/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "ui/UIHelper.h"
#include "ui/UIWidget.h"
#include "ui/UILayoutComponent.h"
#include "base/CCDirector.h"

#include "deprecated/CCString.h"
#include "ui/UIText.h"
#include "ui/UILoadingBar.h"
#include "ui/UIImageView.h"
#include "2d/CCSprite.h"
#include "UITextBMFont.h"
NS_CC_BEGIN

namespace ui {

static bool _activeLayout = true;

Widget* Helper::seekWidgetByTag(Widget* root, int tag)
{
    if (!root)
    {
        return nullptr;
    }
    if (root->getTag() == tag)
    {
        return root;
    }
    const auto& arrayRootChildren = root->getChildren();
    ssize_t length = arrayRootChildren.size();
    for (ssize_t i=0;i<length;i++)
    {
        Widget* child = dynamic_cast<Widget*>(arrayRootChildren.at(i));
        if (child)
        {
            Widget* res = seekWidgetByTag(child,tag);
            if (res != nullptr)
            {
                return res;
            }
        }
    }
    return nullptr;
}

Widget* Helper::seekWidgetByNameDFS(Widget* root, const std::string& name)
{
    if (!root)
    {
        return nullptr;
    }
    if (root->getName() == name)
    {
        return root;
    }
    const auto& arrayRootChildren = root->getChildren();
    for (auto& subWidget : arrayRootChildren)
    {
        Widget* child = dynamic_cast<Widget*>(subWidget);
        if (child)
        {
			Widget* res = seekWidgetByNameDFS(child, name);
            if (res != nullptr)
            {
                return res;
            }
        }
    }
    return nullptr;
}

////////////////////////////////////////////////////////////////////////
// Description: 重构为广搜
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: Widget* 
////////////////////////////////////////////////////////////////////////
Widget* Helper::seekWidgetByName(Widget* root, const std::string& name)
{
    if (!root)
    {
        return nullptr;
    }

    if (root->getName() == name)
    {
        return root;
    }

    const auto& arrayRootChildren = root->getChildren();
    for (auto& subWidget : arrayRootChildren)
    {
        Widget* child = dynamic_cast<Widget*>(subWidget);
        if (child)
        {
			if (child->getName() == name)
			{
				return child;
			}
		}
	}

	for (auto& subWidget : arrayRootChildren)
	{
		Widget* child = dynamic_cast<Widget*>(subWidget);
		if (child)
		{
            Widget* res = seekWidgetByName(child,name);
            if (res != nullptr)
            {
                return res;
            }
        }
    }

    return nullptr;
}

////////////////////////////////////////////////////////////////////////
Node* Helper::seekNodeByName(Node* root, const std::string& name)
{
	if (!root)
	{
		return nullptr;
	}

	if (root->getName() == name)
	{
		return root;
	}

	const auto& arrayRootChildren = root->getChildren();
	for (auto& subNode : arrayRootChildren)
	{
		if (subNode)
		{
			if (subNode->getName() == name)
			{
				return subNode;
			}
		}
	}

	for (auto& subNode : arrayRootChildren)
	{
		if (subNode)
		{
			Node* res = seekNodeByName(subNode, name);
			if (res != nullptr)
			{
				return res;
			}
		}
	}

	return nullptr;
}


/*temp action*/
Widget* Helper::seekActionWidgetByActionTag(Widget* root, int tag)
{
	if (!root)
	{
		return nullptr;
	}
	if (root->getActionTag() == tag)
	{
		return root;
	}
    const auto& arrayRootChildren = root->getChildren();
    for (auto& subWidget : arrayRootChildren)
	{
		Widget* child = dynamic_cast<Widget*>(subWidget);
        if (child)
        {
            Widget* res = seekActionWidgetByActionTag(child,tag);
            if (res != nullptr)
            {
                return res;
            }
        }
	}
	return nullptr;
}
    
std::string Helper::getSubStringOfUTF8String(const std::string& str, std::string::size_type start, std::string::size_type length)
{
    if (length==0)
    {
        return "";
    }
    std::string::size_type c, i, ix, q, min=std::string::npos, max=std::string::npos;
    for (q=0, i=0, ix=str.length(); i < ix; i++, q++)
    {
        if (q==start)
        {
            min = i;
        }
        if (q <= start+length || length==std::string::npos)
        {
            max = i;
        }
        
        c = (unsigned char) str[i];
        
        if      (c<=127) i+=0;
        else if ((c & 0xE0) == 0xC0) i+=1;
        else if ((c & 0xF0) == 0xE0) i+=2;
        else if ((c & 0xF8) == 0xF0) i+=3;
        else return "";//invalid utf8
    }
    if (q <= start+length || length == std::string::npos)
    {
        max = i;
    }
    if (min==std::string::npos || max==std::string::npos)
    {
        return "";
    }
    return str.substr(min,max);
}

void Helper::changeLayoutSystemActiveState(bool bActive)
{
    _activeLayout = bActive;
}
void Helper::doLayout(cocos2d::Node *rootNode)
{
    if(!_activeLayout)
    {
        return;
    }

    for(auto& node : rootNode->getChildren())
    {
        auto com = node->getComponent(__LAYOUT_COMPONENT_NAME);
        Node *parent = node->getParent();
        if (nullptr != com && nullptr != parent) {
            LayoutComponent* layoutComponent = (LayoutComponent*)com;

            layoutComponent->refreshLayout();
        }
    }
}
    
Rect Helper::restrictCapInsetRect(const cocos2d::Rect &capInsets, const Size& textureSize )
{
    float x = capInsets.origin.x;
    float y = capInsets.origin.y;
    float width = capInsets.size.width;
    float height = capInsets.size.height;
    
    if (textureSize.width < width)
    {
        x = 0.0f;
        width = 0.0f;
    }
    if (textureSize.height < height)
    {
        y = 0.0f;
        height = 0.0f;
    }
    return Rect(x, y, width, height);
}

Rect Helper::convertBoundingBoxToScreen(Node* node)
{
    auto director = Director::getInstance();
    auto glView = director->getOpenGLView();
    auto frameSize = glView->getFrameSize();

    auto winSize = director->getWinSize();
    auto leftBottom = node->convertToWorldSpace(Point::ZERO);

    auto contentSize = node->getContentSize();
    auto rightTop = node->convertToWorldSpace(Point(contentSize.width, contentSize.height));

    auto uiLeft = frameSize.width / 2 + (leftBottom.x - winSize.width / 2 ) * glView->getScaleX();
    auto uiTop = frameSize.height /2 - (rightTop.y - winSize.height / 2) * glView->getScaleY();
    auto uiWidth = (rightTop.x - leftBottom.x) * glView->getScaleX();
    auto uiHeight = (rightTop.y - leftBottom.y) * glView->getScaleY();
    
    return Rect(uiLeft, uiTop, uiWidth, uiHeight);
}



////////////////////////////////////////////////////////////////////////
// Description: 设置Text控件文字
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool Helper::setStringTextBMFont(Node* root, const std::string& name, const std::string& str)
{
	if (!root)
	{
		return false;
	}

	auto target = dynamic_cast<ui::TextBMFont*>(ui::Helper::seekNodeByName(root, name));
	if (!target)
	{
		CCLOG("Helper::setStringText can not find target name[%s], str[%s]", name.c_str(), str.c_str());
		return false;
	}

	target->setString(str);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 设置Text控件文字
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool Helper::setStringText(Node* root, const std::string& name, const std::string& str)
{
	if (!root)
	{
		return false;
	}

	auto target = dynamic_cast<ui::Text*>(ui::Helper::seekNodeByName(root, name));
	if (!target)
	{
		CCLOG("Helper::setStringText can not find target name[%s], str[%s]", name.c_str(), str.c_str());
		return false;
	}

	target->setString(str);
	return true;
}


////////////////////////////////////////////////////////////////////////
// Description: 设置Text控件 由数字转文字
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool Helper::setDataText(Node* root, const std::string& name, int64_t data)
{
	if (!root)
	{
		return false;
	}

	auto target = dynamic_cast<ui::Text*>(ui::Helper::seekNodeByName(root, name));
	if (!target)
	{
		CCLOG("Helper::setDataText can not find target name[%s], str[%lld]", name.c_str(), data);
		return false;
	}

	target->setString(StringUtils::format("%lld", data));
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 设置Node 可见性
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool Helper::setVisable(Node* root, const std::string& name, bool bVisable)
{
	if (!root)
	{
		return false;
	}

	auto target = ui::Helper::seekNodeByName(root, name);
	if (!target)
	{
		CCLOG("Helper::setVisable can not find target name[%s]", name.c_str());
		return false;
	}

	target->setVisible(bVisable);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 设置Node 可见性
// Arguments:	需要指定上级node名字
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool Helper::setVisable(Node* root, const std::string& fatherNodeName, const std::string& childName, bool bVisable)
{
	if (!root)
	{
		return false;
	}

	auto fatherNode = ui::Helper::seekNodeByName(root, fatherNodeName);
	if (!fatherNode)
	{
		CCLOG("Helper::setVisable[f->c] can not find fatherNodeName[%s]", fatherNodeName.c_str());
		return false;
	}

	return Helper::setVisable(fatherNode, childName, bVisable);
}

////////////////////////////////////////////////////////////////////////
// Description: 设置Node 触摸性
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool Helper::setTouchEnable(Node* root, const std::string& name, bool bEnable)
{
	if (!root)
	{
		return false;
	}

	auto target = dynamic_cast<ui::Widget*>(ui::Helper::seekNodeByName(root, name));
	if (!target)
	{
		CCLOG("Helper::setTouchEnable can not find target name[%s]", name.c_str());
		return false;
	}

	target->setTouchEnabled(bEnable);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 设置Node 触摸性
// Arguments:	需要指定上级node名字
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool Helper::setTouchEnable(Node* root, const std::string& fatherNodeName, const std::string& childName, bool bEnable)
{
	if (!root)
	{
		return false;
	}

	auto fatherNode = ui::Helper::seekNodeByName(root, fatherNodeName);
	if (!fatherNode)
	{
		CCLOG("Helper::setTouchEnable[f->c] can not find fatherNodeName[%s]", fatherNodeName.c_str());
		return false;
	}

	return Helper::setTouchEnable(fatherNode, childName, bEnable);
}

////////////////////////////////////////////////////////////////////////
// Description: 设置精灵属性
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool Helper::setSprite(Node* root, const std::string& name, const std::string& spriteFrameName, float fScale /*= 1.f*/)
{
	if (!root)
	{
		return false;
	}

	auto target = dynamic_cast<Sprite*>(ui::Helper::seekNodeByName(root, name));
	if (!target)
	{
		CCLOG("Helper::setSprite can not find target name[%s]", name.c_str());
		return false;
	}

	target->setSpriteFrame(spriteFrameName);
	target->setScale(fScale);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 设置ImageView正常/灰化
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool Helper::setImageViewEnable(Node* root, const std::string& name, bool bEnable)
{
	if (!root)
	{
		return false;
	}

	auto target = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(root, name));
	if (!target)
	{
		CCLOG("Helper::setImageViewEnable can not find target name[%s]", name.c_str());
		return false;
	}

	if (bEnable)
	{
		if (target->getShaderEffect() != MY_SHADER_EFFECT_LIGHT)
		{
			target->setShaderEffect(MY_SHADER_EFFECT_NONE);
		}
	}
	else
	{
		target->setShaderEffect(MY_SHADER_EFFECT_BLACK_AND_WHITE);
	}
	
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 设置ImageView图片
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool Helper::setImageViewTexturePlist(Node* root, const std::string& name, const std::string& fileName)
{
	if (!root)
	{
		return false;
	}

	auto target = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(root, name));
	if (!target)
	{
		CCLOG("Helper::setImageViewTexture can not find target name[%s]", name.c_str());
		return false;
	}

	target->loadTexture(fileName, ui::Widget::TextureResType::PLIST);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 设置ImageView图片
// Arguments:	需要指定上级node名字
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool Helper::setImageViewTexturePlist(Node* root, const std::string& fatherNodeName, const std::string& childName, const std::string& fileName)
{
	if (!root)
	{
		return false;
	}

	auto fatherNode = ui::Helper::seekNodeByName(root, fatherNodeName);
	if (!fatherNode)
	{
		CCLOG("Helper::setImageViewTexturePlist[f->c] can not find fatherNodeName[%s]", fatherNodeName.c_str());
		return false;
	}

	return Helper::setImageViewTexturePlist(fatherNode, childName, fileName);
}

////////////////////////////////////////////////////////////////////////
// Description: 设置widget单击事件
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool Helper::setWidgetClickEventListener(Node* root, const std::string& name, const ui::Widget::ccWidgetClickCallback& callback)
{
	if (!root)
	{
		return false;
	}

	auto target = dynamic_cast<ui::Widget*>(ui::Helper::seekNodeByName(root, name));
	if (!target)
	{
		CCLOG("Helper::setWidgetClickEventListener can not find target name[%s]", name.c_str());
		return false;
	}

	target->addClickEventListener(callback);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 设置imageview特效
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool Helper::setImageViewShaderEffect(Node* root, const std::string& name, MY_SHADER_EFFECT eShaderEffect)
{
	if (!root)
	{
		return false;
	}

	auto target = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(root, name));
	if (!target)
	{
		CCLOG("Helper::setImageViewShaderEffect can not find target name[%s]", name.c_str());
		return false;
	}

	target->setShaderEffect(eShaderEffect);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 设置imageview特效
// Arguments:	需要设置父节点
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool Helper::setImageViewShaderEffect(Node* root, const std::string& fatherNodeName, const std::string& childName, MY_SHADER_EFFECT eShaderEffect)
{
	if (!root)
	{
		return false;
	}

	auto fatherNode = ui::Helper::seekNodeByName(root, fatherNodeName);
	if (!fatherNode)
	{
		CCLOG("Helper::setImageViewShaderEffect can not find fatherNode[%s]", fatherNodeName.c_str());
		return false;
	}

	return Helper::setImageViewShaderEffect(fatherNode, childName, eShaderEffect);
}

////////////////////////////////////////////////////////////////////////
// Description: 设置imageview缩放
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool Helper::setImageViewScale(Node* root, const std::string& name, float fScaleX, float fScaleY)
{
	if (!root)
	{
		return false;
	}

	auto target = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(root, name));
	if (!target)
	{
		CCLOG("Helper::setImageViewScale can not find target name[%s]", name.c_str());
		return false;
	}

	target->setScale(fScaleX, fScaleY);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 设置LoadingBar百分比
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool Helper::setPercent(Node* root, const std::string& name, int64_t nowData, int64_t maxData)
{
	if (!root)
	{
		return false;
	}

	auto target = dynamic_cast<ui::LoadingBar*>(ui::Helper::seekNodeByName(root, name));
	if (!target)
	{
		CCLOG("Helper::setPercent can not find target name[%s], now[%lld]/max[%lld]", name.c_str(), nowData, maxData);
		return false;
	}

	if (maxData <= 0)
	{
		target->setPercent(100);
	}
	else
	{
		target->setPercent((float)nowData * 100.f / (float)maxData);
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool Helper::setOpacity(Node* root, const std::string& name, GLubyte opacity)
{
	if (!root)
	{
		return false;
	}

	auto target = ui::Helper::seekNodeByName(root, name);
	if (!target)
	{
		CCLOG("Helper::setOpacity can not find target name[%s]", name.c_str());
		return false;
	}

	target->setOpacity(opacity);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 设置ImageView属性
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool Helper::setImageViewAttr(Node* root, const std::string& name, bool bTouch, bool bEnable, bool bAutoTouch, bool bAutoAction)
{
	if (!root)
	{
		return false;
	}

	auto target = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(root, name));
	if (!target)
	{
		CCLOG("Helper::setImageViewAttr can not find target name[%s]", name.c_str());
		return false;
	}

	target->setTouchEnabled(bTouch);
	target->setEnabled(bEnable);
	target->setAutoTouchChangeRenderer(bAutoTouch);
	target->setAutoTouchAction(bAutoAction ? AUTO_TOUCH_ACTION_scale_small : AUTO_TOUCH_ACTION_none);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 设置ImageView属性
// Arguments:	需要父节点
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool Helper::setImageViewAttr(Node* root, const std::string& fatherNodeName, const std::string& childName, bool bTouch, bool bEnable, bool bAutoTouch, bool bAutoAction)
{
	if (!root)
	{
		return false;
	}

	auto fatherNode = ui::Helper::seekNodeByName(root, fatherNodeName);
	if (!fatherNode)
	{
		CCLOG("Helper::setImageViewAttr can not find fatherNode[%s]", fatherNodeName.c_str());
		return false;
	}

	return Helper::setImageViewAttr(fatherNode, childName, bTouch, bEnable, bAutoTouch, bAutoAction);
}

} // end namespace of ui


NS_CC_END
