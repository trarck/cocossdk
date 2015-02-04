#ifndef __TESTIAPSCENE_SCENE_H__
#define __TESTIAPSCENE_SCENE_H__

#include "cocos2d.h"
#include "ProtocolIAP.h"

class PayActionResult : public opensdk::PayResultListener
{
public:
	void onPayResult(opensdk::PayResultCode ret, const char* msg, opensdk::TProductInfo info);
};

class TestIAPScene : public cocos2d::CCLayer
{
public:
	virtual ~TestIAPScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuBackCallback(CCObject* pSender);
	
	void testPayForProduct(CCObject* pSender);
	void testGetOrderId(CCObject* pSender);
	void testGetPluginId(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(TestIAPScene);
private:
	PayActionResult* _actionListener;
};

#endif // __TESTIAPSCENE_SCENE_H__
