//
// Created by 小苏苏苏 on 2023/6/19.
//
#include <jni.h>
#include <string>
#include <android/log.h>
#include "header/operate_transfer.h"
#include "header/common_utils.h"

#define TAG "TAG_OPERATE_TRANSFER"
#define LOGE(TAG, ...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)
#define ARRAY_LEN(x) ((int)(sizeof(x) / sizeof((x)[0])))

static JavaBean_t javaBean_t;
static InnerClass_t innerClass_t;

static int dump_JavaBean_Info(JavaBean *pJavaBean) {
    LOGE(TAG, "--------------dump_JavaBean_Info start------------------");
    LOGE(TAG, "stringValue: %s\n", pJavaBean->stringValue);
    LOGE(TAG, "boolValue: %d\n", pJavaBean->boolValue);
    LOGE(TAG, "charValue: %c\n", pJavaBean->charValue);
    LOGE(TAG, "doubleValue: %lf\n", pJavaBean->doubleValue);
    LOGE(TAG, "intValue: %d\n", pJavaBean->intValue);

    int length = ARRAY_LEN(pJavaBean->arrayValue);
    for (int i = 0; i < length; ++i) {
        LOGE(TAG, "byte[%d]: %d\n", i, pJavaBean->arrayValue[i]);
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            LOGE(TAG, "double[%d][%d]: %d\n", i, j, pJavaBean->doubleDimenArray[i][j]);
        }
    }
    LOGE(TAG, "message: %s\n", pJavaBean->message);
    LOGE(TAG, "--------------dump_JavaBean_Info end------------------");
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
    innerClass_t.constructor = env->GetMethodID(class_javaBean, "<init>", "()V");
    get_filed(env, class_javaBean, "stringValue", "Ljava/lang/String;", &javaBean_t.stringValue);
    get_filed(env, class_javaBean, "boolValue", "Z", &javaBean_t.boolValue);
    get_filed(env, class_javaBean, "charValue", "C", &javaBean_t.charValue);
    get_filed(env, class_javaBean, "charValue", "D", &javaBean_t.doubleValue);
    get_filed(env, class_javaBean, "intValue", "I", &javaBean_t.intValue);
    get_filed(env, class_javaBean, "byteArray", "B", &javaBean_t.byteArray);
    get_filed(env, class_javaBean, "byteArray", "[[I", &javaBean_t.doubleDimenArray);
    get_filed(env, class_javaBean, "innerClass",
              "Lcom/android/lightnative/bean/JavaBean$InnerClass;", &javaBean_t.innerClass);
}

static void register_class(JNIEnv *env) {
    register_javaBean_class(env);
    register_inner_class(env);
}

static jobject javaBean_cToJava(JNIEnv *env, JavaBean *pJavaBean) {
    if (pJavaBean == NULL) {
        LOGE(TAG, "pJavaBean is NULL\n");
        return NULL;
    }
    // 创建InnerClass
    jobject object_innerClass = env->NewObject(innerClass_t.clazz, innerClass_t.constructor);
    jstring string_message = env->NewStringUTF(pJavaBean->message);
    env->SetObjectField(object_innerClass, innerClass_t.message, string_message);

    // 创建JavaBean
    jobject object_javaBean = env->NewObject(javaBean_t.clazz, javaBean_t.constructor);
    env->SetObjectField(object_javaBean, javaBean_t.stringValue,
                        env->NewStringUTF(pJavaBean->stringValue));
    env->SetBooleanField(object_javaBean, javaBean_t.boolValue, pJavaBean->boolValue);
    env->SetCharField(object_javaBean, javaBean_t.charValue, pJavaBean->charValue);
    env->SetDoubleField(object_javaBean, javaBean_t.doubleValue, pJavaBean->doubleValue);
    env->SetIntField(object_javaBean, javaBean_t.intValue, pJavaBean->intValue);
    // byteArray
    jsize length = ARRAY_LEN(pJavaBean->arrayValue);
    jbyteArray byteArray = env->NewByteArray(length);
    env->SetByteArrayRegion(byteArray, 0, length, (jbyte *) pJavaBean->arrayValue);
    env->SetObjectField(object_javaBean, javaBean_t.byteArray, byteArray);
    // doubleDimenArray
    length = ARRAY_LEN(pJavaBean->doubleDimenArray);
    jclass clazz = env->FindClass("[I");// 一维数组的类
    jobjectArray double_int_array = env->NewObjectArray(length, clazz, NULL);
    for (int i = 0; i < length; ++i) {
        jsize sub_length = ARRAY_LEN(pJavaBean->doubleDimenArray[i]);
        jintArray intArray = env->NewIntArray(sub_length);
        env->SetIntArrayRegion(intArray, 0, sub_length, pJavaBean->doubleDimenArray[i]);
        env->SetObjectArrayElement(double_int_array, i, intArray);
    }
    env->SetObjectField(object_javaBean, javaBean_t.doubleDimenArray, double_int_array);
    // innerClass
    env->SetObjectField(object_javaBean, javaBean_t.innerClass, object_innerClass);

    return object_javaBean;
}

static void javaBean_javaToC(JNIEnv *env, jobject javaBean_in, JavaBean *pJavaBean_out) {

}

jobject getJavaBean(
        JNIEnv *env,
        jobject /* this */) {
    JavaBean javaBean = {

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
