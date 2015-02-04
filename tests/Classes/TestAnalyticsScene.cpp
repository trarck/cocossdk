#include "TestAnalyticsScene.h"
#include "AgentManager.h"
#include "TestOpenSdkScene.h"

USING_NS_CC;
using namespace opensdk;


TestAnalyticsScene::~TestAnalyticsScene()
{
	
}

CCScene* TestAnalyticsScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TestAnalyticsScene *layer = TestAnalyticsScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestAnalyticsScene::init()
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
									menu_selector(TestAnalyticsScene::menuBackCallback));
    
	pItemBack->setPosition(ccp(origin.x + visibleSize.width - pItemBack->getContentSize().width/2 ,
                                origin.y + pItemBack->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pItemBack, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);


	
	CCMenuItemLabel* pItem1=CCMenuItemLabel::create(
									CCLabelTTF::create("start", "Arial", 32),
									this,
									menu_selector(TestAnalyticsScene::testStart));
																					
    CCMenu* pMenuAction = CCMenu::create(pItem1,NULL);
    pMenuAction->setPosition(ccp(origin.x + visibleSize.width/2,100));
	pMenuAction->alignItemsHorizontallyWithPadding(8);
    this->addChild(pMenuAction, 2);
	

	
    return true;
}


void TestAnalyticsScene::menuBackCallback(CCObject* pSender)
{
    CCScene *pScene = TestOpenSdkScene::scene();

    CCDirector::sharedDirector()->replaceScene(pScene);
}

void TestAnalyticsScene::testStart(CCObject* pSender)
{
	AgentManager::getInstance()->getAnalyticsPlugin()->startSession();
}
