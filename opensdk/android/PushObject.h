#ifndef __OPENSDK_PUSH_OBJECT_H__
#define __OPENSDK_PUSH_OBJECT_H__

#include "ProtocolPush.h"
#include <map>
#include <list>
#include <string>

namespace opensdk {
    
typedef struct
{
    PushActionResultCode resultCode;
    std::string msg;
} PushActionResult;
    
/**   
 *  @class  ProtocolPush  
 */
class PushObject : public ProtocolPush
{
public:

	PushObject();
	
	virtual ~PushObject();
	
    /**
    *@brief set plugin name
    */
    virtual void setPluginName(const char* name);
	
    /**
     *@brief get plugin name
     */
    virtual const char* getPluginName();
	
    /**
     *@brief start/register  Push services
     *@return void
     */
    virtual  void startPush();


    /**
     *@brief close Push services
     *@return void
     */
    virtual void closePush();


    /**
     *@brief set alias
     *@param tags
     *@return void
     */
    virtual void setAlias(const std::string& alias);

    /**
     *@brief del alias
     *@param tags
     *@return void
     */
    virtual void delAlias(const std::string& alias);

    /**
     *@brief set tag
     *@param tags
     *@return void
     */
    virtual void setTags(const std::list<std::string>& tags);

    /**
     *@brief delete tag
     *@param tags
     *@return void
     */
    virtual void delTags(const std::list<std::string>& tags);

    /**
     @brief set the result listener
     @param pListener The callback object for push result
     */
    virtual void setActionListener(PushActionListener* listener);

    /**
     @brief get pListener The callback object for Push result
     @return the listener
     */
    virtual  PushActionListener* getActionListener();

protected:
	std::string _pluginName;
	PushActionListener* _listener;
    
    std::vector<PushActionResult> _actionResultList;

};

} // namespace opensdk

#endif /* __OPENSDK_PUSH_OBJECT_H__ */
