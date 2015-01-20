#include "OpenSdk.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtils.h"

namespace opensdk {

static OpenSdk* s_OpenSdk = NULL;

OpenSdk::~OpenSdk()
{

}

OpenSdk* OpenSdk::getInstance()
{
	if(NULL == s_OpenSdk)
	{
		s_OpenSdk = new OpenSdk();
	}
	return s_OpenSdk;
}

void OpenSdk::destroyInstance()
{
	if(s_OpenSdk)
	{
		delete s_OpenSdk;
		s_OpenSdk = NULL;
	}
}

void OpenSdk::onInitPlugins()
{
	if (_listener)
    {
    	_listener->onInitPlugins();
    }
    else
    {
        PluginUtils::outputLog("ProtocolIAP", "Result listener is null!");
    }
}

void OpenSdk::setListener(OpenSdkListener* pListener)
{
	_listener = pListener;
}

}
