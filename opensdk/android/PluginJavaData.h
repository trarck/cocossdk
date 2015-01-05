#ifndef __PLUGIN_JAVA_DATA_H__
#define __PLUGIN_JAVA_DATA_H__

#include <string>
#include <jni.h>

namespace opensdk {

typedef struct _PluginJavaData_
{
	jobject jobj;
	std::string  jclassName;
} PluginJavaData;

} //namespace opensdk {

#endif // __PLUGIN_JAVA_DATA_H__
