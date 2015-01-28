#include "SocialObject.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtils.h"
#include "PluginJavaData.h"

namespace opensdk {


SocialObject::SocialObject()
: _listener(NULL)
, _pluginName("")
{
}

SocialObject::~SocialObject()
{
    
}
    
void SocialObject::setPluginName(const char* name)
{
    _pluginName = name;
}

const char* SocialObject::getPluginName()
{
    return _pluginName.c_str();
}

void SocialObject::configDeveloperInfo(TSocialDeveloperInfo devInfo)
{
    if (devInfo.empty())
    {
        PluginUtils::outputLog("SocialObject", "The developer info is empty!");
        return;
    }
    else
    {
        PluginUtils::callJavaFunctionWithName_map(this, "configDeveloperInfo", &devInfo);
    }
}
    
void SocialObject::signIn()
{
    PluginUtils::callJavaFunctionWithName(this, "signIn");
}
    
void SocialObject::signOut()
{
    PluginUtils::callJavaFunctionWithName(this, "signOut");
}

void SocialObject::submitScore(const char* leadboardID, long score)
{
    PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
    PluginJniMethodInfo t;
    if (PluginJniHelper::getMethodInfo(t
        , pData->jclassName.c_str()
        , "submitScore"
        , "(Ljava/lang/String;J)V"))
    {
        jstring strID = PluginUtils::getEnv()->NewStringUTF(leadboardID);

        // invoke java method
        t.env->CallVoidMethod(pData->jobj, t.methodID, strID, score);
        t.env->DeleteLocalRef(strID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void SocialObject::showLeaderboard(const char* leaderboardID)
{
    jstring jstr = PluginUtils::getEnv()->NewStringUTF(leaderboardID);
    PluginUtils::callJavaFunctionWithName_oneParam(this, "showLeaderboard", "(Ljava/lang/String;)V", jstr);
    PluginUtils::getEnv()->DeleteLocalRef(jstr);
    
//    
//    PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
//    PluginJniMethodInfo t;
//    if (PluginJniHelper::getMethodInfo(t
//        , pData->jclassName.c_str()
//        , "showLeaderboard"
//        , "(Ljava/lang/String;)V"))
//    {
//        jstring strID = PluginUtils::getEnv()->NewStringUTF(leaderboardID);
//
//        // invoke java method
//        t.env->CallVoidMethod(pData->jobj, t.methodID, strID);
//        t.env->DeleteLocalRef(strID);
//        t.env->DeleteLocalRef(t.classID);
//    }
}

void SocialObject::unlockAchievement(TAchievementInfo achInfo)
{
    if (achInfo.empty())
    {
        PluginUtils::outputLog("SocialObject", "The achievement info is empty!");
        return;
    }
    else
    {
        PluginUtils::callJavaFunctionWithName_map(this, "unlockAchievement", &achInfo);
    }
}

void SocialObject::showAchievements()
{
    PluginUtils::callJavaFunctionWithName(this, "showAchievements");
}
    
void SocialObject::setListener(SocialListener* listener) {
    _listener = listener;
}
    
SocialListener* SocialObject::getListener()
{
    return _listener;
}



} // namespace opensdk {
