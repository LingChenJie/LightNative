package com.android.lightnative.bean;

import android.util.Log;

/**
 * Created by SuQi on 2023/6/26.
 * Describe:
 */
public class Car {
    private static final String TAG = "Car";

    protected String name;

    public Car(String name) {
        this.name = name;
        Log.e(TAG, "Car construct call...");
    }

    public void feature() {
        Log.e(TAG, "General Car");
    }

    public String getName() {
        Log.e(TAG, "Car.getName call...");
        return name;
    }
}
