//
// Created by SuQi on 2023/6/24.
//
#include <jni.h>
#include <string>
#include <cstdio>
#include <android/log.h>
#include "header/operate_field.h"
#include "header/common_utils.h"

#define TAG "TAG_OPERATE_FIELD"
#define LOGE(TAG, ...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

void accessFiled(
        JNIEnv *env,
        jobject /* this */,
        jobject student_in) {
    jclass class_student;
    jfieldID fieldID_age;
    jfieldID fieldID_name;

    // --------------------------获取Student类的实例变量并进行修改------------------------------
    class_student = env->GetObjectClass(student_in);
    if (class_student == NULL) {
        LOGE(TAG, "GetObjectClass failed\n");
        return;
    }
    fieldID_age = env->GetFieldID(class_student, "age", "I");
    if (fieldID_age == NULL) {
        LOGE(TAG, "GetFieldID age failed\n");
        return;
    }
    fieldID_name = env->GetFieldID(class_student, "name", "Ljava/lang/String;");
    if (fieldID_name == NULL) {
        LOGE(TAG, "GetFieldID name failed\n");
        return;
    }
    // 获取age的值
    jint age_in = env->GetIntField(student_in, fieldID_age);
    LOGE(TAG, "student_in age: %d\n", age_in);
    // 修改age的值
    env->SetIntField(student_in, fieldID_age, 22);

    // 获取name的值
    jstring name_in = (jstring) env->GetObjectField(student_in, fieldID_name);
    LOGE(TAG, "student_in name: %s\n", jstringToChar(env, name_in));
    // 修改name的值
    env->SetObjectField(student_in, fieldID_name, charToJstring(env, "wangwu"));

    // 删除局部引用
    env->DeleteLocalRef(name_in);
    env->DeleteLocalRef(class_student);
}

void accessStaticFiled(
        JNIEnv *env,
        jobject /* this */) {
    jclass class_student;
    jfieldID fieldID_staticId;
    jfieldID fieldID_staticString;

    class_student = env->FindClass("com/android/lightnative/bean/Student");
    if (class_student == NULL) {
        LOGE(TAG, "FindClass failed\n");
        return;
    }

    fieldID_staticId = env->GetStaticFieldID(class_student, "staticId", "I");
    if (fieldID_staticId == NULL) {
        LOGE(TAG, "GetStaticFieldID fieldID_staticId failed\n");
        return;
    }
    fieldID_staticString = env->GetStaticFieldID(class_student, "staticString",
                                                 "Ljava/lang/String;");
    if (fieldID_staticString == NULL) {
        LOGE(TAG, "GetStaticFieldID fieldID_staticString failed\n");
        return;
    }

    // 获取Student类静态变量staticId的值
    jint staticId_in = env->GetStaticIntField(class_student, fieldID_staticId);
    LOGE(TAG, "Student.staticId: %d\n", staticId_in);
    // 修改Student类静态变量staticId的值
    env->SetStaticIntField(class_student, fieldID_staticId, staticId_in + 1);


    // 获取Student类静态变量staticString的值
    jstring staticString_in = (jstring) env->GetStaticObjectField(class_student,
                                                                  fieldID_staticString);
    char *buf = jstringToChar(env, staticString_in);
    LOGE(TAG, "Student.staticString: %s\n", buf);
    free(buf);
    // 修改Student类静态变量staticString的值
    env->SetStaticObjectField(class_student, fieldID_staticString, charToJstring(env, "Hello"));

    // 释放局部引用
    env->DeleteLocalRef(staticString_in);
    env->DeleteLocalRef(class_student);
}