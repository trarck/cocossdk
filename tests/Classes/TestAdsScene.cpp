#include "TestAdsScene.h"
#include "AgentManager.h"
#include "TestOpenSdkScene.h"

USING_NS_CC;
using namespace opensdk;

void AdsActionResult::onAdsResult(opensdk::AdsResultCode code, const char* msg)
{
	CCLOG("result:%d,msg:%s",code,msg);
}

void AdsActionResult:: onPlayerGetPoints(opensdk::ProtocolAds* pAdsPlugin, int points)
{
	CCLOG("get points:%d",points);
}


TestAdsScene::~TestAdsScene()
{
	delete _actionListener;
}

CCScene* TestAdsScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TestAdsScene *layer = TestAdsScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestAdsScene::init()
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
									menu_selector(TestAdsScene::menuBackCallback));
    
	pItemBack->setPosition(ccp(origin.x + visibleSize.width - pItemBack->getContentSize().width/2 ,
                                origin.y + pItemBack->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pItemBack, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);


	
	CCMenuItemLabel* pItem1=CCMenuItemLabel::create(
									CCLabelTTF::create("show", "Arial", 32),
									this,
									menu_selector(TestAdsScene::testShowAds));
									
	CCMenuItemLabel* pItem2=CCMenuItemLabel::create(
										CCLabelTTF::create("hide", "Arial", 32),
										this,
										menu_selector(TestAdsScene::testHideAds));
										
	CCMenuItemLabel* pItem3=CCMenuItemLabel::create(
									CCLabelTTF::create("preload", "Arial", 32),
									this,
									menu_selector(TestAdsScene::testPreloadAds));
										
	CCMenuItemLabel* pItem4=CCMenuItemLabel::create(
									CCLabelTTF::create("query", "Arial", 32),
									this,
									menu_selector(TestAdsScene::testQueryPoints));
	
	CCMenuItemLabel* pItem5=CCMenuItemLabel::create(
										CCLabelTTF::create("send", "Arial", 32),
										this,
										menu_selector(TestAdsScene::testSpendPoints));
		
	CCMenuItemLabel* pItem6=CCMenuItemLabel::create(
									CCLabelTTF::create("isSupport", "Arial", 32),
									this,
									menu_selector(TestAdsScene::testIsAdTypeSupported));
																					
    CCMenu* pMenuAction = CCMenu::create(pItem1,pItem2,pItem3,pItem4,pItem5,pItem6,NULL);
    pMenuAction->setPosition(ccp(origin.x + visibleSize.width/2,100));
	pMenuAction->alignItemsHorizontallyWithPadding(8);
    this->addChild(pMenuAction, 2);
	
	
	_actionListener=new AdsActionResult();
	
	
	AgentManager::getInstance()->getAdsPlugin()->setAdsListener(_actionListener);
	
    return true;
}


void TestAdsScene::menuBackCallback(CCObject* pSender)
{
    CCScene *pScene = TestOpenSdkScene::scene();

    CCDirector::sharedDirector()->replaceScene(pScene);
}

void TestAdsScene::testShowAds(CCObject* pSender)
{
	AgentManager::getInstance()->getAdsPlugin()->showAds(AD_TYPE_BANNER);
}

void TestAdsScene::testHideAds(CCObject* pSender)
{
	AgentManager::getInstance()->getAdsPlugin()->hideAds(AD_TYPE_BANNER);
}

void TestAdsScene::testPreloadAds(CCObject* pSender)
{
	AgentManager::getInstance()->getAdsPlugin()->preloadAds(AD_TYPE_BANNER);
}

void TestAdsScene::testQueryPoints(CCObject* pSender)
{
	float points=AgentManager::getInstance()->getAdsPlugin()->queryPoints();
	CCLOG("points=%f",points);
}

void TestAdsScene::testSpendPoints(CCObject* pSender)
{
	AgentManager::getInstance()->getAdsPlugin()->spendPoints(10);
}

void TestAdsScene::testIsAdTypeSupported(CCObject* pSender)
{
	AgentManager::getInstance()->getAdsPlugin()->isAdTypeSupported(AD_TYPE_BANNER);
}