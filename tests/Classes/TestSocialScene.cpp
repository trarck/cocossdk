#include "TestSocialScene.h"
#include "AgentManager.h"
#include "TestOpenSdkScene.h"

USING_NS_CC;
using namespace opensdk;

void SocialActionResult::onSocialResult(opensdk::SocialRetCode code, const char* msg)
{
	CCLOG("result:%d,msg:%s",code,msg);
}


TestSocialScene::~TestSocialScene()
{
	delete _actionListener;
}

CCScene* TestSocialScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TestSocialScene *layer = TestSocialScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestSocialScene::init()
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
									menu_selector(TestSocialScene::menuBackCallback));
    
	pItemBack->setPosition(ccp(origin.x + visibleSize.width - pItemBack->getContentSize().width/2 ,
                                origin.y + pItemBack->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pItemBack, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);


	
	CCMenuItemLabel* pItem1=CCMenuItemLabel::create(
									CCLabelTTF::create("signIn", "Arial", 32),
									this,
									menu_selector(TestSocialScene::testSignInt));
									
	CCMenuItemLabel* pItem2=CCMenuItemLabel::create(
									CCLabelTTF::create("signOut", "Arial", 32),
									this,
									menu_selector(TestSocialScene::testSignOut));
																	
	CCMenuItemLabel* pItem3=CCMenuItemLabel::create(
									CCLabelTTF::create("submit", "Arial", 32),
									this,
									menu_selector(TestSocialScene::testSubmitScore));
																					
    CCMenu* pMenuAction = CCMenu::create(pItem1,NULL);
    pMenuAction->setPosition(ccp(origin.x + visibleSize.width/2,100));
	pMenuAction->alignItemsHorizontallyWithPadding(8);
    this->addChild(pMenuAction, 2);
	
	
	_actionListener=new SocialActionResult();
	
	
	AgentManager::getInstance()->getSocialPlugin()->setListener(_actionListener);
	
    return true;
}


void TestSocialScene::menuBackCallback(CCObject* pSender)
{
    CCScene *pScene = TestOpenSdkScene::scene();

    CCDirector::sharedDirector()->replaceScene(pScene);
}

void TestSocialScene::testSignInt(CCObject* pSender)
{
	AgentManager::getInstance()->getSocialPlugin()->signIn();
}

void TestSocialScene::testSignOut(CCObject* pSender)
{
	AgentManager::getInstance()->getSocialPlugin()->signOut();
}

void TestSocialScene::testSubmitScore(CCObject* pSender)
{
	AgentManager::getInstance()->getSocialPlugin()->submitScore("top",100);
}
