//
// Created by SuQi on 2023/6/24.
//
#include <jni.h>
#include <string>
#include <cstdio>
#include <android/log.h>
#include "header/operate_exception.h"
#include "header/common_utils.h"
#include "header/exception_utils.h"

#define TAG "TAG_OPERATE_EXCEPTION"
#define LOGE(TAG, ...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

void throwException(
        JNIEnv *env,
        jobject object) {
    jthrowable throwable;
    jclass class_object = env->GetObjectClass(object);
    jmethodID methodID_callback = env->GetMethodID(class_object, "callback", "()V");
    if (methodID_callback == NULL) {
        LOGE(TAG, "GetMethodID callback failed\n");
        return;
    }
    // 调用callback方法，此时会抛出异常，需要对异常进行处理
    env->CallVoidMethod(object, methodID_callback);

    // 捕获异常方式1，调用ExceptionOccurred判断是否有异常发生
    throwable = env->ExceptionOccurred();

    // 捕获异常方式2，在没有将异常清除前，也可以使用ExceptionCheck检测是否有异常发生
    if (env->ExceptionCheck()) {
        LOGE(TAG, "ExceptionCheck has exception\n");
    }

    if (throwable) {
        // 捕获Java抛出的异常并打印，然后清理
        env->ExceptionDescribe();
        env->ExceptionClear();

//        // 创建一个异常返回给Java
//        jclass exception_new;
//        exception_new = env->FindClass("java/lang/IllegalArgumentException");
//        if (exception_new == NULL) {
//            LOGE(TAG, "FindClass failed\n");
//            return;
//        }
//        // 抛出异常
//        env->ThrowNew(exception_new, "this exception from native");
        throwExceptionByName(env, "java/lang/IllegalArgumentException",
                             "this exception from native");
    }

    // 删除局部引用
    env->DeleteLocalRef(throwable);
    env->DeleteLocalRef(class_object);
}
