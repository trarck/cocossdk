#ifndef __OPENSDK_AGENT_MANAGER_H__
#define __OPENSDK_AGENT_MANAGER_H__

#include <string>
#include <map>

#include "ProtocolShare.h"
#include "ProtocolSocial.h"
#include "ProtocolIAP.h"
#include "ProtocolAds.h"
#include "ProtocolUser.h"

namespace opensdk {

class ProtocolUser;
class ProtocolAnalytics;

class AgentManager{
public:
	virtual ~AgentManager();
	static AgentManager* getInstance();
	static void destroyInstance();
	virtual bool initWithConfigureFile();
	virtual bool init(std::map<std::string, std::string>& conf);
	virtual void purge();

	inline ProtocolUser* getUserPlugin()
	{
		return pUser;
	}

	inline ProtocolShare* getSharePlugin()
	{
		return pShare;
	}

	inline ProtocolSocial* getSocialPlugin()
	{
		return pSocial;
	}

	inline ProtocolAds* getAdsPlugin()
	{
		return pAds;
	}

	inline ProtocolAnalytics* getAnalyticsPlugin()
	{
		return pAnalytics;
	}

	inline ProtocolIAP* getIAPPlugin()
	{
		return pIAP;
	}

protected:
	AgentManager();
	std::map<std::string, std::string> getPluginConfigure();

	ProtocolUser *pUser;
	ProtocolShare *pShare;
	ProtocolSocial *pSocial;
	ProtocolAds *pAds;
	ProtocolAnalytics *pAnalytics;
	ProtocolIAP *pIAP;
};
} //namespace opensdk {
#endif //__OPENSDK_AGENT_MANAGER_H__
