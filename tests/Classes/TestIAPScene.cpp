#include "TestIAPScene.h"
#include "AgentManager.h"
#include "TestOpenSdkScene.h"

USING_NS_CC;
using namespace opensdk;

void PayActionResult::onPayResult(opensdk::PayResultCode ret, const char* msg, opensdk::TProductInfo info)
{
	CCLOG("result:%d,msg:%s",ret,msg);
}

TestIAPScene::~TestIAPScene()
{
	delete _actionListener;
}

CCScene* TestIAPScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TestIAPScene *layer = TestIAPScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestIAPScene::init()
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
									menu_selector(TestIAPScene::menuBackCallback));
    
	pItemBack->setPosition(ccp(origin.x + visibleSize.width - pItemBack->getContentSize().width/2 ,
                                origin.y + pItemBack->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pItemBack, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);


	
	CCMenuItemLabel* pItem1=CCMenuItemLabel::create(
									CCLabelTTF::create("pay", "Arial", 32),
									this,
									menu_selector(TestIAPScene::testPayForProduct));
									
	CCMenuItemLabel* pItem2=CCMenuItemLabel::create(
										CCLabelTTF::create("order", "Arial", 32),
										this,
										menu_selector(TestIAPScene::testGetOrderId));
										
	CCMenuItemLabel* pItem3=CCMenuItemLabel::create(
									CCLabelTTF::create("pluginid", "Arial", 32),
									this,
									menu_selector(TestIAPScene::testGetPluginId));
										
	
																					
    CCMenu* pMenuAction = CCMenu::create(pItem1,pItem2,pItem3,NULL);
    pMenuAction->setPosition(ccp(origin.x + visibleSize.width/2,100));
	pMenuAction->alignItemsHorizontallyWithPadding(8);
    this->addChild(pMenuAction, 2);
	
	
	_actionListener=new PayActionResult();
	
	
	AgentManager::getInstance()->getIAPPlugin()->at("IAPDebug")->setResultListener(_actionListener);
	
    return true;
}


void TestIAPScene::menuBackCallback(CCObject* pSender)
{
    CCScene *pScene = TestOpenSdkScene::scene();

    CCDirector::sharedDirector()->replaceScene(pScene);
}

void TestIAPScene::testPayForProduct(CCObject* pSender)
{
	TProductInfo info;
	info["Product_Id"]="1000";
	info["Product_Name"]="test";
	info["Product_Price"]="10.0";
	info["Product_Count"]="1";
	info["Role_Id"]="1";
	info["Role_Name"]="abc";
	info["Server_Id"]="1001";
	
	AgentManager::getInstance()->getIAPPlugin()->at("IAPDebug")->payForProduct(info);
}

void TestIAPScene::testGetOrderId(CCObject* pSender)
{
	std::string orderId=AgentManager::getInstance()->getIAPPlugin()->at("IAPDebug")->getOrderId();
	CCLOG("orderId=%s",orderId.c_str());
}

void TestIAPScene::testGetPluginId(CCObject* pSender)
{
	std::string pid=AgentManager::getInstance()->getIAPPlugin()->at("IAPDebug")->getPluginId();
	CCLOG("pluginId=%s",pid.c_str());
}