<template>
	<view>
		<button class="eButton" @tap="getPhoneNum()">一键登录</button>
		<textarea v-model="logs"></textarea>
		</view>
</template>

<script>
const MNOModule = uni.requireNativePlugin('Esand-MNOModule');
//阿里云市场appcode(从阿里云市场获取)
const appcode = '2294b96c1dce4aedafa39bfa3fc5708c';
//申请生成密钥 （此密钥需要向一砂获取，可联系 13691664797）
const secretKey ='EUK3SDY4rE5uOgfqv8BuGP+UlGnVgyC+v86XE9/oE92c5t0zUbISvN+g9a61Gbarsl0xtrgdVPGq8WM8BzpHlAn7P2wGhVS+6U6S/ftnADhS38rSy9NwI/V2kcZsp/vPjgU3vvbaFiwtb6sB9LzL4etZoeBJUAvGaVhHmTiXFiIE/26yKFK2r9+1AyPBKpjJxcxnYTgF2PtmTc5Ob5QuYxrwGqkK78nYhUZ5tNGCIksHxWhMdZm6caWlX3CG2gKGtpwEQt45yXTkaecN2Wofstk5gdPYSlOegpQGs+zaQLgtAkfkNWSxvKdFVGlpMjkGWtO90uoFVrc=';
//客制化界面 ios和android 制定界面参数不同，详情参考客制化界面文档
let authUIConfigJson = '';
export default {
	data(){
		return{
			logs:"msg"
		}
	},
	methods: {
		getPhoneNum: function(e) {
			let _this=this;
			//获取软件的运行平台
			let platform = uni.getSystemInfoSync().platform;
			// 1. 页面客制化
			if (platform == 'ios') {
				// UI 定制化 (可选)
				let authUIConfig = {};
				authUIConfig.prefersStatusBarHidden = true;
				authUIConfig.logoImage = 'logo';
				authUIConfigJson = JSON.stringify(authUIConfig);
				//authUIConfigJson = "{\"prefersStatusBarHidden\":true,\"logoImage\":\"logo\",\"checkBoxIsChecked\":true,\"logoWidth\":10.11123,\"logoHeight\":11.11,\"logoTopOffetY\":10.123,\"numberColor\":\"0x0000FF\",\"navTitle\":\"cscscscscs\",\"navTitleColor\":\"0x0000FF\",\"navTitleFont\":20}"
			} else if (platform == 'android') {
				// UI 定制化 (可选)
				let authUIConfig = {};
				//设置隐私条款是否默认勾选 详情可前往 https://esandinfo.yuque.com/books/share/5ddd649d-2afa-48e6-bb07-633105dfec88/pu6myx
				authUIConfig.privacyState = true;
				//设置logo 图片
				authUIConfig.logoImgPath = "a123456";
				authUIConfigJson = JSON.stringify(authUIConfig);
				//authUIConfigJson = "{\n" +
				//          "   \"privacyState\":true,\n" +
				//       "    \"logoImgPath\":\"cscs\"\n" +
				//      "}"
			}
			// 2. 预取号
			MNOModule.getPhoneNum(
				{
					secretKey: secretKey,
					authUIConfigJson: authUIConfigJson
				},
				ret => {
					_this.logs+=JSON.stringify(ret);
					if (ret.code == '0') {
						let dataBody = ret.data;
						let dataBodyJson = JSON.parse(dataBody);
						// 3. 从服务器端获取号码（为了保护APPCODE, 此段逻辑建议放在服务器端，APPCODE切勿泄漏！！）
						uni.request({
							url: 'http://edismno.market.alicloudapi.com/mno/getMobile',
							method: 'POST',
							data: {
								//设备型号
								deviceModel: dataBodyJson.deviceModel,
								//应用包名
								packageId: dataBodyJson.packageId,
								//运行平台
								platform: dataBodyJson.platform,
								//认证TOKEN 由插件生成
								token: dataBodyJson.token,
								//请求ID(用于定位问题)
								transId: dataBodyJson.transId,
								//APP名称
								appName: dataBodyJson.appName,
								//比对号码 (与本机号码比对)
								phoneNum: dataBodyJson.phoneNum
							},
							header: {
								Authorization: 'APPCODE ' + appcode,
								'Content-Type': 'application/x-www-form-urlencoded; charset=UTF-8'
							},
							success: res => {
								console.log('网络请求成功' + JSON.stringify(res.data));
								_this.logs+="获取结果成功"+JSON.stringify(res.data);
							}
						});
					}
				}
			);
		}
	}
};
</script>
<style>
	.eButton{
		margin-top: 40px;
		display: inline-block;
		background-color: #F0AD4E;
	}
	textarea{
		text-align: left;
		font-size: 23px;
		background-color: #333333;
		color: white;
		width: 100%;
	}
</style>
