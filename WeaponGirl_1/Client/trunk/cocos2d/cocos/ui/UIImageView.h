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

#ifndef __UIIMAGEVIEW_H__
#define __UIIMAGEVIEW_H__

#include "ui/UIWidget.h"
#include "ui/GUIExport.h"
#include "UIScale9Sprite.h"

/**
 * @addtogroup ui
 * @{
 */
NS_CC_BEGIN

enum AUTO_TOUCH_ACTION
{
	AUTO_TOUCH_ACTION_none = 0,
	AUTO_TOUCH_ACTION_scale_small,
	AUTO_TOUCH_ACTION_scale_copy_big,
};

namespace ui {
    class Scale9Sprite;
/**
 * @brief A widget to display images.
 */
class CC_GUI_DLL ImageView : public Widget
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    /**
     * Default constructor
     * @js ctor
     * @lua new
     */
    ImageView();

    /**
     * Default destructor
     * @js NA
     * @lua NA
     */
    virtual ~ImageView();

    /**
     * Create a empty ImageView.
     */
    static ImageView* create();
    
    /**
     * Create a  imageview  with a image name.
     *
     * @param imageFileName   file name of texture.
     * @param texType    @see `Widget::TextureResType`
     * @return A ImageView instance.
     */
    static ImageView* create(const std::string& imageFileName, TextureResType texType = TextureResType::LOCAL);
    

    /**
     * Load texture for imageview.
     *
     * @param fileName   file name of texture.
     * @param texType    @see `Widget::TextureResType`
     */
    void loadTexture(const std::string& fileName,TextureResType texType = TextureResType::LOCAL);

    /**
     * Updates the texture rect of the ImageView in points.
     * It will call setTextureRect:rotated:untrimmedSize with rotated = NO, and utrimmedSize = rect.size.
     */
    void setTextureRect(const Rect& rect);

    /**
     * Enable scale9 renderer.
     *
     * @param enabled Set to true will use scale9 renderer, false otherwise.
     */
    void setScale9Enabled(bool enabled);

    /**
     * Query whether button is using scale9 renderer or not.
     *@return whether button use scale9 renderer or not.
     */
    bool isScale9Enabled()const;

    /**
     * Sets capInsets for imageview.
     * The capInsets affects the ImageView's renderer only if `setScale9Enabled(true)` is called.
     *
     * @param capInsets    capinsets for imageview
     */
    void setCapInsets(const Rect &capInsets);

    /**
     * Get ImageView's capInsets size.
     * @return Query capInsets size in Rect
     * @see `setCapInsets(const Rect&)`
     */
    const Rect& getCapInsets()const;

    //override methods.
    virtual void ignoreContentAdaptWithSize(bool ignore) override;
    virtual std::string getDescription() const override;
    virtual Size getVirtualRendererSize() const override;
    virtual Node* getVirtualRenderer() override;
    
	void setAutoTouchChangeRenderer(bool bAuto = true){ m_bAutoTouchChangeRenderer = bAuto; }	// 设置按下自动高亮显示
	void setAutoTouchAction(AUTO_TOUCH_ACTION eAuto = AUTO_TOUCH_ACTION_scale_small){ m_eAutoTouchAction = eAuto; }				// 设置按下自动缩放动画
	void setLongPressed(ccWidgetClickCallback callback, ccWidgetClickCallback callbackCancel = nullptr, int nLoopClickMs = 0);	// 设置长按回调
	void setPressing(ccWidgetClickCallback callback, ccWidgetClickCallback callbackCancel = nullptr, int nWaitPressingMs = 0);	// 设置按住回调

public:
	virtual cocos2d::MY_SHADER_EFFECT getShaderEffect() const;
	virtual void setShaderEffect(cocos2d::MY_SHADER_EFFECT eShaderEffect);
CC_CONSTRUCTOR_ACCESS:
    //initializes state of widget.
    virtual bool init() override;
    virtual bool init(const std::string& imageFileName, TextureResType texType = TextureResType::LOCAL);

protected:
    virtual void initRenderer() override;
    virtual void onSizeChanged() override;
    
    virtual void adaptRenderers() override;
    void loadTexture(SpriteFrame* spriteframe);
    void setupTexture();
    
	virtual void onPressStateChangedToNormal() override;
	virtual void onPressStateChangedToPressed() override;
	virtual void onPressStateChangedToDisabled() override;
    
    void imageTextureScaleChangedWithSize();
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
	virtual void onTimerLongPressed(float dt);
	virtual void onTimerLongPressedLoop(float dt);
	virtual void onTimerPressing(float dt);
	virtual int64_t getUtcMillisecond(void);

protected:
    bool _scale9Enabled;
    bool _prevIgnoreSize;
    Rect _capInsets;
    Scale9Sprite* _imageRenderer;
    TextureResType _imageTexType;
    Size _imageTextureSize;
    bool _imageRendererAdaptDirty;
	bool m_bAutoTouchChangeRenderer;
	cocos2d::MY_SHADER_EFFECT m_eSaveShaderEffect;
	AUTO_TOUCH_ACTION m_eAutoTouchAction;
	ccWidgetClickCallback	m_callbackLongPressed;
	ccWidgetClickCallback	m_callbackLongPressedCancel;
	bool					m_bLoopPressing;
	int						m_nLongPressLoopMs;
	int64_t					m_i64PressedBegin;

	ccWidgetClickCallback	m_callbackPressing;
	ccWidgetClickCallback	m_callbackPressingCancel;
	int64_t					m_i64PressingBegin;
	int64_t					m_i64WaitPressingMs;
};

}

NS_CC_END
// end of ui group
/// @}

#endif /* defined(__CocoGUI__ImageView__) */
