#ifndef __TESTSHARESCENE_SCENE_H__
#define __TESTSHARESCENE_SCENE_H__

#include "cocos2d.h"
#include "ProtocolShare.h"

class ShareActionResult : public opensdk::ShareResultListener
{
public:
	void onShareResult(opensdk::ShareResultCode ret, const char* msg);
};

class TestShareScene : public cocos2d::CCLayer
{
public:
	virtual ~TestShareScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuBackCallback(CCObject* pSender);
	
	void testShare(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(TestShareScene);
private:
	ShareActionResult* _actionListener;
};

#endif // __TESTSHARESCENE_SCENE_H__
