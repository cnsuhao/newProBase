#include "AppDelegate.h"
#include "Audio/Audio.h"
#include "SceneMain/SceneMain.h"
#include "SceneBattle/SceneBattle.h"
#include "SceneLogin/SceneLogin.h"
#include "Root.h"


USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
	Root::getInstance()->release();
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if(!glview) 
	{
		glview = GLViewImpl::createWithRect("WeaponGirl", Rect(0, 0, APP_DESIGN_WIDTH, APP_DESIGN_HEIGHT), 0.5f);
		director->setOpenGLView(glview);
	}
#else
	if(!glview) 
	{
		glview = GLViewImpl::create("GoodGame");
		director->setOpenGLView(glview);
	}
#endif // CC_PLATFORM_WIN32

	// 设计尺寸与对其方式
	glview->setDesignResolutionSize(APP_DESIGN_WIDTH, APP_DESIGN_HEIGHT, ResolutionPolicy::EXACT_FIT);

	// turn on display FPS
#ifdef COCOS2D_DEBUG
	director->setDisplayStats(true);
#endif

    // set FPS. the default value is 1.0/30 if you don't call this
    director->setAnimationInterval(1.0f / 30);

	CHECKF(Root::getInstance()->init());

    // create a scene. it's an autorelease object
    auto scene = SceneLogin::create();
	director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
