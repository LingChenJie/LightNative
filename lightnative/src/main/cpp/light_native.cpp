#include <jni.h>
#include <string>
#include <android/log.h>

#define TAG "LIGHT_NATIVE_TAG"
#define LOGE(TAG, ...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)


// 静态注册
//extern "C" JNIEXPORT jstring JNICALL
//Java_com_android_lightnative_LightNativeLib_hello(
//        JNIEnv *env,
//        jobject /* this */) {
//    LOGE(TAG, "Java_com_android_lightnative_LightNativeLib_hello()\n");
//    std::string hello = "Hello from C++";
//    return env->NewStringUTF(hello.c_str());
//}
// 动态注册定义的方法
jstring hello(
        JNIEnv *env,
        jobject /* this */) {
    LOGE(TAG, "hello()\n");
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

// 调用RegisterNatives注册本地函数
static int registerNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *getMethods,
                                 int methodsNum) {
    jclass clazz;
    // 找到申明native的类
    clazz = env->FindClass(className);
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    // 注册函数
    if (env->RegisterNatives(clazz, getMethods, methodsNum) < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

// 注册LightNativeLib的方法
static int registerLightNativeLib(JNIEnv *env) {
    // 指定类的路径，通过FindClass方法来找到对应的类
    const char *className = "com/android/lightnative/LightNativeLib";
    JNINativeMethod methods[] =
            {
                    {"hello", "()Ljava/lang/String;", (void *) hello},
            };
    return registerNativeMethods(env, className, methods, sizeof(methods) / sizeof(methods[0]));
}

// 动态注册
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGE(TAG, "JNI_OnLoad\n");
    JNIEnv *env = NULL;
    // 获取JNIEnv
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    // 注册函数
    if (!registerLightNativeLib(env)) {
        return -1;
    }
    return JNI_VERSION_1_6;
}