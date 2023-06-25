//
// Created by SuQi on 2023/6/24.
//
#include <jni.h>
#include <string>

#ifndef LIGHTNATIVE_OPERATE_FIELD_H
#define LIGHTNATIVE_OPERATE_FIELD_H
#ifdef __cplusplus
extern "C" {
#endif

void accessFiled(
        JNIEnv *env,
        jobject /* this */,
        jobject student_in);

void accessStaticFiled(
        JNIEnv *env,
        jobject /* this */);

#ifdef __cplusplus
}
#endif
#endif //LIGHTNATIVE_OPERATE_FIELD_H
