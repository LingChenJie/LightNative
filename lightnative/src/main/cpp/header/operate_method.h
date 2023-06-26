//
// Created by SuQi on 2023/6/24.
//
#include <jni.h>
#include <string>

#ifndef LIGHTNATIVE_OPERATE_METHOD_H
#define LIGHTNATIVE_OPERATE_METHOD_H
#ifdef __cplusplus
extern "C" {
#endif

jobject callMethod(
        JNIEnv *env,
        jobject /* this */);

void callStaticMethod(
        JNIEnv *env,
        jobject /* this */);

void callSuperMethod(
        JNIEnv *env,
        jobject /* this */);

#ifdef __cplusplus
}
#endif
#endif //LIGHTNATIVE_OPERATE_METHOD_H
