package com.opensdk.framework;

import java.util.ArrayList;

public abstract interface InterfacePush
{
  public static final int PluginType = 7;

  public abstract void startPush();

  public abstract void closePush();

  public abstract void setAlias(String alias);

  public abstract void delAlias(String alias);

  public abstract void setTags(ArrayList<String> tags);

  public abstract void delTags(ArrayList<String> tags);

  public abstract void setDebugMode(boolean value);

  public abstract String getSDKVersion();

  public abstract String getPluginVersion();
}