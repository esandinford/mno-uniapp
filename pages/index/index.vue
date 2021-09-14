<template>
	<view>
		<button class="eButton" @tap="getPhoneNum()">一键登录</button>
		<textarea v-model="logs"></textarea>
		<button class="eButton" @tap="clearConsole()">清屏</button>
		<div class="bgp"></div>
	</view>
</template>

<script>
const MNOModule = uni.requireNativePlugin('Esand-MNOModule');
//阿里云市场appcode(从阿里云市场获取)
const appcode = '替换为你的appcode';
//申请生成密钥 （此密钥需要向一砂获取，可联系 13691664797）
const secretKey = "申请生成密钥";
//客制化界面 ios和android 制定界面参数不同，详情参考客制化界面文档
let authUIConfigJson = '';
export default {
	data() {
		return {
			logs: 'msg'
		};
	},
	methods: {
		getPhoneNum: function(e) {
			let _this = this;
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
				authUIConfig.logoImgPath = 'cscs';
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
					_this.logs += JSON.stringify(ret);
					console.log(ret)
					alert("ret")
					if (ret.code == '0') {
						let dataBody = ret.data;
						let dataBodyJson = JSON.parse(dataBody);
						// 3. 从服务器 端获取号码（为了保护APPCODE, 此段逻辑建议放在服务器端，APPCODE切勿泄漏！！）
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
								_this.logs += '获取结果成功' + JSON.stringify(res.data);
							}
						});
					}
				}
			);
		},
		clearConsole() {
			this.logs = '';
		}
	}
};
</script>
<style>
.eButton {
	margin-top: 40px;
	display: inline-block;
	background-color: #f0ad4e;
}
textarea {
	text-align: left;
	font-size: 23px;
	color: white;
	width: calc(100% - 4px);
	border: #333333 2px solid;
}
.bgp {
	display: inline-block;
	position: fixed;
	left: 0px;
	top: 0px;
	width: 100%;
	height: 100%;
	background-color: #c8c7cc;
	z-index: -1;
}
</style>
