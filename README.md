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



# 私有Pod库

版本控制是 GitLab

Podfile：描述了工程中 Taget 的依赖。客户端使用这个文件使用 Pod 库。
Pod library：具体的库，即通常所说的第三方库。
Podspec：一个描述文件，描述 Pod library。
Spec Repo：存放 Podspec 的仓库。 Repository 注意和 library 区别，刚始看官方英语文档时，没能很好区分这两个词，给后面的理解造成了不是困难。
需要的组件

Podfile（必须）
Pod library（必须），一堆文件的集合，不一定是 xcode 工程，可以是一个文件，或者文件夹等。一般以 project(github 叫 Repository) 形式放到 GitLab 上，是一个 repo。
Podspec（必须）
这三个文件是必须的 调用关系：Podfile 引用 Podspec， Podspec 引用 Pod library。
Spec Repo 一般是一个 git 库 只存放 Podspec
现在来实现这些组件。

制作 Pod library 两种方法

直接在 GitLab 新建一个 project,添加相关文件即可。
用 CocoaPod 提供的命令 pod lib create MyLib1 一般情况下，第三库都需要demo和测试来验证。cocopods 的这条命令帮我们完成了这些繁琐的工作。 并且帮我们制作了对应的 podspec 参考官网
测试时，如果是 swift 的库 注意给类和方法根据需要添加 publice 关键字
这个命令会 git pod-template 到本地，根据需要删除 git 相关的目录和文件。
一般情况要将 Pod library 上传到 自己的 GitLab。
制作 Podspec 三种方法

上面的方法2已经产生了podspec
用 CocoaPod 提供的命令 pod spec create Mylib1.podspec 参考官网
手动创建一个这样的文件
注意：
soure URL 对应的地址是 pod library的地址。 不是 Spec Repo 的地址
tag 的版本号要对应。当然也可以不使用 tag
官方推荐的制作方法

官方推荐的方法步骤最多，但标准规范。

创建 Spec Repo，一般就是在 GitLab 上新建一个 project，github 叫 Repository。并添加 Mylib1.podspec 等spec文件
Add your Private Repo to your CocoaPods installation
pod repo add REPO_NAME SOURCE_URL
Add your Podspec to your repo
pod repo push REPO_NAME SPEC_NAME.podspec
注意：

SOURCE_URL 是 Spec Repo 的地址
如果 spec 文件中使用了tag 确保对应的 Pod library 打了对应的 tag。
Spec Repo 的目录结构 一定注意是这样的
.
├── Specs

    └── [SPEC_NAME]

        └── [VERSION]

            └── [SPEC_NAME].podspec

这样 私有库就做好了，但是在使用时，请注意添加

source 'URL_TO_REPOSITORY'
URL_TO_REPOSITORY 是 Spec Repo 的地址
根据文档总结的其他方法

官方推荐的制作方法中的步骤2和步骤3可以不实现。只要在Podfile中加入 source 'URL_TO_REPOSITORY' pod install后会自动实现。可以使用Pod repo list 查看前后变化
直接在 Podfile 中使用 参考
pod 'Alamofire', :git => 'https://github.com/Alamofire/Alamofire.git'
这种格式
注意：
podspec 文件必须在 Pod library 的根目录。
也可以这样参考官网
pod 'JSONKit', :podspec => 'https://example.com/JSONKit.podspec'
地址可以是任何可以访问得到的地址也可以是本地地址
JSONKit.podspec 也可以 使用 JSONKit.podspec.json 的json格式
pod ipc spec JSONKit.podspec > JSONKit.podspec.json
看 Cocoapod 官网的方法

网站右上角分了4部分，guids 是关注的重点，guids 页面分了四部分，根据需要查找对应部分，然后细读。

总结

细读文档，动手实践发现有很多实现方法

方法    优点
pod 'XXX', :git=>''    便于直接使用
pod 'XXX'，:podspec=>'.podspec'    原生
pod 'XXX'，:podspec=>'.json'    便于理解
specs 文件    便于详细配置工程
specs放在本地    便于调试
创建 Specs Reopsitroy    便于集中管理
命令总结

pod lib create MyLib1
pod spec create Mylib1.podspec
Pod repo list
pod repo add REPO_NAME SOURCE_URL
pod repo push REPO_NAME SPEC_NAME.podspec
pod ipc spec JSONKit.podspec > JSONKit.podspec.json
pod 'XXX'，:podspec=>''
pod 'XXX'，git=>''
pod lib lint



# Mediator中间人（路由）

怎样让Mediator解除对各个组件的依赖，同时又能调到各个组件暴露出来的方法？对于OC有一个法宝可以做到，就是runtime反射调用：
```
//Mediator.m
@implementation Mediator

+ (UIViewController *)BookDetailComponent_viewController:(NSString *)bookId {
 Class cls = NSClassFromString(@"BookDetailComponent");
 return [cls performSelector:NSSelectorFromString(@"detailViewController:") withObject:@{@"bookId":bookId}];
}

+ (UIViewController *)ReviewComponent_viewController:(NSString *)bookId type:(NSInteger)type {
 Class cls = NSClassFromString(@"ReviewComponent");
 return [cls performSelector:NSSelectorFromString(@"reviewViewController:") withObject:@{@"bookId":bookId, @"type": @(type)}];
}

@end
```
这下 Mediator 没有再对各个组件有依赖了，你看已经不需要 #import 什么东西了
只有调用其他组件接口时才需要依赖 Mediator，组件开发者不需要知道 Mediator 的存在。
等等，既然用runtime就可以解耦取消依赖，那还要Mediator做什么？组件间调用时直接用runtime接口调不就行了，这样就可以没有任何依赖就完成调用：
```
//WRReadingViewController.m
@implementation WRReadingViewController
- (void)gotoReview:(NSString *)bookId {
 Class cls = NSClassFromString(@"ReviewComponent");
 UIViewController *reviewVC = [cls performSelector:NSSelectorFromString(@"reviewViewController:") withObject:@{@"bookId":bookId, @"type": @(1)}];
 [self.navigationController pushViewController:reviewVC];
}
@end

```
这样就完全解耦了，但这样做的问题是：
调用者写起来很恶心，代码提示都没有，每次调用写一坨。
runtime方法的参数个数和类型限制，导致只能每个接口都统一传一个 NSDictionary。这个 NSDictionary里的key value是什么不明确，需要找个地方写文档说明和查看。
编译器层面不依赖其他组件，实际上还是依赖了，直接在这里调用，没有引入调用的组件时就挂了

把它移到Mediator后：
调用者写起来不恶心，代码提示也有了。
参数类型和个数无限制，由 Mediator 去转就行了，组件提供的还是一个 NSDictionary 参数的接口，但在Mediator 里可以提供任意类型和个数的参数，像上面的例子显式要求参数 NSString *bookId 和 NSInteger type。
Mediator可以做统一处理，调用某个组件方法时如果某个组件不存在，可以做相应操作，让调用者与组件间没有耦合。

到这里，基本上能解决我们的问题：各组件互不依赖，组件间调用只依赖中间件Mediator，Mediator不依赖其他组件。接下来就是优化这套写法，有两个优化点：
Mediator 每一个方法里都要写 runtime 方法，格式是确定的，这是可以抽取出来的。
每个组件对外方法都要在 Mediator 写一遍，组件一多 Mediator 类的长度是恐怖的。

target-action 对应第一点，target就是class，action就是selector，通过一些规则简化动态调用。
Category 对应第二点，每个组件写一个 Mediator 的 Category，让 Mediator 不至于太长。

总结起来就是，组件通过中间件通信，中间件通过 runtime 接口解耦，通过 target-action 简化写法，通过 category 感官上分离组件接口代码。
