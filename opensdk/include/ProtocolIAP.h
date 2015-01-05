#ifndef __OPENSDK_PROTOCOL_IAP_H__
#define __OPENSDK_PROTOCOL_IAP_H__

#include "PluginProtocol.h"
#include <map>
#include <string>

namespace opensdk {

typedef std::map<std::string, std::string> TIAPDeveloperInfo;
typedef std::map<std::string, std::string> TProductInfo;
typedef std::vector<TProductInfo> TProductList;
typedef enum 
{
    kPaySuccess = 0,
    kPayFail,
    kPayCancel,
    kPayTimeOut,
} PayResultCode;
    
typedef enum {
    RequestSuccees=0,
    RequestFail,
    RequestTimeout,
} IAPProductRequest;

class PayResultListener
{
public:
    virtual void onPayResult(PayResultCode ret, const char* msg, TProductInfo info) = 0;
    virtual void onRequestProductsResult(IAPProductRequest ret, TProductList info){}
};

class ProtocolIAP : public PluginProtocol
{
public:
	ProtocolIAP();
	virtual ~ProtocolIAP();

    /**
    @brief config the developer info
    @param devInfo This parameter is the info of developer,
           different plugin have different format
    @warning Must invoke this interface before other interfaces.
             And invoked only once.
    */
    void configDeveloperInfo(TIAPDeveloperInfo devInfo);

    /**
    @brief pay for product
    @param info The info of product, must contains key:
            productName         The name of product
            productPrice        The price of product(must can be parse to float)
            productDesc         The description of product
    @warning For different plugin, the parameter should have other keys to pay.
             Look at the manual of plugins.
    */
    void payForProduct(TProductInfo info);

    /**
    @deprecated
    @breif set the result listener
    @param pListener The callback object for pay result
    @wraning Must invoke this interface before payForProduct.
    */
    void setResultListener(PayResultListener* pListener);
    
    /**
    @deprecated
    @breif get the result listener
    */
    inline PayResultListener* getResultListener()
    {
        return _listener;
    }
    
    /**
    @brief pay result callback
    */
    void onPayResult(PayResultCode ret, const char* msg);


protected:
    static bool _paying;

    TProductInfo _curInfo;
    PayResultListener* _listener;
};

} // namespace opensdk {

#endif /* __OPENSDK_PROTOCOL_IAP_H__ */
