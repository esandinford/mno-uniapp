<script>
	export default {
		onLaunch: function() {
			console.log('App Launch')
		},
		onShow: function() {
			console.log('App Show')
		},
		onHide: function() {
			console.log('App Hide')
		}
	}
</script>

<style>
	/*每个页面公共css */
	view{
		text-align: center;
	}
	.ripple{
		display: inline-block;
		position: absolute;
		background-color: #C8C7CC;
		border-radius: 50%;
		opacity: 1;
	}
</style>
