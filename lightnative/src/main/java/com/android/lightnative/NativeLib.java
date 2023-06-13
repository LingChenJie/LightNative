package com.android.lightnative;

public class NativeLib {

    // Used to load the 'lightnative' library on application startup.
    static {
        System.loadLibrary("lightnative");
    }

    /**
     * A native method that is implemented by the 'lightnative' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}