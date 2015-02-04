#ifndef __TESTADSSCENE_SCENE_H__
#define __TESTADSSCENE_SCENE_H__

#include "cocos2d.h"
#include "ProtocolAds.h"

class AdsActionResult : public opensdk::AdsListener
{
public:
	void onAdsResult(opensdk::AdsResultCode code, const char* msg);
	
	void onPlayerGetPoints(opensdk::ProtocolAds* pAdsPlugin, int points);
};

class TestAdsScene : public cocos2d::CCLayer
{
public:
	virtual ~TestAdsScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuBackCallback(CCObject* pSender);
	
	void testShowAds(CCObject* pSender);
	void testHideAds(CCObject* pSender);
	void testPreloadAds(CCObject* pSender);
	void testQueryPoints(CCObject* pSender);
	void testSpendPoints(CCObject* pSender);
	void testIsAdTypeSupported(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(TestAdsScene);
private:
	AdsActionResult* _actionListener;
};

#endif // __TESTADSSCENE_SCENE_H__
