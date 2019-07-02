P2P传输(流媒体+P2P)SDK库，用于支持应用程序进行内网穿透通信，跨平台支持Windows、Linux、Android和IOS平台，具备高流畅度、低延迟的传输特性，广泛应用于网络直播、文件传输、即时通讯程序和WEB网页中。
内网穿透率极高，是UDP穿透的完全解决方案。支持Cone NAT，Symmetric NAT等类型路由的穿越。

基于PPeasy的开源播放器项目: https://github.com/SeaHaige/pkplayer

支持的协议：

1）直播协议，RTMP and HLS

2）视频电话协议 ，SIP 

3）基于TCP协议的对等节点通讯

以上所有协议都支持加密传输

## 调用接口

### uni-app 调用

main.js 初始化
	const ppeasySerivce = uni.requireNativePlugin('PPeasy-P2P');   
	ppeasySerivce.start();   

播放时调用：
  this.videoUrl=this.p2pvideo(url); //点播地址

  this.videoUrl=this.p2plive(url); //直播地址
  
### android 调用

添加libppeasy.so到工程

初始化：  

import tv.danmaku.ijk.media.example.activities.PPeasyService;  

PPeasyService.start(getApplicationContext());

播放时候调用：

player.play( PPeasyService.p2pvideo(getUrl()));

  
### ios 调用

添加libppeasy.a到工程

初始化：  

void ppeasy_init();

ppeasy_init();

播放时候调用：




QQ交流群：466907566
