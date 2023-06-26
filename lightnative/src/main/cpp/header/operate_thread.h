//
// Created by SuQi on 2023/6/24.
//
#include <jni.h>
#include <string>

#ifndef LIGHTNATIVE_OPERATE_THREAD_H
#define LIGHTNATIVE_OPERATE_THREAD_H
#ifdef __cplusplus
extern "C" {
#endif

void threadWork(
        JNIEnv *env,
        jobject /* this */);

#ifdef __cplusplus
}
#endif
#endif //LIGHTNATIVE_OPERATE_THREAD_H
