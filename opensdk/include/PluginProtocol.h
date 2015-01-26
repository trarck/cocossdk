#ifndef __OPENSDK_IPLUGIN_H__
#define __OPENSDK_IPLUGIN_H__

#include "PluginParam.h"
#include <vector>

namespace opensdk {

/**
 *@brief The super class for all plugins.
 */

class PluginProtocol
{
public:
    virtual ~PluginProtocol();

    virtual void setPluginName(const char* name) = 0;
	
    /**
     *@brief get plugin name
     */
    virtual const char* getPluginName() =0;
	
   /**
    *@brief get plugin version
    */
    virtual std::string getPluginVersion();
	
   /**
    *@brief get sdk name
    */
    virtual std::string getSDKVersion();

    /**
    @brief switch debug plug-in on/off
    */
    virtual void setDebugMode(bool bDebug);

    /**
     * @brief methods for reflections
     */
    virtual void callFuncWithParam(const char* funcName, PluginParam* param, ...);
    virtual void callFuncWithParam(const char* funcName, std::vector<PluginParam*> params);

    virtual std::string callStringFuncWithParam(const char* funcName, PluginParam* param, ...);
    virtual std::string callStringFuncWithParam(const char* funcName, std::vector<PluginParam*> params);

    virtual int callIntFuncWithParam(const char* funcName, PluginParam* param, ...);
    virtual int callIntFuncWithParam(const char* funcName, std::vector<PluginParam*> params);

    virtual bool callBoolFuncWithParam(const char* funcName, PluginParam* param, ...);
    virtual bool callBoolFuncWithParam(const char* funcName, std::vector<PluginParam*> params);

    virtual float callFloatFuncWithParam(const char* funcName, PluginParam* param, ...);
    virtual float callFloatFuncWithParam(const char* funcName, std::vector<PluginParam*> params);

};

} //namespace opensdk {

#endif /* __OPENSDK_IPLUGIN_H__ */
