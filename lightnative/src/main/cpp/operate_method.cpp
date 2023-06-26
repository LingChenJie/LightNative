//
// Created by SuQi on 2023/6/24.
//
#include <jni.h>
#include <string>
#include <android/log.h>
#include "header/operate_method.h"
#include "header/common_utils.h"

#define TAG "TAG_OPERATE_METHOD"
#define LOGE(TAG, ...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

jobject callMethod(
        JNIEnv *env,
        jobject /* this */) {
    // --------------------------创建Java实例对象并调用方法--------------------------
    jclass class_student = env->FindClass("com/android/lightnative/bean/Student");
    if (class_student == NULL) {
        LOGE("TAG", "FindClass failed\n");
        return NULL;
    }
    jmethodID methodID_student_init = env->GetMethodID(class_student, "<init>", "()V");
    if (methodID_student_init == NULL) {
        LOGE("TAG", "GetMethodID init failed\n");
        return NULL;
    }
    // 创建实例
    jobject object_student = env->NewObject(class_student, methodID_student_init);
    if (object_student == NULL) {
        LOGE("TAG", "NewObject failed\n");
        return NULL;
    }
    jmethodID methodID_student_setAge = env->GetMethodID(class_student, "setAge", "(I)V");
    if (methodID_student_setAge == NULL) {
        LOGE("TAG", "GetMethodID setAge failed\n");
        return NULL;
    }
    jmethodID methodID_student_setName = env->GetMethodID(class_student, "setName",
                                                          "(Ljava/lang/String;)V");
    if (methodID_student_setName == NULL) {
        LOGE("TAG", "GetMethodID setName failed\n");
        return NULL;
    }
    // 调用方法
    jstring string_name = charToJstring(env, "wangwu");
    env->CallVoidMethod(object_student, methodID_student_setAge, 100);
    env->CallVoidMethod(object_student, methodID_student_setName, string_name);

    // 删除局部引用
    env->DeleteLocalRef(string_name);
    env->DeleteLocalRef(class_student);

    return object_student;
}

void callStaticMethod(
        JNIEnv *env,
        jobject /* this */) {
    // --------------------------创建Java实例对象并调用静态方法--------------------------
    jclass class_student = env->FindClass("com/android/lightnative/bean/Student");
    if (class_student == NULL) {
        LOGE("TAG", "FindClass failed\n");
        return;
    }
    jmethodID methodID_setStaticString = env->GetStaticMethodID(class_student, "setStaticString",
                                                                "(Ljava/lang/String;)V");
    if (methodID_setStaticString == NULL) {
        LOGE("TAG", "GetStaticMethodID setStaticString failed\n");
        return;
    }
    jstring string_name = charToJstring(env, "Hello");
    env->CallStaticVoidMethod(class_student, methodID_setStaticString, string_name);

    // 删除局部引用
    env->DeleteLocalRef(class_student);
    env->DeleteLocalRef(string_name);
}