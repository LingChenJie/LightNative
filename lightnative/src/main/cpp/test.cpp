//
// Created by 小苏苏苏 on 2023/6/19.
//
#include <jni.h>
#include "test.h"


extern "C"
JNIEXPORT jobject JNICALL
Java_com_android_lightnative_LightNativeLib_getJavaBeanFromNative(JNIEnv *env, jobject thiz) {
}

extern "C"
JNIEXPORT void JNICALL
Java_com_android_lightnative_LightNativeLib_transferJavaBeanToNative(JNIEnv *env, jobject thiz,
                                                                     jobject bean) {
}