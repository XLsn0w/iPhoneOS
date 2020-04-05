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

## 正确的组件化方案 via CTMediator


先来看一下方案的架构图

             --------------------------------------
             |              Mediator 中间人        |
             |                                    |
             |                openUrl:       <<<<<<<<<  (AppDelegate)  <<<<  Call From Other App With URL
             |                                    |
             |                   |                |
             |                   |                |
             |                   |/               |
             |                                    |
             |                parseUrl            |
             |                                    |
             |                   |                |
             |                   |                |
          .................................|...............................
             |                   |                |
             |                   |                |
             |                   |/               |
             |                                    |
             |  performTarget:action:params: <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  Call From Native Module
             |                                    |
             |                   |                |
             |                   |                |
             |                   |                |
             |                   |/               |
             |                                    |
             |             -------------          |
             |             |           |          |
             |             |  runtime  |          |
             |             |           |          |
             |             -------------          |
             |               .       .            |
             ---------------.---------.------------
                           .           .
                          .             .
                         .               .
                        .                 .
                       .                   .
                      .                     .
                     .                       .
                    .                         .
       -------------------.-----------      ----------.---------------------
       |                 .           |      |          .                   |
       |                .            |      |           .                  |
       |               .             |      |            .                 |
       |              .              |      |             .                |
       |                             |      |                              |
       |           Target            |      |           Target             |
       |                             |      |                              |
       |         /   |   \           |      |         /   |   \            |
       |        /    |    \          |      |        /    |    \           |
       |                             |      |                              |
       |   Action Action Action ...  |      |   Action Action Action ...   |
       |                             |      |                              |
       |                             |      |                              |
       |                             |      |                              |
       |Business A                   |      | Business B                   |
       -------------------------------      --------------------------------



### 这幅图是组件化方案的一个简化版架构描述，主要是基于Mediator模式和Target-Action模式，中间采用了runtime来完成调用。

调用方式

先说本地应用调用，本地组件A在某处调用
[Mediator performTarget:targetName action:actionName params:@{}]

向CTMediator发起跨组件调用，CTMediator根据获得的target和action信息，通过objective-C的runtime转化生成target实例以及对应的action选择子，然后最终调用到目标业务提供的逻辑，完成需求。
```
Class targetClass = NSClassFromString(targetClassString);
target = [[targetClass alloc] init];

SEL action = NSSelectorFromString(actionString);

```

在远程应用调用中，远程应用通过openURL的方式，由iOS系统根据info.plist里的scheme配置找到可以响应URL的应用（在当前我们讨论的上下文中，这就是你自己的应用），应用通过AppDelegate接收到URL之后，调用CTMediator的openUrl:方法将接收到的URL信息传入。当然，CTMediator也可以用openUrl:options:的方式顺便把随之而来的option也接收，这取决于你本地业务执行逻辑时的充要条件是否包含option数据。

传入URL之后，CTMediator通过解析URL，将请求路由到对应的target和action，随后的过程就变成了上面说过的本地应用调用的过程了，最终完成响应。


针对请求的路由操作很少会采用本地文件记录路由表的方式，服务端经常处理这种业务，在服务端领域基本上都是通过正则表达式来做路由解析。App中做路由解析可以做得简单点，制定URL规范就也能完成，最简单的方式就是scheme://target/action这种，简单做个字符串处理就能把target和action信息从URL中提取出来了。


组件仅通过Action暴露可调用接口


所有组件都通过组件自带的Target-Action来响应，也就是说，模块与模块之间的接口被固化在了Target-Action这一层，避免了实施组件化的改造过程中，对Business的侵入，同时也提高了组件化接口的可维护性。

            --------------------------------
            |                              |
            |           Business A         |
            |                              |
            ---  ----------  ----------  ---
              |  |        |  |        |  |
              |  |        |  |        |  |
    ...........|  |........|  |........|  |...........
    .          |  |        |  |        |  |          .
    .          |  |        |  |        |  |          .
    .        ---  ---    ---  ---    ---  ---        .
    .        |      |    |      |    |      |        .
    .        |action|    |action|    |action|        .
    .        |      |    |      |    |      |        .
    .        ---|----    -----|--    --|-----        .
    .           |             |        |             .
    .           |             |        |             .
    .       ----|------     --|--------|--           .
    .       |         |     |            |           .
    .       |Target_A1|     |  Target_A2 |           .
    .       |         |     |            |           .
    .       -----------     --------------           .
    .                                                .
    .                                                .
    ..................................................


大家可以看到，虚线圈起来的地方就是用于跨组件调用的target和action，这种方式避免了由BusinessA直接提供组件间调用会增加的复杂度，

而且任何组件如果想要对外提供调用服务，直接挂上target和action就可以了，业务本身在大多数场景下去进行组件化改造时，是基本不用动的。




复杂参数和非常规参数，以及组件化相关设计思路


这里我们需要针对术语做一个理解上的统一：

复杂参数是指由普通类型的数据组成的多层级参数。在本文中，我们定义只要是能够被json解析的类型就都是普通类型，包括NSNumber， NSString， NSArray， NSDictionary，以及相关衍生类型，比如来自系统的NSMutableArray或者你自己定义的都算。

总结一下就是：在本文讨论的场景中，复杂参数的定义是由普通类型组成的具有复杂结构的参数。普通类型的定义就是指能够被json解析的类型。

非常规参数是指由普通类型以外的类型组成的参数，例如UIImage等这些不能够被json解析的类型。然后这些类型组成的参数在文中就被定义为非常规参数。

总结一下就是：非常规参数是包含非常规类型的参数。非常规类型的定义就是不能被json解析的类型都叫非常规类型。




边界情况：



假设多层级参数中有存在任何一个内容是非常规参数，本文中这种参数就也被认为是非常规参数。



如果某个类型当前不能够被json解析，但通过某种转化方式能够转化成json，那么这种类型在场景上下文中，我们也称为普通类型。


举个例子就是通过json描述的自定义view。如果这个view能够通过某个组件被转化成json，那么即使这个view本身并不是普通类型，在具有转化器的上下文场景中，我们依旧认为它是普通类型。




如果上下文场景中没有转化器，这个view就是非常规类型了。



假设转化出的json不能够被还原成view，比如组件A有转化器，组件B中没有转化器，因此在组件间调用过程中json在B组件里不能被还原成view。在这种调用方向中，只要调用者能将非常规类型转化成json的，我们就依然认为这个view是普通类型。如果调用者是组件A，转化器在组件B中，A传递view参数时是没办法转化成json的，那么这个view就被认为是非常规类型，哪怕它在组件B中能够被转化成json。


然后我来解释一下为什么应该由本地组件间调用来支持远程应用调用：


在远程App调用时，远程App是不可能通过URL来提供非常规参数的，最多只能以json string的方式经过URLEncode之后再通过GET来提供复杂参数，然后再在本地组件中解析json，最终完成调用。

在组件间调用时，通过performTarget:action:params:是能够提供非常规参数的，于是我们可以知道，远程App调用时的上下文环境以及功能是本地组件间调用时上下文环境以及功能的子集。



因此这个逻辑注定了必须由本地组件间调用来为远程App调用来提供服务，只有符合这个逻辑的设计思路才是正确的组件化方案的设计思路，其他跟这个不一致的思路一定就是错的。因为逻辑上子集为父集提供服务说不通，所以强行这么做的话，用一个成语来总结就叫做倒行逆施。



另外，远程App调用和本地组件间调用必须要拆分开，远程App调用只能走CTMediator提供的专用远程的方法，本地组件间调用只能走CTMediator提供的专用本地的方法，两者不能通过同一个接口来调用。

这里有两个原因：



远程App调用处理入参的过程比本地多了一个URL解析的过程，这是远程App调用特有的过程。这一点我前面说过，这里我就不细说了。

架构师没有充要条件条件可以认为远程App调用对于无响应请求的处理方式和本地组件间调用无响应请求的处理方式在未来产品的演进过程中是一致的


在远程App调用中，用户通过url进入app，当app无法为这个url提供服务时，常见的办法是展示一个所谓的404界面，告诉用户"当前没有相对应的内容，不过你可以在app里别的地方再逛逛"。这个场景多见于用户使用的App版本不一致。比如有一个URL只有1.1版本的app能完整响应，1.0版本的app虽然能被唤起，但是无法完成整个响应过程，那么1.0的app就要展示一个404了。


在组件间调用中，如果遇到了无法响应的请求，就要分两种场景考虑了。

场景1

如果这种无法响应的请求发生场景是在开发过程中，比如两个组件同时在开发，组件A调用组件B时，组件B还处于旧版本没有发布新版本，因此响应不了，那么这时候的处理方式可以相对随意，只要能体现B模块是旧版本就行了，最后在RC阶段统测时是一定能够发现的，只要App没发版，怎么处理都来得及。


场景2

如果这种无法响应的请求发生场景是在已发布的App中，有可能展示个404就结束了，那这就跟远程App调用时的404处理场景一样。但也有可能需要为此做一些额外的事情，有可能因为做了额外的事情，就不展示404了，展示别的页面了，这一切取决于产品经理。


那么这种场景是如何发生的呢？

我举一个例子：当用户在1.0版本时收藏了一个东西，然后用户升级App到1.1版本。1.0版本的收藏项目在本地持久层存入的数据有可能是会跟1.1版本收藏时存入的数据是不一致的。此时用户在1.1版本的app中对1.0版本收藏的东西做了一些操作，触发了本地组件间调用，这个本地间调用又与收藏项目本身的数据相关，那么这时这个调用就是有可能变成无响应调用，此时的处理方式就不见得跟以前一样展示个404页面就结束了，因为用户已经看到了收藏了的东西，结果你还告诉他找不到，用户立刻懵逼。。。这时候的处理方式就会用很多种，至于产品经理会选择哪种，你作为架构师是没有办法预测的。如果产品经理提的需求落实到架构上，对调用入口产生要求然而你的架构又没有拆分调用入口，对于你的选择就只有两个：要么打回产品需求，要么加个班去拆分调用入口。


当然，架构师可以选择打回产品经理的需求，最终挑选一个自己的架构能够承载的需求。但是，如果这种是因为你早期设计架构时挖的坑而打回的产品需求，你不觉得丢脸么？

鉴于远程app调用和本地组件间调用下的无响应请求处理方式不同，以及未来不可知的产品演进，拆分远程app调用入口和本地组件间调用入口是功在当代利在千秋的事情。


组件化方案中的去model设计


组件间调用时，是需要针对参数做去model化的。如果组件间调用不对参数做去model化的设计，就会导致业务形式上被组件化了，实质上依然没有被独立。


假设模块A和模块B之间采用model化的方案去调用，那么调用方法时传递的参数就会是一个对象。


如果对象不是一个面向接口的通用对象，那么mediator的参数处理就会非常复杂，因为要区分不同的对象类型。如果mediator不处理参数，直接将对象以范型的方式转交给模块B，那么模块B必然要包含对象类型的声明。假设对象声明放在模块A，那么B和A之间的组件化只是个形式主义。

如果对象类型声明放在mediator，那么对于B而言，就不得不依赖mediator。但是，大家可以从上面的架构图中看到，对于响应请求的模块而言，依赖mediator并不是必要条件，因此这种依赖是完全不需要的，这种依赖的存在对于架构整体而言，是一种污染。


如果参数是一个面向接口的对象，那么mediator对于这种参数的处理其实就没必要了，更多的是直接转给响应方的模块。而且接口的定义就不可能放在发起方的模块中了，只能放在mediator中。响应方如果要完成响应，就也必须要依赖mediator，然而前面我已经说过，响应方对于mediator的依赖是不必要的，因此参数其实也并不适合以面向接口的对象的方式去传递。


因此，使用对象化的参数无论是否面向接口，带来的结果就是业务模块形式上是被组件化了，但实质上依然没有被独立。


## 在这种跨模块场景中，参数最好还是以去model化的方式去传递，在iOS的开发中，就是以字典的方式去传递。

这样就能够做到只有调用方依赖mediator，而响应方不需要依赖mediator。然而在去model化的实践中，由于这种方式自由度太大，我们至少需要保证调用方生成的参数能够被响应方理解，然而在组件化场景中，限制去model化方案的自由度的手段，相比于网络层和持久层更加容易得多。


因为组件化天然具备了限制手段：参数不对就无法调用！无法调用时直接debug就能很快找到原因。所以接下来要解决的去model化方案的另一个问题就是：如何提高开发效率。


在去model的组件化方案中，影响效率的点有两个：调用方如何知道接收方需要哪些key的参数？调用方如何知道有哪些target可以被调用？其实后面的那个问题不管是不是去model的方案，都会遇到。为什么放在一起说，因为我接下来要说的解决方案可以把这两个问题一起解决。


解决方案就是使用category


mediator这个repo维护了若干个针对mediator的category，每一个对应一个target，每个category里的方法对应了这个target下所有可能的调用场景，这样调用者在包含mediator的时候，自动获得了所有可用的target-action，无论是调用还是参数传递，都非常方便。接下来我要解释一下为什么是category而不是其他：


category本身就是一种组合模式，根据不同的分类提供不同的方法，此时每一个组件就是一个分类，因此把每个组件可以支持的调用用category封装是很合理的。

在category的方法中可以做到参数的验证，在架构中对于保证参数安全是很有必要的。当参数不对时，category就提供了补救的入口。

category可以很轻松地做请求转发，如果不采用category，请求转发逻辑就非常难做了。

category统一了所有的组件间调用入口，因此无论是在调试还是源码阅读上，都为工程师提供了极大的方便。

由于category统一了所有的调用入口，使得在跨模块调用时，对于param的hardcode在整个App中的作用域仅存在于category中，在这种场景下的hardcode就已经变成和调用宏或者调用声明没有任何区别了，因此是可以接受的。

这里是业务方使用category调用时的场景，大家可以看到非常方便，不用去记URL也不用纠结到底应该传哪些参数。
