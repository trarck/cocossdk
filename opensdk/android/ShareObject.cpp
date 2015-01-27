#include "ShareObject.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtils.h"
#include "PluginJavaData.h"

namespace opensdk {


ShareObject::ShareObject()
: _listener(NULL)
{
}

ShareObject::~ShareObject()
{
}
    
void ShareObject::setPluginName(const char* name)
{
    _pluginName = name;
}

const char* ShareObject::getPluginName()
{
    return _pluginName.c_str();
}

void ShareObject::configDeveloperInfo(TShareDeveloperInfo devInfo)
{
    if (devInfo.empty())
    {
        PluginUtils::outputLog("ShareObject", "The developer info is empty!");
        return;
    }
    else
    {
        PluginUtils::callJavaFunctionWithName_map(this, "configDeveloperInfo", &devInfo);
    }
}

void ShareObject::share(TShareInfo info)
{
    if (info.empty())
    {
        if (NULL != _listener)
        {
            onShareResult(kShareFail, "Share info error");
        }
        PluginUtils::outputLog("ShareObject", "The Share info is empty!");
        return;
    }
    else
    {
        PluginUtils::callJavaFunctionWithName_map(this, "share", &info);
    }
}


void ShareObject::setResultListener(ShareResultListener* pListener)
{
	_listener = pListener;
}

ShareResultListener* ShareObject::getResultListener()
{
    return _listener;
}

void ShareObject::onShareResult(ShareResultCode ret, const char* msg)
{
    if (_listener)
    {
    	_listener->onShareResult(ret, msg);
    }
    else
    {
        PluginUtils::outputLog("ShareObject", "Result listener is null!");
    }
    PluginUtils::outputLog("ShareObject", "Share result is : %d(%s)", (int) ret, msg);
}

} // namespace opensdk {
