#ifndef _WATERPINE_COMMON_UTILS_LOG_H_
#define _WATERPINE_COMMON_UTILS_LOG_H_

#ifdef __ANDROID__

#include <android/log.h>

#define LOG(...) ((void)__android_log_print(ANDROID_LOG_INFO, "waterpine", __VA_ARGS__))
#define LOG_ERROR(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "waterpine", __VA_ARGS__))

#ifndef NDEBUG
#define LOGV(...) ((void)__android_log_print(ANDROID_LOG_VERBOSE, "waterpine", __VA_ARGS__))
#else
#define LOGV(...) ((void)0)
#endif

#define UNUSED(x) (void)(x)

#else

#include <cstdio>

#define LOG printf
#define LOG_ERROR printf

#endif

#endif  // _WATERPINE_COMMON_UTILS_LOG_H_
