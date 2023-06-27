//
// Created by 小苏苏苏 on 2023/6/19.
//
#include <jni.h>
#include <string>
#include <android/log.h>
#include "header/operate_transfer.h"
#include "../utils/header/common_utils.h"

#define TAG "TAG_OPERATE_TRANSFER"
#define LOGE(TAG, ...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)
#define ARRAY_LEN(x) ((int)(sizeof(x) / sizeof((x)[0])))

static JavaBean_t javaBean_t;
static InnerClass_t innerClass_t;

static int dump_JavaBean_Info(JavaBean *javaBean) {
    LOGE(TAG, "--------------dump_JavaBean_Info start------------------\n");
    LOGE(TAG, "stringValue: %s\n", javaBean->stringValue);
    LOGE(TAG, "boolValue: %d\n", javaBean->boolValue);
    LOGE(TAG, "charValue: %c\n", javaBean->charValue);
    LOGE(TAG, "doubleValue: %lf\n", javaBean->doubleValue);
    LOGE(TAG, "intValue: %d\n", javaBean->intValue);

    int length = ARRAY_LEN(javaBean->byteArray);
    for (int i = 0; i < length; ++i) {
        LOGE(TAG, "byte[%d]: %d\n", i, javaBean->byteArray[i]);
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            LOGE(TAG, "double[%d][%d]: %d\n", i, j, javaBean->doubleDimenArray[i][j]);
        }
    }
    LOGE(TAG, "message: %s\n", javaBean->message);
    LOGE(TAG, "--------------dump_JavaBean_Info end------------------\n");
    return 0;
}

static int find_class(JNIEnv *env, const char *className, jclass *classOut) {
    jclass clazz = env->FindClass(className);
    if (clazz == NULL) {
        LOGE(TAG, "FindClass failed for class %s\n", className);
        return -1;
    }
    *classOut = (jclass) env->NewGlobalRef(clazz);// 这里必须新建一个全局的引用
    return 0;
}

static int
get_filed(JNIEnv *env, jclass clazz, const char *name, const char *sig, jfieldID *filedIdOut) {
    jfieldID fieldID = env->GetFieldID(clazz, name, sig);
    if (fieldID == NULL) {
        LOGE(TAG, "GetFieldID failed for name: %s, sig: %s", name, sig);
        return -1;
    }
    *filedIdOut = fieldID;
    return 0;
}

static void register_inner_class(JNIEnv *env) {
    int ret = find_class(env, "com/android/lightnative/bean/JavaBean$InnerClass",
                         &innerClass_t.clazz);
    if (ret != 0) {
        LOGE(TAG, "register_inner_class failed\n");
        return;
    }
    jclass class_inner = innerClass_t.clazz;
    innerClass_t.constructor = env->GetMethodID(class_inner, "<init>", "()V");
    get_filed(env, class_inner, "message", "Ljava/lang/String;", &innerClass_t.message);
}

static void register_javaBean_class(JNIEnv *env) {
    int ret = find_class(env, "com/android/lightnative/bean/JavaBean",
                         &javaBean_t.clazz);
    if (ret != 0) {
        LOGE(TAG, "register_javaBean_class failed\n");
        return;
    }
    jclass class_javaBean = javaBean_t.clazz;
    javaBean_t.constructor = env->GetMethodID(class_javaBean, "<init>", "()V");
    get_filed(env, class_javaBean, "stringValue", "Ljava/lang/String;", &javaBean_t.stringValue);
    get_filed(env, class_javaBean, "boolValue", "Z", &javaBean_t.boolValue);
    get_filed(env, class_javaBean, "charValue", "C", &javaBean_t.charValue);
    get_filed(env, class_javaBean, "doubleValue", "D", &javaBean_t.doubleValue);
    get_filed(env, class_javaBean, "intValue", "I", &javaBean_t.intValue);
    get_filed(env, class_javaBean, "byteArray", "[B", &javaBean_t.byteArray);
    get_filed(env, class_javaBean, "doubleDimenArray", "[[I", &javaBean_t.doubleDimenArray);
    get_filed(env, class_javaBean, "innerClass",
              "Lcom/android/lightnative/bean/JavaBean$InnerClass;", &javaBean_t.innerClass);
}

void register_class(JNIEnv *env) {
    register_javaBean_class(env);
    register_inner_class(env);
}

static jobject javaBean_cToJava(JNIEnv *env, JavaBean *javaBean) {
    if (javaBean == NULL) {
        LOGE(TAG, "javaBean is NULL\n");
        return NULL;
    }
    // 创建InnerClass
    jobject object_innerClass = env->NewObject(innerClass_t.clazz, innerClass_t.constructor);
    // message
    jstring string_message = env->NewStringUTF(javaBean->message);
    env->SetObjectField(object_innerClass, innerClass_t.message, string_message);

    // 创建JavaBean
    jobject object_javaBean = env->NewObject(javaBean_t.clazz, javaBean_t.constructor);
    // stringValue
    jstring string_stringValue = env->NewStringUTF(javaBean->stringValue);
    env->SetObjectField(object_javaBean, javaBean_t.stringValue, string_stringValue);
    // boolValue
    env->SetBooleanField(object_javaBean, javaBean_t.boolValue, javaBean->boolValue);
    // charValue
    env->SetCharField(object_javaBean, javaBean_t.charValue, javaBean->charValue);
    // doubleValue
    env->SetDoubleField(object_javaBean, javaBean_t.doubleValue, javaBean->doubleValue);
    // intValue
    env->SetIntField(object_javaBean, javaBean_t.intValue, javaBean->intValue);
    // byteArray
    jsize length = ARRAY_LEN(javaBean->byteArray);
    jbyteArray byteArray = env->NewByteArray(length);
    env->SetByteArrayRegion(byteArray, 0, length, (jbyte *) javaBean->byteArray);
    env->SetObjectField(object_javaBean, javaBean_t.byteArray, byteArray);
    // doubleDimenArray
    length = ARRAY_LEN(javaBean->doubleDimenArray);
    jclass clazz = env->FindClass("[I");// 一维数组的类
    jobjectArray double_int_array = env->NewObjectArray(length, clazz, NULL);
    jintArray intArray;
    for (int i = 0; i < length; ++i) {
        jsize sub_length = ARRAY_LEN(javaBean->doubleDimenArray[i]);
        intArray = env->NewIntArray(sub_length);
        env->SetIntArrayRegion(intArray, 0, sub_length, javaBean->doubleDimenArray[i]);
        env->SetObjectArrayElement(double_int_array, i, intArray);
    }
    env->SetObjectField(object_javaBean, javaBean_t.doubleDimenArray, double_int_array);
    // innerClass
    env->SetObjectField(object_javaBean, javaBean_t.innerClass, object_innerClass);

    // 删除局部引用
    env->DeleteLocalRef(object_innerClass);
    env->DeleteLocalRef(string_message);
    env->DeleteLocalRef(string_stringValue);
    env->DeleteLocalRef(byteArray);
    env->DeleteLocalRef(clazz);
    env->DeleteLocalRef(double_int_array);
    env->DeleteLocalRef(intArray);

    return object_javaBean;
}

static void javaBean_javaToC(JNIEnv *env, jobject object_javaBean, JavaBean *javaBean_out) {
    if (object_javaBean == NULL) {
        LOGE(TAG, "object_javaBean is NULL\n");
        return;
    }
    // stringValue
    jstring string_stringValue = (jstring) env->GetObjectField(object_javaBean,
                                                               javaBean_t.stringValue);
    javaBean_out->stringValue = env->GetStringUTFChars(string_stringValue, NULL);
    // boolValue
    javaBean_out->boolValue = env->GetBooleanField(object_javaBean, javaBean_t.boolValue);
    // charValue
    javaBean_out->charValue = env->GetCharField(object_javaBean, javaBean_t.charValue);
    // doubleValue
    javaBean_out->doubleValue = env->GetDoubleField(object_javaBean, javaBean_t.doubleValue);
    // intValue
    javaBean_out->intValue = env->GetIntField(object_javaBean, javaBean_t.intValue);
    // byteArray
    jbyteArray byteArray = (jbyteArray) env->GetObjectField(object_javaBean, javaBean_t.byteArray);
    jbyte *byte_data = env->GetByteArrayElements(byteArray, NULL);
    jsize length = env->GetArrayLength(byteArray);
    memcpy(javaBean_out->byteArray, byte_data, sizeof(jbyte) * length);
    // doubleDimenArray
    jobjectArray objectArray = (jobjectArray) env->GetObjectField(object_javaBean,
                                                                  javaBean_t.doubleDimenArray);
    length = env->GetArrayLength(objectArray);
    for (int i = 0; i < length; ++i) {
        jintArray intArray = (jintArray) env->GetObjectArrayElement(objectArray, i);
        jint *sub_int = env->GetIntArrayElements(intArray, 0);
        jsize sub_length = env->GetArrayLength(intArray);
        memcpy(javaBean_out->doubleDimenArray[i], sub_int, sizeof(jint) * sub_length);
        env->ReleaseIntArrayElements(intArray, sub_int, 0);
    }
    // innerClass
    jobject object_innerClass = env->GetObjectField(object_javaBean, javaBean_t.innerClass);
    jstring string_message = (jstring) env->GetObjectField(object_innerClass, innerClass_t.message);
    javaBean_out->message = env->GetStringUTFChars(string_message, NULL);

    // 删除局部引用
    env->DeleteLocalRef(string_stringValue);
    env->DeleteLocalRef(byteArray);
    env->DeleteLocalRef(objectArray);
    env->DeleteLocalRef(object_innerClass);
    env->DeleteLocalRef(string_message);
}

jobject getJavaBean(
        JNIEnv *env,
        jobject /* this */) {
    JavaBean javaBean = {
            "I'm StringValue",
            true,
            'C',
            2.0,
            5,
            {1, 2, 3, 5},
            {
                    {6, 7},
                    {9, 0}
            },
            "I'm message"
    };
    dump_JavaBean_Info(&javaBean);
    jobject object = javaBean_cToJava(env, &javaBean);
    return object;
}

void transferJavaBean(
        JNIEnv *env,
        jobject /* this */,
        jobject javaBean_in) {
    JavaBean javaBean;
    javaBean_javaToC(env, javaBean_in, &javaBean);
    dump_JavaBean_Info(&javaBean);
}
