#include "ProtocolSocial.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtilsAndroid.h"
#include <jni.h>

using namespace opensdk;

extern "C" {
    JNIEXPORT void JNICALL Java_org_cocos2dx_plugin_SocialWrapper_nativeOnSocialResult(JNIEnv*  env, jobject thiz, jstring className, jint ret, jstring msg)
    {
        std::string strMsg = PluginJniHelper::jstring2string(msg);
        std::string strClassName = PluginJniHelper::jstring2string(className);
        PluginProtocol* pPlugin = PluginUtilsAndroid::getPluginPtr(strClassName);
        PluginUtilsAndroid::outputLog("ProtocolSocial", "nativeOnSocialResult(), Get plugin ptr : %p", pPlugin);
        if (pPlugin != NULL)
        {
            PluginUtilsAndroid::outputLog("ProtocolSocial", "nativeOnSocialResult(), Get plugin name : %s", pPlugin->getPluginName());
            ProtocolSocial* pSocial = dynamic_cast<ProtocolSocial*>(pPlugin);
            if (pSocial != NULL)
            {
                SocialListener* pListener = pSocial->getListener();
                if (NULL != pListener)
                {
                    pListener->onSocialResult((SocialRetCode) ret, strMsg.c_str());
                }
                else
                {
                    PluginUtilsAndroid::outputLog("ProtocolShare", "Can't find the nativeOnSocialResult listener of plugin %s", pPlugin->getPluginName());
                }
            }
        }
    }
    
    
}
