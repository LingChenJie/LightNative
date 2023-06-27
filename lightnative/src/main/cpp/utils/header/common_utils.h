//
// Created by 小苏苏苏 on 2023/6/24.
//
#include <jni.h>
#include <string>

#ifndef LIGHTNATIVE_COMMON_UTILS_H
#define LIGHTNATIVE_COMMON_UTILS_H
#ifdef __cplusplus
extern "C" {
#endif

jstring charToJstring(JNIEnv *env, const char *str);

char *jstringToChar(JNIEnv *env, jstring jstr);

int findClass(JNIEnv *env, const char *className, jclass *classOut);

int getFiledID(JNIEnv *env, jclass clazz, const char *name, const char *sig, jfieldID *filedIdOut);

#ifdef __cplusplus
}
#endif
#endif //LIGHTNATIVE_COMMON_UTILS_H
