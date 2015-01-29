package com.opensdk.framework;

import android.content.Context;
import android.content.res.Resources;
import android.util.Log;
import android.widget.ImageView;
import android.widget.PopupWindow;
import org.json.JSONObject;

public class AdsDebug
  implements InterfaceAds
{
  private static Context mContext = null;
  protected static String TAG = "AdsDebug";
  private static AdsDebug mAdapter = null;
  private static boolean isDebug = true;
  private static PopupWindow popupWindow = null;
  private ImageView imageView = null;

  protected static void LogE(String paramString, Exception paramException)
  {
    Log.e(TAG, paramString, paramException);
    paramException.printStackTrace();
  }

  protected static void LogD(String paramString)
  {
    if (isDebug)
      Log.d(TAG, paramString);
  }

  public AdsDebug(Context paramContext)
  {
    mContext = paramContext;
    mAdapter = this;
  }

  public float queryPoints()
  {
    LogD("debug not support query points");
    return 0.0F;
  }

  public void spendPoints(int paramInt)
  {
    LogD("debug not support spend points");
  }

  public void setDebugMode(boolean paramBoolean)
  {
    isDebug = paramBoolean;
  }

  public String getSDKVersion()
  {
    return "2.0.3";
  }

  public String getPluginVersion()
  {
    return "2.0.3";
  }

  public static void showDialog(String paramString1, String paramString2)
  {
    PluginWrapper.runOnMainThread(new AdsDebug.1(paramString1, paramString2));
  }

  public static int getResourceId(String paramString1, String paramString2)
  {
    return mContext.getResources().getIdentifier(paramString1, paramString2, mContext.getPackageName());
  }

  public boolean isAdTypeSupported(int paramInt)
  {
    return true;
  }

  public void showAds(JSONObject paramJSONObject)
  {
    LogD("showAds " + paramJSONObject.toString() + "invoked!");
    PluginWrapper.runOnMainThread(new AdsDebug.2(this));
  }

  public void hideAds(JSONObject paramJSONObject)
  {
    LogD("hideAds " + paramJSONObject.toString() + "invoked!");
    PluginWrapper.runOnMainThread(new AdsDebug.3(this));
  }

  public void preloadAds(JSONObject paramJSONObject)
  {
    LogD("debug not support preloadAds");
  }
}

/* Location:           /Users/duanhouhai/Develops/anysdk-src/framework/cpp/libPluginProtocol.jar
 * Qualified Name:     com.anysdk.framework.AdsDebug
 * JD-Core Version:    0.6.2
 */