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
      
//      byte binaryBytes[]=Base64.decode(bytes, 0);
      return new String(bytes);
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

      return URLEncoder.encode(new String(bytes));
  }

  private static String convertToHex(byte[] bytes)
  {
    StringBuffer stringBuffer = new StringBuffer();

    int j=0;
    for(int i=0;i<bytes.length;++i){

        j=0xF & bytes[i] >>> 4;
        if(j >= 0 && j <= 9)
            stringBuffer.append((char)(j + 48));
        else
            stringBuffer.append((char)(97 + (j - 10)));

        j=0xF & bytes[i];
        if(j >= 0 && j <= 9)
            stringBuffer.append((char)(j + 48));
        else
            stringBuffer.append((char)(97 + (j - 10)));
    }
    return stringBuffer.toString();
  }

  public static void getAccessToken(Context context, Hashtable<String, String> param, final SdkHttpListener curListener)
  {
    try
    {
        String serverUrl = param.get("server_url");
        param.remove("server_url");
        param.put("private_key", Wrapper.getDeveloperInfo().get("private_key"));
        param.put("server_id", UserWrapper.getLoginServerId());
      ArrayList<NameValuePair> arrayList = new ArrayList<NameValuePair>();
      Iterator<String> iterator = param.keySet().iterator();
      while (iterator.hasNext()){
            String str2 = iterator.next();
            arrayList.add(new BasicNameValuePair(str2, param.get(str2)));
      }

      sSdkHttpTask = new SdkHttpTask(context);
      sSdkHttpTask.doPost(new SdkHttpListener(){
          public void onError()
          {
              curListener.onError();
              sSdkHttpTask = null;
          }

          public void onResponse(String responseText)
          {
              curListener.onResponse(responseText);
              sSdkHttpTask = null;
          }
      } , arrayList, serverUrl, 60000);

    }
    catch (Exception e)
    {
        e.printStackTrace();
        curListener.onError();
    }
  }

  public static String getAppv(Context context)
  {
    PackageInfo packageInfo = getPackageInfo(context);
    if (packageInfo == null)
      return "";
    Log.d("test", packageInfo.versionName);
    return packageInfo.versionName;
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
    if(context==null)
        return "";
    try {
        String deviceId = ((TelephonyManager) context.getSystemService("phone")).getDeviceId();

        if (deviceId == null || "".equals(deviceId)) {
            deviceId = getODIN1(context);
        }
        return deviceId==null?"":deviceId;
    } catch (Exception e)
    {
        e.printStackTrace();
    }
      return null;
  }

  public static String getIMSI(Context context)
  {
    try
    {
      String subscriberId = ((TelephonyManager)context.getSystemService("phone")).getSubscriberId();
      return subscriberId;
    }
    catch (Exception localException)
    {
      localException.printStackTrace();
    }
    return "";
  }

  public static String getIP()
  {
    try {
        Iterator<NetworkInterface> iterator = Collections.list(NetworkInterface.getNetworkInterfaces()).iterator();
        while(iterator.hasNext()){

            InetAddress inetaddress;
            String ip;
            Iterator<InetAddress> iteratorAddress = Collections.list( iterator.next().getInetAddresses()).iterator();
            while (iteratorAddress.hasNext()){
                inetaddress=iteratorAddress.next();
                if(!inetaddress.isLoopbackAddress()){
                    ip=inetaddress.getHostAddress();
                    if( InetAddressUtils.isIPv4Address(ip)){
                        return ip;
                    }
                }
            }
        }
    }catch (SocketException localSocketException)
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

  public static String getMd5(String str)
  {
      byte[] bytes;
      StringBuffer stringBuffer
    try {
        bytes = MessageDigest.getInstance("MD5").digest(str.getBytes("UTF-8"));
        stringBuffer = new StringBuffer();
    } catch (NoSuchAlgorithmException e)
    {
        e.printStackTrace();
        return str;
    }
    catch (UnsupportedEncodingException e)
    {
        e.printStackTrace();
        return str;
    }

      for (int i = 0;i<bytes.length ; i++)
      {
        int j = 0xFF & bytes[i];
        if (j < 16)
            stringBuffer.append("0");
        stringBuffer.append(Integer.toHexString(j));
      }
      return stringBuffer.toString();
  }

  public static String getNet(Context context)
  {
    try
    {
      NetworkInfo networkInfo = ((ConnectivityManager)context.getSystemService("connectivity")).getActiveNetworkInfo();
      int i = networkInfo.getType();
      if (i == 0)
      {
        boolean bool = networkInfo.getExtraInfo().toLowerCase().equals("cmnet");
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

  public static void getPayOrderId(Context context, Hashtable<String, String> params,final SdkHttpListener curListener)
  {
    try {
        params.remove("uapi_secret");
        String jsonValue = Base64.encodeToString(new JSONObject(params).toString().getBytes(), 2);
        String[] sortKeys = new String[params.size()];
        Object[] keys = params.keySet().toArray();

        for (int i = 0; i < keys.length; ++i) {
            sortKeys[i] = keys[i].toString();
        }
        Arrays.sort(sortKeys);
        StringBuffer sortedValueStr = new StringBuffer();
        for (int j = 0; j < sortKeys.length; ++j) {
            sortedValueStr.append(params.get(sortKeys[j]));
        }

        String token = getMd5(sortedValueStr.toString() + (String) Wrapper.getDeveloperInfo().get("private_key"));
        ArrayList postData = new ArrayList();
        postData.add(new BasicNameValuePair("token", token));
        postData.add(new BasicNameValuePair("json_data", jsonValue));
        postData.add(new BasicNameValuePair("flag", "custom"));
        sSdkHttpTask = new SdkHttpTask(context);
        if ((Wrapper.getDeveloperInfo().containsKey("order_url")) && (!((String) Wrapper.getDeveloperInfo().get("order_url")).isEmpty()))
            Config.SERVER_URL_GET_ORDER = (String) Wrapper.getDeveloperInfo().get("order_url");
        Log.d("SERVER_URL_GET_ORDER", Config.SERVER_URL_GET_ORDER);
        sSdkHttpTask.doPost(new SdkHttpListener() {
            public void onError() {
                curListener.onError();
                sSdkHttpTask = null;
            }

            public void onResponse(String responseText) {
                curListener.onResponse(responseText);
                sSdkHttpTask = null;
            }
        }, localArrayList, Config.SERVER_URL_GET_ORDER, 60000);

    } catch (Exception e)
    {
      e.printStackTrace();
      curListener.onError();
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

  private static String getToken(String str1, String str2)
  {
    long l = System.currentTimeMillis() / 1000L;
    String str = getMd5(String.valueOf(l) + str1 + str2).substring(0, 16);
    return Base64.encodeToString((str1 + "." + str + "." + l).trim().getBytes(), 2);
  }

  public static String pluginDecode(String str)
  {
    return new String(Base64.decode(ckDecode(str), 0));
  }

    public static String pluginEncode(String str)
    {
        return new String(ckEnecode(Base64.encode(str, 0)));
    }

  public static void pluginHttp(Context context, Hashtable<String, String> params,final SdkHttpListener curListener)
  {
    try
    {
      String serverUrl = (String)params.get("server_url");
        params.remove("server_url");
      ArrayList postData = new ArrayList();
      Iterator<String> iterator = params.keySet().iterator();
        String key;
      while (iterator.hasNext()){
          key = iterator.next();
          postData.add(new BasicNameValuePair(key, params.get(key)));
      }

        sSdkHttpTask = new SdkHttpTask(context);
        sSdkHttpTask.doPost(new SdkHttpListener()
        {
            public void onError()
            {
                curListener.onError();
                sSdkHttpTask = null;
            }

            public void onResponse(String responseText)
            {
                curListener.onResponse(responseText);
                sSdkHttpTask = null;
            }
        } , postData, serverUrl, 60000);
    }
    catch (Exception e)
    {
        e.printStackTrace();
        curListener.onError();
    }
  }

  public static void setPackage(String packageStr)
  {
    if ((!Wrapper.getChannelId().equals("999999")) && (Wrapper.getDeveloperInfo().containsKey("privateKey")) && (!packageStr.equals(Wrapper.getDeveloperInfo().get("privateKey"))))
    {
      Log.e("OpenSDK", " the params(appKey、appSecret、privateKey) are wrong ");
      System.exit(0);
    }
  }
}