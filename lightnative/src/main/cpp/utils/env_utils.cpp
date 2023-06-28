//
// Created by SuQi on 2023/6/24.
//
#include <string>
#include <android/log.h>
#include "header/env_utils.h"
#include "header/log_utils.h"

/**
* 依据JavaVM获取JNIEnv对象
* @return
*/
JNIEnv *GetAttachEnv() {
    if (JniData::vm == NULL) {
        LOGE("JavaVM is NULL\n");
        return NULL;
    }
    JNIEnv *env = NULL;
    int status = JniData::vm->GetEnv((void **) &env, JNI_VERSION_1_6);
    if (status == JNI_EDETACHED || env == NULL) {
        status = JniData::vm->AttachCurrentThread(&env, NULL);
        if (status < 0) {
            LOGE("AttachCurrentThread failed, status:%d\n", status);
            env = NULL;
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