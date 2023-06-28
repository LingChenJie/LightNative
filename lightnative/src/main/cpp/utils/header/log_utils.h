//
// Created by 小苏苏苏 on 2023/6/24.
//
#include <jni.h>
#include <string>

#ifndef LIGHTNATIVE_LOG_UTILS_H
#define LIGHTNATIVE_LOG_UTILS_H
#ifdef __cplusplus
extern "C" {
#endif

void setEnableLog(bool enable);
bool getEnableLog();

/**
 * Verbose logging
 * @param fmt format
 * @param values
 */
void LOGV(const char *fmt, ...);

/**
 * Debug logging
 * @param fmt format
 * @param values
 */
void LOGD(const char *fmt, ...);

/**
 * Informational logging
 * @param fmt format
 * @param values
 */
void LOGI(const char *fmt, ...);

/**
 * Warning logging
 * @param fmt format
 * @param values
 */
void LOGW(const char *fmt, ...);

/**
 * Error logging
 * @param fmt format
 * @param values
 */
void LOGE(const char *fmt, ...);

#ifdef __cplusplus
}
#endif
#endif //LIGHTNATIVE_LOG_UTILS_H
