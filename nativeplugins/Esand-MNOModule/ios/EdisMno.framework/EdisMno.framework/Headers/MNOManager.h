//
//  MNOManager.h
//  changyoyo_cloud_mno
//
//  Created by changyoyo on 2019/2/21.
//  Copyright © 2019年 changyoyo. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "MNOResult.h"
#import "TXCustomModel.h"

/**
 * 此类提供 MNO 的如下功能：
 * - 一键登录(取号)
 * - 本机号码认证
 */
@interface MNOManager:NSObject

/*
 * 初始化
 */
- (id) init;

/**
 * 一键登录
 * @param vc UIViewController
 * @param secretKey SDK授权密钥，和bundleId绑定，可向一砂索取
 * @param model 客制化授权界面示例(可为空)
 * @param callback 回调，result.code可能的值：
 * SUCCESS,CLIENT_NETWORK_ERROR,CLIENT_NETWORK_ERROR,CLIENT_USER_CONCEL,TIME_OUT,CLIENT_CHANGE,返回报文内容如下（result.data字段）：
 <pre>
 {
    "deviceModel": "",
    "packageId": "",
    "platform": "",
    "token": "",
    "transId": "",
    "appName": ""
 }
 </pre>
 */
- (void)getPhoneNum:(UIViewController *) vc secretKey:(NSString*)secretKey model: (TXCustomModel* _Nullable) model callback:(MNOCallback) callback;

/**
 * 本机号码校验
 * @param phoneNumber 手机号码
 * @param secretKey SDK授权密钥，和bundleId绑定，可向一砂索取
 * @param callback 回调，result.code可能的值：
 *          SUCCESS,CLIENT_NETWORK_ERROR,CLIENT_NETWORK_ERROR,返回报文内容如下（result.data字段）：
  <pre>
 {
    "deviceModel": "",
    "packageId": "",
    "platform": "",
    "token": "",
    "transId": "",
    "appName": "",
    "phoneNum": ""
 }
  </pre>
 */
- (void)verifyPhoneNum:(NSString*)phoneNumber secretKey:(NSString*)secretKey callback:(MNOCallback)callback;

/**
 * 检查本机的执行环境
 * @return 返回内容(key:value)：
 * <pre>
 *      Version: 当前版本
 *      CellularData: 蜂窝网络是否开启
 *      Operator: 当前sim卡运营商 ChinaMobile, ChinaTelecom, ChinaUnicom
 *      NetworkName: 获取当前上网卡网络名称 ChinaMobile,ChinaUnicom,ChinaTelecom,OtherChinaMobileNetwork,NoChinaMobileNetwork
 *      CarrierName: 当前上网卡运营商名称: 中国移动，中国联通，中国电信
 *      NetworkType: 当前上网网络类型 WiFi，4G，3G，2G，NoInternet
 *      HasSim: 设备是否有SIM卡 YES, NO
 *      IsWWANOpen: wwan是否开启
 *      IP: 设备当前网络私网IP地址
 * </pre>
 */
+ (NSMutableDictionary*_Nullable) checkEnv;

@end
