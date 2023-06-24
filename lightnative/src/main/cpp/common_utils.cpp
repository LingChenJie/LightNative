//
// Created by SuQi on 2023/6/24.
//
#include <string>
#include <cstdio>
#include <android/log.h>
#include "header/common_utils.h"

#define TAG "COMMON_UTILS_TAG"
#define LOGE(TAG, ...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

/**
 * 实现 char* 转为 jstring 的转换
 * @param env
 * @param pat
 * @return
 */
jstring charToJstring(JNIEnv *env, const char *pat) {
    jclass class_string = env->FindClass("java/lang/String");
    jmethodID methodID_string_init = env->GetMethodID(class_string, "<init>",
                                                      "([BLjava/lang/String;)V");
    jbyteArray byteArray = env->NewByteArray((jsize) strlen(pat));
    env->SetByteArrayRegion(byteArray, 0, (jsize) strlen(pat), (jbyte *) pat);
    jstring encoding = env->NewStringUTF("utf-8");
    return (jstring) env->NewObject(class_string, methodID_string_init, byteArray, encoding);
}