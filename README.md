# 解决CocoaPods镜像源地址卡下载慢问题

## 优先推荐（ source 'https://gitee.com/mirrors/CocoaPods-Specs‘ ）
使用gitee源安装CocoaPods库
git clone https://gitee.com/mirrors/CocoaPods-Specs.git ~/.cocoapods/repos/master

使用coding源安装CocoaPods库
git clone https://git.coding.net/CocoaPods/Specs.git ~/.cocoapods/repos/master

为了解决方案二出现clone github镜像源比较慢的问题，可以换成coding提供的一个镜像源，命令行如下：
```
$ cd ~/.cocoapods/repos 
$ pod repo remove master
$ git clone https://git.coding.net/CocoaPods/Specs.git master
```
这样在clone的时候会发现速度很快哈。另外，在自己工程中的Podfile文件加入下面一行描述：
```
source 'https://git.coding.net/CocoaPods/Specs.git'
```
如果不加这一句话，它默认还是从github镜像源地址去下载的，这个不要给忘记了。
![截屏2020-04-01 20.45.12.png](https://upload-images.jianshu.io/upload_images/1155391-6e2688e72060442e.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

国内Gitee码云也很厉害(https://gitee.com/mirrors/CocoaPods-Specs)'
![截屏2020-04-01 20.51.43.png](https://upload-images.jianshu.io/upload_images/1155391-cca4f44b13396924.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

Podfile第一行设置：
```
source 'https://gitee.com/mirrors/CocoaPods-Specs‘
```
然后执行以下命令：
pod setup

打开podfile文件 指定旧方式下载。
// source 源地址
source 'https://gitee.com/mirrors/CocoaPods-Specs'

```
platform :ios, ‘9.0’

source 'https://gitee.com/mirrors/CocoaPods-Specs'


target '项目target名' do
    pod 'AFNetworking', '~> 3.1.0'
end
```
