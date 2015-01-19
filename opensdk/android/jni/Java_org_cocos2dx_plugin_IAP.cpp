#include "ProtocolIAP.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtils.h"
#include <jni.h>

using namespace opensdk;

extern "C" {
    
    JNIEXPORT void JNICALL Java_org_cocos2dx_plugin_IAPWrapper_nativeOnPayResult(JNIEnv*  env, jobject thiz, jstring className, jint ret, jstring msg)
    {
        std::string strMsg = PluginJniHelper::jstring2string(msg);
        std::string strClassName = PluginJniHelper::jstring2string(className);
        PluginProtocol* pPlugin = PluginUtils::getPluginPtr(strClassName);
        PluginUtils::outputLog("ProtocolIAP", "nativeOnPayResult(), Get plugin ptr : %p", pPlugin);
        if (pPlugin != NULL)
        {
            PluginUtils::outputLog("ProtocolIAP", "nativeOnPayResult(), Get plugin name : %s", pPlugin->getPluginName());
            ProtocolIAP* pIAP = dynamic_cast<ProtocolIAP*>(pPlugin);
            if (pIAP != NULL)
            {
                pIAP->onPayResult((PayResultCode) ret, strMsg.c_str());
            }else{
            	PluginUtils::outputLog("ProtocolIAP", "Can't find nativeOnPayResult listener of plugin %s", pPlugin->getPluginName());
            }
        }
    }
    
}
