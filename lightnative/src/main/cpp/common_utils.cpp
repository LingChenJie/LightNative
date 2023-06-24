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
 * @param str
 * @return
 */
jstring charToJstring(JNIEnv *env, const char *str) {
    jclass class_string = env->FindClass("java/lang/String");
    jmethodID methodID_string_init = env->GetMethodID(class_string, "<init>",
                                                      "([BLjava/lang/String;)V");
    jbyteArray byteArray = env->NewByteArray((jsize) strlen(str));
    env->SetByteArrayRegion(byteArray, 0, (jsize) strlen(str), (jbyte *) str);
    jstring encoding = env->NewStringUTF("utf-8");
    return (jstring) env->NewObject(class_string, methodID_string_init, byteArray, encoding);
}

/**
 * 将jstring转换成char *
 * @param env
 * @param jstr
 * @return
 */
char *jstringToChar(JNIEnv *env, jstring jstr) {
    if (env->ExceptionCheck() == JNI_TRUE || jstr == NULL) {
        env->ExceptionDescribe();
        env->ExceptionClear();
        LOGE(TAG, "jstringToChar 函数转换时,传入的参数str为空");
        return NULL;
    }
    jbyteArray byteArray = 0;
    jthrowable exc;
    char *result = 0;
    if (env->EnsureLocalCapacity(2) < 0) {
        return 0;/* out of memory error */
    }
    jclass class_string = env->FindClass("java/lang/String");
    jmethodID methodID_string_getBytes = env->GetMethodID(class_string, "getBytes", "()[B");
    byteArray = (jbyteArray) (env->CallObjectMethod(jstr, methodID_string_getBytes));
    exc = env->ExceptionOccurred();
    if (!exc) {
        jint length = env->GetArrayLength(byteArray);
        result = (char *) malloc(length + 1);
        if (result == 0) {
            //JNU_ThrowByName( "java/lang/OutOfMemoryError", 	0);
            env->DeleteGlobalRef(byteArray);
            return 0;
        }
        env->GetByteArrayRegion(byteArray, 0, length, (jbyte *) result);
        result[length] = 0;/* NULL-terminate */
    } else {
        env->DeleteGlobalRef(exc);
    }
    env->DeleteLocalRef(byteArray);
    return (char *) result;
}