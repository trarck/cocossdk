#include "ProtocolAds.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtils.h"
#include <jni.h>

using namespace opensdk;

extern "C" {
    JNIEXPORT void JNICALL Java_com_opensdk_framework_AdsWrapper_nativeOnAdsResult(JNIEnv*  env, jobject thiz, jstring className, jint ret, jstring msg) {
        std::string strMsg = PluginJniHelper::jstring2string(msg);
        std::string strClassName = PluginJniHelper::jstring2string(className);
        PluginProtocol* pPlugin = PluginUtils::getPluginPtr(strClassName);
        PluginUtils::outputLog("ProtocolAds", "nativeOnAdsResult(), Get plugin ptr : %p", pPlugin);
        if (pPlugin != NULL)
        {
            PluginUtils::outputLog("ProtocolAds", "nativeOnAdsResult(), Get plugin name : %s", pPlugin->getPluginName());
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
                    PluginUtils::outputLog("ProtocolAds", "Can't find nativeOnAdsResult() listener of plugin %s", pPlugin->getPluginName());
                }
            }
        }
    }
    
    JNIEXPORT void JNICALL Java_com_opensdk_framework_AdsWrapper_nativeOnPlayerGetPoints(JNIEnv*  env, jobject thiz, jstring className, jint points) {
        std::string strClassName = PluginJniHelper::jstring2string(className);
        PluginProtocol* pPlugin = PluginUtils::getPluginPtr(strClassName);
        PluginUtils::outputLog("ProtocolAds", "nativeOnPlayerGetPoints(), Get plugin ptr : %p", pPlugin);
        if (pPlugin != NULL)
        {
            PluginUtils::outputLog("ProtocolAds", "nativeOnPlayerGetPoints(), Get plugin name : %s", pPlugin->getPluginName());
            ProtocolAds* pAds = dynamic_cast<ProtocolAds*>(pPlugin);
            if (pAds != NULL)
            {
                AdsListener* listener = pAds->getAdsListener();
                if (listener)
                {
                    listener->onPlayerGetPoints(pAds, points);
                }else{
                	PluginUtils::outputLog("ProtocolAds", "Can't find nativeOnPlayerGetPoints() listener of plugin %s", pPlugin->getPluginName());
                }
            }
        }
    }
    
}