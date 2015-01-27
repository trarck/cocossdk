#include "AdsObject.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtils.h"
#include "PluginJavaData.h"

namespace opensdk {

AdsObject::AdsObject()
: _listener(NULL)
{
}

AdsObject::~AdsObject()
{
	
}

void AdsObject::setPluginName(const char* name)
{
	_pluginName = name;
}

/**
 *@brief get plugin name
 */
const char* AdsObject::getPluginName()
{
	return _pluginName.c_str();
}

void AdsObject::configDeveloperInfo(TAdsDeveloperInfo devInfo)
{
    if (devInfo.empty())
    {
        PluginUtils::outputLog("AdsObject", "The application info is empty!");
        return;
    }
    else
    {
        PluginUtils::callJavaFunctionWithName_map(this, "configDeveloperInfo", &devInfo);
    }
}

void AdsObject::showAds(TAdsInfo info, AdsPos pos)
{
	PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
	PluginJniMethodInfo t;

	PluginUtils::outputLog("AdsObject", "Class name : %s", pData->jclassName.c_str());
	if (PluginJniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, "showAds"
		, "(Ljava/util/Hashtable;I)V"))
	{
	    jobject obj_Map = PluginUtils::createJavaMapObject(&info);
		t.env->CallVoidMethod(pData->jobj, t.methodID, obj_Map, pos);
		t.env->DeleteLocalRef(obj_Map);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AdsObject::hideAds(TAdsInfo info)
{
    PluginUtils::callJavaFunctionWithName_map(this, "hideAds", &info);
}

void AdsObject::showAds(AdsType adsType, int idx = 1)
{
	PluginParam paramAdsType(adsType);
	PluginParam paramIdx(idx);
	callFuncWithParam("showAds",&paramAdsType,&paramIdx,NULL);
}

void AdsObject::hideAds(AdsType adsType, int idx = 1)
{
	PluginParam paramAdsType(adsType);
	PluginParam paramIdx(idx);
	callFuncWithParam("hideAds",&paramAdsType,&paramIdx,NULL);
}

void AdsObject::preloadAds(AdsType adsType, int idx = 1)
{
	PluginParam paramAdsType(adsType);
	PluginParam paramIdx(idx);
	callFuncWithParam("preloadAds",&paramAdsType,&paramIdx,NULL);
}

void AdsObject::queryPoints()
{
    PluginUtils::callJavaFunctionWithName(this, "queryPoints");
}

void AdsObject::spendPoints(int points)
{
	PluginUtils::callJavaFunctionWithName_oneParam(this, "spendPoints", "(I)V", points);
}

void AdsObject::setAdsListener(AdsListener* listener)
{
	_listener=listener;
}

AdsListener* AdsObject::getAdsListener()
{
	return _listener;
}

bool AdsObject::isAdTypeSupported(AdsType adType)
{
	PluginParam paramAdsType(adsType);
	return callBoolFuncWithParam("isAdTypeSupported",&paramAdsType,NULL);
}

} // namespace opensdk {
