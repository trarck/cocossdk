package com.opensdk.framework;

public class IAPWrapper {
	public static final int PAYRESULT_SUCCESS = 0;
	public static final int PAYRESULT_FAIL    = 1;
	public static final int PAYRESULT_CANCEL  = 2;
	public static final int PAYRESULT_TIMEOUT = 3;

	public static void onPayResult(InterfaceIAP obj, int ret, String msg) {
		final int curRet = ret;
		final String curMsg = msg;
		final InterfaceIAP curObj = obj;
		PluginWrapper.runOnGLThread(new Runnable() {
			@Override
			public void run() {
				String name = curObj.getClass().getName();
				name = name.replace('.', '/');
				nativeOnPayResult(name, curRet, curMsg);
			}
		});
	}
	private static native void nativeOnPayResult(String className, int ret, String msg);
}
