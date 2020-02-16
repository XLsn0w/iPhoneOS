//
//  RunLooooop.m
//  iPhoneOS
//
//  Created by XLsn0w on 2020/2/16.
//  Copyright © 2020 XLsn0w. All rights reserved.
//

#import "RunLooooop.h"

@implementation RunLooooop



@end


/*
 
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
