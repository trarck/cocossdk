#include "TestUserScene.h"
#include "AgentManager.h"
#include "TestOpenSdkScene.h"

USING_NS_CC;
using namespace opensdk;

void UserActionResult::onActionResult(ProtocolUser* pPlugin, UserActionResultCode code, const char* msg)
{
	CCLOG("result:%d,msg:%s",code,msg);
}

TestUserScene::~TestUserScene()
{
	delete _actionListener;
}

CCScene* TestUserScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TestUserScene *layer = TestUserScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestUserScene::init()
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
									menu_selector(TestUserScene::menuBackCallback));
    
	pItemBack->setPosition(ccp(origin.x + visibleSize.width - pItemBack->getContentSize().width/2 ,
                                origin.y + pItemBack->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pItemBack, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);


	
	CCMenuItemLabel* pItem1=CCMenuItemLabel::create(
									CCLabelTTF::create("login", "Arial", 32),
									this,
									menu_selector(TestUserScene::testLogin));
									
	CCMenuItemLabel* pItem2=CCMenuItemLabel::create(
										CCLabelTTF::create("logout", "Arial", 32),
										this,
										menu_selector(TestUserScene::testLogout));
										
	CCMenuItemLabel* pItem3=CCMenuItemLabel::create(
									CCLabelTTF::create("showBar", "Arial", 32),
									this,
									menu_selector(TestUserScene::testShowToolBar));

	CCMenuItemLabel* pItem4=CCMenuItemLabel::create(
										CCLabelTTF::create("hideBar", "Arial", 32),
										this,
										menu_selector(TestUserScene::testHideToolBar));
										
	
																					
    CCMenu* pMenuAction = CCMenu::create(pItem1,pItem2,pItem3,pItem4,NULL);
    pMenuAction->setPosition(ccp(origin.x + visibleSize.width/2,100));
	pMenuAction->alignItemsHorizontallyWithPadding(8);
    this->addChild(pMenuAction, 2);
	
	
	_actionListener=new UserActionResult();
	AgentManager::getInstance()->getUserPlugin()->setActionListener(_actionListener);
	
    return true;
}


void TestUserScene::menuBackCallback(CCObject* pSender)
{
    CCScene *pScene = TestOpenSdkScene::scene();

    CCDirector::sharedDirector()->replaceScene(pScene);
}

void TestUserScene::testLogin(CCObject* pSender)
{
	AgentManager::getInstance()->getUserPlugin()->login();
}

void TestUserScene::testLogout(CCObject* pSender)
{
	AgentManager::getInstance()->getUserPlugin()->logout();
}

void TestUserScene::testShowToolBar(CCObject* pSender)
{
	PluginParam intParam(1);
	AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("showToolBar",&intParam,NULL);
}

void TestUserScene::testHideToolBar(CCObject* pSender)
{
	AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("hideToolBar",NULL);
}
