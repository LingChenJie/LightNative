package com.android.lightnative;

public class LightNativeLib {

    // Used to load the 'light_native' library on application startup.
    static {
        System.loadLibrary("light_native");
    }

    /**
     * A native method that is implemented by the 'light_native' native library,
     * which is packaged with this application.
     */
    public native String hello();

}