#include "PluginProtocol.h"
#include "PluginUtilsAndroid.h"

#define LOG_TAG     "PluginProtocol"

namespace opensdk {

PluginProtocol::~PluginProtocol()
{
    PluginUtilsAndroid::erasePluginJavaData(this);
}

std::string PluginProtocol::getPluginVersion()
{
    return PluginUtilsAndroid::callJavaStringFuncWithName(this, "getPluginVersion");
}

std::string PluginProtocol::getSDKVersion()
{
    return PluginUtilsAndroid::callJavaStringFuncWithName(this, "getSDKVersion");
}

void PluginProtocol::setDebugMode(bool isDebugMode)
{
    PluginUtilsAndroid::callJavaFunctionWithName_oneParam(this, "setDebugMode", "(Z)V", isDebugMode);
}

void PluginProtocol::callFuncWithParam(const char* funcName, PluginParam* param, ...)
{
    std::vector<PluginParam*> allParams;
    if (NULL != param)
    {
        allParams.push_back(param);

        va_list argp;
        PluginParam* pArg = NULL;
        va_start( argp, param );
        while (1)
        {
            pArg = va_arg(argp, PluginParam*);
            if (pArg == NULL)
                break;

            allParams.push_back(pArg);
        }
        va_end(argp);
    }

    callFuncWithParam(funcName, allParams);
}

void PluginProtocol::callFuncWithParam(const char* funcName, std::vector<PluginParam*> params)
{
    PluginJavaData* pData = PluginUtilsAndroid::getPluginJavaData(this);
    if (NULL == pData) {
        PluginUtilsAndroid::outputLog(LOG_TAG, "Can't find java data for plugin : %s", this->getPluginName());
        return;
    }

    int nParamNum = params.size();
    if (nParamNum == 0)
    {
        PluginUtilsAndroid::callJavaFunctionWithName(this, funcName);
    } else
    {
        PluginParam* pRetParam = NULL;
        bool needDel = false;
        if (nParamNum == 1) {
            pRetParam = params[0];
        } else {
            std::map<std::string, PluginParam*> allParams;
            for (int i = 0; i < nParamNum; i++)
            {
                PluginParam* pArg = params[i];
                if (pArg == NULL)
                {
                    break;
                }

                char strKey[8] = { 0 };
                sprintf(strKey, "Param%d", i + 1);
                allParams[strKey] = pArg;
            }

            pRetParam = new PluginParam(allParams);
            needDel = true;
        }

        switch(pRetParam->getCurrentType())
        {
        case PluginParam::kParamTypeInt:
            PluginUtilsAndroid::callJavaFunctionWithName_oneParam(this, funcName, "(I)V", pRetParam->getIntValue());
            break;
        case PluginParam::kParamTypeFloat:
            PluginUtilsAndroid::callJavaFunctionWithName_oneParam(this, funcName, "(F)V", pRetParam->getFloatValue());
            break;
        case PluginParam::kParamTypeBool:
            PluginUtilsAndroid::callJavaFunctionWithName_oneParam(this, funcName, "(Z)V", pRetParam->getBoolValue());
            break;
        case PluginParam::kParamTypeString:
            {
                jstring jstr = PluginUtilsAndroid::getEnv()->NewStringUTF(pRetParam->getStringValue());
                PluginUtilsAndroid::callJavaFunctionWithName_oneParam(this, funcName, "(Ljava/lang/String;)V", jstr);
                PluginUtilsAndroid::getEnv()->DeleteLocalRef(jstr);
            }
            break;
        case PluginParam::kParamTypeStringMap:
        case PluginParam::kParamTypeMap:
            {
                jobject jMap = PluginUtilsAndroid::getJObjFromParam(pRetParam);
                PluginUtilsAndroid::callJavaFunctionWithName_oneParam(this, funcName, "(Lorg/json/JSONObject;)V", jMap);
                PluginUtilsAndroid::getEnv()->DeleteLocalRef(jMap);
            }
            break;
        default:
            break;
        }

        if (needDel && pRetParam != NULL)
        {
            delete pRetParam;
            pRetParam = NULL;
        }
    }
}

std::string PluginProtocol::callStringFuncWithParam(const char* funcName, PluginParam* param, ...)
{
    CALL_JAVA_FUNC_WITH_VALIST(String)
}

std::string PluginProtocol::callStringFuncWithParam(const char* funcName, std::vector<PluginParam*> params)
{
    CALL_JAVA_FUNC(std::string, String, "", "Ljava/lang/String;")
}

int PluginProtocol::callIntFuncWithParam(const char* funcName, PluginParam* param, ...)
{
    CALL_JAVA_FUNC_WITH_VALIST(Int)
}

int PluginProtocol::callIntFuncWithParam(const char* funcName, std::vector<PluginParam*> params)
{
    CALL_JAVA_FUNC(int, Int, 0, "I")
}

bool PluginProtocol::callBoolFuncWithParam(const char* funcName, PluginParam* param, ...)
{
    CALL_JAVA_FUNC_WITH_VALIST(Bool)
}

bool PluginProtocol::callBoolFuncWithParam(const char* funcName, std::vector<PluginParam*> params)
{
    CALL_JAVA_FUNC(bool, Bool, false, "Z")
}

float PluginProtocol::callFloatFuncWithParam(const char* funcName, PluginParam* param, ...)
{
    CALL_JAVA_FUNC_WITH_VALIST(Float)
}

float PluginProtocol::callFloatFuncWithParam(const char* funcName, std::vector<PluginParam*> params)
{
    CALL_JAVA_FUNC(float, Float, 0.0f, "F")
}

} //namespace opensdk {
