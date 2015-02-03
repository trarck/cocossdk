#include "TestOpenSdkScene.h"
#include "TestUserScene.h"

USING_NS_CC;

TestOpenSdkScene::~TestOpenSdkScene()
{
	
}

CCScene* TestOpenSdkScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TestOpenSdkScene *layer = TestOpenSdkScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestOpenSdkScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(TestOpenSdkScene::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
	
	CCMenuItemLabel* pItemUser=CCMenuItemLabel::create(
									CCLabelTTF::create("user", "Arial", 32),
									this,
									menu_selector(TestOpenSdkScene::testUser));
									
	CCMenuItemLabel* pItemIAP=CCMenuItemLabel::create(
										CCLabelTTF::create("iap", "Arial", 32),
										this,
										menu_selector(TestOpenSdkScene::testIAP));
										
	CCMenuItemLabel* pItemAds=CCMenuItemLabel::create(
									CCLabelTTF::create("ads", "Arial", 32),
									this,
									menu_selector(TestOpenSdkScene::testAds));

	CCMenuItemLabel* pItemAnalytics=CCMenuItemLabel::create(
										CCLabelTTF::create("analytics", "Arial", 32),
										this,
										menu_selector(TestOpenSdkScene::testAnalytics));
										
										
	CCMenuItemLabel* pItemSocial=CCMenuItemLabel::create(
									CCLabelTTF::create("social", "Arial", 32),
									this,
									menu_selector(TestOpenSdkScene::testSocial));

	CCMenuItemLabel* pItemShare=CCMenuItemLabel::create(
										CCLabelTTF::create("share", "Arial", 32),
										this,
										menu_selector(TestOpenSdkScene::testShare));
										
	CCMenuItemLabel* pItemPush=CCMenuItemLabel::create(
									CCLabelTTF::create("push", "Arial", 32),
									this,
									menu_selector(TestOpenSdkScene::testPush));

																					
    CCMenu* pMenuAction = CCMenu::create(pItemUser,pItemIAP,pItemAds,pItemAnalytics, pItemSocial,pItemShare,pItemPush,NULL);
    pMenuAction->setPosition(ccp(origin.x + visibleSize.width/2,100));
	pMenuAction->alignItemsHorizontallyWithPadding(8);
    this->addChild(pMenuAction, 2);
	
    return true;
}


void TestOpenSdkScene::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void TestOpenSdkScene::testUser(CCObject* pSender)
{
    CCScene *pScene = TestUserScene::scene();

    CCDirector::sharedDirector()->replaceScene(pScene);
}

void TestOpenSdkScene::testIAP(CCObject* pSender)
{
	
}

void TestOpenSdkScene::testAds(CCObject* pSender)
{
	
}

void TestOpenSdkScene::testAnalytics(CCObject* pSender)
{
	
}

void TestOpenSdkScene::testSocial(CCObject* pSender)
{
	
}

void TestOpenSdkScene::testShare(CCObject* pSender)
{
	
}

void TestOpenSdkScene::testPush(CCObject* pSender)
{
	
}
