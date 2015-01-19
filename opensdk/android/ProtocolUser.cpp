#include "ProtocolUser.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtils.h"
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
        PluginUtils::outputLog("ProtocolUser", "The developer info is empty!");
        return;
    }
    else
    {
        PluginUtils::callJavaFunctionWithName_map(this, "configDeveloperInfo", &devInfo);
    }
}

void ProtocolUser::login()
{
    PluginUtils::callJavaFunctionWithName(this, "login");
}

void ProtocolUser::logout()
{
    PluginUtils::callJavaFunctionWithName(this, "logout");
}

bool ProtocolUser::isLoggedIn()
{
    return PluginUtils::callJavaBoolFuncWithName(this, "isLogined");
}

std::string ProtocolUser::getSessionID()
{
    return PluginUtils::callJavaStringFuncWithName(this, "getSessionID");
}

std::string ProtocolUser::getAccessToken()
{
	return PluginUtils::callJavaStringFuncWithName(this, "getAccessToken");
}

} // namespace opensdk {

