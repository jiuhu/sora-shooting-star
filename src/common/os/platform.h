#ifndef _COMMON_OS_PLATFORM_H
#define _COMMON_OS_PLATFORM_H

#ifdef __APPLE__

#include "TargetConditionals.h"

#ifdef TARGET_OS_OSX
#define __DESKTOP__ 1
#define __OPENGL__ 1
#define __OSX__ 1

#elif TARGET_OS_IPHONE
#define __PHONE__ 1
#define __GLES__ 1
#define __IOS__ 1
#elif TARGET_IPHONE_SIMULATOR
#define __PHONE__ 1
#define __GLES__ 1
#define __IOS__ 1
#elif TARGET_OS_MAC
// other mac
#else
// Unsupported platform
#endif

#elif defined _WIN32 || defined _WIN64
#define __DESKTOP__ 1
#define __OPENGL__ 1

#elif __EMSCRIPTEN__
#define __WEB__ 1
#define __GLES__ 1

#endif

#endif  // _COMMON_OS_PLATFORM_H