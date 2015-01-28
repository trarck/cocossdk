#include "PushObject.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtils.h"
#include "PluginJavaData.h"

namespace opensdk {

PushObject::PushObject()
:_listener(NULL)
, _pluginName("")
{
	
}

PushObject::~PushObject()
{
	
}

void PushObject::setPluginName(const char* name)
{
	_pluginName = name;
}

const char* PushObject::getPluginName()
{
	return _pluginName.c_str();
}

void PushObject::startPush()
{
    PluginUtils::callJavaFunctionWithName(this,"startPush");
}

void PushObject::closePush()
{
    PluginUtils::callJavaFunctionWithName(this,"closePush");
}

void PushObject::setAlias(const std::string& alias)
{
    PluginParam paramAlias(alias.c_str());
    
    callFuncWithParam("setAlias", &paramAlias,NULL);
}

void PushObject::delAlias(const std::string& alias)
{
    PluginParam paramAlias(alias.c_str());
    
    callFuncWithParam("delAlias", &paramAlias,NULL);
}

void PushObject::setTags(const std::list<std::string>& tags)
{
    PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
    
    if (NULL == pData) {
        PluginUtils::outputLog("PushObject", "Can't find java data for plugin : %s", this->getPluginName());
        return;
    }
    
    PluginJniMethodInfo t;

 
    if (PluginJniHelper::getMethodInfo(t
                                       , pData->jclassName.c_str()
                                       , "setTags"
                                       , "(Ljava/util/ArrayList;)V"))
    {
        jobject obj_List = PluginUtils::createJavaMapObject(tags);
        t.env->CallVoidMethod(pData->jobj, t.methodID, obj_List);
        t.env->DeleteLocalRef(obj_List);
        t.env->DeleteLocalRef(t.classID);
    }
}

void PushObject::delTags(const std::list<std::string>& tags)
{
    PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
    
    if (NULL == pData) {
        PluginUtils::outputLog("PushObject", "Can't find java data for plugin : %s", this->getPluginName());
        return;
    }
    
    PluginJniMethodInfo t;
    
    
    if (PluginJniHelper::getMethodInfo(t
                                       , pData->jclassName.c_str()
                                       , "delTags"
                                       , "(Ljava/util/ArrayList;)V"))
    {
        jobject obj_List = PluginUtils::createJavaMapObject(tags);
        t.env->CallVoidMethod(pData->jobj, t.methodID, obj_List);
        t.env->DeleteLocalRef(obj_List);
        t.env->DeleteLocalRef(t.classID);
    }
}

void PushObject::setActionListener(PushActionListener* listener)
{
	_listener=listener;
}

PushActionListener* PushObject::getActionListener()
{
	return _listener;
}

} // namespace opensdk

