#include "IAPObject.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtils.h"
#include "PluginJavaData.h"

namespace opensdk {

bool ProtocolIAP::_paying = false;

IAPObject::IAPObject()
: _listener(NULL)
, _pluginName("")
{
}

IAPObject::~IAPObject()
{
}

void IAPObject::setPluginName(const char* name)
{
	_pluginName = name;
}

const char* IAPObject::getPluginName()
{
	return _pluginName.c_str();
}

void IAPObject::configDeveloperInfo(TIAPDeveloperInfo devInfo)
{
    if (devInfo.empty())
    {
        PluginUtils::outputLog("IAPObject", "The developer info is empty!");
        return;
    }
    else
    {
        PluginUtils::callJavaFunctionWithName_map(this, "configDeveloperInfo", &devInfo);
    }
}

void IAPObject::payForProduct(TProductInfo info)
{
    if (_paying)
    {
        PluginUtils::outputLog("IAPObject", "Now is paying");
        return;
    }

    if (info.empty())
    {
        if (NULL != _listener)
        {
            onPayResult(kPayFail, "Product info error");
        }
        PluginUtils::outputLog("IAPObject", "The product info is empty!");
        return;
    }
    else
    {
        _paying = true;
        _curInfo = info;
        
        PluginUtils::callJavaFunctionWithName_map(this, "payForProduct", &info);
    }
}

std::string IAPObject::getOrderId()
{
	return PluginUtils::callJavaStringFuncWithName(this,"getOrderId");
}

void IAPObject::setResultListener(PayResultListener* pListener)
{
	_listener = pListener;
    popActionResult();
}

PayResultListener* IAPObject::getResultListener()
{
	return _listener;
}

std::string IAPObject::getPluginId()
{
	return PluginUtils::callJavaStringFuncWithName(this,"getPluginId");
}

void IAPObject::onPayResult(PayResultCode ret, const char* msg)
{
    _paying = false;
    if (_listener)
    {
    	_listener->onPayResult(ret, msg, _curInfo);
    }
    else
    {
        PluginUtils::outputLog("IAPObject", "Result listener is null!");
		//处理没有设置listener导致丢单。可以使用一个列表保存所有没有处理的结果
        pushActionResult(ret, msg);
    }
    _curInfo.clear();
    PluginUtils::outputLog("IAPObject", "Pay result is : %d(%s)", (int) ret, msg);
}

void IAPObject::popActionResult()
{
    if (_listener) {
        while(_actionResultList.size()>0){
            IAPActionResult actionResult=_actionResultList.back();
            _listener->onPayResult(actionResult.payResultCode, actionResult.msg.c_str(), actionResult.productInfo);
            _actionResultList.pop_back();
        }
    }
}

void IAPObject::pushActionResult(const IAPActionResult& actionResult)
{
    _actionResultList.push_back(actionResult);
}

void IAPObject::pushActionResult(PayResultCode ret, const char* msg)
{
    IAPActionResult actionResult={ret,msg,_curInfo};
    _actionResultList.push_back(actionResult);
}

} // namespace opensdk {
