package com.android.lightnative.bean;

import java.util.Arrays;

/**
 * Created by SuQi on 2023/6/19.
 * Describe:
 */
public class JavaBean {
    public String stringValue = "Hello";
    public boolean boolValue = false; // boolean类型
    public char charValue = 'A'; // char类型
    public double doubleValue = 100; // double类型
    public int intValue = 100; // 整形
    public byte[] byteArray = {0, 1, 2, 3}; // byte数组

    public int[][] doubleDimenArray = {
            {10, 10},
            {20, 20}
    }; // 二维数组

    public InnerClass innerClass = new InnerClass(); // 静态内部类

    static class InnerClass {
        public String message = "Im from Java!";// 字符串

        @Override
        public String toString() {
            return "InnerClass [message=" + message + "]";
        }
    }

    @Override
    public String toString() {
        return "JavaBean{" +
                "stringValue='" + stringValue + '\'' +
                ", boolValue=" + boolValue +
                ", charValue=" + charValue +
                ", doubleValue=" + doubleValue +
                ", intValue=" + intValue +
                ", byteArray=" + Arrays.toString(byteArray) +
                ", doubleDimenArray=" + Arrays.toString(doubleDimenArray) +
                ", innerClass=" + innerClass.toString() +
                '}';
    }
}
