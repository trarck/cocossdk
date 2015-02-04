#ifndef __TESTANALYTICSSCENE_SCENE_H__
#define __TESTANALYTICSSCENE_SCENE_H__

#include "cocos2d.h"
#include "ProtocolAnalytics.h"


class TestAnalyticsScene : public cocos2d::CCLayer
{
public:
	virtual ~TestAnalyticsScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuBackCallback(CCObject* pSender);
	
	void testStart(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(TestAnalyticsScene);
};

#endif // __TESTANALYTICSSCENE_SCENE_H__
