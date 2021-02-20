//
//  Logger.h
//  changyoyo_cloud_mno
//
//  Created by changyoyo on 2019/3/26.
//  Copyright © 2019年 changyoyo. All rights reserved.
//

#ifndef Logger_h
#define Logger_h

#import <Foundation/Foundation.h>

#ifdef DEBUG // DEBUG 版本
#define __DEBUG__
#else // RELEASE 版本
#undef __DEBUG__
#endif

#define LOG_LEVEL_DEBUG     5
#define LOG_LEVEL_INFO      4
#define LOG_LEVEL_WARN      3
#define LOG_LEVEL_ERROR     2
#define LOG_LEVEL_FATAL     1
#define CURRENT_LEVEL       LOG_LEVEL_DEBUG
#define LOG_TAG "mnoLog"

#define LOG(level, format, ...)                                               \
do {                                                                          \
NSLog(@"[%s][%s]%s[%d]:",LOG_TAG,level, __FUNCTION__, __LINE__);          \
NSLog(format, ##__VA_ARGS__);                                             \
NSLog(@"\n");                                                             \
} while(0)


#define LOG_ERR_FORMAT(level, format, ...)                                         \
do {                                                                               \
NSLog(@"\033[31m [%s][%s]%s[%d]:",LOG_TAG, level, __FUNCTION__, __LINE__ );    \
NSLog(format, ##__VA_ARGS__);                                                  \
NSLog(@" :( \033[0m\n");                                                       \
} while(0)

// "\033[31m 红色字 \033[0m"
#define LOG_ERROR(format, ...) if (CURRENT_LEVEL >= LOG_LEVEL_ERROR) { LOG_ERR_FORMAT("ERRO", format, ##__VA_ARGS__); }
#define LOG_FATAL(format, ...) if (CURRENT_LEVEL >= LOG_LEVEL_FATAL) { LOG_ERR_FORMAT("FATA", format, ##__VA_ARGS__); }

#ifdef __DEBUG__  //线下环境本地打日志

#define LOG_DEBUG(format, ...) if (CURRENT_LEVEL >= LOG_LEVEL_DEBUG) { LOG("DBUG", format, ##__VA_ARGS__); }
#define LOG_INFO(format, ...) if (CURRENT_LEVEL >= LOG_LEVEL_INFO) { LOG("INFO", format, ##__VA_ARGS__); }
#define LOG_WARNING(format, ...) if (CURRENT_LEVEL >= LOG_LEVEL_WARN) { LOG("WARN", format, ##__VA_ARGS__); }
#define ENTER_FUNC LOG_DEBUG(@"enter %s\n", __func__);
#define LEAVE_FUNC LOG_DEBUG(@"leave %s\n", __func__);
#else           //Release版本取消日志

#define LOG_DEBUG(format, ...)
#define LOG_INFO(format, ...)
#define LOG_WARNING(format, ...)
#define ENTER_FUNC
#define LEAVE_FUNC
#endif // END OF __DEBUG__

#endif /* Logger_h */
