//
//  isa.h
//  iPhoneOS
//
//  Created by XLsn0w on 2020/2/14.
//  Copyright © 2020 XLsn0w. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface isa : NSObject

@end

NS_ASSUME_NONNULL_END
/*

／/  arm64 架构
 
struct {
    uintptr_t nonpointer        : 1;  // 0:普通指针，1:优化过，使用位域存储更多信息
    uintptr_t has_assoc         : 1;  // 对象是否含有或曾经含有关联引用
    uintptr_t has_cxx_dtor      : 1;  // 表示是否有C++析构函数或OC的dealloc
    uintptr_t shiftcls          : 33; // 存放着 Class、Meta-Class 对象的内存地址信息
    uintptr_t magic             : 6;  // 用于在调试时分辨对象是否未完成初始化
    uintptr_t weakly_referenced : 1;  // 是否被弱引用指向
    uintptr_t deallocating      : 1;  // 对象是否正在释放
    uintptr_t has_sidetable_rc  : 1;  // 是否需要使用 sidetable 来存储引用计数
    uintptr_t extra_rc          : 19;  // 引用计数能够用 19 个二进制位存储时，直接存储在这里
};
 
 
 
 
 
 
 
 
 // x86_64 架构 //弃用
 struct {
     uintptr_t nonpointer        : 1;   0:普通指针，1:优化过，使用位域存储更多信息
     uintptr_t has_assoc         : 1;   对象是否含有或曾经含有关联引用
     uintptr_t has_cxx_dtor      : 1;   表示是否有C++析构函数或OC的dealloc
     uintptr_t shiftcls          : 44;  存放着 Class、Meta-Class 对象的内存地址信息
     uintptr_t magic             : 6;   用于在调试时分辨对象是否未完成初始化
     uintptr_t weakly_referenced : 1;   是否被弱引用指向
     uintptr_t deallocating      : 1;   对象是否正在释放
     uintptr_t has_sidetable_rc  : 1;   是否需要使用 sidetable 来存储引用计数
     uintptr_t extra_rc          : 8;   引用计数能够用 8 个二进制位存储时，直接存储在这里
 };
*/


/*
 
 iOS内存内存区域划分
 iOS进程内存布局从高地址往低地址分位几个区块：

 1.栈区域
 2.堆区域
 3.未初始化静态、全局数据       (存放程序中未初始化)
 全局区(静态区) (static) 全局变量和静态变量的存储是放在一起的，初始化的全局变量和静态变量存放在一块区域，未初始化的全局变量和静态变量在相邻的另一块区域，程序结束后有系统释放。
 4.已初始化静态、全局数据       (存放程序静态分配的变量和全局变量)
 5.常量区                    (存放程序常量)
 6.代码区                    (存放程序代码)
 
 栈： 栈是由编译器自动分配并释放

 通常是用户存放临时创建的局部变量，存放函数的参数值，局部变量等
 通常包括在"{}"中创建的变量，不包含static修饰的变量
 通常函数参数，以及函数返回值也是会被分配到栈中
 通常alloc的对象，对象指针在栈中，而对象本身地址在堆中
 我的理解就是栈是一个临时数据寄存、交换的区域
 堆： 堆是由程序员分配和释放，通常用alloc等函数分配的对象

 用于存放程序运行中被动态分配的内存段，它的大小并不固定，可动态扩张或缩减
 在OC中对象通常指在一块特定布局的连续内存区域
 用alloc等函数分配内存时,新分配的内存就被动态添加到堆上(堆被扩张)
 在OC中通常用retain保存对象引用计数，release释放对象(堆被缩减)
 通常alloc的对象，对象指针在栈中，而实际对象实现地址在堆中
 常量区： 用于存放常量字符串，程序结束后由系统释放

 全局区： 用于存放程序静态分配的变量和全局变量 细分2种

 未初始化静态、全局数据
 已初始化静态、全局数据
 代码区： 用于存放函数的二进制代码

 代码段需要防止在运行时中被非法修改，所以只准读不准写
 61.2: 内存管理
 61.2.1: 引用计数
 在iOS中使用了"引用计数"来管理内存，指将资源的被引用次数保存起来，当被引用次数变为0的时候该对象就会被释放。

 当创建一个对象A的实例并在堆上申请完内存，对象A的引用计数为1，在其他对象B持有这个对象A时，就需要把对象A的引用计数+1，持有者需要释放对象A的时候，引用计数-1，当最后对象A的引用计数为0时，对象的内存会被释放。

 iOS在xcode4.2版本之前一直是使用的是MRC(手动引用计数)，当xcode4.2版本之后就使用了ARC(自动引用计数)

 61.2.2 MRC(Manual Retain Count)
 在MRC中管理内存的引用计数，全部都是手动完成的，所以我们需要知道哪些是初始化为1，哪些是+1，哪些是-1

 61.2.2.1 影响引用计数的方式：
 对象操作    对应方法    引用计数变化
 生成并持有对象    alloc、new、copy、mutablecopy    1
 持有对象    retain    +1
 释放对象    release    -1
 延迟释放对象    autorelease    -1
 新的对象
 alloc、new、copy、mutablecopy都会创建一个新的对象，那么新的对象则是引用计数为1
 retain 引用计数 +1
 release 引用计数 -1
 autorelease 将代码放入到自动释放池中，当代码运行完成以后，所有调用autorelease的对象调用relrese
 61.2.2.2 MRC管理的四法则
 1 . 自己生成并自己持有

//自己生成并持有该对象
  id obj0 = [[NSObeject alloc] init];
  id obj1 = [NSObeject new];
 2 . 非自己生成的对象，自己也能持有

 
   //持有非自己生成的对象
  
 id obj = [NSArray array]; // 非自己生成的对象，且该对象存在，但自己不持有
 [obj retain]; // 自己持有对象
 3 . 不再需要自己持有对象的时候，释放

//不在需要自己持有的对象的时候，释放
 id obj = [[NSObeject alloc] init]; // 此时持有对象
 [obj release]; // 释放对象
 // 指向对象的指针仍就被保留在obj这个变量中
  // 但对象已经释放，不可访问
  [obj method];  //崩溃
 4 . 非自己持有的对象无法释放

 //非自己持有的对象无法释放
 id obj = [NSArray array]; // 非自己生成的对象，且该对象存在，但自己不持有
 [obj release]; // 此时将运行时crash 或编译器报error

 //非自己生成的对象，且该对象存在，但自己不持有,这个特性是使用autorelease实现的
 - (id) getAObjNotRetain {
     id obj = [[NSObject alloc] init]; // 自己生成并持有该对象
     [obj autorelease]; // 取得的对象存在，但自己不持有该对象
     return obj;
 }

 61.2.3 ARC(Automatic Retain Count)
 ARC是自动引用计数，也就是说编译器在编译的时候自动在已有的代码中插入合适的内存管理代码

 目前iOS开发基本上都是基于ARC的编程，开发人员在大部分情况下不需要考虑内存管理，因为编译器已经帮你做了。

 在ARC中会经常出现的一个问题循环引用问题。

 61.2.3.1 ARC中的所有权修饰符
 strong
 weak
 unsafe_unretaied
 __autoreleasing
 所有权修饰符对应属性修饰符

 对应关系    所有权修饰符    属性修饰符
 -    __strong    strong
 -    __strong    copy
 -    __strong    retain
 -    __unsafe_unretaied    unsafe_unretaied
 -    __weak    weak
 -    __unsafe_unretained    assign
 __strong

 表示引用为强引用。对应在定义property时的"strong"。
 所有对象只有当没有任何一个强引用指向时，才会被释放。
 注意：如果在声明引用时不加修饰符，那么引用将默认是强引用。当需要释放强引用指向的对象时，需要将强引用置nil。
 __weak表示引用为弱引用。

 对应在定义property时用的"weak"。
 弱引用不会影响对象的释放，即只要对象没有任何强引用指向，即使有100个弱引用对象指向也没用，该对象依然会被释放。不过好在，对象在被释放的同时，指向它的弱引用会自动被置nil，这个技术叫zeroing weak pointer,这样有效得防止无效指针、野指针的产生。
 __weak一般用在delegate关系中防止循环引用或者用来修饰指向由Interface Builder编辑与生成的UI控件。
 __autoreleasing表示在autorelease pool中自动释放对象的引用，和MRC时代autorelease的用法相同。

 定义property时不能使用这个修饰符，任何一个对象的property都不应该是autorelease型的。
 自动释放用来表示引用(id *)传递的参数，并且在返回时自动释放。
 一个常见的误解是，在ARC中没有autorelease，因为这样一个“自动释放”看起来好像有点多余。这个误解可能源自于将ARC的“自动”和autorelease“自动”的混淆。其实你只要看一下每个iOS App的main.m文件就能知道，autorelease还是存在的存在的，不需要再手工被创建，也不需要再显式得调用[drain]方法释放内存池。
 int main(int argc, char * argv[]) {
     @autoreleasepool {
         return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
     }
 }
 __autoreleasing需要注意的地方1

 当定义了一个方法：

 - (void)doWithError:(NSError **)outError;
 上述方法，ARC模式下会自动编程如下代码

 - (void)doWithError:(NSError * __autoreleasing *)outError;
 error指向的对象在创建出来后，被放入到了autoreleasing pool中，等待使用结束后的自动释放，函数外error的使用者并不需要关心*error指向对象的释放。

 __autoreleasing需要注意的地方2

 - (void)loopThroughDictionary:(NSDictionary *)dict error:(NSError **)error
 {
     [dict enumerateKeysAndObjectsUsingBlock:^(id key, id obj, BOOL *stop){

           // do stuff
           if (there is some error && error != nil)
           {
                 *error = [NSError errorWithDomain:@"MyError" code:1 userInfo:nil];
           }

     }];
 }
 会隐式地创建一个autorelease pool，上面代码实际类似于：

 - (void)loopThroughDictionary:(NSDictionary *)dict error:(NSError **)error
 {
     [dict enumerateKeysAndObjectsUsingBlock:^(id key, id obj, BOOL *stop){

           @autoreleasepool  // 被隐式创建
 　　　　　　{
               if (there is some error && error != nil)
               {
                     *error = [NSError errorWithDomain:@"MyError" code:1 userInfo:nil];
               }
           }
     }];

     // *error 在这里已经被dict的做枚举遍历时创建的autorelease pool释放掉了 ：(
 }
 为了能够正常的使用*error，我们需要一个__block型的临时引用，在dict的枚举Block中是用这个临时引用，保证引用指向的对象不会在出了dict的枚举Block后被释放，正确的方式如下

 - (void)loopThroughDictionary:(NSDictionary *)dict error:(NSError **)error
 {
 　　__block NSError* tempError; // 加__block保证可以在Block内被修改
 　　[dict enumerateKeysAndObjectsUsingBlock:^(id key, id obj, BOOL *stop)
 　　{
 　　　　if (there is some error)
 　　　　{
 　　　　　　*tempError = [NSError errorWithDomain:@"MyError" code:1 userInfo:nil];
 　　　　}

 　　}]

 　　if (error != nil)
 　　{
 　　　　*error = tempError;
 　　}
 }
 在ARC与MRC当中使用autorelease

 //ARC 下  释放了内存
 NSString *__autoreleasing str1;
 @autoreleasepool {
     str1 = [[NSString alloc] initWithFormat:@"hehe2321321312213"]; // ARC
 }
 NSLog(@"%@",str1);  //崩溃

 //MRC 下  释放了内存
 NSString * str1;
 @autoreleasepool {
     str1 = [[[NSString alloc] initWithFormat:@"hehe2321321312213"]autorelease]; // MRC
 }
 NSLog(@"%@",str1);  //崩溃

 61.2.3.2 ARC中的属性标示符
 @property(assign/retain/strong/weak/unsafe_unretained/copy)NSObject *object;
 assign 表示setter仅仅是一个简单的赋值操作，通常用于基本的数值类型，例如CGFloat和NSInteger等

 strong 属性定义了强引用关系，当这个属性设置一个新值的时候：首先对新值retain，对旧值release，然后再赋值。

 weak 属性定义了弱引用关系，当给属性设置一个新值的时候，只是跟assign一样简单的赋值，如果当属性指向的对象销毁的时候，该属性会被置nil

 unsafe_unretained 也是定义了一个弱引用关系，与weak类似，不同点是unsafe_unretained修饰的属性，指向的对象如果释放，本属性不会置nil

 copy 类似于strong，不过在赋值时进行copy操作而不是retain操作，通常用于保留某个不可变的对象，防止它的意外改变时使用

 61.2.3.3 ARC模式下对象何时被释放
 局部变量会在作用域完成以后全部使用release一遍，也就是说过了作用域，这个临时变量将被释放
 ARC模式下变量的默认所有权修饰符是__strong,当变量的强引用指向一个都没有时，该对象被释放(也可以说是它的引用计数为0时)
 ARC模式下在非Alloc、new、copy、mutablecopy创建的对象时，在这些工厂方法的返回值都会自动添加到autoreleasepool中
 Autorelease返回值的快速释放机制，在ARC模式下：
 在工厂方法生成的对象，返回值会调用objc_autoreleaseReturnValue方法，代替我们调用autorelease
 调用该工厂方法的对象中，会实现objc_retainAutoreleasedReturnValue(工厂方法)代替retain
 在使用完成以后系统会自动添加objc_storeStrong(&创建的对象，nil)代理实现release
 通过pthread的线程存储技术，以工厂方法为key返回值为value存储，最终objc_autoreleaseReturnValue存value，objc_retainAutoreleasedReturnValue获取值，最后得到的数值没有进行内存管理。
 61.2.4 AutoreleasePool(自动释放池)
 61.2.4.1 AutoreleasePool基本概念
 什么是AutoreleasePool？
 AutoreleasePool是自动释放池，更灵活的管理内存
 AutoreleasePool什么时候释放？
 自动释放池释放的时候可以自动将池子中的对象release一边
 为什么要使用AutoreleasePool
 在循环当中我们需要创建很多的临时对象，每次循环都不会去释放临时对象，慢慢就会增加内存占用
 在生成辅助线程时，我们需要自己创建自动释放池，否则会泄漏对象
 61.2.4.2 @autoreleasepool底层实现
 首先从中间代码入手，使用下面命令来得到C++代码

 int main(int argc, char * argv[]) {
     @autoreleasepool {
         return 0;
     }
 }
 这里我直接用main.m文件进行分析
 clang -rewrite-objc main.m
 得到的C++代码：

 只看有关代码

 extern "C" __declspec(dllimport) void * objc_autoreleasePoolPush(void);
 extern "C" __declspec(dllimport) void objc_autoreleasePoolPop(void *);

 struct __AtAutoreleasePool {
   __AtAutoreleasePool() {atautoreleasepoolobj = objc_autoreleasePoolPush();}
   ~__AtAutoreleasePool() {objc_autoreleasePoolPop(atautoreleasepoolobj);}
   void * atautoreleasepoolobj;
 };

 #define __OFFSETOFIVAR__(TYPE, MEMBER) ((long long) &((TYPE *)0)->MEMBER)
 int main(int argc, char * argv[]) {

     /* @autoreleasepool */ { __AtAutoreleasePool __autoreleasepool;
         return 0;
     }
 }

 从上面内容我们可以看到main函数中声明了一个__AtAutoreleasePool对象，相当于调用了objc_autoreleasePoolPush()函数，该函数的作用就是向堆栈中压入一个"自动释放池"，当main函数执行完成以后，则执行__AtAutoreleasePool的析构函数objc_autoreleasePoolPop(atautoreleasepoolobj)，用于释放"自动释放池"，

 如上述所说，拼装成一个伪代码

 int main(int argc, char * argv[]) {
     /* @autoreleasepool */ {
         //创建自动释放池
         __AtAutoreleasePool __autoreleasepool = objc_autoreleasePoolPush();
         //TODO 执行各种操作，将对象加入自动释放池
         
         //释放自动释放池
         objc_autoreleasePoolPop(__autoreleasepool)
     }
 }
 61.2.4.3 AutoreleasePool本质
 在苹果开放源码中我们可以找到AutoreleasePool的底层实现
 objc_autoreleasePoolPush()以及objc_autoreleasePoolPop(__autoreleasepool)的实现如下：

 void *
 objc_autoreleasePoolPush(void)
 {
     return AutoreleasePoolPage::push();
 }

 void
 objc_autoreleasePoolPop(void *ctxt)
 {
     AutoreleasePoolPage::pop(ctxt);
 }
 从源码中我们可以发现，AutoreleasePoolPage才是AutoreleasePool的实现对象所在，找到AutoreleasePoolPage，如下代码：

 class AutoreleasePoolPage
 {
 #   define EMPTY_POOL_PLACEHOLDER ((id*)1)

 #   define POOL_BOUNDARY nil
     static pthread_key_t const key = AUTORELEASE_POOL_KEY;
     static uint8_t const SCRIBBLE = 0xA3;  // 0xA3A3A3A3 after releasing
     static size_t const SIZE =
 #if PROTECT_AUTORELEASEPOOL
         PAGE_MAX_SIZE;  //4096  必须是多个vm页面大小
 #else
         PAGE_MAX_SIZE;  //4096   大小和对齐，功率为2
 #endif
     static size_t const COUNT = SIZE / sizeof(id);

     magic_t const magic;    //数据校验
     id *next;               //栈顶地址，默认创建一个新的AutoreleasePoolPage对象的时候next是nil
     pthread_t const thread; //所在线程
     AutoreleasePoolPage * const parent;  //父对象
     AutoreleasePoolPage *child;          //子对象
     uint32_t const depth;
     uint32_t hiwat;
     ...
 }
 去除不必要的代码我们可以看到，通过这个结构体我们可以了解到AutoreleasePool实质上是若干个AutoreleasePoolPage组成的双向链表

 61.2.4.4 AutoreleasePoolPage工作原理
 创建AutoreleasePoolPage

 在void *objc_autoreleasePoolPush(void)中实际上调用了AutoreleasePoolPage::push()函数，代码如下

 static inline void *push()
 {
     id *dest;
     if (DebugPoolAllocation) {
           //当自动释放池出现顺序错误时停止，并允许堆调试器跟踪自动释放池的时候调用
         // 每个自动释放池都从一个新的池页面开始。
         dest = autoreleaseNewPage(POOL_BOUNDARY);
     } else {
         //代码正常运行时调用
         dest = autoreleaseFast(POOL_BOUNDARY);
     }
     assert(dest == EMPTY_POOL_PLACEHOLDER || *dest == POOL_BOUNDARY);
     return dest;
 }
 static inline id *autoreleaseFast(id obj)
 {
     AutoreleasePoolPage *page = hotPage(); //得到hotPage对象
     if (page && !page->full()) {
     //这个对象存在 且没有满的时候调用
         return page->add(obj);
     } else if (page) {
     //这个AutoreleasePoolPage对象存在  AutoreleasePoolPage已经满了以后调用
         return autoreleaseFullPage(obj, page);
     } else {
         //这个AutoreleasePoolPage对象不存在时调用
         return autoreleaseNoPage(obj);
     }
 }


 /*
  *  得到当前线程中所使用的AutoreleasePoolPage
  **/
  
 static pthread_key_t const key = AUTORELEASE_POOL_KEY;
  
 static inline AutoreleasePoolPage *hotPage()
 {
      //根据线程为key找到这个线程中的AutoreleasePoolPage对象
     AutoreleasePoolPage *result = (AutoreleasePoolPage *)
         tls_get_direct(key);
     if ((id *)result == EMPTY_POOL_PLACEHOLDER) return nil;
     if (result) result->fastcheck();
     return result;
 }


 /*
  * 当前hotPage存在并且没有满，
  **/
 id *add(id obj)
 {
     assert(!full());
     unprotect();
     id *ret = next;  // faster than `return next-1` because of aliasing
     *next++ = obj;
     protect();
     return ret;
 }

 /*
  *  这个AutoreleasePoolPage对象存在  AutoreleasePoolPage已经满了以后调用
  **/

 static __attribute__((noinline))
 id *autoreleaseFullPage(id obj, AutoreleasePoolPage *page)
 {
     //如果hotpage满了以后查找下一个page直到找不到，没有满的page那么就新建一个page，然后将对象添加到该页，并设置其为hotPage
     assert(page == hotPage());
     assert(page->full()  ||  DebugPoolAllocation);

     do {
         if (page->child) page = page->child;
         else page = new AutoreleasePoolPage(page);
     } while (page->full());

     setHotPage(page);
     return page->add(obj);
 }



 /*
  * //这个AutoreleasePoolPage对象不存在时调用
  **/
 static __attribute__((noinline))
 id *autoreleaseNoPage(id obj)
 {
     // We are pushing an object or a non-placeholder'd pool.

     // Install the first page.
     AutoreleasePoolPage *page = new AutoreleasePoolPage(nil);
     setHotPage(page);
         
     // Push the requested object or pool.
     return page->add(obj);
 }

 大致逻辑：

 本质上AutoreleasePool是底层是调用了AutoreleasePoolpage结构体中的push方法，而push方法调用的是Autoreleasefast。

 如果第一次hotPage()为NULL，那么调用autoreleaseNoPage(obj)新建一个parent=NULL的AutoreleasePoolPage对象做为自动释放池加入栈中，并将其设置为hotPage，最后返回给main()函数中的 __AtAutoreleasePool __autoreleasepool变量,

 hotPage()找到了正在运行的page，并且当前page并没有满那么调用add(obj)添加这个page进入到链表，并将hotpage返回给__AtAutoreleasePool __autoreleasepool变量

 hotPage()如果当前page满了，那么就会在child当中查找是否有不满的page，如果找到不满的就将这个child设置成hotPage，并调用add(obj)，如果在child中没有找到不满的page，那么就创建一个新的page然后在设置hotPage，并调用add(obj)最后将并将hotpage返回给__AtAutoreleasePool __autoreleasepool变量

 销毁AutoreleasePoolPage

 销毁这个自动释放池的方法是：

 static inline void pop(void *token)
 token 就是push()的返回值，通过该地址我们可以找到对应的page,pop()代码如下：

 static inline void pop(void *token)
 {
     AutoreleasePoolPage *page;
     id *stop;

     if (token) {
         page = pageForPointer(token); //找到所在的page地址
         stop = (id *)token; //POOL_SENTINEL的地址，从栈顶释放对象直到这个位置
     } else {
         // Token 0 is top-level pool
         page = coldPage();
         stop = page->begin();
     }

     page->releaseUntil(stop); //对自动释放池中对象调用objc_release()进行释放

     // memory: delete empty children
     // hysteresis: keep one empty child if this page is more than half full
     // special case: delete everything for pop(0)
     if (!token) {
         page->kill();
         setHotPage(NULL);
     } else if (page->child) {
         if (page->lessThanHalfFull()) {
             page->child->kill();
         }
         else if (page->child->child) {
             page->child->child->kill();
         }
     }
 }
 过程分为两部分：

 page->releaseUntil(stop)，对栈顶（page->next）到stop地址（POOL_SENTINEL）之间的所有对象调用objc_release()，进行引用计数减1；
 清空page对象page->kill()
 61.2.4.5 AutoreleasePoolPage总结
 AutoreleasePool并没有单独的结构，而是由若干个AutoreleasePoolPage以双向链表的形式组合而成（分别对应结构中的parent指针和child指针）

 AutoreleasePool是按线程一一对应的（结构中的thread指针指向当前线程）

 AutoreleasePoolPage每个对象会开辟4096字节内存（也就是虚拟内存一页的大小），除了上面的实例变量所占空间，剩下的空间全部用来储存autorelease对象的地址

 上面的id *next指针作为游标指向栈顶最新add进来的autorelease对象的下一个位置

 一个AutoreleasePoolPage的空间被占满时，会新建一个AutoreleasePoolPage对象，连接链表，后来的autorelease对象在新的page加入

 若当前线程中只有一个AutoreleasePoolPage对象，并记录了很多autorelease对象地址快满的时候，需要建立下一页page对象，与这一页链表连接完成后，新page的next指针被初始化在栈底（begin的位置），然后继续向栈顶添加新对象
 所以，向一个对象发送一个autorelease消息，就是将这个对象加入到当前AutoreleasePoolPage的栈顶next指针指向的位置

 释放
 objc_autoreleasePoolPush的返回值正是这个哨兵对象的地址，被objc_autoreleasePoolPop(哨兵对象)作为入参,

 根据传入的哨兵对象地址找到哨兵对象所处的page
 在当前page中，将晚于哨兵对象插入的所有autorelease对象都发送一次release消息，并向回移动next指针到正确位置，从最新加入的对象一直向前清理，可以向前跨越若干个page，直到哨兵所在的page
 嵌套的AutoreleasePool
 嵌套的AutoreleasePool，pop的时候总会释放到上次push的位置为止，多层的pool就是多个哨兵对象而已，就像剥洋葱一样，每次一层，互不影响。

 最后简单概括

 autoreleasepool由若干个autoreleasePoolPage类以双向链表的形式组合而成, 当程序运行到@autoreleasepool{时, objc_autoreleasePoolPush()将被调用, runtime会向当前的AutoreleasePoolPage中添加一个nil对象作为哨兵,
 在{}中创建的对象会被依次记录到AutoreleasePoolPage的栈顶指针,
 当运行完@autoreleasepool{}时, objc_autoreleasePoolPop(哨兵)将被调用, runtime就会向AutoreleasePoolPage中记录的对象发送release消息直到哨兵的位置, 即完成了一次完整的运作.

 62：iOS动态添加属性
 62.1 iOS动态添加属性
 62.1.1 使用场景
 为现有的类添加私有变量以帮助实现细节。
 为现有的类添加公有属性。
 为KVO创建一个关联的观察者。
 62.1.2 动态加添属性的相关函数
 在runtime源码的runtime.h文件中，找到它们的声明：

 //设置关联属性
 void objc_setAssociatedObject(id object,const void *key,id value,objc_AssociationPolicy policy);
 //获取关联属性
 id objc_getAssociatedObject(id object, const void *key);
 //删除所有关联属性
 void objc_removeAssociatedObjects(id object);
 objc_setAssociatedObject用于给对象添加关联对象，传入nil则可以移除已有的关联对象
 objc_getAssociatedObject用于获取关联对象
 objc_removeAssociatedObjects用于移除一个对象的所有关联对象
 参数：object对象的实例，voidkey类似对象级别唯一的一个常量，value值，关联策略*

 关键字    关联策略    对应属性修饰符
 OBJC_ASSOCIATION_ASSIGN    @property (assign) or @property (unsafe_unretained)    弱引用关联对象
 OBJC_ASSOCIATION_RETAIN_NONATOMIC    @property (strong, nonatomic)    强引用关联对象，且为非原子操作
 OBJC_ASSOCIATION_COPY_NONATOMIC    @property (copy, nonatomic)    复制关联对象，且为非原子操作
 OBJC_ASSOCIATION_RETAIN    @property (strong, atomic)    强引用关联对象，且为原子操作
 OBJC_ASSOCIATION_COPY    @property (copy, atomic)    复制关联对象，且为原子操作
 62.1.3 动态加添属性的实现
 //UserModel对象
 @interface UserModel : NSObject
 @end

 @implementation UserModel
 @end

 //在类扩展中的动态添加属性
 #import <objc/runtime.h>
 @interface UserModel(my)
 @property (nonatomic,copy)NSString *str;
 @end

 @implementation UserModel(my)
 - (NSString *)str{
     return objc_getAssociatedObject(self, _cmd);
 }
 - (void)setStr:(NSString *)str{
     objc_setAssociatedObject(self, @selector(str), str, OBJC_ASSOCIATION_COPY);
 }
 @end

 62.2 iOS动态添加属性的实现原理
 AssciationsManager 维护了一个无序的AssociationsHashMap键值哈希表
 AssociationsHashMap中有一个以object地址为key，value为objectassociationMap表的映射，
 objectassociationMap中维护了以key为key，以value为objcAssociation的映射，关联记录
 objcAssociation是一个对象，里面包含了关联的策略以及关联的值
 总结：每一个对象本身都存在一个AssciationsManager，并维护着AssociationsHashMap，AssociationsHashMap中以对象地址为key维护者一个ObjectAssociationMap，ObjectAssociationMap以key为key维护者一个objcAssociation对象，这个对象就是我们关联属性的值以及关联策略

 63: 为什么要使用taggedPointer
 假设要存储一个NSNumber对象，其值是一个整数。正常情况下，如果这个整数只是一个NSInteger的普通变量，在64位CPU下是占8个字节的。1个字节有8位，如果我们存储了一个很小的值，会出现很多位没有使用的情况，这样就造成了内存浪费，苹果为了解决这个问题，引入了taggedPointer的概念。

 首先来上一段代码：

 NSString *str1              =   @"1";
 NSString *str2              =   [NSString stringWithString:@"1"];
 NSString *str3              =   [NSString stringWithFormat:@"1"];
 NSString *str4              =   [[NSString alloc]initWithString:@"1"];
 NSString *str5              =   [[NSString alloc]initWithFormat:@"%@",str1];
 NSMutableString * str6      =   [str1 copy];
 NSMutableString * str7      =   [str1 mutableCopy];
 NSMutableString * str8      =   [[NSMutableString alloc]initWithString:@"123456"];
 [str7 appendString:@"2"];
 NSMutableString * str9      =   [str8 mutableCopy];
 [str9 appendString:@"23"];
 NSMutableString * str10     =   [str8 copy];

 打印数据：

 str1:__NSCFConstantString,0x102500060,1
 str2:__NSCFConstantString,0x102500060,1
 str3:NSTaggedPointerString,0xd11716512661ffd9,1
 str4:__NSCFConstantString,0x102500060,1
 str5:NSTaggedPointerString,0xd11716512661ffd9,1
 str6:__NSCFConstantString,0x102500060,1
 str7:__NSCFString,0x2831d82d0,12
 str8:__NSCFString,0x2831d8540,123456
 str9:__NSCFString,0x2831d80f0,12345623
 str10:NSTaggedPointerString,0xd11475026552dfde,123456

 根据上述内容我们可以发现几种字符串类型：

 NSTaggedPointerString
 __NSCFConstantString
 __NSCFString
 63.1 NSTaggedPointerString(taggedPointer)
 objc750中的taggedPointer源码分析


 extern uintptr_t objc_debug_taggedpointer_obfuscator;

 static inline void * _Nonnull
 _objc_encodeTaggedPointer(uintptr_t ptr)
 {
     return (void *)(objc_debug_taggedpointer_obfuscator ^ ptr);
 }

 static inline uintptr_t
 _objc_decodeTaggedPointer(const void * _Nullable ptr)
 {
     return (uintptr_t)ptr ^ objc_debug_taggedpointer_obfuscator;
 }

 static inline void * _Nonnull
 _objc_makeTaggedPointer(objc_tag_index_t tag, uintptr_t value)
 {
     if (tag <= OBJC_TAG_Last60BitPayload) {
         uintptr_t result =
             (_OBJC_TAG_MASK |
              ((uintptr_t)tag << _OBJC_TAG_INDEX_SHIFT) |
              ((value << _OBJC_TAG_PAYLOAD_RSHIFT) >> _OBJC_TAG_PAYLOAD_LSHIFT));
         return _objc_encodeTaggedPointer(result);
     } else {

         uintptr_t result =
             (_OBJC_TAG_EXT_MASK |
              ((uintptr_t)(tag - OBJC_TAG_First52BitPayload) << _OBJC_TAG_EXT_INDEX_SHIFT) |
              ((value << _OBJC_TAG_EXT_PAYLOAD_RSHIFT) >> _OBJC_TAG_EXT_PAYLOAD_LSHIFT));
         return _objc_encodeTaggedPointer(result);
     }
 }

 上述源码：_objc_encodeTaggedPointer是对TaggedPointer进行编码，而_objc_decodeTaggedPointer对其解码
 所以我们在iOS中只需要将NSTaggedPointerString类型的值带入到_objc_decodeTaggedPointer

 NSString *str1              =   @"1";
 NSString *str5              =   [[NSString alloc]initWithFormat:@"%@",str1];
 NSMutableString * str10     =   [str8 copy];

 NSLog(@"str5:%@,0x%lx,%@", [str5 class],_objc_decodeTaggedPointer(str5),str5);
 NSLog(@"str10:%@,0x%lx,%@", [str10 class],_objc_decodeTaggedPointer(str10),str10);
 打印结果:

 str5:NSTaggedPointerString,0xa000000000000611,a
 str10:NSTaggedPointerString,0xa000000000000611,a
 从64bit开始，iOS引入了Tagged Pointer技术，用于优化NSNumber、NSDate、NSString等小对象的存储
 在没有使用Tagged Pointer之前， NSNumber等对象需要动态分配内存、维护引用计数等，NSNumber指针存储的是堆中NSNumber对象的地址值
 使用Tagged Pointer之后，NSNumber指针里面存储的数据变成了: Tag + Data，也就是将数据直接存储在了指针中
 当指针不够存储数据时，才会使用动态分配内存的方式来存储数据
 63.1.1 如何判断是否是Tagged Pointer
 判断一个指针是否是Tagged Pointer的源码：

 static inline bool _objc_isTaggedPointer(const void * _Nullable ptr) {
     return ((uintptr_t)ptr & _OBJC_TAG_MASK) == _OBJC_TAG_MASK;
 }
 63.1.2 关于Tagged Pointer的面试题
 1.下面这段代码执行后, 会发生什么

 @property (nonatomic, copy) NSString *name;

 dispatch_queue_t queue = dispatch_get_global_queue(0, 0);
 for (int i = 0; i < 1000; i++) {
     dispatch_async(queue, ^{
         self.name = [NSString stringWithFormat:@"abcdefghijklmn"];
     });
 }
 会崩溃，原因是在setName:方法中，实际的实现是：

 - (void)setName:(NSString *)name
 {
     if (_name != name) {
         [_name release];
         _name = [name copy];
     }
 }

 原因：

 因为使用了多线程赋值，所以会有多个线程同时调用[_name release], 所以才发触发上面的崩溃
 解决办法是开锁，或者是设置属性的原子属性atomic
 2. 下面的代码为什么可以正常运行, 不会崩溃

 @property (nonatomic, copy) NSString *name;

 dispatch_queue_t queue = dispatch_get_global_queue(0, 0);
 for (int i = 0; i < 1000; i++) {
     dispatch_async(queue, ^{
         self.name = [NSString stringWithFormat:@"abc"];
     });
 }
 运行程序, 上面的代码确实不会发生崩溃

 这是因为[NSString stringWithFormat:@"abc"]是一个Tagged Pointer, 在调用-setName:方法时, 底层使用的是objc_msgSend(self, @selector(setName:)
 此时就会在底层调用_objc_isTaggedPointer函数判断是否是Tagged Pointer, 如果是, 就会直接将地址赋值给_name, 没有release和copy的操作
 63.2 __NSCFConstantString
 字符串常量，是一种编译时常量，它的 retainCount 值很大，是 4294967295，在控制台打印出的数值则是 18446744073709551615==2^64-1，测试证明，即便对其进行 release 操作，retainCount 也不会产生任何变化。是创建之后便是放不掉的对象。相同内容的 __NSCFConstantString 对象的地址相同，也就是说常量字符串对象是一种单例。

 这种对象一般通过字面值 @"..."、CFSTR("...") 或者 stringWithString: 方法（需要说明的是，这个方法在 iOS6 SDK 中已经被称为redundant，使用这个方法会产生一条编译器警告。这个方法等同于字面值创建的方法）产生。

 这种对象存储在字符串常量区。

 63.2 __NSCFString
 和 __NSCFConstantString 不同， __NSCFString 对象是在运行时创建的一种 NSString 子类，他并不是一种字符串常量。所以和其他的对象一样在被创建时获得了 1 的引用计数。

 通过 NSString 的 stringWithFormat 等方法创建的 NSString 对象一般都是这种类型。

 这种对象被存储在堆上。

 64 计算机位运算
 含义    运算符    例子
 左移    << 1    0011 => 0110
 右移    >> 1    0110 => 0011
 按位或(两位只要有一个为1就为1)    |    0011 | 1011 => 1011
 按位与(两位只要有一个为0就为0)    &    0011 & 1011 => 0011
 按位取反    ～    0011 => 1100
 按位异或(相同为0不同为1)    ^    0011 ^ 1011 => 1000
 65 initWithString、stringWithString、initWithFormat、stringWithFormat的区别
 65.1 initWithString和stringWithString
 65.1.1 NSString调用
 initWithString，stringWithString生成一个常量字符串，只读取数据
 使用[[NSString alloc]initWithString:]、[NSString stringWithString:]方式获取的是一个不可变的字符串常量，而这个常量是存放到内存中的常量区。不用引用计数管理内存，代码如下

 NSString *str1 = @"1";
 NSString *str2 = [[NSString alloc]initWithString:@"1"];
 NSString *str3 = [NSString stringWithString:@"1"];

 打印内容：
 str1:__NSCFConstantString,0x7ffee9bb3868,0x10604b060,1,retaincount = -1
 str2:__NSCFConstantString,0x7ffee9bb3860,0x10604b060,1,retaincount = -1
 str3:__NSCFConstantString,0x7ffee9bb3858,0x10604b060,1,retaincount = -1
 65.1.2 NSMutableString调用
 initWithString，stringWithString生成一个可变对象，会另外申请空间存放后面的常量字符串，这时其retaincount为1，代码如下：

 NSMutableString *str4 = [[NSMutableString alloc]initWithString:@"1"];
 NSMutableString *str5 = [NSMutableString stringWithString:@"1"];
 //打印
 str4:__NSCFString,0x7ffee67c3850,0x6000038dde90,1,retaincount = 1
 str5:__NSCFString,0x7ffee67c3848,0x6000038de1c0,1,retaincount = 1
 65.1.2 总结
 initWithString是实例方式，是字符串对象初始化的方法，而stringWithString这个则是一个工厂方法，并不是类的初始化构造方法
 两种方法，从结果来看没有区别
 对于可变生成一个全新的对象(开辟堆空间)，不可变对象创建的时候生成一个常量字符串，只读取数据
 65.2 initWithFormat和stringWithFormat
 65.2.1 NSString调用
 调用initWithFormat:、stringWithFormat是一编码格式读入数据，数据存放在哪是根据读入的参数确定的
 减少内存开销，减少不必要的堆空间开辟例如：
 NSInteger在32系统中是4个字节在64位占8个字节，如果一个变量的值为1，那么在8个字节中也就只占用了1位，有63位没有被使用，为了1位区开辟一块堆区域，很浪费，为了减少性能的消耗，而采取了变量指针来直接进行值操作。
 代码如下：

 //当字符串不超过字符串的内存空间，那么就使用NSTaggedPointerString
 NSString *str1 = @"sa";
 NSString *str2 = [[NSString alloc]initWithFormat:@"%@",str1];
 NSString *str3 = [NSString stringWithFormat:@"%@",str1];

 打印如下：
 str1:__NSCFConstantString,0x7ffee6628868,0x1095d6060,sa,retaincount = -1
 str2:NSTaggedPointerString,0x7ffee6628860,0xe5343da0d0e38890,sa,retaincount = -1
 str3:NSTaggedPointerString,0x7ffee6628858,0xe5343da0d0e38890,sa,retaincount = -1

 //当字符串超过字符串的内存空间，那么就使用NSTaggedPointerString
 NSString *str1 = @"sa321312312312";
 NSString *str2 = [[NSString alloc]initWithFormat:@"%@",str1];
 NSString *str3 = [NSString stringWithFormat:@"%@",str1];

 打印如下：
 str1:__NSCFConstantString,0x7ffee412d868,0x10bad1060,sa321312312312,retaincount = -1
 str2:__NSCFString,0x7ffee412d860,0x600000939060,sa321312312312,retaincount = 1
 str3:__NSCFString,0x7ffee412d858,0x600000939080,sa321312312312,retaincount = 1

 65.2.2 NSMutableString调用
 调用initWithFormat:、stringWithFormat不管输入的数据是什么都会开辟堆空间
 代码如下：

 NSMutableString *str4 = [[NSMutableString alloc]initWithFormat:@"%@",str1];
 NSMutableString *str5 = [NSMutableString stringWithFormat:@"%@",str1];

 打印如下：
 str4:__NSCFString,0x7ffeef95a850,0x6000024c93e0,sa3213123123121,retaincount = 1
 str5:__NSCFString,0x7ffeef95a848,0x6000024c96e0,sa3213123123121,retaincount = 1
 65.2.3 总结
 initWithFormat是构造初始化方法，而stringWithFormat是工厂类方法
 initWithFormat、stringWithFormat都是重新创建一个对象，重新开辟堆空间，不同点在于在不可变对象调用这两个方法的时候，如果这个对象的值的大小不超过你的指针占位大小，就是使用taggedpointer这个指针做值的特性，从而减小系统资源的浪费，
 65.3 总结
 在不可变字符串中：

 initWithFormat、stringWithFormat生成一个新的对象，可分为taggedpointer
 initWithString，stringWithString生成了一个常量
 在可变字符串中

 initWithFormat、stringWithFormat与initWithString，stringWithString生成一个新的对象
 initWithFormat、stringWithFormat
 66 Autorelease返回值的快速释放机制
 ARC下，runtime有一套对autorelease返回值的优化策略。
 比如在一个工厂方法中：

 + (instancetype)CreateObject {
     return [self new];
 }
 Sark *sark = [Sark createSark];
 谁创建谁释放的原则，返回值需要是一个autorelease对象才能配合调用方正确管理内存，于是乎编译器改写成了形如下面的代码：

 + (instancetype)createSark {
     id tmp = [self new];
     return objc_autoreleaseReturnValue(tmp); // 代替我们调用autorelease
 }
 // caller
 id tmp = objc_retainAutoreleasedReturnValue([Sark createSark]) // 代替我们调用retain
 Sark *sark = tmp;
 objc_storeStrong(&sark, nil); // 相当于代替我们调用了release
 Thread Local Storage(线程局部存储 TLS)通过

 Thread Local Storage（TLS）线程局部存储，目的很简单，将一块内存作为某个线程专有的存储，以key-value的形式进行读写，比如在非arm架构下，使用pthread提供的方法实现：

 void* pthread_getspecific(pthread_key_t);
 int pthread_setspecific(pthread_key_t , const void *);
 在返回值身上调用objc_autoreleaseReturnValue方法时，runtime将这个返回值object储存在TLS中，然后直接返回这个object（不调用autorelease）；同时，在外部接收这个返回值的objc_retainAutoreleasedReturnValue里，发现TLS中正好存了这个对象，那么直接返回这个object（不调用retain）。
 于是乎，调用方和被调方利用TLS做中转，很有默契的免去了对返回值的内存管理。

 67 block循环引用
 typedef void(^MyBlock)();
 @property (copy, nonatomic) MyBlock myBlock;
 @property (copy, nonatomic) NSString *blockString;

 - (void)testBlock {
     self.myBlock = ^() {
         NSLog(@"%@",self.blockString);//产生了循环引用
     };
 }
 上述代码：由于block会对block中的对象进行持有操作,就相当于持有了其中的对象，而如果此时block中的对象又持有了该block，则会造成循环引用。解决方案就是添加__weak

 __weak typeof(self) weakSelf = self;

 self.myBlock = ^() {
         NSLog(@"%@",weakSelf.blockString);//没有产生循环引用
  };
 并不是所有block都会造成循环引用,只有被强引用了的block才会产生循环引用,比如dispatch_async(dispatch_get_main_queue(), ^{}),[UIView animateWithDuration:1 animations:^{}]这些系统方法等或者block不是强引用而是临时变量，简单来说栈block不会产生循环引用。

 typedef void(^MyBlock)(void);
 - (void)testWithBlock:(MyBlock)block {
     block();
 }
 [self testWithBlock:^{
     NSLog(@"%@",self);//不会产生循环引用
 }];
     
 还有一种情况：在一个实例类A中强引用了一个block和一个实例B，这个block执行过程中调用了实例B中的属性，且在执行过程中实例B释放了，此时访问实例B是没有任何反应的。

 typedef void(^MyBlock)();
 @property (copy, nonatomic) MyBlock myBlock;
 @property (copy, nonatomic) NSString *blockString;
 @property (strong,nonatomic)UserModel *user;
 self.user = [[UserModel alloc]init];
 self.user.nama = @"wode";
     
 __weak typeof(self.user)weakuser = self.user;
     
 self.myBlock = ^{
     //self.user 再别的地方玩释放了它,所以应该保持住它
     __strong typeof(weakuser)stronguser = weakuser;
     
     NSLog(@"%@",stronguser.nama);
 };
     self.myBlock();

 68 NSTimer循环引用属于相互循环使用
 在对象实例中，创建一个NSTimer做为一个属性，由于定时器创建后会请引用这个实例对戏那个，该实例对象和NSTimer互相引用，形成循环引用。
 解决方式：

 如果是不重复的定时器，可以在回调中直接invalidate并置为nil即可
 如果是重复定时器，需要你在这个定向销毁之前调用invalidate并置为nil即可
 69 代理(delegate)循环引用属于相互循环引用
 delegate 是iOS中开发中比较常遇到的循环引用，一般在声明delegate的时候都要使用弱引用 weak,或者assign,当然怎么选择使用assign还是weak，MRC的话只能用assign，在ARC的情况下最好使用weak，因为weak修饰的变量在释放后自动指向nil，防止野指针存在

 70 __block的作用
 还可以使用__block来修饰变量
 在MRC下，__block不会增加其引用计数，避免了循环引用
 在ARC下，__block修饰对象会被强引用，无法避免循环引用，需要手动解除。

 71 UITableViewCell如何优化
 简单优化：

 正确的处理Cell的复用
 尽量少或不设置cell及子类的透明度
 cell中内容设计到延迟内容的代码，尽量使用异步操作，主线程通知结果或刷新UI
 尽量少的在heightForRowAtIndexPath:中去增加一些计算量操作，可以直接在请求结果以后在直接计算出高度在通知UI刷新
 尽可能的在cell中addView，尽量减少subviews
 进一步优化

 滑动过程中按需要加在数据(与SDWebImage异步加载会更好)
 避免大量的图片缩放，最好是大小刚刚好的资源，如果必须缩放也必须是图片等比缩放
 避免使用CALayer特效
 高级优化

 异步绘制界面，主线程刷新UI
 缓存所有计算、以及负责的创建类、耗费系统资源的对象，使用时直接赋值。
 72 什么是image
 Executable：应用的主要二进制(比如.0文件) 可执行文件
 Dylib:动态链接库
 Bundle: 资源文件
 73 App启动性能优化
 73.1 (Main函数加载之前的调用优化)Total pre-main time
 在Xcode->Edit scheme->Arguments->Environment Variables中添加key = DYLD_PRINT_STATISTICS，value = YES，就可以打印出来pre-main的内容

 Total pre-main time: 910.97 milliseconds (100.0%)
          dylib loading time: 126.46 milliseconds (13.8%)
         rebase/binding time: 697.11 milliseconds (76.5%)
             ObjC setup time:  59.21 milliseconds (6.5%)
            initializer time:  28.00 milliseconds (3.0%)
            slowest intializers :
              libSystem.B.dylib :   3.04 milliseconds (0.3%)
 从上面可以看到过程

 dylib loading time 动态库加载过程花费的时间
 rebase bind time 重定绑定，
 因为iOS引入了ASLR技术和代码签名
 镜像会在随机的地址上进行加载，和之前指针指向的地址会有一个偏差，dyld需要修正这个偏差
 Objc setup time 对象设置时间
 注册声明过的Objc类
 将分类插入类的方法列表
 检查selector的唯一性
 initializer time 初始化器时间
 调用每个Objc类和分类的+load方法
 调用C/C++中的构造器函数
 创建非基本类型全局变量
 73.1.1 dylib loading加载优化
 尽量合并已有的动态库和静态库，减少这些库的个数
 73.1.2 rebase bind 优化
 减少Objc类、方法、分类的数量
 减少C++虚函数的数量
 在Swift中尽量多使用Struct因为这个事值类型不是对象
 更多的使用值类型
 73.1.3 Objc setup 优化
 如果rebase bind已经做的很好，那么Objc setup 也就完成了
 73.1.4 Initializers
 少在类的+load方法里做事情，尽量把这些事情推迟到+initiailize
 减少构造器函数个数，在构造器函数里少做些事情
 减少C++静态全局变量的个数
 73.2 (Main调用之后优化)main After
 满足业务需要的前提下，didFinishLaunchingWithOptions在主线程里做的事情越少越好:

 梳理三方库，将可以延迟加载的库，推迟处理
 梳理业务逻辑，可以延迟执行的，推迟执行
 避免多余的逻辑计算
 尽量不要在首屏界面viewWillAppear，以及viewDidLoad中做太多的事情，可以延迟创建的对象可以使用懒加载
 首屏建议使用纯代码开发，速度比较快
 持久化读取数据到内存中是不是需要时间，这个操作是否可以延迟处理
 使用instruments的time profiler分析
 74 swift和oc的区别
 74.1 Protocol不同：
     OC：    主要用来传值，传递事件
     Swift： 不仅仅可以传值跟传递事件，
             可以在协议中定义属性以及方法，
             并且还能对其进行扩展，
 74.2 类型推断
     OC：    在定义属性的多时候必须添加你的类型(id是一个指向所有类的指针)
     swift： 当我添加一个变量的时候，我无需定义他的类型，会根据初始化的值，推断出来适合这个值的一个类型
 74.3 结构体和类
     OC：    结构体值类型、类指针类型，
             简单谈一下结构体，因为这个是跟swift的最大的差别：
                 1. 通常情况下，我们在初始化结构体完成以后如果需要修改结构体中的成员变量，直接使用点语法就能直接修改成员变量，
                 2. 当一个对象持有一个结构体变量，如果不使用属性property，默认是受保护的，所以你并不能修改这个结构体
                 3. 当一个对象中有一个结构体属性的时候，点语法其实就是setter、getter方法，当我获取这个属性的时候，如果是类对象，那么就是这个属性的引用，如果是结构体getter返回的值就是一个新的结构体的值，你在怎么修改也不会影响到这个对象中的结构体属性。
                 
                 
     swift： 结构体值类型、类指针类型，这个规则并没有改变
             对比OC，Swift中的结构体的功能被扩大了，基本上拥有了类差不多的功能
                 1.定义属性
                 2.定义方法
                 3.定义getter和setter
                 4.可以定义初始化器来设置初始状态
                 5.实现扩展的功能
                 6.遵守协议，并实现协议的方法
                 7.结构总是被复制，并不使用引用计数
             不过也有一些结构体不具备的类的功能
                 1.允许一个类继承另一个类的特征
                 2.能够在运行时检查和解释类实例的类型
                 3.初始化器使一个类的实例能够释放它所分配的任何资源，可以使用deinit来释放资源
                 4.引用计数允许多个引用到一个类实例
             总体来讲struct的优势在于：
                     1.结构较小，适用于复制操作，相比一个class的实例被多次引用，struct更加安全
                     2.更不需要担心内存泄漏以及多线程冲突问题
             可以定义inout的关键字来让值类型可以进行引用传递
             swift之所以讲Dictionary、array、String设计成值类型：
                     1.值类型在栈上面操作，而引用类型在堆上面操作，栈上的操作仅仅是单个指针的移动，而堆上面的操作牵扯到合并、移动、重新链接等问题，这样做大幅度减少了堆上内存分配和回收的次数，从而讲开销降到最低。
                     2.解决并发，多线程、、循环引用、内存泄漏
 74.4 函数式编程
     OC只是面向对象的编程，而Swift既面向对象又是面向函数式的编程
     特点：
             1. 没有附加作用， 函数保持独立，所有功能就是返回一个值，没有其他行为，尤其是不得修改外部的变量
             2. 不修改状态，也不会修改系统的变量，后者函数内部对象的变量，只是单纯的算法
             3.  引用透明，函数运行不依赖于外部变量和状态，只依赖于传递的参数。任何情况下，只要传递的参数相同，那么得到的返回值都是一样的。
             4. 函数式编程可以看作成表达式，而并不是执行语句，表达式是一个单独的计算公式，总是有一个返回值，而执行语句，只是执行过程并没有返回值。
     举例子说明：
     Swift中拥有 map，reduce、filter、flatmap这类数学函数式的方法，而OC并没有
 74.5 可选类型
     1.在oc中可选类型是为了表达一个变量的值是否为空的情况，如果为空，那么它就是nil，在Swift中这一概念被扩大化了，无论是引用变量还是值类型，都可以是可选类型。
     2.在Swift当中明确提出可选类型的概念，当我的变量(不管是值还是引用类型)，可以是空值，我就在变量类型的后面加上?如果这个变量类型后面没有加任何修饰符号，或者加了!那么这个值是必须有一个值的，
 74.6 属性观察以及setter、getter
     1.在OC中，属性观察需要KVO，Setter、getter方法可以是有property、或者自定义setter、getter方法
     2.而在swift中，属性观察增加一个初始化时就可以直接观察的方式，willset、以及didSet
 74.7 swift有一个copy-on-write功能
 当数组A copy生成数组B，两个数组是同样的地址，当我修改数组B中的元素的，在打印会发现，数组B完全变成了另外一个数组，而数组A不变，这就是copy-on-write
 75 SDWebImage怎么实现的
 75.1 角色划分
 UIimageView+WebCache 提供给客户端的一个API
 SDWebImageManager 这个是管理中心
 SDWebImageDownLoader 这个是下载中心 有operationQueue
 SDWebImageDownLoaderOperation 抽象的网络操作
 SDImageCache
 SDImageCachesManager 图片缓存类 主要做缓存操作
 SDImageCachesManagerOperation 单独的缓存类
 SDDiskCache 磁盘缓存类
 SDWebImagePrefetcher 批量缓存器‘
 SDWebImageDecoder 解码器 Argb专程rgb
 SDWebImageCompat 平台兼容性类
 75.1 优点：
 提供很多分类，这些分类都可以使用图片缓存 如：ImageView、UIbutton、MKAnnotationView、UIview
 异步下载图片
 异步缓存、内存+磁盘缓存
 后台解压缩
 同一个URL不会重复下载
 自动是被无效的URL，不重复系在
 不阻塞主线程
 高性能
 使用GCD和ARC结合
 支持多种图片格式
 支持动态图片
 75.1 缓存过程
 UIimageView->管理器->下载器->缓存器
 2.3版本

 Client通过UIimageView类扩展调用sd_setImageWithURL方法通知Manager
 Manager通过downloadWithURL方法告诉SDImageCache中的queryDiskCacheForKey方法来检查磁盘是否缓存
 SDImageCache的方法中会首先检测内存是否缓存，再去磁盘读取(使用了队列NSOperationQueue * cacheOutQueue)，是否有缓存，如果没有缓存那么就会通知给SDWebImageDownloader下载图片
 SDWebImageDownloader下载完成通知更新UI，并通知SDImageCache缓存图片
 有队列类型 先进先出 先进后出
 设置请求头
 SDImageCache 先缓存内存，在缓存磁盘 缓存磁盘的时候用了队列的形式NSOperationQueue * cacheInQueue
 75.2 URL不变怎么知道图片更新
 NSURLRequestUseProtocolCachePolicy:对特定的URL请求使用网络协议（如HTTP）中实现的缓存逻辑。这是默认的策略。该策略表示如果缓存不存在，直接从服务端获取。如果缓存存在，会根据response中的Cache-Control字段判断 下一步操作，如: Cache-Control字段为must-revalidata, 则 询问服务端该数据是否有更新，无更新话 直接返回给用户缓存数据，若已更新，则请求服务端

 75.3 为啥要解码
 图片格式转换， jpg->png，gif->jpg，iOS不支持透明通道 不支持arpg

 75.4 设计模式
 下载重载，如果当我去下载图片的时候，将这下载对象缓存在内存当中，如果这个图片没有下载成功是不会清理的。

 75.5 为什么添加图片类型
 为了区分 gif跟普通图片
 因为根据规则，图片数据的第一个字节是图片的类型，

 76 子视图随父视图动画
 76.1 设置clipsToBounds
 YES剪裁超出父视图范围的子视图部分。当设置成NO的时候，不剪裁超出父视图范围的子视图，

 设置YES以后这样视觉上来说是子视图在跟随父视图变化，但其实是被裁减了
 77 项目开发中业务分层
 四层：

 网络层 Networklayer
 业务层 Business
 数据层 Data
 工具层 Utils
 项目结构
 网路基础库结构
 网络层和业务层
 业务层分层结构
 UI展示层结构
 UI展示层和业务层

 78 项目开发->存在的疑惑
 层与层之间的关系？
 (网路基础层)和(业务层分层)怎么交互需要通过(网络层和业务层)
 (业务层分层)和(UI展示层)如何交互需要通过(UI展示层和业务层)
 主程序如何引用静态库的？
 引用4个组件：
 1.导入静态库到项目中，(出现错误需要关闭静态库项目，重新打开就好)
 2.项目配置setting target dependencies 添加静态库
 3.配置我们头文件 user header User Header search Paths 添加静态库的路径
 第三方库的引用链接：哪些需要哪些不需要
 1.主程序依赖:UI层
 2.UI层之外的不需要
 静态库引用静态库？
 静态库配置setting 搜索search paths User Header search Paths 添加静态库的路径
 静态库如何引用pods第三方库？
 安装一个pods 添加pod库，搜索search paths User Header search Paths 添加pod中header中的路径
 各层之间为什么要通过组建化的方式来设计？
 为什么要使用静态库来做？
 79 新建的静态库在哪存放？
 静态库全部在根目录单独的文件夹

 80 C与OC的桥接(Core Foundation和Foundation的桥接)
 __bridge只做类型转换，但是不修改对象（内存）管理权；
 __bridge_retained（也可以使用CFBridgingRetain）将Objective-C的对象转换为Core Foundation的对象，同时将对象（内存）的管理权交给我们，后续需要使用CFRelease或者相关方法来释放对象；
 __bridge_transfer（也可以使用CFBridgingRelease）将Core Foundation的对象转换为Objective-C的对象，同时将对象（内存）的管理权交给ARC。
 
 */
