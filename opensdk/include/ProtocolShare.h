#ifndef  __OPENSDK_PROTOCOL_SHARE_H__
#define  __OPENSDK_PROTOCOL_SHARE_H__

#include "PluginProtocol.h"
#include <map>
#include <string>
#include <functional>

namespace opensdk {

typedef std::map<std::string, std::string> TShareDeveloperInfo;
typedef std::map<std::string, std::string> TShareInfo;

typedef enum 
{
    kShareSuccess = 0,
    kShareFail,
    kShareCancel,
    kShareTimeOut,
} ShareResultCode;

class ShareResultListener
{
public:
    virtual void onShareResult(ShareResultCode ret, const char* msg) = 0;
};

class ProtocolShare : public PluginProtocol
{
public:
	ProtocolShare();
	virtual ~ProtocolShare();
    
    typedef std::function<void(int, std::string&)> ProtocolShareCallback;

    /**
    @brief config the share developer info
    @param devInfo This parameter is the info of developer,
           different plugin have different format
    @warning Must invoke this interface before other interfaces.
             And invoked only once.
    */
    void configDeveloperInfo(TShareDeveloperInfo devInfo);

    /**
    @brief share information
    @param info The info of share, contains key:
            SharedText                	The text need to share
            SharedImagePath				The full path of image file need to share (optinal)
    @warning For different plugin, the parameter should have other keys to share.
             Look at the manual of plugins.
    */
    void share(TShareInfo info);
    void share(TShareInfo &info, ProtocolShareCallback &cb);

    /**
    @deprecated
    @breif set the result listener
    @param pListener The callback object for share result
    @wraning Must invoke this interface before share
    */
    CC_DEPRECATED_ATTRIBUTE void setResultListener(ShareResultListener* pListener);
    
    /**
     @deprecated
     @breif get the result listener
     @return The callback object for share result
     @wraning Must invoke this interface before share
     */
    CC_DEPRECATED_ATTRIBUTE ShareResultListener* getResultListener();
    
    /**
     @brief set login callback function
     */
    inline void setCallback(const ProtocolShareCallback &cb)
    {
        _callback = cb;
    }
    
    /**
     @brief get login callback function
     */
    inline ProtocolShareCallback getCallback()
    {
        return _callback;
    }

    /**
    @brief share result callback
    */
    void onShareResult(ShareResultCode ret, const char* msg);

protected:
    ShareResultListener* _listener;
    ProtocolShareCallback _callback;
};

} // namespace opensdk {

#endif   /* ----- #ifndef __OPENSDK_PROTOCOL_SHARE_H__ ----- */
