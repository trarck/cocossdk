#include "PushObject.h"

namespace opensdk {

PushObject::PushObject()
{
	
}

PushObject::~PushObject()
{
	
}


void PushObject::setPluginName(const char* name)
{
	_pluginName = name;
}

const char* PushObject::getPluginName()
{
	return _pluginName.c_str();
}

void PushObject::startPush()
{
}


void PushObject::closePush()
{
}

void PushObject::setAlias(std::string alias)
{
}

void PushObject::delAlias(std::string alias)
{
}

void PushObject::setTags(std::list<std::string> tags)
{
}

void PushObject::delTags(std::list<std::string> tags)
{
}

void PushObject::setActionListener(PushActionListener* listener)
{
	_listener=listener;
}

PushActionListener* PushObject::getActionListener()
{
	return _listener;
}

} // namespace opensdk

