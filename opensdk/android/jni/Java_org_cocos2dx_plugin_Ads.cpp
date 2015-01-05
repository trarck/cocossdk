#include "ProtocolAds.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtilsAndroid.h"
#include <jni.h>

using namespace opensdk;

extern "C" {
    JNIEXPORT void JNICALL Java_org_cocos2dx_plugin_AdsWrapper_nativeOnAdsResult(JNIEnv*  env, jobject thiz, jstring className, jint ret, jstring msg) {
        std::string strMsg = PluginJniHelper::jstring2string(msg);
        std::string strClassName = PluginJniHelper::jstring2string(className);
        PluginProtocol* pPlugin = PluginUtilsAndroid::getPluginPtr(strClassName);
        PluginUtilsAndroid::outputLog("ProtocolAds", "nativeOnAdsResult(), Get plugin ptr : %p", pPlugin);
        if (pPlugin != NULL)
        {
            PluginUtilsAndroid::outputLog("ProtocolAds", "nativeOnAdsResult(), Get plugin name : %s", pPlugin->getPluginName());
            ProtocolAds* pAds = dynamic_cast<ProtocolAds*>(pPlugin);
            if (pAds != NULL)
            {
                AdsListener* listener = pAds->getAdsListener();
                if (listener)
                {
                    listener->onAdsResult((AdsResultCode) ret, strMsg.c_str());
                }
                else
                {
                    PluginUtilsAndroid::outputLog("ProtocolAds", "Can't find nativeOnAdsResult() listener of plugin %s", pPlugin->getPluginName());
                }
            }
        }
    }
    
    JNIEXPORT void JNICALL Java_org_cocos2dx_plugin_AdsWrapper_nativeOnPlayerGetPoints(JNIEnv*  env, jobject thiz, jstring className, jint points) {
        std::string strClassName = PluginJniHelper::jstring2string(className);
        PluginProtocol* pPlugin = PluginUtilsAndroid::getPluginPtr(strClassName);
        PluginUtilsAndroid::outputLog("ProtocolAds", "nativeOnPlayerGetPoints(), Get plugin ptr : %p", pPlugin);
        if (pPlugin != NULL)
        {
            PluginUtilsAndroid::outputLog("ProtocolAds", "nativeOnPlayerGetPoints(), Get plugin name : %s", pPlugin->getPluginName());
            ProtocolAds* pAds = dynamic_cast<ProtocolAds*>(pPlugin);
            if (pAds != NULL)
            {
                AdsListener* listener = pAds->getAdsListener();
                if (listener)
                {
                    listener->onPlayerGetPoints(pAds, points);
                }else{
                	PluginUtilsAndroid::outputLog("ProtocolAds", "Can't find nativeOnPlayerGetPoints() listener of plugin %s", pPlugin->getPluginName());
                }
            }
        }
    }
    
}
