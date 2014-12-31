#ifndef __OPENSDK_PROTOCOL_ADS_H__
#define __OPENSDK_PROTOCOL_ADS_H__

#include "PluginProtocol.h"
#include <map>
#include <string>

namespace opensdk {

typedef std::map<std::string, std::string> TAdsDeveloperInfo;
typedef std::map<std::string, std::string> TAdsInfo;

typedef enum
{
    kAdsReceived = 0,            // The ad is received

    kAdsShown,                  // The advertisement shown
    kAdsDismissed,              // The advertisement dismissed

    kPointsSpendSucceed,        // The points spend succeed
    kPointsSpendFailed,         // The points spend failed

    kNetworkError,              // Network error
    kUnknownError,              // Unknown error
} AdsResultCode;

class ProtocolAds;
class AdsListener
{
public:
    /**
    @brief The advertisement request result
    */
    virtual void onAdsResult(AdsResultCode code, const char* msg) = 0;
    
    /**
    @brief Player get points from advertisement(For example: Tapjoy)
    @param points The point number player has got.
    @param pAdsPlugin  The plugin which the player get points. Used to spend the points.
    */
    virtual void onPlayerGetPoints(ProtocolAds* pAdsPlugin, int points) {}
};

class ProtocolAds : public PluginProtocol
{
public:
	ProtocolAds();
	virtual ~ProtocolAds();

    typedef enum {
        kPosCenter = 0,
        kPosTop,
        kPosTopLeft,
        kPosTopRight,
        kPosBottom,
        kPosBottomLeft,
        kPosBottomRight,
    } AdsPos;

    /**
    @brief config the application info
    @param devInfo This parameter is the info of aplication,
           different plugin have different format
    @warning Must invoke this interface before other interfaces.
             And invoked only once.
    */
    void configDeveloperInfo(TAdsDeveloperInfo devInfo);

    /**
    @brief show adview
    @param info The information of adview will be shown
                Pay attention to the subclass definition
    @param pos The position where the adview be shown.
    */
    void showAds(TAdsInfo info, AdsPos pos = kPosCenter);

    /**
    @brief Hide the adview
    @param info The information of adview will be hided
    */
    void hideAds(TAdsInfo info);

    /**
    @brief Query the points of player
    */
    void queryPoints();

    /**
    @brief Spend the points.
           Use this method to notify server spend points.
    @param points Need spend number of points
    */
    void spendPoints(int points);

    /**
     @deprecated
     @brief set the Ads listener
    */
    inline void setAdsListener(AdsListener* listener)
    {
        _listener = listener;
    }

    /**
     @deprecated
     @brief set the Ads listener
    */
    inline AdsListener* getAdsListener()
    {
        return _listener;
    }

   
protected:
    AdsListener* _listener;

};

} // namespace opensdk {

#endif /* __OPENSDK_PROTOCOL_ADS_H__ */
