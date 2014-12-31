#ifndef __OPENSDK_IPLUGIN_H__
#define __OPENSDK_IPLUGIN_H__

#include "PluginParam.h"
#include <vector>

#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
    #define CC_DEPRECATED_ATTRIBUTE __attribute__((deprecated))
#elif _MSC_VER >= 1400 //vs 2005 or higher
    #define CC_DEPRECATED_ATTRIBUTE __declspec(deprecated) 
#else
    #define CC_DEPRECATED_ATTRIBUTE
#endif 

namespace opensdk {

/**
	The super class for all plugins.
*/
class PluginFactory;
class PluginProtocol
{
public:
    virtual ~PluginProtocol();

    /**
    @brief plug-in info methods(name, version, SDK version)
    */
    inline const char* getPluginName() { return _pluginName.c_str(); }
    std::string getPluginVersion();
    std::string getSDKVersion();

    /**
    @brief switch debug plug-in on/off
    */
    void setDebugMode(bool bDebug);

    /**
     * @brief methods for reflections
     */
    void callFuncWithParam(const char* funcName, PluginParam* param, ...);
    void callFuncWithParam(const char* funcName, std::vector<PluginParam*> params);

    std::string callStringFuncWithParam(const char* funcName, PluginParam* param, ...);
    std::string callStringFuncWithParam(const char* funcName, std::vector<PluginParam*> params);

    int callIntFuncWithParam(const char* funcName, PluginParam* param, ...);
    int callIntFuncWithParam(const char* funcName, std::vector<PluginParam*> params);

    bool callBoolFuncWithParam(const char* funcName, PluginParam* param, ...);
    bool callBoolFuncWithParam(const char* funcName, std::vector<PluginParam*> params);

    float callFloatFuncWithParam(const char* funcName, PluginParam* param, ...);
    float callFloatFuncWithParam(const char* funcName, std::vector<PluginParam*> params);

protected:
    PluginProtocol() {}

private:
    friend class PluginFactory;
    inline void setPluginName(const char* name) {
    	_pluginName = name;
    }
    std::string _pluginName;
};

} //namespace opensdk {

#endif /* __OPENSDK_IPLUGIN_H__ */
