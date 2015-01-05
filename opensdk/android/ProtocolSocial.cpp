#include "ProtocolSocial.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtilsAndroid.h"
#include "PluginJavaData.h"

namespace opensdk {


ProtocolSocial::ProtocolSocial()
: _listener(NULL)
{
}

ProtocolSocial::~ProtocolSocial()
{
}

void ProtocolSocial::configDeveloperInfo(TSocialDeveloperInfo devInfo)
{
    if (devInfo.empty())
    {
        PluginUtilsAndroid::outputLog("ProtocolSocial", "The developer info is empty!");
        return;
    }
    else
    {
        PluginUtilsAndroid::callJavaFunctionWithName_map(this, "configDeveloperInfo", &devInfo);
    }
}

void ProtocolSocial::submitScore(const char* leadboardID, long score)
{
    PluginJavaData* pData = PluginUtilsAndroid::getPluginJavaData(this);
    PluginJniMethodInfo t;
    if (PluginJniHelper::getMethodInfo(t
        , pData->jclassName.c_str()
        , "submitScore"
        , "(Ljava/lang/String;J)V"))
    {
        jstring strID = PluginUtilsAndroid::getEnv()->NewStringUTF(leadboardID);

        // invoke java method
        t.env->CallVoidMethod(pData->jobj, t.methodID, strID, score);
        t.env->DeleteLocalRef(strID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void ProtocolSocial::showLeaderboard(const char* leaderboardID)
{
    PluginUtilsAndroid::callJavaFunctionWithName_oneParam(this, "showLeaderboard", "(Ljava/lang/String;)V", leaderboardID);
//    
//    PluginJavaData* pData = PluginUtilsAndroid::getPluginJavaData(this);
//    PluginJniMethodInfo t;
//    if (PluginJniHelper::getMethodInfo(t
//        , pData->jclassName.c_str()
//        , "showLeaderboard"
//        , "(Ljava/lang/String;)V"))
//    {
//        jstring strID = PluginUtilsAndroid::getEnv()->NewStringUTF(leaderboardID);
//
//        // invoke java method
//        t.env->CallVoidMethod(pData->jobj, t.methodID, strID);
//        t.env->DeleteLocalRef(strID);
//        t.env->DeleteLocalRef(t.classID);
//    }
}

void ProtocolSocial::unlockAchievement(TAchievementInfo achInfo)
{
    if (achInfo.empty())
    {
        PluginUtilsAndroid::outputLog("ProtocolSocial", "The achievement info is empty!");
        return;
    }
    else
    {
        PluginUtilsAndroid::callJavaFunctionWithName_map(this, "unlockAchievement", &achInfo);
    }
}

void ProtocolSocial::showAchievements()
{
    PluginUtilsAndroid::callJavaFunctionWithName(this, "showAchievements");
}

} // namespace opensdk {
