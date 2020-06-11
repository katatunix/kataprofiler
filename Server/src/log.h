#pragma once

#define VERBOSE 0

#if defined OS_ANDROID
	#define LOG_TAG "KataProfiler"
	#include <android/log.h>
	#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,		LOG_TAG,	__VA_ARGS__)
	#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,		LOG_TAG,	__VA_ARGS__)
	#if VERBOSE
		#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,		LOG_TAG,	__VA_ARGS__)
	#else
		#define LOGD(...)
	#endif
	#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,		LOG_TAG,	__VA_ARGS__)

#elif defined OS_TIZEN
	#include <FBaseLog.h>
	#define LOGI			AppLog
	#define LOGE			AppLogException
	#if VERBOSE
		#define LOGD		AppLog
	#else
		#define LOGD
	#endif
	#define LOGW			AppLog

#elif defined OS_WIN32
	#include <stdio.h>
	#define LOGI(...)		{ char buf[1024]; sprintf(buf, __VA_ARGS__); printf("[KataProfiler] %s\n", buf); }
	#define LOGE(...)		{ char buf[1024]; sprintf(buf, __VA_ARGS__); printf("[KataProfiler_ERROR] %s\n", buf); }
	//#define LOGE(...)
	#if VERBOSE	
		#define LOGD(...)		{ char buf[1024]; sprintf(buf, __VA_ARGS__); printf("[KataProfiler] %s\n", buf); }
	#else	
		#define LOGD(...)
	#endif
	#define LOGW(...)		{ char buf[1024]; sprintf(buf, __VA_ARGS__); printf("[KataProfiler_WARNING] %s\n", buf); }
#endif
