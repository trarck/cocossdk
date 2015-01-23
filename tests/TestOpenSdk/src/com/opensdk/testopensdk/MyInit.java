package com.opensdk.testopensdk;

import android.content.Context;
import android.util.Log;

public class MyInit {

	private static String TAG="OpenSdk";
	
	public static void myAppInit(Context context){
		Log.d(TAG,"my app init for only one method");
	}
}
