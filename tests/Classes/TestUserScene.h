#ifndef __TESTUSERSCENE_SCENE_H__
#define __TESTUSERSCENE_SCENE_H__

#include "cocos2d.h"
#include "ProtocolUser.h"

class UserActionResult : public opensdk::UserActionListener
{
public:
	void onActionResult(opensdk::ProtocolUser* pPlugin, opensdk::UserActionResultCode code, const char* msg);
};

class TestUserScene : public cocos2d::CCLayer
{
public:
	virtual ~TestUserScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuBackCallback(CCObject* pSender);
	
	void testLogin(CCObject* pSender);
	void testLogout(CCObject* pSender);
	void testShowToolBar(CCObject* pSender);
	void testHideToolBar(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(TestUserScene);
private:
	UserActionResult* _actionListener;
};

#endif // __TESTUSERSCENE_SCENE_H__
