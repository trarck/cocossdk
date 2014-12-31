#ifndef  __OPENSDK_PROTOCOL_SOCIAL_H__
#define  __OPENSDK_PROTOCOL_SOCIAL_H__

#include "PluginProtocol.h"
#include <map>
#include <string>
#include <functional>

namespace opensdk {

typedef std::map<std::string, std::string> TSocialDeveloperInfo;
typedef std::map<std::string, std::string> TAchievementInfo;

typedef enum
{
    // code for leaderboard feature
    SCORE_SUBMIT_SUCCESS = 1,
    SCORE_SUBMIT_FAILED,

    // code for achievement feature
    ACH_UNLOCK_SUCCESS,
    ACH_UNLOCK_FAILED,

} SocialRetCode;

class SocialListener
{
public:
    virtual void onSocialResult(SocialRetCode code, const char* msg) = 0;
};

class ProtocolSocial : public PluginProtocol
{
public:
    ProtocolSocial();
    virtual ~ProtocolSocial();

	typedef std::function<void(int, std::string&)> ProtocolSocialCallback;

    /**
    @brief config the share developer info
    @param devInfo This parameter is the info of developer,
           different plugin have different format
    @warning Must invoke this interface before other interfaces.
             And invoked only once.
    */
    void configDeveloperInfo(TSocialDeveloperInfo devInfo);

    /**
     * @brief methods of leaderboard feature
     */
    void submitScore(const char* leadboardID, long score);
    void submitScore(const char* leadboardID, long score, ProtocolSocialCallback cb);
    void showLeaderboard(const char* leaderboardID);

    /**
     * @brief methods of achievement feature
     */
    void unlockAchievement(TAchievementInfo achInfo);
    void unlockAchievement(TAchievementInfo achInfo, ProtocolSocialCallback cb);
    void showAchievements();

    /*
     @deprecated
     @brief set listener
     */
    CC_DEPRECATED_ATTRIBUTE inline void setListener(SocialListener* listener) {
        _listener = listener;
    }

    /*
     @deprecated
     @brief get listener
     */
    CC_DEPRECATED_ATTRIBUTE inline SocialListener* getListener()
    {
        return _listener;
    }

    /*
     @brief set callback function
     */
    inline void setCallback(ProtocolSocialCallback &cb)
    {
    	_callback = cb;
    }

    /*
     @brief get callback function
     */
    inline ProtocolSocialCallback& getCallback()
    {
    	return _callback;
    }

protected:
    SocialListener* _listener;
    ProtocolSocialCallback _callback;
};

} // namespace opensdk {

#endif   /* ----- #ifndef __OPENSDK_PROTOCOL_SOCIAL_H__ ----- */
