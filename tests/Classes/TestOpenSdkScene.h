#ifndef __TESTOPENSDKSCENE_SCENE_H__
#define __TESTOPENSDKSCENE_SCENE_H__

#include "cocos2d.h"

class TestOpenSdkScene : public cocos2d::CCLayer
{
public:
	virtual ~TestOpenSdkScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
	
	void testUser(CCObject* pSender);
	void testIAP(CCObject* pSender);
	void testAds(CCObject* pSender);
	void testAnalytics(CCObject* pSender);
	void testSocial(CCObject* pSender);
	void testShare(CCObject* pSender);
	void testPush(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(TestOpenSdkScene);
};

#endif // __TESTOPENSDKSCENE_SCENE_H__
