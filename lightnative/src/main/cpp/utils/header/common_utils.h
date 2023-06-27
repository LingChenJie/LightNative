//
// Created by 小苏苏苏 on 2023/6/24.
//
#include "../../../../../../../../../Library/Android/sdk/ndk/23.1.7779620/toolchains/llvm/prebuilt/darwin-x86_64/sysroot/usr/include/jni.h"
#include "../../../../../../../../../Library/Android/sdk/ndk/23.1.7779620/toolchains/llvm/prebuilt/darwin-x86_64/sysroot/usr/include/c++/v1/string"

#ifndef LIGHTNATIVE_COMMON_UTILS_H
#define LIGHTNATIVE_COMMON_UTILS_H
#ifdef __cplusplus
extern "C" {
#endif

jstring charToJstring(JNIEnv *env, const char *str);

char *jstringToChar(JNIEnv *env, jstring jstr);

#ifdef __cplusplus
}
#endif
#endif //LIGHTNATIVE_COMMON_UTILS_H
