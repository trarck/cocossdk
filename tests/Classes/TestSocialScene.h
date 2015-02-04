#ifndef __TESTSOCAILSCENE_SCENE_H__
#define __TESTSOCAILSCENE_SCENE_H__

#include "cocos2d.h"
#include "ProtocolSocial.h"

class SocialActionResult : public opensdk::SocialListener
{
public:
	void onSocialResult(opensdk::SocialRetCode code, const char* msg);
};

class TestSocialScene : public cocos2d::CCLayer
{
public:
	virtual ~TestSocialScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuBackCallback(CCObject* pSender);
	
	void testSignInt(CCObject* pSender);
	void testSignOut(CCObject* pSender);
	void testSubmitScore(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(TestSocialScene);
private:
	SocialActionResult* _actionListener;
};

#endif // __TESTSOCAILSCENE_SCENE_H__
