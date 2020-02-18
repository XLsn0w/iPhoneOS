//
//  RunLooooop.m
//  iPhoneOS
//
//  Created by XLsn0w on 2020/2/16.
//  Copyright © 2020 XLsn0w. All rights reserved.
//

#import "RunLooooop.h"

@implementation RunLooooop


/// https://blog.ibireme.com/2015/05/18/runloop/
@end


/*
 Run Loop是一让线程能随时处理事件但不退出的机制。RunLoop 实际上是一个对象，这个对象管理了其需要处理的事件和消息，并提供了一个入口函数来执行Event Loop 的逻辑。线程执行了这个函数后，就会一直处于这个函数内部 “接受消息->等待->处理” 的循环中，直到这个循环结束（比如传入 quit 的消息），函数返回。让线程在没有处理消息时休眠以避免资源占用、在有消息到来时立刻被唤醒。

 OSX/iOS 系统中，提供了两个这样的对象：NSRunLoop 和 CFRunLoopRef。CFRunLoopRef 是在 CoreFoundation 框架内的，它提供了纯 C 函数的 API，所有这些 API 都是线程安全的。NSRunLoop 是基于 CFRunLoopRef 的封装，提供了面向对象的 API，但是这些 API 不是线程安全的。

 线程和 RunLoop 之间是一一对应的，其关系是保存在一个全局的 Dictionary 里。线程刚创建时并没有 RunLoop，如果你不主动获取，那它一直都不会有。RunLoop 的创建是发生在第一次获取时，RunLoop 的销毁是发生在线程结束时。你只能在一个线程的内部获取其 RunLoop（主线程除外）。


 
 Runloop，运行循环。当我们应用启动之后，就会在主线程开启一个运行循环，来监听我们的触摸事件和消息，等。
 
 注意，这个时候，子线程中是默认不开启运行循环的，另外，也不建议开启。

 在项目中应用的话，
 1. RunLoop保证子线程的长时间存活，而不是执行完任务后就立刻销毁的应用场景。这个是系统自己在底层自己处理得。
 2. 滑动与图片刷新: 当tableview的cell上有需要从网络获取的图片的时候，滚动tableView，异步线程会去加载图片，加载完成后主线程就会设置cell的图片(主线程刷新UI)，但是会造成卡顿。
 
 可以让设置图片的任务在CFRunLoopDefaultMode下进行，当滚动tableView的时候，RunLoop是在 UITrackingRunLoopMode 下进行，不去设置图片，而是当停止的时候，再去设置图片。

 - (void)viewDidLoad {
   [super viewDidLoad];
 
   // 只在NSDefaultRunLoopMode下执行(刷新图片)
   [self.myImageView performSelector:@selector(setImage:) withObject:[UIImage imageNamed:@""] afterDelay:ti inModes:@[NSDefaultRunLoopMode]];
 }
 
 
 系统默认注册了5个Mode:

 kCFRunLoopDefaultMode: App的默认 Mode，通常主线程是在这个 Mode 下运行的。

 UITrackingRunLoopMode: 界面跟踪 Mode，用于 ScrollView 追踪触摸滑动，保证界面滑动时不受其他 Mode 影响。

 UIInitializationRunLoopMode: 在刚启动 App 时第进入的第一个 Mode，启动完成后就不再使用。

 GSEventReceiveRunLoopMode: 接受系统事件的内部 Mode，通常用不到。

 kCFRunLoopCommonModes: 这是一个占位的 Mode，没有实际作用。(公用Mode)

 
  
 3. 保持子线程一直处理事件: 为了保证线程长期运转，可以在子线程中加入RunLoop，并且给Runloop设置item，防止Runloop自动退出。


 + (void)networkRequestThreadEntryPoint:(id)__unused object {
     @autoreleasepool {
         [[NSThread currentThread] setName:@"AFNetworking"];
         NSRunLoop *runLoop = [NSRunLoop currentRunLoop];
         [runLoop addPort:[NSMachPort port] forMode:NSDefaultRunLoopMode];
         [runLoop run];
     }
 }

 + (NSThread *)networkRequestThread {
     static NSThread *_networkRequestThread = nil;
     static dispatch_once_t oncePredicate;
     dispatch_once(&oncePredicate, ^{
         _networkRequestThread = [[NSThread alloc] initWithTarget:self selector:@selector(networkRequestThreadEntryPoint:) object:nil];
         [_networkRequestThread start];
     });
     return _networkRequestThread;
 }
 - (void)start {
     [self.lock lock];
     if ([self isCancelled]) {
         [self performSelector:@selector(cancelConnection) onThread:[[self class] networkRequestThread] withObject:nil waitUntilDone:NO modes:[self.runLoopModes allObjects]];
     } else if ([self isReady]) {
         self.state = AFOperationExecutingState;
         [self performSelector:@selector(operationDidStart) onThread:[[self class] networkRequestThread] withObject:nil waitUntilDone:NO modes:[self.runLoopModes allObjects]];
     }
     [self.lock unlock];
 }
 */
