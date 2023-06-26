package com.android.lightnative;

import android.util.Log;

/**
 * Created by SuQi on 2023/6/24.
 * Describe:
 */
public class OperateThread {

    public native void threadWork();

    public void callback(int count) {
        Log.e("OperateThread", "callback:" + count);
    }

}
