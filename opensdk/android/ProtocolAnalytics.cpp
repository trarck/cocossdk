#include "ProtocolAnalytics.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtilsAndroid.h"
#include "PluginJavaData.h"

namespace opensdk {

ProtocolAnalytics::ProtocolAnalytics()
{
}

ProtocolAnalytics::~ProtocolAnalytics()
{
}

void ProtocolAnalytics::startSession(const char* appKey)
{
	PluginUtilsAndroid::callJavaFunctionWithName_string_map(this, "startSession", appKey, NULL);
}

void ProtocolAnalytics::stopSession()
{
    PluginUtilsAndroid::callJavaBoolFuncWithName(this, "stopSession");
}

void ProtocolAnalytics::setSessionContinueMillis(long millis)
{
	PluginUtilsAndroid::callJavaFunctionWithName_oneParam(this, "setSessionContinueMillis", "(I)V", millis);
}

void ProtocolAnalytics::setCaptureUncaughtException(bool isEnabled)
{
	PluginUtilsAndroid::callJavaFunctionWithName_oneParam(this, "setCaptureUncaughtException", "(Z)V", isEnabled);
}

void ProtocolAnalytics::logError(const char* errorId, const char* message)
{
    PluginUtilsAndroid::callJavaFunctionWithName_string_string(this, "logError", errorId, message);
}

void ProtocolAnalytics::logEvent(const char* eventId, LogEventParamMap* pParams/* = NULL */)
{
	PluginUtilsAndroid::callJavaFunctionWithName_string_map(this, "logEvent", eventId, pParams);
}

void ProtocolAnalytics::logTimedEventBegin(const char* eventId)
{
	PluginUtilsAndroid::callJavaFunctionWithName_string_map(this, "logTimedEventBegin", eventId, NULL);
}

void ProtocolAnalytics::logTimedEventEnd(const char* eventId)
{
	PluginUtilsAndroid::callJavaFunctionWithName_string_map(this, "logTimedEventEnd", eventId, NULL);
}

} //namespace plugin {
