//
// Created by SuQi on 2023/6/24.
//
#include <jni.h>
#include <string>
#include <android/log.h>
#include "header/operate_method.h"
#include "../utils/header/common_utils.h"

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

void callSuperMethod(
        JNIEnv *env,
        jobject /* this */) {
    // 创建Tesla对象的实例，调用其父类的feather和getName方法
    jclass class_car;
    jclass class_tesla;
    jmethodID methodID_tesla_init;
    jmethodID methodID_feather;
    jmethodID methodID_getName;
    jobject object_tesla;

    class_car = env->FindClass("com/android/lightnative/bean/Car");
    if (class_car == NULL) {
        LOGE(TAG, "FindClass Car failed\n");
        return;
    }
    class_tesla = env->FindClass("com/android/lightnative/bean/Tesla");
    if (class_tesla == NULL) {
        LOGE(TAG, "FindClass Tesla failed\n");
        return;
    }
    methodID_tesla_init = env->GetMethodID(class_tesla, "<init>", "(Ljava/lang/String;)V");
    if (methodID_tesla_init == NULL) {
        LOGE(TAG, "GetMethodID Tesla init failed\n");
        return;
    }

    jstring string_name = charToJstring(env, "ModelY");
    if (string_name == NULL) {
        LOGE(TAG, "charToJstring failed\n");
        return;
    }

    // 创建Tesla
    object_tesla = env->NewObject(class_tesla, methodID_tesla_init, string_name);
    if (object_tesla == NULL) {
        LOGE(TAG, "NewObject Tesla failed\n");
        return;
    }

    // 判断object_tesla 是否是class_car 的实例
    jboolean flag = env->IsInstanceOf(object_tesla, class_car);
    if (flag) {
        LOGE(TAG, "object_tesla IsInstanceOf class_car\n");
    }

    // 获取Car 的方法ID
    methodID_feather = env->GetMethodID(class_car, "feature", "()V");
    if (methodID_feather == NULL) {
        LOGE(TAG, "GetMethodID feather failed\n");
        return;
    }
    methodID_getName = env->GetMethodID(class_car, "getName", "()Ljava/lang/String;");
    if (methodID_getName == NULL) {
        LOGE(TAG, "GetMethodID getName failed\n");
        return;
    }

    // 用CallNonvirtualVoidMethod获取被子类覆盖的父类方法
    env->CallNonvirtualVoidMethod(object_tesla, class_car, methodID_feather);

    // 用CallNonvirtualObjectMethod获取被子类覆盖的父类方法
    env->CallNonvirtualObjectMethod(object_tesla, class_car, methodID_getName);


    exit:
    // 删除局部引用
    env->DeleteLocalRef(string_name);
    env->DeleteLocalRef(class_car);
    env->DeleteLocalRef(class_tesla);
    env->DeleteLocalRef(object_tesla);
}