//
// Created by SuQi on 2023/6/24.
//
#include <string>
#include <android/log.h>
#include "header/exception_utils.h"

#define TAG "EXCEPTION_UTILS_TAG"
#define LOGE(TAG, ...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

/**
 * 检查异常
 * @param env
 */
int checkException(JNIEnv *env) {
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();// 打印异常信息
        env->ExceptionClear();// 清除异常信息
    }
    return -1;
}

/**
 * 向Java层抛出异常
 * @param env
 * @param exception_name 异常类名的全路径，例如: java/lang/Exception
 * @param msg 异常信息
 */
void throwExceptionByName(JNIEnv *env, const char *exception_name, const char *msg) {
    // 查找异常类
    jclass class_exception = env->FindClass(exception_name);
    if (class_exception != NULL) {
        // 抛出指定名称的异常
        env->ThrowNew(class_exception, msg);
    }
    // 释放局部变量
    env->DeleteLocalRef(class_exception);
}