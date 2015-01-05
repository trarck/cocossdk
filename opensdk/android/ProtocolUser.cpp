#include "ProtocolUser.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtilsAndroid.h"
#include "PluginJavaData.h"

namespace opensdk {


ProtocolUser::ProtocolUser()
: _listener(NULL)
{
}

ProtocolUser::~ProtocolUser()
{
}

void ProtocolUser::configDeveloperInfo(TUserDeveloperInfo devInfo)
{
    if (devInfo.empty())
    {
        PluginUtilsAndroid::outputLog("ProtocolUser", "The developer info is empty!");
        return;
    }
    else
    {
        PluginUtilsAndroid::callJavaFunctionWithName_map(this, "configDeveloperInfo", &devInfo);
    }
}

void ProtocolUser::login()
{
    PluginUtilsAndroid::callJavaFunctionWithName(this, "login");
}

void ProtocolUser::logout()
{
    PluginUtilsAndroid::callJavaFunctionWithName(this, "logout");
}

bool ProtocolUser::isLoggedIn()
{
    return PluginUtilsAndroid::callJavaBoolFuncWithName(this, "isLogined");
}

std::string ProtocolUser::getSessionID()
{
    return PluginUtilsAndroid::callJavaStringFuncWithName(this, "getSessionID");
}

std::string ProtocolUser::getAccessToken()
{
	return PluginUtilsAndroid::callJavaStringFuncWithName(this, "getAccessToken");
}

} // namespace opensdk {

