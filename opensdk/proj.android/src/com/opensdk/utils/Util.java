package com.opensdk.utils;

import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.res.Configuration;
import android.content.res.Resources;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Build;
import android.os.Build.VERSION;
import android.provider.Settings.Secure;
import android.telephony.TelephonyManager;
import android.util.Base64;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Display;
import android.view.WindowManager;
import com.anysdk.framework.UserWrapper;
import com.anysdk.framework.Wrapper;
import java.io.UnsupportedEncodingException;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.net.URLDecoder;
import java.net.URLEncoder;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.List;
import java.util.Locale;
import java.util.Set;
import org.apache.http.conn.util.InetAddressUtils;
import org.apache.http.message.BasicNameValuePair;
import org.json.JSONObject;

public class Util
{
  private static SdkHttpTask sSdkHttpTask = null;

  private static String SHA1(String str)
  {
    try
    {
      MessageDigest messageDigest = MessageDigest.getInstance("SHA-1");
//      byte[] _tmp = new byte[40];
      messageDigest.update(str.getBytes("UTF-8"), 0, str.length());
      return convertToHex(messageDigest.digest());
    }
    catch (Exception localException)
    {
    }
    return null;
  }

  public static Hashtable<String, String> addData(Context context, Hashtable<String, String> data)
  {
	  data.put("imei", getIMEI(context));
	  data.put("ost", getOst(context));
	  data.put("gps", getGPS(context));
	  data.put("dt", getDt());
	  data.put("osv", getOsv());
	  data.put("jb", getJb());
	  data.put("sr", getSr(context));
    data.put("ori", getOri(context));
    data.put("net", getNet(context));
    data.put("appv", getAppv(context));
    data.put("os", getDevice());
    data.put("cc", getCc());
    data.put("lang", getLang());
    data.put("sdk", getSDK());
    data.put("ckid", getCkid(context));
    data.put("wmac", getMACAddress(context));
    data.put("isp", getIsp(context));
    String imsi;
    String phoneNum;
    String ip;
    if(getIMSI(context) == null)
    	imsi = "";
    else
    	imsi = getIMSI(context);
    
    data.put("imsi", imsi);
    
    if(getPhoneNum(context) == null)
    	phoneNum = "";
    else
    	phoneNum = getPhoneNum(context);
    data.put("phonenum", phoneNum);
    
    if(getIP() == null)
    	ip = "";
    else
    	ip = getIP();
    data.put("ip", ip);
    return data;
  }

  public static String ckDecode(String str)
  {
      if(str == null)
          return null;
      byte bytes[] = URLDecoder.decode(str).getBytes();
      byte left;
      if(bytes.length % 2 == 0)
    	  left = 5;
      else
    	  left = 4;
      for(int i=0;i<bytes.length - left;i+=2){
    	  byte tmp = bytes[i];
    	  bytes[i] = bytes[i + 1];
    	  bytes[i + 1] = tmp;
      }
      
      byte binaryBytes[]=Base64.decode(bytes, 0);
      return new String(binaryBytes);
  }

  public static String ckEncode(String str)
  {
	  byte bytes[] = str.getBytes();
      byte left;
      if(bytes.length % 2 == 0)
    	  left = 5;
      else
    	  left = 4;
      
      for(int i=0;i<bytes.length - left;i+=2){
    	  byte tmp = bytes[i];
          bytes[i] = bytes[i + 1];
          bytes[i + 1] = tmp;
      }
  }

  private static String convertToHex(byte[] paramArrayOfByte)
  {
    StringBuffer localStringBuffer = new StringBuffer();
    int i = 0;
    if (i >= paramArrayOfByte.length)
      return localStringBuffer.toString();
    int j = 0xF & paramArrayOfByte[i] >>> 4;
    int m;
    label94: for (int k = 0; ; k = m)
    {
      if ((j >= 0) && (j <= 9))
        localStringBuffer.append((char)(j + 48));
      while (true)
      {
        j = 0xF & paramArrayOfByte[i];
        m = k + 1;
        if (k < 1)
          break label94;
        i++;
        break;
        localStringBuffer.append((char)(97 + (j - 10)));
      }
    }
  }

  public static void getAccessToken(Context context, Hashtable<String, String> paramHashtable, SdkHttpListener paramSdkHttpListener)
  {
    try
    {
      String str1 = (String)paramHashtable.get("server_url");
      paramHashtable.remove("server_url");
      paramHashtable.put("private_key", (String)Wrapper.getDeveloperInfo().get("private_key"));
      paramHashtable.put("server_id", UserWrapper.getLoginServerId());
      ArrayList localArrayList = new ArrayList();
      Iterator localIterator = paramHashtable.keySet().iterator();
      while (true)
      {
        if (!localIterator.hasNext())
        {
          sSdkHttpTask = new SdkHttpTask(context);
          sSdkHttpTask.doPost(new SdkHttpListener()
          {
            public void onError()
            {
              Util.this.onError();
              Util.sSdkHttpTask = null;
            }

            public void onResponse(String paramAnonymousString)
            {
              Util.this.onResponse(paramAnonymousString);
              Util.sSdkHttpTask = null;
            }
          }
          , localArrayList, str1, 60000);
          return;
        }
        String str2 = (String)localIterator.next();
        localArrayList.add(new BasicNameValuePair(str2, (String)paramHashtable.get(str2)));
      }
    }
    catch (Exception localException)
    {
      localException.printStackTrace();
      paramSdkHttpListener.onError();
    }
  }

  public static String getAppv(Context context)
  {
    PackageInfo localPackageInfo = getPackageInfo(context);
    if (localPackageInfo == null)
      return "";
    Log.d("test", localPackageInfo.versionName);
    return localPackageInfo.versionName;
  }

  public static String getCc()
  {
    String str = Locale.getDefault().getCountry();
    if (("".equals(str)) || (str == null))
      str = "";
    return str;
  }

  public static String getCkid(Context context)
  {
    return getODIN1(context);
  }

  public static String getDevice()
  {
    new Build();
    if (("".equals(Build.MODEL)) || (Build.MODEL == null))
      return "";
    return Build.MODEL;
  }

  public static String getDt()
  {
    return "Android";
  }

  public static String getGPS(Context context)
  {
    return "0,0";
  }

  public static String getIMEI(Context context)
  {
    String str2;
    if (context == null)
      str2 = null;
    String str1;
    while (true)
    {
      return str2;
      str1 = "";
      try
      {
        str1 = ((TelephonyManager)context.getSystemService("phone")).getDeviceId();
        if (("".equals(str1)) || (str1 == null))
        {
          str2 = getODIN1(context);
          boolean bool = "".equals(str2);
          if ((!bool) && (str2 != null))
            continue;
          return "";
        }
      }
      catch (Exception localException)
      {
        localException.printStackTrace();
      }
    }
    return str1;
  }

  public static String getIMSI(Context context)
  {
    try
    {
      String str = ((TelephonyManager)context.getSystemService("phone")).getSubscriberId();
      return str;
    }
    catch (Exception localException)
    {
      localException.printStackTrace();
    }
    return "";
  }

  public static String getIP()
  {
    try
    {
      String str;
      boolean bool2;
      do
      {
        InetAddress localInetAddress;
        do
        {
          Iterator localIterator1 = Collections.list(NetworkInterface.getNetworkInterfaces()).iterator();
          Iterator localIterator2;
          while (!localIterator2.hasNext())
          {
            boolean bool1 = localIterator1.hasNext();
            if (!bool1)
              return "1.1.1.1";
            localIterator2 = Collections.list(((NetworkInterface)localIterator1.next()).getInetAddresses()).iterator();
          }
          localInetAddress = (InetAddress)localIterator2.next();
        }
        while (localInetAddress.isLoopbackAddress());
        str = localInetAddress.getHostAddress();
        bool2 = InetAddressUtils.isIPv4Address(str);
      }
      while (!bool2);
      return str;
    }
    catch (SocketException localSocketException)
    {
    }
    return "1.1.1.1";
  }

  public static String getIsp(Context context)
  {
    TelephonyManager localTelephonyManager = (TelephonyManager)context.getSystemService("phone");
    if (("".equals(localTelephonyManager.getSimOperator())) || (localTelephonyManager.getSimOperator() == null))
      return "";
    return localTelephonyManager.getSimOperator();
  }

  public static String getJb()
  {
    return "0";
  }

  public static String getLang()
  {
    String str = Locale.getDefault().getLanguage();
    if (("".equals(str)) || (str == null))
      str = "";
    return str;
  }

  public static String getMACAddress(Context context)
  {
    if (context == null)
      return null;
    String str = ((WifiManager)context.getSystemService("wifi")).getConnectionInfo().getMacAddress();
    if (("".equals(str)) || (str == null))
      return "";
    return str.replace(":", "");
  }

  public static String getMd5(String paramString)
  {
    try
    {
      byte[] arrayOfByte = MessageDigest.getInstance("MD5").digest(paramString.getBytes("UTF-8"));
      StringBuffer localStringBuffer = new StringBuffer();
      for (int i = 0; ; i++)
      {
        if (i >= arrayOfByte.length)
          return localStringBuffer.toString();
        int j = 0xFF & arrayOfByte[i];
        if (j < 16)
          localStringBuffer.append("0");
        localStringBuffer.append(Integer.toHexString(j));
      }
    }
    catch (NoSuchAlgorithmException localNoSuchAlgorithmException)
    {
      localNoSuchAlgorithmException.printStackTrace();
      return paramString;
    }
    catch (UnsupportedEncodingException localUnsupportedEncodingException)
    {
      localUnsupportedEncodingException.printStackTrace();
    }
    return paramString;
  }

  public static String getNet(Context context)
  {
    try
    {
      NetworkInfo localNetworkInfo = ((ConnectivityManager)context.getSystemService("connectivity")).getActiveNetworkInfo();
      int i = localNetworkInfo.getType();
      if (i == 0)
      {
        boolean bool = localNetworkInfo.getExtraInfo().toLowerCase().equals("cmnet");
        if (bool)
          return "2";
        return "3";
      }
      if (i == 1)
        return "1";
      return "4";
    }
    catch (Exception localException)
    {
    }
    return "4";
  }

  private static String getODIN1(Context context)
  {
    return SHA1(Settings.Secure.getString(context.getContentResolver(), "android_id"));
  }

  public static String getOri(Context context)
  {
    if (context.getResources().getConfiguration().orientation == 1)
      return "3";
    if (context.getResources().getConfiguration().orientation == 1)
      return "1";
    return "0";
  }

  public static String getOst(Context context)
  {
    if ("000000000000000".equalsIgnoreCase(((TelephonyManager)context.getSystemService("phone")).getDeviceId()))
      return "5";
    return "2";
  }

  public static String getOsv()
  {
    String str = Build.VERSION.RELEASE;
    if (("".equals(str)) || (str == null))
      str = "";
    return str;
  }

  public static PackageInfo getPackageInfo(Context context)
  {
    PackageManager localPackageManager = context.getPackageManager();
    try
    {
      PackageInfo localPackageInfo = localPackageManager.getPackageInfo(context.getPackageName(), 0);
      return localPackageInfo;
    }
    catch (PackageManager.NameNotFoundException localNameNotFoundException)
    {
      localNameNotFoundException.printStackTrace();
    }
    return null;
  }

  public static void getPayOrderId(Context context, Hashtable<String, String> paramHashtable, SdkHttpListener paramSdkHttpListener)
  {
    try
    {
      paramHashtable.remove("uapi_secret");
      String str1 = Base64.encodeToString(new JSONObject(paramHashtable).toString().getBytes(), 2);
      String[] arrayOfString = new String[paramHashtable.size()];
      Object[] arrayOfObject = paramHashtable.keySet().toArray();
      int i = 0;
      StringBuffer localStringBuffer;
      if (i >= arrayOfObject.length)
      {
        Arrays.sort(arrayOfString);
        localStringBuffer = new StringBuffer();
      }
      for (int j = 0; ; j++)
      {
        if (j >= arrayOfString.length)
        {
          String str2 = getMd5(localStringBuffer.toString() + (String)Wrapper.getDeveloperInfo().get("private_key"));
          ArrayList localArrayList = new ArrayList();
          localArrayList.add(new BasicNameValuePair("token", str2));
          localArrayList.add(new BasicNameValuePair("json_data", str1));
          localArrayList.add(new BasicNameValuePair("flag", "custom"));
          sSdkHttpTask = new SdkHttpTask(context);
          if ((Wrapper.getDeveloperInfo().containsKey("order_url")) && (!((String)Wrapper.getDeveloperInfo().get("order_url")).isEmpty()))
            Config.SERVER_URL_GET_ORDER = (String)Wrapper.getDeveloperInfo().get("order_url");
          Log.d("SERVER_URL_GET_ORDER", Config.SERVER_URL_GET_ORDER);
          sSdkHttpTask.doPost(new SdkHttpListener()
          {
            public void onError()
            {
              Util.this.onError();
              Util.sSdkHttpTask = null;
            }

            public void onResponse(String paramAnonymousString)
            {
              Util.this.onResponse(paramAnonymousString);
              Util.sSdkHttpTask = null;
            }
          }
          , localArrayList, Config.SERVER_URL_GET_ORDER, 60000);
          return;
          arrayOfString[i] = arrayOfObject[i].toString();
          i++;
          break;
        }
        localStringBuffer.append((String)paramHashtable.get(arrayOfString[j]));
      }
    }
    catch (Exception localException)
    {
      localException.printStackTrace();
      paramSdkHttpListener.onError();
    }
  }

  public static String getPhoneNum(Context context)
  {
    try
    {
      String str = ((TelephonyManager)context.getSystemService("phone")).getLine1Number();
      return str;
    }
    catch (Exception localException)
    {
      localException.printStackTrace();
    }
    return "";
  }

  public static String getSDK()
  {
    return "0.1C2013031201";
  }

  public static String getSr(Context context)
  {
    DisplayMetrics localDisplayMetrics = new DisplayMetrics();
    ((Activity)context).getWindowManager().getDefaultDisplay().getMetrics(localDisplayMetrics);
    return localDisplayMetrics.widthPixels + "," + localDisplayMetrics.heightPixels;
  }

  private static String getToken(String paramString1, String paramString2)
  {
    long l = System.currentTimeMillis() / 1000L;
    String str = getMd5(l + paramString1 + paramString2).substring(0, 16);
    return Base64.encodeToString((paramString1 + "." + str + "." + l).trim().getBytes(), 2);
  }

  public static String pluginDecode(String paramString)
  {
    return new String(Base64.decode(ckDecode(paramString), 0));
  }

  public static void pluginHttp(Context context, Hashtable<String, String> paramHashtable, SdkHttpListener paramSdkHttpListener)
  {
    try
    {
      String str1 = (String)paramHashtable.get("server_url");
      paramHashtable.remove("server_url");
      ArrayList localArrayList = new ArrayList();
      Iterator localIterator = paramHashtable.keySet().iterator();
      while (true)
      {
        if (!localIterator.hasNext())
        {
          sSdkHttpTask = new SdkHttpTask(context);
          sSdkHttpTask.doPost(new SdkHttpListener()
          {
            public void onError()
            {
              Util.this.onError();
              Util.sSdkHttpTask = null;
            }

            public void onResponse(String paramAnonymousString)
            {
              Util.this.onResponse(paramAnonymousString);
              Util.sSdkHttpTask = null;
            }
          }
          , localArrayList, str1, 60000);
          return;
        }
        String str2 = (String)localIterator.next();
        localArrayList.add(new BasicNameValuePair(str2, (String)paramHashtable.get(str2)));
      }
    }
    catch (Exception localException)
    {
      localException.printStackTrace();
      paramSdkHttpListener.onError();
    }
  }

  public static void setPackage(String paramString)
  {
    if ((!Wrapper.getChannelId().equals("999999")) && (Wrapper.getDeveloperInfo().containsKey("privateKey")) && (!paramString.equals(Wrapper.getDeveloperInfo().get("privateKey"))))
    {
      Log.e("AnySDK", " the params(appKey、appSecret、privateKey) are wrong ");
      System.exit(0);
    }
  }
}

/* Location:           /Users/duanhouhai/Develops/anysdk-src/sdk/cm_single/classes_dex2jar.jar
 * Qualified Name:     com.anysdk.Util.Util
 * JD-Core Version:    0.6.2
 */