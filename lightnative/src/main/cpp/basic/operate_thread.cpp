//
// Created by SuQi on 2023/6/24.
//
#include <jni.h>
#include <string>
#include <android/log.h>
#include <unistd.h>
#include <pthread.h>
#include "header/operate_thread.h"
#include "../utils/header/common_utils.h"
#include "../utils/header/env_utils.h"

#define TAG "TAG_OPERATE_THREAD"
#define LOGE(TAG, ...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

JavaVM *g_JavaVM;// 全局JavaVM
jobject g_object;// 全局object
jmethodID methodID_callback;// 全局的callback方法ID
static int count = 0;

static void *thread_exec(void *arg) {
    LOGE(TAG, "thread_exec\n");
    LOGE(TAG, "The pthread id: %ld\n", pthread_self());
//    JNIEnv *env;
//    g_JavaVM->AttachCurrentThread(&env, nullptr);
    JNIEnv *env = GetAttachEnv();
    for (int i = 0; i < 5; i++) {
        usleep(20);
        // 回调Java层函数
        env->CallVoidMethod(g_object, methodID_callback, count++);
    }
//    g_JavaVM->DetachCurrentThread();
    DetachEnv();
    LOGE(TAG, "thread stoped\n");
    return ((void *) 0);
}

void threadWork(
        JNIEnv *env,
        jobject object) {
    env->GetJavaVM(&g_JavaVM);// 保存在全局变量中
    g_object = env->NewGlobalRef(object);

    jclass class_object = env->GetObjectClass(object);
    methodID_callback = env->GetMethodID(class_object, "callback", "(I)V");

    // 通过pthread库创建线程
    LOGE(TAG, "create native thread\n");
    pthread_t id;
    if (pthread_create(&id, nullptr, thread_exec, nullptr) != 0) {
        LOGE(TAG, "pthread_create fail\n");
        return;
    }
    for (int i = 0; i < 5; ++i) {
        usleep(20);
        // 跨线程回调Java层函数
        env->CallVoidMethod(object, methodID_callback, count++);
    }
    LOGE(TAG, "pthread_create success\n");

    // 删除局部引用
    env->DeleteLocalRef(class_object);
}