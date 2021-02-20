//
//  MNOResult.h
//  changyoyo_cloud_mno
//
//  Created by ReidLee on 2018/6/15.
//  Copyright © 2018年 changyoyo. All rights reserved.
//
#import <Foundation/Foundation.h>

/**
 MNO 执行结果
 */
@interface MNOResult : NSObject

/**
 回调代码块定义
 @param result 执行结果 `MNOResult`
 */
typedef void (^MNOCallback)(MNOResult* result);
- (id) initWithCode:(NSString *)code msg:(NSString *) msg data:(NSString*) data;

/**
 * 执行结果的状态码
 */
@property  (nonatomic, copy) NSString *code;

/**
 * 执行结果描述
 */
@property  (nonatomic, copy) NSString *msg;

/**
 * 执行结果数据
 */
@property  (nonatomic, copy) NSString *data;

@end

