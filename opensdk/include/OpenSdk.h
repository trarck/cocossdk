#ifndef __OPENSDK_OPENSDK_H__
#define __OPENSDK_OPENSDK_H__

namespace opensdk {

class OpenSdkListener
{
public:
    virtual void onInitPlugins() = 0;
};

class OpenSdk
{
public:
    virtual ~OpenSdk();

	static OpenSdk* getInstance();
	static void destroyInstance();

	void onInitPlugins();

	void setListener(OpenSdkListener* pListener);
    
    inline OpenSdkListener* getListener()
    {
        return _listener;
    }

private:
	OpenSdkListener* _listener;
};

} //namespace opensdk {

#endif /* __OPENSDK_OPENSDK_H__ */
