package com.android.lightnative;

/**
 * Created by SuQi on 2023/6/24.
 * Describe:
 */
public class OperateException {

    public native void throwException() throws IllegalArgumentException;

    public native void throwException2() throws IllegalArgumentException;

    public void callback() {// 回调方法
        throw new NullPointerException("throw NullPointerException for test!");
    }

}
