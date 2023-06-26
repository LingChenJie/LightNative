package com.android.lightnative;

import com.android.lightnative.bean.Student;

/**
 * Created by SuQi on 2023/6/24.
 * Describe:
 */
public class OperateMethod {

    public native Student callMethod();

    public native void callStaticMethod();

    public native void callSuperMethod();

}
