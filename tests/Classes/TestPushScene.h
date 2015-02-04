#ifndef __TESTPUSHSCENE_SCENE_H__
#define __TESTPUSHSCENE_SCENE_H__

#include "cocos2d.h"
#include "ProtocolPush.h"

class PushActionResult : public opensdk::PushActionListener
{
public:
	void onActionResult(opensdk::ProtocolPush* pPlugin, opensdk::PushActionResultCode code, const char* msg);
};

class TestPushScene : public cocos2d::CCLayer
{
public:
	virtual ~TestPushScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuBackCallback(CCObject* pSender);
	
	void testStartPush(CCObject* pSender);
	void testClosePush(CCObject* pSender);
	void testSetAlias(CCObject* pSender);
	void testDelAlias(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(TestPushScene);
private:
	PushActionResult* _actionListener;
};

#endif // __TESTPUSHSCENE_SCENE_H__
