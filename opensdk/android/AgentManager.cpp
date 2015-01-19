#include <vector>

#include "AgentManager.h"
#include "PluginManager.h"
#include "ProtocolUser.h"
#include "ProtocolAnalytics.h"
#include "PluginUtils.h"

namespace opensdk {

static AgentManager* s_AgentManager = NULL;

AgentManager::AgentManager():pUser(NULL), pShare(NULL), pSocial(NULL), pAds(NULL), pAnalytics(NULL), pIAP(NULL)
{

}

AgentManager::~AgentManager()
{
	this->purge();
}

void AgentManager::purge()
{
	delete pUser;
	delete pShare;
	delete pSocial;
	delete pAds;
	delete pAnalytics;
	delete pIAP;
}

AgentManager* AgentManager::getInstance()
{
	if(NULL == s_AgentManager)
	{
		s_AgentManager = new (std::nothrow) AgentManager();
		//s_AgentManager->init();
	}
	return s_AgentManager;
}

void AgentManager::destroyInstance()
{
	if(s_AgentManager)
	{
		delete s_AgentManager;
		s_AgentManager = NULL;
	}
}

bool AgentManager::initWithConfigureFile()
{
	std::map<std::string, std::string> conf = getPluginConfigure();
	return init(conf);
}

bool AgentManager::init(std::map<std::string, std::string>& conf)
{
	if(conf.empty())
		return false;

	for(std::map<std::string, std::string>::iterator iter = conf.begin(); iter != conf.end(); ++iter)
	{
		std::string pluginName = iter->first;
		if("PluginUser" == pluginName)
		{
			pUser = dynamic_cast<ProtocolUser *>(PluginManager::getInstance()->loadPlugin(iter->second.c_str()));
		}
		else if("PluginShare" == pluginName)
		{
			pShare = dynamic_cast<ProtocolShare *>(PluginManager::getInstance()->loadPlugin(iter->second.c_str()));
		}
		else if("PluginSocial" == pluginName)
		{
			pSocial = dynamic_cast<ProtocolSocial *>(PluginManager::getInstance()->loadPlugin(iter->second.c_str()));
		}
		else if("PluginAds" == pluginName)
		{
			pAds = dynamic_cast<ProtocolAds *>(PluginManager::getInstance()->loadPlugin(iter->second.c_str()));
		}
		else if("PluginAnalytics" == pluginName)
		{
			pAnalytics = dynamic_cast<ProtocolAnalytics *>(PluginManager::getInstance()->loadPlugin(iter->second.c_str()));
		}
		else if("PluginIAP" == pluginName)
		{
			pIAP = dynamic_cast<ProtocolIAP *>(PluginManager::getInstance()->loadPlugin(iter->second.c_str()));
		}
	}

	return true;
}

static std::string s_plugins[]={"PluginUser", "PluginShare", "PluginSocial", "PluginAds", "PluginAnalytics", "PluginIAP"};

std::map<std::string, std::string> AgentManager::getPluginConfigure()
{
	std::map<std::string, std::string> configure;

	PluginJniMethodInfo t;
	JNIEnv* env = PluginUtils::getEnv();

	if(PluginJniHelper::getStaticMethodInfo(t, "org/cocos2dx/plugin/PluginWrapper", "getPluginConfigure", "()Ljava/util/Hashtable;"))
	{
		jobject jhashtable = t.env->CallStaticObjectMethod(t.classID, t.methodID);
		PluginJniMethodInfo tGetMethod;
		if(PluginJniHelper::getMethodInfo(tGetMethod, "java/util/Hashtable", "get", "(Ljava/lang/Object;)Ljava/lang/Object;"))
		{
			jstring jKey;
			jstring jValue;
			std::string stdValue;
			
			size_t count=sizeof(s_plugins)/sizeof(std::string);

			for(int i=0;i<count;++i)
			{
				jKey = env->NewStringUTF(s_plugins[i].c_str());
				jValue = (jstring) (env->CallObjectMethod(jhashtable,tGetMethod.methodID,jKey));
				stdValue = PluginJniHelper::jstring2string(jValue);
				if(!stdValue.empty())
					configure.insert(std::make_pair(s_plugins[i], stdValue));
			}

			tGetMethod.env->DeleteLocalRef(jKey);
			tGetMethod.env->DeleteLocalRef(jValue);

		}
		env->DeleteLocalRef(jhashtable);
		env->DeleteLocalRef(tGetMethod.classID);
	}
	env->DeleteLocalRef(t.classID);
	return configure;
}

}
