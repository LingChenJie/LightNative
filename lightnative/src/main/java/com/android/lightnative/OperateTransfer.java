package com.android.lightnative;

import com.android.lightnative.bean.ClassA;
import com.android.lightnative.bean.JavaBean;

/**
 * Created by SuQi on 2023/6/24.
 * Describe:
 */
public class OperateTransfer {

    // 将C/C++结构体转为Java类
    public native JavaBean getJavaBean();

    // 将Java对象转换成C/C++结构体
    public native void transferJavaBean(JavaBean bean);

    public native int getClassA(byte[] bytes);

}
