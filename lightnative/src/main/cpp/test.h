//
// Created by 小苏苏苏 on 2023/6/19.
//
#include <jni.h>

#ifndef LIGHTNATIVE_TEST_H
#define LIGHTNATIVE_TEST_H

// 对应com.android.lightnative.bean.TestBean
typedef struct {
    const char *stringValue;// String
    bool boolValue;// boolean
    char charValue;// char
    double doubleValue;// double
    int intValue;// int
    char arrayValue[4];// byte[]
    int doubleDimenArray[2][2];// int[][]
    const char *message;// String
} JNI_TestBean;

// 对应com.android.lightnative.bean.TestBean$InnerClass的域和方法
typedef struct {
    jclass clazz;
    jfieldID message;
    jmethodID constructor;
} InnerClass_t;

// 对应com.android.lightnative.bean.TestBean的域和方法
typedef struct {
    jclass clazz;

    jfieldID stringValue;
    jfieldID boolValue;
    jmethodID charValue;
    jmethodID doubleValue;
    jmethodID intValue;
    jmethodID byteArray;
    jmethodID doubleDimenArray;
    jmethodID inner_message;

    jmethodID constructor;
} TestBean_t;

#endif //LIGHTNATIVE_TEST_H
