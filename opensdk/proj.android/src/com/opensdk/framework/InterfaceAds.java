package com.opensdk.framework;

import java.util.Hashtable;

public interface InterfaceAds {

	public static final int PluginType = 1;

	public void configDeveloperInfo(Hashtable<String, String> devInfo);
	public void showAds(Hashtable<String, String> adsInfo, int pos);
	public void hideAds(Hashtable<String, String> adsInfo);
	public void queryPoints();
	public void spendPoints(int points);
	public void setDebugMode(boolean debug);
	public String getSDKVersion();
	public String getPluginVersion();
}
