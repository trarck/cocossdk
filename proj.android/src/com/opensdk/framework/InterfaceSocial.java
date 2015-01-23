package com.opensdk.framework;

import java.util.Hashtable;

public interface InterfaceSocial {
    public final int PluginType = 6;

    public void configDeveloperInfo(Hashtable<String, String> cpInfo);
    public void submitScore(String leaderboardID, long score);
    public void showLeaderboard(String leaderboardID);
    public void unlockAchievement(Hashtable<String, String> achInfo);
    public void showAchievements();
    public void setDebugMode(boolean debug);
    public String getSDKVersion();
    public String getPluginVersion();
}