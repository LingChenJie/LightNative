package com.android.lightnative.bean;

import android.util.Log;

/**
 * Created by SuQi on 2023/6/26.
 * Describe:
 */
public class Tesla extends Car {

    private static final String TAG = "Tesla";

    public Tesla(String name) {
        super(name);
        Log.e(TAG, "Tesla construct call...");
    }

    @Override
    public void feature() {
        super.feature();
        Log.e(TAG, "Very fast");
    }

    @Override
    public String getName() {
        super.getName();
        Log.e(TAG, "Tesla.getName call...");
        return "T-" + this.name;
    }
}
