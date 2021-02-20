## 商品地址

https://market.aliyun.com/products/57126001/cmapi00044151.html

## 产品介绍

本接口提供一键登录(一键取号)，本机号码认证功能

## 使用方式

### 1. 将插件Esand-MNOModule放入项目根目录下的nativeplugins文件夹下

### 2. 导入插件

### 3. 到商品地址购买免费套餐（不用花钱!!!!!）

### 4. 替换自己的appcode

### 5. 申请secretKey

### 6. 调用插件


#### 业务流程
如下
![](https://cdn.nlark.com/yuque/__puml/ec20b86b478363b9a525d7ddf4a6f5fc.svg#lake_card_v2=eyJjb2RlIjoiQHN0YXJ0dW1sXG5hdXRvbnVtYmVyXG5cbmFjdG9yIOeUqOaItyAjeWVsbG93XG5wYXJ0aWNpcGFudCBNTk9Nb2R1bGUgI29yYW5nZVxucGFydGljaXBhbnQgQVBQICNncmVlblxucGFydGljaXBhbnQg5Lia5Yqh5pyN5Yqh5ZmoICNncmVlbiBcblxuQVBQIC0tPiBNTk9Nb2R1bGU6IOWPluWPtyBnZXRQaG9uZU51bVxu55So5oi3IC0tPiBBUFA6IOeUqOaIt-aOiOadg1xuQVBQIC0tPiDkuJrliqHmnI3liqHlmag6IOWPluWPt1xuXG5AZW5kdW1sIiwidHlwZSI6InB1bWwiLCJtYXJnaW4iOnRydWUsImlkIjoicDFYdjIiLCJ1cmwiOiJodHRwczovL2Nkbi5ubGFyay5jb20veXVxdWUvX19wdW1sL2VjMjBiODZiNDc4MzYzYjlhNTI1ZDdkZGY0YTZmNWZjLnN2ZyIsImNhcmQiOiJkaWFncmFtIn0=)## 插件接口定义
如下
```javascript
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
#### 权限
andriod 需要如下权限：
```xml
<uses-permission android:name="android.permission.INTERNET" />
<uses-permission android:name="android.permission.ACCESS_WIFI_STATE" />
<uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />
<uses-permission android:name="android.permission.CHANGE_NETWORK_STATE" />
```
#### 伪代码
接入一键登录包括如下几步，伪代码如下：
```python
# 1. 客制化一键登录授权界面(可选，Andoid ios 需分别定制)
authUIConfigJson = 'xxxxxxxxx'
# 2. 预取号
data = MNOModule.getPhoneNum(secretKey,authUIConfigJson, mnoCallback)
# 3. 从服务器端获取电话号码
phoneNumber = syncToServer(data)
```
#### 代码Demo
```javascript
<template>
	<view>
		<button v-on:click="getPhoneNum()">一键登录</button>
	</view>
</template>

<script>
	var MNOModule = uni.requireNativePlugin("Esand-MNOModule")
  //阿里云市场appcode(从阿里云市场获取)
  let appcode = ""
  //申请生成密钥 （此密钥需要向一砂获取，可联系 13691664797）
	let secretKey = ""
  //客制化界面 ios和android 制定界面参数不同，详情参考客制化界面文档
	let authUIConfigJson = ""
	export default {
		methods: {
			getPhoneNum: function(e) {
        let platform=uni.getSystemInfoSync().platform
        // 1. 页面客制化
				if(platform=='ios'){
          // UI 定制化 (可选)
          authUIConfig = {}
          authUIConfig.prefersStatusBarHidden = true
					authUIConfig.logoImage = "logo"
					authUIConfigJson = JSON.stringify(authUIConfig)
				//	authUIConfigJson = "{\"prefersStatusBarHidden\":true,\"logoImage\":\"logo\",\"checkBoxIsChecked\":true,\"logoWidth\":10.11123,\"logoHeight\":11.11,\"logoTopOffetY\":10.123,\"numberColor\":\"0x0000FF\",\"navTitle\":\"cscscscscs\",\"navTitleColor\":\"0x0000FF\",\"navTitleFont\":20}"
					secretKey = ""
				} else if(platform=='android') {
          // UI 定制化 (可选)
          authUIConfig = {}
          authUIConfig.privacyState = true
					authUIConfig.logoImgPath = "cscs"
					authUIConfigJson = JSON.stringify(authUIConfig)
					//authUIConfigJson = "{\n" +
				//	        "    \"privacyState\":true,\n" +
					//        "    \"logoImgPath\":\"cscs\"\n" +
					  //      "}"
					secretKey = ""
				}
        
        // 2. 预取号
				MNOModule.getPhoneNum({
					'secretKey': secretKey,
					'authUIConfigJson': authUIConfigJson
				}, (ret) => {
					if (ret.code == '0') {
						let dataBody = ret.data
						let dataBodyJson = JSON.parse(dataBody)
            // 3. 从服务器端获取号码（为了保护APPCODE, 此段逻辑建议放在服务器端，APPCODE切勿泄漏！！）
						uni.request({
							url: 'http://edismno.market.alicloudapi.com/mno/getMobile',
							method: 'POST',
							data: {
								'deviceModel': dataBodyJson.deviceModel,
								'packageId':dataBodyJson.packageId,
								'platform':dataBodyJson.platform,
								'token':dataBodyJson.token,
								'transId':dataBodyJson.transId,
								'appName':dataBodyJson.appName,
								'phoneNum':dataBodyJson.phoneNum
							},
							header: {
								'Authorization': 'APPCODE '+ appcode,
								'Content-Type': 'application/x-www-form-urlencoded; charset=UTF-8'
							},
							success: (res) => {
								console.log('网络请求成功' + JSON.stringify(res.data))
								uni.showModal({
									title: "获取结果成功",
									content: JSON.stringify(res.data),
								})
							}
						})
					} 
				})
			},
		}
	}
</script>

```

### 7. 客制化界面
参考
https://esandinfo.yuque.com/books/share/5ddd649d-2afa-48e6-bb07-633105dfec88?# 《一键登录》

# Q&A

客服联系方式：

* QQ群 --1145603428
* 售前服务--18643777712
* 技术支持2--17604027801
* 技术支持1--18513625590

--- 

有使用上的问题可以随时联系，谢谢

 [1]: http://static.zybuluo.com/745479540/9q3ukxbdevqsnqmmk3vqnatl/Screenshot_2020-06-11-21-32-58-005_com.esandinfo.zim.jpg
  [2]: http://static.zybuluo.com/745479540/f1mad7gglaxkgs8my6rnexi8/Screenshot_2020-06-11-21-33-33-221_com.esandinfo.zim.jpg
