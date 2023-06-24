//
// Created by 小苏苏苏 on 2023/6/24.
//
#include <jni.h>
#include <string>

#ifndef LIGHTNATIVE_COMMON_UTILS_H
#define LIGHTNATIVE_COMMON_UTILS_H

jstring charToJstring(JNIEnv *env, const char *str);

char *jstringToChar(JNIEnv *env, jstring jstr);

#endif //LIGHTNATIVE_COMMON_UTILS_H
