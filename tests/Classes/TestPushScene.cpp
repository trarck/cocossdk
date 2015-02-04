#include "TestPushScene.h"
#include "AgentManager.h"
#include "TestOpenSdkScene.h"

USING_NS_CC;
using namespace opensdk;

void PushActionResult::onActionResult(opensdk::ProtocolPush* pPlugin, opensdk::PushActionResultCode code, const char* msg)
{
	CCLOG("result:%d,msg:%s",code,msg);
}

TestPushScene::~TestPushScene()
{
	delete _actionListener;
}

CCScene* TestPushScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TestPushScene *layer = TestPushScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestPushScene::init()
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
									menu_selector(TestPushScene::menuBackCallback));
    
	pItemBack->setPosition(ccp(origin.x + visibleSize.width - pItemBack->getContentSize().width/2 ,
                                origin.y + pItemBack->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pItemBack, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);


	
	CCMenuItemLabel* pItem1=CCMenuItemLabel::create(
									CCLabelTTF::create("start", "Arial", 32),
									this,
									menu_selector(TestPushScene::testStartPush));
									
	CCMenuItemLabel* pItem2=CCMenuItemLabel::create(
									CCLabelTTF::create("close", "Arial", 32),
									this,
									menu_selector(TestPushScene::testClosePush));
									
	CCMenuItemLabel* pItem3=CCMenuItemLabel::create(
									CCLabelTTF::create("set", "Arial", 32),
									this,
									menu_selector(TestPushScene::testSetAlias));
	
	CCMenuItemLabel* pItem4=CCMenuItemLabel::create(
									CCLabelTTF::create("del", "Arial", 32),
									this,
									menu_selector(TestPushScene::testDelAlias));
																					
    CCMenu* pMenuAction = CCMenu::create(pItem1,pItem2,pItem3,pItem4,NULL);
    pMenuAction->setPosition(ccp(origin.x + visibleSize.width/2,100));
	pMenuAction->alignItemsHorizontallyWithPadding(8);
    this->addChild(pMenuAction, 2);
	
	
	_actionListener=new PushActionResult();
	
	
	AgentManager::getInstance()->getPushPlugin()->setActionListener(_actionListener);
	
    return true;
}


void TestPushScene::menuBackCallback(CCObject* pSender)
{
    CCScene *pScene = TestOpenSdkScene::scene();

    CCDirector::sharedDirector()->replaceScene(pScene);
}

void TestPushScene::testStartPush(CCObject* pSender)
{
	AgentManager::getInstance()->getPushPlugin()->startPush();
}

void TestPushScene::testClosePush(CCObject* pSender)
{
	AgentManager::getInstance()->getPushPlugin()->closePush();
}

void TestPushScene::testSetAlias(CCObject* pSender)
{
	AgentManager::getInstance()->getPushPlugin()->setAlias("test");
}

void TestPushScene::testDelAlias(CCObject* pSender)
{
	AgentManager::getInstance()->getPushPlugin()->delAlias("test");
}
