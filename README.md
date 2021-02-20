# mno-uniapp
一键登录(支持三网，支持页面定制)
## 概述
本接口提供一键登录(一键取号)，本机号码认证功能

---
### 商品地址
[https://market.aliyun.com/products/57126001/cmapi00044151.html](https://market.aliyun.com/products/57126001/cmapi00044151.html)

---
## 插件接口说明
插件地址：[https://ext.dcloud.net.cn/plugin?id=3446](https://ext.dcloud.net.cn/plugin?id=3446)

接口如下
### 获取手机号码
```java
/**
 * 获取手机号码
 * @param secretKey SDK授权密钥，和ios的bundleId/android的签名绑定，可向一砂索取,Android和IOS的密钥不一样
 * @param authUIConfigJson 登录授权⻚UI⾃定义配配置, 可参考Android/IOS授权界面客制化
 * @param mnoCallback 异步结果回调ret, 有三个字段：code, msg, data
        - code字段是执行状态码可能的值及描述： 
            "0": 客户端成功
            "1": 客户端失败（预取号，token没取到，其他本地错误）
            "2": 用户取消操作
            "3": 切换登录方式
            "4": 超时
            "5": 网络异常，请检查本机是否插入Sim卡或者蜂窝网络是否打开了
        - msg字段是结果的描述，给程序员调试看的
        - data字段是执行结果(json字符串)，内容如下：
               {
                  "deviceModel": "",
                  "packageId": "",
                  "platform": "",
                  "token": "",
                  "transId": "",
                  "appName": ""
              }
 */
MNOModule.getPhoneNum(secretKey, authUIConfigJson, mnoCallback)
 ```


## 其他信息
1. 完整接入文档：[https://esandinfo.yuque.com/yv6e1k/caebif/bd2u6a](https://esandinfo.yuque.com/yv6e1k/caebif/bd2u6a)
2. 服务器端协议文档：[https://market.aliyun.com/products/57126001/cmapi00044151.html?spm=5176.2020520132.101.2.2fda7218U1yeq5#sku=yuncode3815100001](https://market.aliyun.com/products/57126001/cmapi00044151.html?spm=5176.2020520132.101.2.2fda7218U1yeq5#sku=yuncode3815100001)
3. 后端管理控制台地址: [http://openali.esandcloud.com](http://openali.esandcloud.com)
4. 技术支持
```
微信：esand_info
qq: 3626921591
电话：18033076802
邮箱：ruide.li@esandinfo.com
```
![wechatqrcode](http://open.esandcloud.com/share/index.php/s/hzT4Gb0BN81svae/download)

