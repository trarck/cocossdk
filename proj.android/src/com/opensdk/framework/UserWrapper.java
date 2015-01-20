package com.opensdk.framework;

public class UserWrapper {
	public static final int ACTION_RET_LOGIN_SUCCEED = 0;
    public static final int ACTION_RET_LOGIN_FAILED = 1;
    public static final int ACTION_RET_LOGOUT_SUCCEED = 2;

	public static void onActionResult(InterfaceUser obj, int ret, String msg) {
		final int curRet = ret;
		final String curMsg = msg;
		final InterfaceUser curAdapter = obj;
		PluginWrapper.runOnGLThread(new Runnable() {
			@Override
			public void run() {
				String name = curAdapter.getClass().getName();
				name = name.replace('.', '/');
				nativeOnActionResult(name, curRet, curMsg);
			}
		});
	}
	
	private static native void nativeOnActionResult(String className, int ret, String msg);
}
