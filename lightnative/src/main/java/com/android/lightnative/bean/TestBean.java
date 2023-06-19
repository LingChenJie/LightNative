package com.android.lightnative.bean;

import java.util.Arrays;

/**
 * Created by SuQi on 2023/6/19.
 * Describe:
 */
public class TestBean {
    public String stringValue = "Hello";
    public boolean boolValue = false; // boolean类型
    public char charValue = 'A'; // char类型
    public double doubleValue = 100; // double类型
    public int intValue = 100; // 整形
    public byte[] arrayValue = {0, 1, 2, 3}; // byte数组

    public int[][] doubleDimenArray = {
            {10, 10},
            {20, 20}
    }; // 二维数组

    static class InnerClass {
        public String message = "Im from Java!";// 字符串

        @Override
        public String toString() {
            return "InnerClass [message=" + message + "]";
        }
    }

    @Override
    public String toString() {
        return "TestBean{" +
                "stringValue='" + stringValue + '\'' +
                ", boolValue=" + boolValue +
                ", charValue=" + charValue +
                ", doubleValue=" + doubleValue +
                ", intValue=" + intValue +
                ", arrayValue=" + Arrays.toString(arrayValue) +
                ", doubleDimenArray=" + Arrays.toString(doubleDimenArray) +
                '}';
    }
}
