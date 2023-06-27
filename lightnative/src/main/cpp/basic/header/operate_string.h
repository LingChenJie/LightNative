//
// Created by SuQi on 2023/6/24.
//
#include <jni.h>
#include <string>

#ifndef LIGHTNATIVE_OPERATE_STRING_H
#define LIGHTNATIVE_OPERATE_STRING_H
#ifdef __cplusplus
extern "C" {
#endif

jstring helloJni(
        JNIEnv *env,
        jobject /* this */,
        jstring string);

#ifdef __cplusplus
}
#endif
#endif //LIGHTNATIVE_OPERATE_STRING_H
