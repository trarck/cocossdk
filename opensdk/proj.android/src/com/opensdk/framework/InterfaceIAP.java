package com.opensdk.framework;

import java.util.Hashtable;

public interface InterfaceIAP {
	public final int PluginType = 3;

	public void configDeveloperInfo(Hashtable<String, String> cpInfo);
	public void payForProduct(Hashtable<String, String> cpInfo);
	public void setDebugMode(boolean debug);
	public String getSDKVersion();
	public String getPluginVersion();
}
