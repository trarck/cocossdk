#ifndef __OPENSDK_PLUGIN_FACTORY_H__
#define __OPENSDK_PLUGIN_FACTORY_H__

namespace opensdk {

typedef enum {
	kPluginAds = 1,/**< enum value kPluginAds. */
	kPluginAnalytics,/**< enum value kPluginAnalytics. */
	kPluginIAP,/**< enum value kPluginIAP. */
	kPluginShare,/**< enum value kPluginShare. */
	kPluginUser,/**< enum value kPluginUser. */
	kPluginSocial,/**< enum value kPluginSocial. */
	kPluginPush,/**< enum value kPluginPush. */
} PluginType;
	
class PluginProtocol;
class PluginManager;

class PluginFactory
{
public:
	virtual ~PluginFactory();
	/** Get singleton of PluginFactory */
    static PluginFactory* getInstance();

    /** Destory the instance of PluginFactory */
    static void purgeFactory();

private:
    friend class PluginManager;
    PluginFactory(void);

    /** create the plugin by name */
    PluginProtocol* createPlugin(const char* name,int pluginType);
};

} //namespace opensdk {

#endif /* __OPENSDK_PLUGIN_FACTORY_H__ */
