#include "ProtocolAds.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtilsAndroid.h"
#include "PluginJavaData.h"

namespace opensdk {

ProtocolAds::ProtocolAds()
: _listener(NULL)
{
}

ProtocolAds::~ProtocolAds()
{
}

void ProtocolAds::configDeveloperInfo(TAdsDeveloperInfo devInfo)
{
    if (devInfo.empty())
    {
        PluginUtilsAndroid::outputLog("ProtocolAds", "The application info is empty!");
        return;
    }
    else
    {
        PluginUtilsAndroid::callJavaFunctionWithName_map(this, "configDeveloperInfo", &devInfo);
    }
}

void ProtocolAds::showAds(TAdsInfo info, AdsPos pos)
{
	PluginJavaData* pData = PluginUtilsAndroid::getPluginJavaData(this);
	PluginJniMethodInfo t;

	PluginUtilsAndroid::outputLog("ProtocolAds", "Class name : %s", pData->jclassName.c_str());
	if (PluginJniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, "showAds"
		, "(Ljava/util/Hashtable;I)V"))
	{
	    jobject obj_Map = PluginUtilsAndroid::createJavaMapObject(&info);
		t.env->CallVoidMethod(pData->jobj, t.methodID, obj_Map, pos);
		t.env->DeleteLocalRef(obj_Map);
		t.env->DeleteLocalRef(t.classID);
	}
}

void ProtocolAds::hideAds(TAdsInfo info)
{
    PluginUtilsAndroid::callJavaFunctionWithName_map(this, "hideAds", &info);
}

void ProtocolAds::queryPoints()
{
    PluginUtilsAndroid::callJavaFunctionWithName(this, "queryPoints");
}

void ProtocolAds::spendPoints(int points)
{
	PluginUtilsAndroid::callJavaFunctionWithName_oneParam(this, "spendPoints", "(I)V", points);
}

} // namespace opensdk {
