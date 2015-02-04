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
    AgentManager::getInstance()->init("E366F9F3-570E-4F9E-0B42-57A868DC4EC7","69ab62a83a3edf48ac85ee5977ee1656","9BE2243B53F070D00AA4B40B3F4CE558","http://oauth.anysdk.com/api/OauthLoginDemo/Login.php");
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
