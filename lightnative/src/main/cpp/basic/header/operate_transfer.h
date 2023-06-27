//
// Created by 小苏苏苏 on 2023/6/19.
//
#include <jni.h>
#include <string>

#ifndef LIGHTNATIVE_OPERATE_TRNASFER_H
#define LIGHTNATIVE_OPERATE_TRNASFER_H

#ifdef __cplusplus
extern "C" {
#endif

// 对应com.android.lightnative.bean.JavaBean
typedef struct {
    const char *stringValue;// String
    bool boolValue;// boolean
    char charValue;// char
    double doubleValue;// double
    int intValue;// int
    char byteArray[4];// byte[]
    int doubleDimenArray[2][2];// int[][]
    const char *message;// String
} JavaBean;

// 对应com.android.lightnative.bean.JavaBean$InnerClass的域和方法
typedef struct {
    jclass clazz;
    jmethodID constructor;
    jfieldID message;
} InnerClass_t;

// 对应com.android.lightnative.bean.JavaBean的域和方法
typedef struct {
    jclass clazz;
    jmethodID constructor;
    jfieldID stringValue;
    jfieldID boolValue;
    jfieldID charValue;
    jfieldID doubleValue;
    jfieldID intValue;
    jfieldID byteArray;
    jfieldID doubleDimenArray;
    jfieldID innerClass;
} JavaBean_t;

void register_class(JNIEnv *env);

jobject getJavaBean(
        JNIEnv *env,
        jobject /* this */);

void transferJavaBean(
        JNIEnv *env,
        jobject /* this */,
        jobject javaBean_in);

#ifdef __cplusplus
}
#endif
#endif //LIGHTNATIVE_OPERATE_TRNASFER_H
