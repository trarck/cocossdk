#ifndef  __OPENSDK_SOCIAL_OBJECT_H__
#define  __OPENSDK_SOCIAL_OBJECT_H__

#include "ProtocolSocial.h"
#include <map>
#include <string>

namespace opensdk {

class SocialObject : public ProtocolSocial
{
public:
    
    SocialObject();
    virtual ~SocialObject();

    /**
     *@brief set plugin name
     */
    virtual void setPluginName(const char* name);
    
    /**
     *@brief get plugin name
     */
    virtual const char* getPluginName();
    
    /**
    @brief config the share developer info
    @param devInfo This parameter is the info of developer,
           different plugin have different format
    @warning Must invoke this interface before other interfaces.
             And invoked only once.
    */
    virtual void configDeveloperInfo(TSocialDeveloperInfo devInfo);
    
    /**
     @brief user signIn
     */
    virtual void signIn();
    
    /**
     @brief user signOut
     */
    virtual void signOut();

    /**
     * @brief methods of leaderboard feature
     */
    virtual void submitScore(const char* leadboardID, long score);

    virtual void showLeaderboard(const char* leaderboardID);

    /**
     * @brief methods of achievement feature
     */
    virtual void unlockAchievement(TAchievementInfo achInfo);

    virtual void showAchievements();

    /*
     @deprecated
     @brief set listener
     */
    virtual void setListener(SocialListener* listener);
    /*
     @deprecated
     @brief get listener
     */
    virtual SocialListener* getListener();

protected:
    std::string _pluginName;
    SocialListener* _listener;
};

} // namespace opensdk {

#endif   /* ----- #ifndef __OPENSDK_SOCIAL_OBJECT_H__ ----- */
