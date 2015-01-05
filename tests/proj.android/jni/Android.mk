LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
			       ../../opensdk/android/AgentManager.cpp \
				   ../../opensdk/android/PluginFactory.cpp \
				   ../../opensdk/android/PluginJniHelper.cpp \
				   ../../opensdk/android/PluginProtocol.cpp \
				   ../../opensdk/android/PluginUtilsAndroid.cpp \
				   ../../opensdk/android/ProtocolAds.cpp \
				   ../../opensdk/android/ProtocolAnalytics.cpp \
				   ../../opensdk/android/ProtocolIAP.cpp \
				   ../../opensdk/android/ProtocolShare.cpp \
				   ../../opensdk/android/ProtocolSocial.cpp \
				   ../../opensdk/android/ProtocolUser.cpp \
				   ../../opensdk/android/jni/Java_org_cocos2dx_plugin_Ads.cpp \
				   ../../opensdk/android/jni/Java_org_cocos2dx_plugin_IAP.cpp \
				   ../../opensdk/android/jni/Java_org_cocos2dx_plugin_Share.cpp \
				   ../../opensdk/android/jni/Java_org_cocos2dx_plugin_Social.cpp \
				   ../../opensdk/android/jni/Java_org_cocos2dx_plugin_User.cpp \
				   ../../opensdk/PluginManager.cpp \
				   ../../opensdk/PluginParam.cpp \
                   ../../tests/AppDelegate.cpp \
                   ../../tests/HelloWorldScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../tests \
					$(LOCAL_PATH)/../../opensdk/include

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
