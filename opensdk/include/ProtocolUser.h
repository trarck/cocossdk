#ifndef __OPENSDK_PROTOCOL_USER_H__
#define __OPENSDK_PROTOCOL_USER_H__

#include "PluginProtocol.h"
#include <map>
#include <string>
#include <functional>

namespace opensdk {

typedef std::map<std::string, std::string> TUserDeveloperInfo;

typedef enum
{
    kLoginSucceed = 0,
    kLoginFailed,

    kLogoutSucceed,
} UserActionResultCode;

class ProtocolUser;
class UserActionListener
{
public:
    virtual void onActionResult(ProtocolUser* pPlugin, UserActionResultCode code, const char* msg) = 0;
};

class ProtocolUser : public PluginProtocol
{
public:
    ProtocolUser();
    virtual ~ProtocolUser();

    typedef std::function<void(int, std::string&)> ProtocolUserCallback;

    /**
    @brief config the application info
    @param devInfo This parameter is the info of aplication,
           different plugin have different format
    @warning Must invoke this interface before other interfaces.
             And invoked only once.
    */
    void configDeveloperInfo(TUserDeveloperInfo devInfo);

    /**
     @brief User login
     */
    void login();
    void login(ProtocolUserCallback &cb);

    /**
     @brief User logout
     */
    void logout();
    void logout(ProtocolUserCallback &cb);

    /**
     @brief Check whether the user logined or not
     */
    CC_DEPRECATED_ATTRIBUTE bool isLogined() {return isLoggedIn();}

    bool isLoggedIn();
    /**
     @brief Get session ID
     @return If user logined, return value is session ID;
             else return value is empty string.
     */
    std::string getSessionID();
    
    /**
     @brief get Access Token
     */
    std::string getAccessToken();

    /*
     @deprecated
     @brief set login callback function
     */
    CC_DEPRECATED_ATTRIBUTE inline void setActionListener(UserActionListener* listener)
    {
        _listener = listener;
    }
    /*
     @deprecated
     @brief get login callback function
     */
    CC_DEPRECATED_ATTRIBUTE inline UserActionListener* getActionListener()
    {
        return _listener;
    }

    /**
     @brief set login callback function
     */
    inline void setCallback(const ProtocolUserCallback &cb)
    {
        _callback = cb;
    }

    /**
     @brief get login callback function
     */
    inline ProtocolUserCallback& getCallback()
    {
        return _callback;
    }

protected:
    UserActionListener* _listener;
    ProtocolUserCallback _callback;
};

} // namespace opensdk {

#endif /* __OPENSDK_PROTOCOL_USER_H__ */
