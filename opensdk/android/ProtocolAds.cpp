#include "ProtocolAds.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtils.h"
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
        PluginUtils::outputLog("ProtocolAds", "The application info is empty!");
        return;
    }
    else
    {
        PluginUtils::callJavaFunctionWithName_map(this, "configDeveloperInfo", &devInfo);
    }
}

void ProtocolAds::showAds(TAdsInfo info, AdsPos pos)
{
	PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
	PluginJniMethodInfo t;

	PluginUtils::outputLog("ProtocolAds", "Class name : %s", pData->jclassName.c_str());
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

void ProtocolAds::hideAds(TAdsInfo info)
{
    PluginUtils::callJavaFunctionWithName_map(this, "hideAds", &info);
}

void ProtocolAds::queryPoints()
{
    PluginUtils::callJavaFunctionWithName(this, "queryPoints");
}

void ProtocolAds::spendPoints(int points)
{
	PluginUtils::callJavaFunctionWithName_oneParam(this, "spendPoints", "(I)V", points);
}

} // namespace opensdk {
