package com.opensdk.framework;

public class SocialWrapper {
    public static final int SOCIAL_SUBMITSCORE_SUCCESS = 1;
    public static final int SOCIAL_SUBMITSCORE_FAILED = 2;
    public static final int SOCIAL_UNLOCKACH_SUCCESS = 3;
    public static final int SOCIAL_UNLOCKACH_FAILED = 4;

    public static void onSocialResult(InterfaceSocial obj, int ret, String msg) {
        final int curRet = ret;
        final String curMsg = msg;
        final InterfaceSocial curAdapter = obj;
        PluginWrapper.runOnGLThread(new Runnable() {
            @Override
            public void run() {
                String name = curAdapter.getClass().getName();
                name = name.replace('.', '/');
                nativeOnSocialResult(name, curRet, curMsg);
            }
        });
    }
    private static native void nativeOnSocialResult(String className, int ret, String msg);
}
