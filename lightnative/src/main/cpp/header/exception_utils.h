//
// Created by 小苏苏苏 on 2023/6/24.
//
#include <jni.h>
#include <string>

#ifndef LIGHTNATIVE_EXCEPTION_UTILS_H
#define LIGHTNATIVE_EXCEPTION_UTILS_H
#ifdef __cplusplus
extern "C" {
#endif

int checkException(JNIEnv *env);

void throwExceptionByName(JNIEnv *env, const char *exception_name, const char *msg);

#ifdef __cplusplus
}
#endif
#endif //LIGHTNATIVE_EXCEPTION_UTILS_H
