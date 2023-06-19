package com.android.lightnative;

import com.android.lightnative.bean.TestBean;

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

    // 将C/C++结构体转为Java类
    public native TestBean getJavaBeanFromNative();

    // 将Java对象转换成C/C++结构体
    public native void transferJavaBeanToNative(TestBean bean);

}