//
// Created by 小苏苏苏 on 2023/6/24.
//
#include <jni.h>
#include <string>

#ifndef LIGHTNATIVE_ENV_UTILS_H
#define LIGHTNATIVE_ENV_UTILS_H
#ifdef __cplusplus
extern "C" {
#endif

class JniData {
public:
    static JavaVM *vm;
};

void setJavaVM(JavaVM *vm);

JNIEnv *GetAttachEnv();

jint DetachEnv();

#ifdef __cplusplus
}
#endif
#endif //LIGHTNATIVE_ENV_UTILS_H
