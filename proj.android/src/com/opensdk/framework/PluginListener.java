package com.opensdk.framework;

import android.content.Intent;

public interface PluginListener {
	public void onResume();
	public void onPause();
	public void onDestroy();
	public boolean onActivityResult(int requestCode, int resultCode, Intent data);
}
