//
// Created by SuQi on 2023/6/24.
//
#include <jni.h>
#include <string>

#ifndef LIGHTNATIVE_OPERATE_EXCEPTION_H
#define LIGHTNATIVE_OPERATE_EXCEPTION_H
#ifdef __cplusplus
extern "C" {
#endif

void throwException(
        JNIEnv *env,
        jobject /* this */);

#ifdef __cplusplus
}
#endif
#endif //LIGHTNATIVE_OPERATE_EXCEPTION_H
