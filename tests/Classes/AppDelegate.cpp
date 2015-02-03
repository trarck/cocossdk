#include "AppDelegate.h"
#include "TestOpenSdkScene.h"
#include "AgentManager.h"

USING_NS_CC;
using namespace opensdk;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
	CCLOG("destroy AgentManager instance");
	AgentManager::getInstance()->destroyInstance();
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);


	CCLOG("begin init plugin ");
    AgentManager::getInstance()->init("1111-1111-1111-1111","acdbcedba32442dcbfe","384defa7b09c893d4e","");
	CCLOG("end init plugin ");
	CCLOG("begin load all plugin");
    AgentManager::getInstance()->loadAllPlugin();
	
	CCLOG("end load all plugin ");
	
    // create a scene. it's an autorelease object
    CCScene *pScene = TestOpenSdkScene::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
