
package com.opensdk.framework;

import java.util.Hashtable;

import android.app.AlertDialog.Builder;
import android.content.Context;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

public class SocialDebug
    implements InterfaceSocial
{
    private static final String SIMSDK_LOGIN_URL = "http://sim.qudao.info/account/login";
    private static final String SIMSDK_LOGOUT_URL = "http://sim.qudao.info/account/logout";
    private static final String SIMSDK_PAY_URL = "http://sim.qudao.info/api/pay/exec";
    public final int PluginType = 7;
    private static Context mContext = null;
    protected static String TAG = "DebugMode";
    private static SocialDebug mAdapter = null;
    private static boolean isInited = false;
    private static boolean mLogined = false;
    private static String mUserId = "";
    private static String mSessionId = "";
    private static String mUApiKey = "";
    private static String mUApiSecret = "";
    private static String mServerUrl = "";
    private static String mOrderId = "";
    private static Hashtable mGoodsInfo = null;
    private static boolean isDebug = true;
    
    protected static void LogE(String msg, Exception exception)
    {
        Log.e(TAG, msg, exception);
        exception.printStackTrace();
    }

    protected static void LogD(String msg)
    {
        if(isDebug)
            Log.d(TAG, msg);
    }

    public SocialDebug(Context context)
    {
        mContext = context;
        mAdapter = this;
        configDeveloperInfo(Wrapper.getDeveloperInfo());
    }

    public void configDeveloperInfo(Hashtable<String, String> cpInfo)
    {
        if(isInited)
        {
            return;
        } else
        {
            isInited = true;
            mServerUrl = (String)Wrapper.getDeveloperInfo().get("oauthLoginServer");
            mUApiKey = (String)Wrapper.getDeveloperInfo().get("uApiKey");
            mUApiSecret = (String)Wrapper.getDeveloperInfo().get("uApiSecret");
            return;
        }
    }

    private void userLogin(String username, String password, final ILoginCallback callback)
    {
        Hashtable<String,String> param = new Hashtable<String,String>();
        param.put("username", username);
        param.put("password", password);
        param.put("server_url", SIMSDK_LOGIN_URL);
        /*
        g.c(mContext, param, new SdkHttpListener(){
        	public void onResponse(String response)
            {
                Log.d("onResponse", response);
                String msg;
                try
                {
                	JSONObject json = new JSONObject(response);
                	msg=json.getString("errMsg");
                    if(msg!= null && msg.equals("success"))
                    {
                    	JSONObject data = json.getJSONObject("data");
                        Log.d("data", data.toString());
                        SocialDebug.mUserId = data.getString("user_id");
                        SocialDebug.mSessionId = data.getString("session_id");
                        Log.d("user_id", SocialDebug.mUserId);
                        Log.d("session_id", SocialDebug.mSessionId);
                        Hashtable<String,String> param = new Hashtable<String,String>();
                        param.put("channel", "simsdk");
                        param.put("server_url", SocialDebug.mServerUrl);
                        param.put("session_id", SocialDebug.mSessionId);
                        param.put("user_id", SocialDebug.mUserId);
                        param.put("uapi_key", SocialDebug.mUApiKey);
                        param.put("uapi_secret", SocialDebug.mUApiSecret);
                        
                        UserWrapper.getAccessToken(SocialDebug.mContext, param, new SdkHttpListener(){
                        	 public void onResponse(String response2)
                             {
                                 Log.d("onResponse", response2);
                                 String status;
                                 try
                                 {
                                	 JSONObject json2 = new JSONObject(response2);
                                	 status=json2.getString("status");
                                     if(status != null && status.equals("ok"))
                                     {
                                    	 String ext=json2.optString("ext");
                                         callback.onSuccessed(2, ext!=null?ext:"");
                                         return;
                                     } else
                                     {
                                         callback.onFailed(UserWrapper.ACTION_RET_LOGIN_FAIL, "");
                                         return;
                                     }
                                 }
                                 catch(JSONException _ex)
                                 {
                                     callback.onFailed(UserWrapper.ACTION_RET_LOGIN_FAIL, "");
                                 }
                             }

                             public void onError()
                             {
                                 callback.onFailed(UserWrapper.ACTION_RET_LOGIN_FAIL, "");
                             }
                        });
                        
                    } else
                    {
                        callback.onFailed(UserWrapper.ACTION_RET_LOGIN_FAIL, "");
                        return;
                    }
                }
                catch(JSONException _ex)
                {
                    callback.onFailed(UserWrapper.ACTION_RET_LOGIN_FAIL, "");
                }
            }

            public void onError()
            {
                callback.onFailed(UserWrapper.ACTION_RET_LOGIN_FAIL, "");
            }
        });
        */
    }

    private void userLogout()
    {
    	Hashtable<String,String> param = new Hashtable<String,String>();
    	param.put("user_id", mUserId);
    	param.put("session_id", mSessionId);
    	param.put("server_url", SIMSDK_LOGOUT_URL);
    	
//        g.c(mContext, param, new SdkHttpListener() {
//			
//        	public void onResponse(String response)
//            {
//                Log.d("onResponse", response);
//                String msg;
//                try
//                {
//                	JSONObject json = new JSONObject(response);
//                	msg=json.getString("errMsg");
//                    if(msg!= null && msg.equals("success"))
//                    {
//                        SocialDebug.mLogined = false;
//                        SocialWrapper.onSocialResult(SocialDebug.mAdapter, SocialWrapper.SOCIAL_SIGNOUT_SUCCEED, "");
//                    } else
//                    {
//                        SocialWrapper.onSocialResult(SocialDebug.mAdapter, SocialWrapper.SOCIAL_SIGNOUT_FAIL, msg);
//                    }
//                }
//                catch(Exception e)
//                {
//                    SocialWrapper.onSocialResult(SocialDebug.mAdapter, SocialWrapper.SOCIAL_SIGNOUT_FAIL, e.toString());
//                }
//            }
//
//            public void onError()
//            {
//                SocialWrapper.onSocialResult(SocialDebug.mAdapter, 8, "");
//            }
//		});
    }

    public boolean isLogined()
    {
        return mLogined;
    }

    private boolean networkReachable()
    {
        boolean flag = false;
        NetworkInfo networkinfo;
        try
        {
            flag = (networkinfo = ((ConnectivityManager)mContext.getSystemService("connectivity")).getActiveNetworkInfo()) != null ? networkinfo.isAvailable() : false;
        }
        catch(Exception exception)
        {
            LogE("Fail to check network status", exception);
        }
        LogD((new StringBuilder("NetWork reachable : ")).append(flag).toString());
        return flag;
    }

    public void setDebugMode(boolean flag)
    {
        isDebug = flag;
    }

    public String getSDKVersion()
    {
        return "2.0.3";
    }

    public String getPluginVersion()
    {
        return "2.0.3";
    }

    public static void showDialog(final String curTitle, final String curMsg)
    {
        PluginWrapper.runOnMainThread(new Runnable() {
			
			@Override
			public final void run()
	        {
	            Builder builder=new Builder(SocialDebug.mContext);
	            
	            builder.setTitle(SocialDebug.getResourceId(curTitle, "string"));
	            builder.setMessage(SocialDebug.getResourceId(curMsg, "string"));
	            builder.setPositiveButton("Ok", new OnClickListener(){
	                public void onClick(DialogInterface dialoginterface, int i)
	                {
	                }
	            });
	            builder.create();
	            builder.show();
	        }
		});
    }

    public static int getResourceId(String key, String type)
    {
        return mContext.getResources().getIdentifier(key, type, mContext.getPackageName());
    }

    public void signIn()
    {
        PluginWrapper.runOnMainThread(new Runnable() {
			
			@Override
			public void run()
	        {
	            if(SocialDebug.mLogined)
	            {
	                SocialWrapper.onSocialResult(SocialDebug.mAdapter, SocialWrapper.SOCIAL_SIGNIN_FAIL, "Already logined!");
	            } else
	            {
	                Builder builder= new Builder(SocialDebug.mContext);
	                builder.setTitle(SocialDebug.getResourceId("plugin_login_title", "string"));
	                final View view = LayoutInflater.from(SocialDebug.mContext).inflate(SocialDebug.getResourceId("plugin_login", "layout"), null);
	                builder.setView(view);


	                OnClickListener listener = new OnClickListener(){
	                	public void onClick(DialogInterface dialoginterface, int i)
	                    {
	                        switch(i)
	                        {
	                        case -2: 
	                            SocialDebug.mLogined = false;
	                            SocialWrapper.onSocialResult(SocialDebug.mAdapter, 6, "the login has been canceled");
	                            return;

	                        case -1: 
	                        	EditText username = (EditText)view.findViewById(SocialDebug.getResourceId("txt_username", "id"));
	                        	EditText password = (EditText)view.findViewById(SocialDebug.getResourceId("txt_password", "id"));
	                            if(username.getText().toString().length()==0 || password.getText().toString().length()==0)
	                            {
	                                SocialWrapper.onSocialResult(SocialDebug.mAdapter, 6, "username or password is empty");
	                            }
	    

	                            userLogin(username.getText().toString(), password.getText().toString(), new ILoginCallback(){
	                            	 public void onSuccessed(int j, String s)
		                                {
		                                    SocialDebug.mLogined = true;
		                                    SocialWrapper.onSocialResult(SocialDebug.mAdapter, 5, s);
		                                }

		                                public void onFailed(int j, String s)
		                                {
		                                    SocialDebug.mLogined = false;
		                                    SocialWrapper.onSocialResult(SocialDebug.mAdapter, 6, s);
		                                }
	                            });
	                            break;
	                        }
	                    }
	                };
	                
	                builder.setPositiveButton(SocialDebug.getResourceId("plugin_login", "string"), listener);
	                builder.setNegativeButton(SocialDebug.getResourceId("plugin_cancel", "string"), listener).create();
	                builder.setCancelable(false);
	                builder.show();
	                return;
	            }
	        }
		});
    }

    public void signOut()
    {
        PluginWrapper.runOnMainThread(new Runnable() {
			
			@Override
			public void run()
	        {
	            if(!isLogined())
	            {
	                SocialWrapper.onSocialResult(SocialDebug.mAdapter, SocialWrapper.SOCIAL_SIGNIN_FAIL, "not need logout");
	                SocialDebug.LogD("User not logined!");
	            } else
	            {
	                userLogout();
	            }
	        }
		});
    }

    public void submitScore(String leaderboardID, long score)
    {
        PluginWrapper.runOnMainThread(new Runnable() {
			
			@Override
			public void run()
	        {
	            Toast.makeText(SocialDebug.mContext, "success to submit", Toast.LENGTH_SHORT).show();
	        }
		});
    }

    public void showLeaderboard(String leaderboardID)
    {
        PluginWrapper.runOnMainThread(new Runnable() {
			
			@Override
			public void run()
	        {
	            SocialDebug.showDialog("plugin_rank", "plugin_rank");
	        }
		});
    }

    public void unlockAchievement(Hashtable<String, String> achInfo)
    {
        PluginWrapper.runOnMainThread(new Runnable() {
			
			@Override
	        public void run()
	        {
	            Toast.makeText(SocialDebug.mContext, "success to unlock", Toast.LENGTH_SHORT).show();
	        }
		});
    }

    public void showAchievements()
    {
        PluginWrapper.runOnMainThread(new Runnable() {
			
			@Override
			public void run()
	        {
	            SocialDebug.showDialog("plugin_achievement", "plugin_achievement");
	        }
		});
    }

}
