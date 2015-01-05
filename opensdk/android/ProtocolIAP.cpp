#include "ProtocolIAP.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtilsAndroid.h"
#include "PluginJavaData.h"

namespace opensdk {

bool ProtocolIAP::_paying = false;

ProtocolIAP::ProtocolIAP()
: _listener(NULL)
{
}

ProtocolIAP::~ProtocolIAP()
{
}

void ProtocolIAP::configDeveloperInfo(TIAPDeveloperInfo devInfo)
{
    if (devInfo.empty())
    {
        PluginUtilsAndroid::outputLog("ProtocolIAP", "The developer info is empty!");
        return;
    }
    else
    {
        PluginUtilsAndroid::callJavaFunctionWithName_map(this, "configDeveloperInfo", &devInfo);
    }
}

void ProtocolIAP::payForProduct(TProductInfo info)
{
    if (_paying)
    {
        PluginUtilsAndroid::outputLog("ProtocolIAP", "Now is paying");
        return;
    }

    if (info.empty())
    {
        if (NULL != _listener)
        {
            onPayResult(kPayFail, "Product info error");
        }
        PluginUtilsAndroid::outputLog("ProtocolIAP", "The product info is empty!");
        return;
    }
    else
    {
        _paying = true;
        _curInfo = info;
        
        PluginUtilsAndroid::callJavaFunctionWithName_map(this, "payForProduct", &info);
    }
}


void ProtocolIAP::setResultListener(PayResultListener* pListener)
{
	_listener = pListener;
}

void ProtocolIAP::onPayResult(PayResultCode ret, const char* msg)
{
    _paying = false;
    if (_listener)
    {
    	_listener->onPayResult(ret, msg, _curInfo);
    }
    else
    {
        PluginUtilsAndroid::outputLog("ProtocolIAP", "Result listener is null!");
    }
    _curInfo.clear();
    PluginUtilsAndroid::outputLog("ProtocolIAP", "Pay result is : %d(%s)", (int) ret, msg);
}

} // namespace opensdk {
