//
// Created by SuQi on 2023/6/24.
//
#include <android/log.h>
#include "header/log_utils.h"

#define TAG "LIGHT_NATIVE"

static bool isEnableLog = true;

void setEnableLog(bool enable) {
    isEnableLog = enable;
}

bool getEnableLog() {
    return isEnableLog;
}

/**
 * Verbose logging
 * @param fmt format
 * @param values
 */
void LOGV(const char *fmt, ...) {
    if (!isEnableLog) {
        return;
    }
    va_list vaList;
    va_start(vaList, fmt);
    __android_log_vprint(ANDROID_LOG_VERBOSE, TAG, fmt, vaList);
    va_end(vaList);
}

/**
 * Debug logging
 * @param fmt format
 * @param values
 */
void LOGD(const char *fmt, ...) {
    if (!isEnableLog) {
        return;
    }
    va_list vaList;
    va_start(vaList, fmt);
    __android_log_vprint(ANDROID_LOG_DEBUG, TAG, fmt, vaList);
    va_end(vaList);
}

/**
 * Informational logging
 * @param fmt format
 * @param values
 */
void LOGI(const char *fmt, ...) {
    if (!isEnableLog) {
        return;
    }
    va_list vaList;
    va_start(vaList, fmt);
    __android_log_vprint(ANDROID_LOG_INFO, TAG, fmt, vaList);
    va_end(vaList);
}

/**
 * Warning logging
 * @param fmt format
 * @param values
 */
void LOGW(const char *fmt, ...) {
    if (!isEnableLog) {
        return;
    }
    va_list vaList;
    va_start(vaList, fmt);
    __android_log_vprint(ANDROID_LOG_WARN, TAG, fmt, vaList);
    va_end(vaList);
}

/**
 * Error logging
 * @param fmt format
 * @param values
 */
void LOGE(const char *fmt, ...) {
    if (!isEnableLog) {
        return;
    }
    va_list vaList;
    va_start(vaList, fmt);
    __android_log_vprint(ANDROID_LOG_ERROR, TAG, fmt, vaList);
    va_end(vaList);
}