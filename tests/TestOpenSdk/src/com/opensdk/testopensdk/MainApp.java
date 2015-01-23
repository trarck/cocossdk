package com.opensdk.testopensdk;

import com.opensdk.framework.OpenSdk;

import android.app.Application;

public class MainApp extends Application {
	public void onCreate()
	  {
	    System.out.println("ChinaMobileApplication :: onCreate");
	    super.onCreate();
	    System.out.println("start opensdk init" + System.currentTimeMillis());
	    OpenSdk.getInstance().initApp(this);
	    System.out.println("finish opensdk init" + System.currentTimeMillis());
	    
	    System.out.print("appContext:");
	    System.out.println(this);
	  }
}
