package com.opensdk.testopensdk;

import com.anysdk.framework.java.AnySDK;

import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;


public class MainActivity extends ActionBarActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        System.out.print("activity context:");
        System.out.println(this);
        
        System.out.print("direct view context:");
        System.out.println(this.getWindow().getDecorView().getContext());
        
        System.out.print("window context:");
        System.out.println(this.getWindow().getContext());
        
        AnySDK.getInstance().initPluginSystem(this, "E366F9F3-570E-4F9E-0B42-57A868DC4EC7", "69ab62a83a3edf48ac85ee5977ee1656", "9BE2243B53F070D00AA4B40B3F4CE558", "");
    
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }
}
