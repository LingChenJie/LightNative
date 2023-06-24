//
// Created by SuQi on 2023/6/24.
//
#include <jni.h>
#include <string>

#ifndef LIGHTNATIVE_OPERATE_ARRAY_H
#define LIGHTNATIVE_OPERATE_ARRAY_H

jintArray operateIntArray(
        JNIEnv *env,
        jobject /* this */,
        jintArray intArray_in);

#endif //LIGHTNATIVE_OPERATE_ARRAY_H