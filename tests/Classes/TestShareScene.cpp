#include "TestShareScene.h"
#include "AgentManager.h"
#include "TestOpenSdkScene.h"

USING_NS_CC;
using namespace opensdk;

void ShareActionResult::onShareResult(opensdk::ShareResultCode ret, const char* msg)
{
	CCLOG("result:%d,msg:%s",ret,msg);
}

TestShareScene::~TestShareScene()
{
	delete _actionListener;
}

CCScene* TestShareScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TestShareScene *layer = TestShareScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestShareScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCMenuItemLabel* pItemBack=CCMenuItemLabel::create(
									CCLabelTTF::create("back", "Arial", 32),
									this,
									menu_selector(TestShareScene::menuBackCallback));
    
	pItemBack->setPosition(ccp(origin.x + visibleSize.width - pItemBack->getContentSize().width/2 ,
                                origin.y + pItemBack->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pItemBack, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);


	
	CCMenuItemLabel* pItem1=CCMenuItemLabel::create(
									CCLabelTTF::create("share", "Arial", 32),
									this,
									menu_selector(TestShareScene::testShare));
																					
    CCMenu* pMenuAction = CCMenu::create(pItem1,NULL);
    pMenuAction->setPosition(ccp(origin.x + visibleSize.width/2,100));
	pMenuAction->alignItemsHorizontallyWithPadding(8);
    this->addChild(pMenuAction, 2);
	
	
	_actionListener=new ShareActionResult();
	CCLOG("share init before");
	
	AgentManager::getInstance()->getSharePlugin()->setResultListener(_actionListener);
	CCLOG("share init after");
    return true;
}


void TestShareScene::menuBackCallback(CCObject* pSender)
{
    CCScene *pScene = TestOpenSdkScene::scene();

    CCDirector::sharedDirector()->replaceScene(pScene);
}

void TestShareScene::testShare(CCObject* pSender)
{
	TShareInfo info;
	info["id"]="1000";
	info["SharedText"]="test content";
	AgentManager::getInstance()->getSharePlugin()->share(info);
}
