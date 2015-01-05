#include "ProtocolUser.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtilsAndroid.h"
#include <jni.h>

using namespace opensdk;

extern "C" {
    
    JNIEXPORT void JNICALL Java_org_cocos2dx_plugin_UserWrapper_nativeOnActionResult(JNIEnv*  env, jobject thiz, jstring className, jint ret, jstring msg)
    {
        std::string strMsg = PluginJniHelper::jstring2string(msg);
        std::string strClassName = PluginJniHelper::jstring2string(className);
        PluginProtocol* pPlugin = PluginUtilsAndroid::getPluginPtr(strClassName);
        PluginUtilsAndroid::outputLog("ProtocolUser", "nativeOnActionResult(), Get plugin ptr : %p", pPlugin);
        if (pPlugin != NULL)
        {
            PluginUtilsAndroid::outputLog("ProtocolUser", "nativeOnActionResult(), Get plugin name : %s", pPlugin->getPluginName());
            ProtocolUser* pUser = dynamic_cast<ProtocolUser*>(pPlugin);
            if (pUser != NULL)
            {
                UserActionListener* listener = pUser->getActionListener();
                if (NULL != listener)
                {
                    listener->onActionResult(pUser, (UserActionResultCode) ret, strMsg.c_str());
                }
                else
                {
					PluginUtilsAndroid::outputLog("Listener of plugin %s not set correctly", pPlugin->getPluginName());
                }
            }
        }
    }
    
}
