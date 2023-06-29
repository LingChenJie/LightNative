//
// Created by SuQi on 2023/6/24.
//
#include <jni.h>
#include <string>
#include <android/log.h>
#include "header/operate_string.h"
#include "../utils/header/common_utils.h"

#define TAG "TAG_OPERATE_STRING"
#define LOGE(TAG, ...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

jstring helloJni(
        JNIEnv *env,
        jobject /* this */,
        jstring string) {
    LOGE(TAG, "helloJni()\n");

    // GetStringLength
    jsize string_length = env->GetStringLength(string);
    LOGE(TAG, "The String GetStringLength: %d\n", string_length);
    // GetStringUTFLength
    string_length = env->GetStringUTFLength(string);
    LOGE(TAG, "The String GetStringUTFLength: %d\n", string_length);

    char const *c_str = nullptr;
    jboolean isCopy;
    c_str = env->GetStringUTFChars(string, &isCopy);// 从jstring指针中获取数据
    LOGE(TAG, "isCopy:%d\n", isCopy);
    if (c_str == nullptr) {
        return nullptr;
    }
    LOGE(TAG, "The String from Java: %s\n", c_str);
    env->ReleaseStringUTFChars(string, c_str);

    char buff[128] = "Hello I'm from JNI";
//    return env->NewStringUTF(buff);//不推荐直接使用,遇到如下错误:JNI DETECTED ERROR IN APPLICATION: input is not valid Modified UTF-8: illegal start byte 0x80
    return charToJstring(env, buff);// 推荐使用
}