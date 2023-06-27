//
// Created by SuQi on 2023/6/24.
//
#include <jni.h>
#include <string>

#ifndef LIGHTNATIVE_OPERATE_ARRAY_H
#define LIGHTNATIVE_OPERATE_ARRAY_H
#ifdef __cplusplus
extern "C" {
#endif

// 和Java层的Student类对应
typedef struct Student {
    int age;
    char *name;
};

jintArray operateIntArray(
        JNIEnv *env,
        jobject /* this */,
        jintArray intArray_in);

jobjectArray operateStringArray(
        JNIEnv *env,
        jobject /* this */,
        jobjectArray stringArray_in);

jobjectArray operateStudentArray(
        JNIEnv *env,
        jobject /* this */,
        jobjectArray studentArray_in);

jobjectArray operateTwoIntArray(
        JNIEnv *env,
        jobject /* this */,
        jobjectArray objectArray_in);

#ifdef __cplusplus
}
#endif
#endif //LIGHTNATIVE_OPERATE_ARRAY_H