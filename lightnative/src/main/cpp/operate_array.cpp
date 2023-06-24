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

jobjectArray operateStudentArray(
        JNIEnv *env,
        jobject /* this */,
        jobjectArray studentArray_in) {
    // ---------------解析从Java Native得到的studentArray数组-----------
    jclass class_student = env->FindClass("com/android/lightnative/bean/Student");
    jfieldID fieldId_age = env->GetFieldID(class_student, "age", "I");
    jfieldID fieldId_name = env->GetFieldID(class_student, "name", "Ljava/lang/String;");
    const int length_in = env->GetArrayLength(studentArray_in);//获取数组长度

    // 将数组分转换成结构体
    jobject student_in;
    Student students_in[length_in];
    for (int i = 0; i < length_in; ++i) {
        student_in = env->GetObjectArrayElement(studentArray_in, i);
        students_in[i].age = env->GetIntField(student_in, fieldId_age);
        students_in[i].name = jstringToChar(env,
                                            (jstring) env->GetObjectField(student_in,
                                                                          fieldId_name));
        LOGE(TAG, "students_in[%d] age : %d\n", i, students_in[i].age);
        LOGE(TAG, "students_in[%d] name : %s\n", i, students_in[i].name);
    }

    // ---------------创建自定义Class数组对象并返回-----------
    const int length_out = 2;
    Student students_out[length_out];
    for (int i = 0; i < length_out; ++i) {
        students_out[i].age = 10 + i;
        students_out[i].name = (char *) malloc(sizeof(char) * 20);//长度为20
        sprintf(students_out[i].name, "name : %d", i);
    }

    // 这里获得构造函数方法
    jmethodID methodID_student_init = env->GetMethodID(class_student, "<init>", "()V");
    // 将数据封装成对象然后再封装成数组
    jobject student_out;
    // 创建Student对象数组
    jobjectArray studentArray_out = env->NewObjectArray(length_out, class_student, NULL);
    for (int i = 0; i < length_out; ++i) {
        student_out = env->NewObject(class_student, methodID_student_init);
        env->SetIntField(student_out, fieldId_age, students_out[i].age);
        env->SetObjectField(student_out, fieldId_name, charToJstring(env, students_out[i].name));
        // 将对象插入到数组的特定位置
        env->SetObjectArrayElement(studentArray_out, i, student_out);
    }
    return studentArray_out;
}

jobjectArray operateTwoIntArray(
        JNIEnv *env,
        jobject /* this */,
        jobjectArray objectArray_in) {
    // ---------------解析从Java Native得到的int型二维数组-----------
    const int row = env->GetArrayLength(objectArray_in);// 获取二维数组的行数
    jarray array = (jarray) env->GetObjectArrayElement(objectArray_in, 0);
    const int col = env->GetArrayLength(array);//获取二维数组每行的列数

    // 根据行数和列数创建int型二维数组
    jint intDimArray_in[row][col];
    for (int i = 0; i < row; ++i) {
        array = (jintArray) env->GetObjectArrayElement(objectArray_in, i);
        // 操作方式1，这种方式会申请native memory内存
        jint *coldata = env->GetIntArrayElements((jintArray) array, NULL);
        for (int j = 0; j < col; ++j) {
            intDimArray_in[i][j] = coldata[j];// 取出JAVA类中int二维数组的数据,并赋值给JNI中的数组
        }

        // 操作方式2，赋值，这种方式不会申请内存
        env->GetIntArrayRegion((jintArray) array, 0, col, (jint *) &intDimArray_in[i]);

        env->ReleaseIntArrayElements((jintArray) array, coldata, 0);
    }

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            LOGE(TAG, "The intDimArray_in[%d][%d] is %d\n", i, j, intDimArray_in[i][j]);
        }
    }

    // ---------------创建一个int型二维数组返回给Java-----------
    const int row_out = 2;// 行数
    const int col_out = 2;// 列数

    // 获取数组的class
    jclass class_int_array = env->FindClass("[I");// 一维数组的类
    // 新建object数组，里面是int[]
    jobjectArray intDimArray_out = env->NewObjectArray(row_out, class_int_array, NULL);

    int temp_array[row_out][col_out] = {{0, 1},
                                        {2, 3}};
    for (int i = 0; i < row_out; ++i) {
        jintArray intArray = env->NewIntArray(col_out);
        env->SetIntArrayRegion(intArray, 0, col_out, (jint *) &temp_array[i]);
        env->SetObjectArrayElement(intDimArray_out, i, intArray);
    }
    return intDimArray_out;
}