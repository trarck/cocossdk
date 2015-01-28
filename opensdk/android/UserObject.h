#ifndef __OPENSDK_USER_OBJECT_H__
#define __OPENSDK_USER_OBJECT_H__

#include "ProtocolUser.h"
#include <map>
#include <string>

namespace opensdk {

class UserObject : public ProtocolUser
{
public:
    
    UserObject();
    
    virtual ~UserObject();

    /**
     *@brief set plugin name
     */
    virtual void setPluginName(const char* name);
    
    /**
     *@brief get plugin name
     */
    virtual const char* getPluginName();
    
    /**
    @brief config the application info
    @param devInfo This parameter is the info of aplication,
           different plugin have different format
    @warning Must invoke this interface before other interfaces.
             And invoked only once.
    */
    virtual void configDeveloperInfo(TUserDeveloperInfo devInfo);

    /**
     @brief User login
     */
    virtual void login();
    
    virtual void login(std::string server_id, std::string oauthLoginServer = "");

    /**
     @brief User logout
     */
    virtual void logout();

    /**
     @brief Check whether the user logined or not
     */
    virtual bool isLogined();
    
    virtual std::string getUserID();
    
    /**
     @brief Get session ID
     @return If user logined, return value is session ID;
             else return value is empty string.
     */
    virtual std::string getSessionID();
    
    /**
     @brief get Access Token
     */
    virtual std::string getAccessToken();

    /*
     @deprecated
     @brief set login callback function
     */
    virtual void setActionListener(UserActionListener* listener);
    
    /*
     @deprecated
     @brief get login callback function
     */
    virtual UserActionListener* getActionListener();
    
    /**
     @brief Check function the plugin support or not
     @param the name of plugin
     @return if the function support ,return true
     else retur false
     */
    virtual bool isFunctionSupported(std::string functionName);
    
    /**
     @brief get plugin id
     @return the plugin id
     */
    virtual std::string getPluginId();
    
    static std::string _serverID;
    static std::string _serverIP;
	
protected:
    std::string _pluginName;
    
    UserActionListener* _listener;
};

} // namespace opensdk {

#endif /* __OPENSDK_USER_OBJECT_H__ */
