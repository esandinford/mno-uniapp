//
//  MNOCommon.h
//  changyoyo_cloud_mno
//
//  Created by changyoyo on 2019/4/25.
//  Copyright © 2019 changyoyo. All rights reserved.
//

#ifndef MNOCommon_h
#define MNOCommon_h

typedef NSString *MNOErrorCode;

/**
 * 执行成功
 */
static MNOErrorCode const SUCCESS                                         = @"0";
/**
 * 执行异常（token没取到或其他本地错误）
 */
static MNOErrorCode const CLIENT_ERROR                                    = @"1";
/**
 * 用户取消了一键登录操作
 */
static MNOErrorCode const CLIENT_USER_CONCEL                              = @"2";
/**
 * 点击了其他方式登录按钮
 */
static MNOErrorCode const CLIENT_CHANGE                                   = @"3";
/**
 * 执行超时
 */
static MNOErrorCode const TIME_OUT                                        = @"4";
/**
 * 网络异常
 */
static MNOErrorCode const CLIENT_NETWORK_ERROR                            = @"5";

#endif /* MNOCommon_h */
