package com.opensdk.framework;

import java.util.Hashtable;

public interface InterfaceUser {
	public final int PluginType = 5;

	public void configDeveloperInfo(Hashtable<String, String> cpInfo);
	public void login();
	public void logout();
	public boolean isLogined();
	public String getSessionID();
	public void setDebugMode(boolean debug);
	public String getSDKVersion();
	public String getPluginVersion();
}
