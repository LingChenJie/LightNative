//
// Created by SuQi on 2023/6/24.
//
#include <jni.h>
#include <string>
#include <cstdio>
#include <android/log.h>
#include "header/operate_array.h"
#include "header/common_utils.h"

#define TAG "TAG_OPERATE_ARRAY"
#define LOGE(TAG, ...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

jintArray operateIntArray(
        JNIEnv *env,
        jobject /* this */,
        jintArray inIntArray) {
    LOGE(TAG, "operateIntArray()\n");
    // ---------------解析从Java Native得到的jintArray数组-----------
    jint *pJint;
    // 操作方式1
    // 如同 getUTFString 一样，会申请 native 内存
    pJint = env->GetIntArrayElements(inIntArray, NULL);
    if (pJint == NULL) {
        return NULL;
    }
    // 得到数组的长度
    const int length = env->GetArrayLength(inIntArray);
    LOGE(TAG, "The inIntArray length is : %d\n", length);
    for (int i = 0; i < length; ++i) {
        LOGE(TAG, "The inIntArray[%d] is %d\n", i, pJint[i]);
    }

    // 操作方式2
    if (length > 0) {
        jint *buff_in;// 定义一个jni型数组
        buff_in = (int *) malloc(sizeof(int) * length);
        env->GetIntArrayRegion(inIntArray, 0, length, buff_in);
        free(buff_in);
    }

    // 对于操作方式1，使用完了需要啊释放内存
    env->ReleaseIntArrayElements(inIntArray, pJint, 0);


    // ----------------从JNI返回jintArray给Java层----------------
    jintArray outIntArray;// 返回给Java
    const int out_length = 10;
    outIntArray = env->NewIntArray(out_length);
    jint buff_out[out_length] = {0};
    for (int i = 0; i < out_length; ++i) {
        buff_out[i] = i * 10;
    }
    // 使用SetIntArrayRegion赋值
    env->SetIntArrayRegion(outIntArray, 0, out_length, buff_out);
    return outIntArray;
}

jobjectArray operateStringArray(
        JNIEnv *env,
        jobject /* this */,
        jobjectArray stringArray_in) {
    LOGE(TAG, "operateStringArray()\n");
    // ---------------解析从Java Native得到的stringArray数组-----------
    jsize length = env->GetArrayLength(stringArray_in);
    for (int i = 0; i < length; ++i) {
        jstring string_in = (jstring) env->GetObjectArrayElement(stringArray_in, i);
        char *char_in = jstringToChar(env, string_in);
        LOGE(TAG, "stringArray_in[%d] : %s\n", i, char_in);
    }

    // ---------------从JNI返回String数组给Java层-----------
    jclass class_string = env->FindClass("java/lang/String");
    jobjectArray outStringArray;
    const int out_length = 5;
    outStringArray = env->NewObjectArray(out_length, class_string, NULL);
    char *char_out[] = {"Hello", "world", "JNI", "is", "run."};

    jstring temp_string;
    for (int i = 0; i < out_length; ++i) {
        temp_string = charToJstring(env, char_out[i]);
        env->SetObjectArrayElement(outStringArray, i, temp_string);
    }
    return outStringArray;
}