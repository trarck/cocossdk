#include "ProtocolShare.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtilsAndroid.h"
#include <jni.h>

using namespace opensdk;

extern "C" {
    JNIEXPORT void JNICALL Java_org_cocos2dx_plugin_ShareWrapper_nativeOnShareResult(JNIEnv*  env, jobject thiz, jstring className, jint ret, jstring msg)
    {
        std::string strMsg = PluginJniHelper::jstring2string(msg);
        std::string strClassName = PluginJniHelper::jstring2string(className);
        PluginProtocol* pPlugin = PluginUtilsAndroid::getPluginPtr(strClassName);
        PluginUtilsAndroid::outputLog("ProtocolShare", "nativeOnShareResult(), Get plugin ptr : %p", pPlugin);
        if (pPlugin != NULL)
        {
            PluginUtilsAndroid::outputLog("ProtocolShare", "nativeOnShareResult(), Get plugin name : %s", pPlugin->getPluginName());
            ProtocolShare* pShare = dynamic_cast<ProtocolShare*>(pPlugin);
            if (pShare != NULL)
            {
                ShareResultListener* listener = pShare->getResultListener();
                if (NULL != listener)
                {
                    ShareResultCode cRet = (ShareResultCode) ret;
                    listener->onShareResult(cRet, strMsg.c_str());
                }else
                {
					PluginUtilsAndroid::outputLog("ProtocolShare", "Can't find the listener of plugin %s", pPlugin->getPluginName());
                }
            }
            
        }
    }
    
    
}
