#include "ProtocolIAP.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtils.h"
#include <jni.h>
#include "OpenSdk.h"

using namespace opensdk;

extern "C" {
    
    JNIEXPORT void JNICALL Java_com_opensdk_framework_OpenSdk_nativeInitPlugins(JNIEnv*  env, jobject thiz)
    {
		OpenSdk::getInstance()->onInitPlugins();
    }
}
