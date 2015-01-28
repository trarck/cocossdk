#include "UserObject.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtils.h"
#include "PluginJavaData.h"

namespace opensdk {

std::string UserObject::_serverID="";
std::string UserObject::_serverIP="";


UserObject::UserObject()
: _listener(NULL)
, _pluginName("")
{
}

UserObject::~UserObject()
{
}

void UserObject::setPluginName(const char* name)
{
    _pluginName = name;
}

const char* UserObject::getPluginName()
{
    return _pluginName.c_str();
}
    
void UserObject::configDeveloperInfo(TUserDeveloperInfo devInfo)
{
    if (devInfo.empty())
    {
        PluginUtils::outputLog("UserObject", "The developer info is empty!");
        return;
    }
    else
    {
        PluginUtils::callJavaFunctionWithName_map(this, "configDeveloperInfo", &devInfo);
    }
}

void UserObject::login()
{
    PluginUtils::callJavaFunctionWithName(this, "login");
}
    
void UserObject::login(const std::string& server_id, const std::string& oauthLoginServer)
{
    if(!server_id.empty()){
        _serverID=server_id;
    }
    
    if(!oauthLoginServer.empty()){
        _serverIP=oauthLoginServer;
    }
    
    PluginUtils::callJavaFunctionWithName(this, "login");
}

void UserObject::logout()
{
    PluginUtils::callJavaFunctionWithName(this, "logout");
}

bool UserObject::isLogined()
{
    return PluginUtils::callJavaBoolFuncWithName(this, "isLogined");
}
    
std::string UserObject::getUserID()
{
    return PluginUtils::callJavaStringFuncWithName(this, "getUserID");
}

std::string UserObject::getSessionID()
{
    return PluginUtils::callJavaStringFuncWithName(this, "getSessionID");
}

std::string UserObject::getAccessToken()
{
	return PluginUtils::callJavaStringFuncWithName(this, "getAccessToken");
}
    
void UserObject::setActionListener(UserActionListener* listener)
{
    _listener = listener;
}

UserActionListener* UserObject::getActionListener()
{
    return _listener;
}

bool UserObject::isFunctionSupported(const std::string& functionName)
{
    jstring jstr = PluginUtils::getEnv()->NewStringUTF(functionName.c_str());
    bool ret=PluginUtils::callJavaBoolFuncWithName_oneParam(this, "isFunctionSupported", "(Ljava/lang/String;)V", jstr);
    PluginUtils::getEnv()->DeleteLocalRef(jstr);
    
    return ret;
}

std::string UserObject::getPluginId()
{
    return PluginUtils::callJavaStringFuncWithName(this, "getPluginId");
}

} // namespace opensdk {

