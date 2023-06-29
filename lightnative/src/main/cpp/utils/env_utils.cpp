//
// Created by SuQi on 2023/6/24.
//
#include <string>
#include <android/log.h>
#include "header/env_utils.h"
#include "header/log_utils.h"

JavaVM *JniData::vm = nullptr;

/**
* 依据JavaVM获取JNIEnv对象
* @return
*/
JNIEnv *GetAttachEnv() {
    if (JniData::vm == nullptr) {
        LOGE("JniData::vm is nullptr, please set the value in JNI_OnLoad\n");
        return nullptr;
    }
    JNIEnv *env = nullptr;
    int status = JniData::vm->GetEnv((void **) &env, JNI_VERSION_1_6);
    if (status == JNI_EDETACHED || env == nullptr) {
        status = JniData::vm->AttachCurrentThread(&env, nullptr);
        if (status < 0) {
            LOGE("AttachCurrentThread failed, status:%d\n", status);
            env = nullptr;
        }
    }
    return env;
}


/**
* 依据JavaVM释放JNIEnv对象
* @return
*/
jint DetachEnv() {
    return JniData::vm->DetachCurrentThread();
}