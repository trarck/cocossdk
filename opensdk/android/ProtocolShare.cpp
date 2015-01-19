#include "ProtocolShare.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtils.h"
#include "PluginJavaData.h"

namespace opensdk {


ProtocolShare::ProtocolShare()
: _listener(NULL)
{
}

ProtocolShare::~ProtocolShare()
{
}

void ProtocolShare::configDeveloperInfo(TShareDeveloperInfo devInfo)
{
    if (devInfo.empty())
    {
        PluginUtils::outputLog("ProtocolShare", "The developer info is empty!");
        return;
    }
    else
    {
        PluginUtils::callJavaFunctionWithName_map(this, "configDeveloperInfo", &devInfo);
    }
}

void ProtocolShare::share(TShareInfo info)
{
    if (info.empty())
    {
        if (NULL != _listener)
        {
            onShareResult(kShareFail, "Share info error");
        }
        PluginUtils::outputLog("ProtocolShare", "The Share info is empty!");
        return;
    }
    else
    {
        PluginUtils::callJavaFunctionWithName_map(this, "configDeveloperInfo", &info);
    }
}


void ProtocolShare::setResultListener(ShareResultListener* pListener)
{
	_listener = pListener;
}

ShareResultListener* ProtocolShare::getResultListener()
{
    return _listener;
}

void ProtocolShare::onShareResult(ShareResultCode ret, const char* msg)
{
    if (_listener)
    {
    	_listener->onShareResult(ret, msg);
    }
    else
    {
        PluginUtils::outputLog("ProtocolShare", "Result listener is null!");
    }
    PluginUtils::outputLog("ProtocolShare", "Share result is : %d(%s)", (int) ret, msg);
}

} // namespace opensdk {
