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
    jint age_in = env->GetIntField(class_student, fieldID_age);
    LOGE(TAG, "student_in age: %d\n", age_in);
    // 修改age的值
    env->SetIntField(class_student, fieldID_age, 22);

    // 获取name的值
    jstring name_in = (jstring) env->GetObjectField(class_student, fieldID_name);
    LOGE(TAG, "student_in name: %s\n", jstringToChar(env, name_in));
    // 修改name的值
    env->SetObjectField(class_student, fieldID_name, charToJstring(env, "wangwu"));

    // 删除局部引用
    env->DeleteLocalRef(name_in);
    env->DeleteLocalRef(class_student);
}