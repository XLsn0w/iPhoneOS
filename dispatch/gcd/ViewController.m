//
//  ViewController.m
//  gcd
//
//  Created by XLsn0w on 2020/2/16.
//  Copyright © 2020 XLsn0w. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    [self gcdTest];
}

- (void)gcdTest {
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        NSLog(@"4");
    });
    dispatch_async(dispatch_get_main_queue(), ^{
        NSLog(@"5");
    });
    [self performSelector:@selector(test2)];
    [self performSelector:@selector(test3) withObject:nil afterDelay:0];
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        NSLog(@"6");
    });
    [self test1];
}

- (void)test1 {
    NSLog(@"1");
}
- (void)test2 {
    NSLog(@"2");
}
- (void)test3 {
    NSLog(@"3");
}

//  /*
//     苹果文档
//     Enqueue a block for execution at the specified time.
//     This function waits until the specified time and then asynchronously adds block to the specified queue.
//
//     dispatch_after 第二个参数为0，以此可以理解为在当前时刻往主队列添加一个block, 文档中 asynchronously 可以看出是在当前时刻
//     添加到主队列的尾部
//     */
//    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
//        NSLog(@"4");
//    });
//
//    /*
//    这里主要考的是 dispatch_async 这个函数的特点，往指定的队列添加一个block立马返回
//
//    以下代码在主线程上执行
//     dispatch_async(dispatch_get_main_queue(), ^{
//        NSLog(@"A");
//     });
//     NSLog(@"B");
//      结果为 BA
//
//     */
//    dispatch_async(dispatch_get_main_queue(), ^{
//        NSLog(@"5");
//    });
//
//    /*
//     performSelector:
//     先看苹果文档的解析:
//     Sends a specified message to the receiver and returns the result of the message.
//
//     那么这句话相当于
//     [self test2]
//     */
//    [self performSelector:@selector(test2)];
//
//    /*
//     performSelector:withObject:afterDelay:
//     Invokes a method of the receiver on the current thread using the default mode after a delay.
//     This method sets up a timer to perform the aSelector message on the current thread’s run loop. The timer is configured to run in the default mode (NSDefaultRunLoopMode). When the timer fires, the thread attempts to dequeue the message from the run loop and perform the selector. It succeeds if the run loop is running and in the default mode; otherwise, the timer waits until the run loop is in the default mode.
//
//     这些解析中最关键的一个单词是 NSDefaultRunLoopMode
//     NSDefaultRunLoopMode 是当前线程上正在执行的任务优先，
//     那么如果当前线程上有其他任务要执行，test3 先让步，然后在轮到它执行
//
//     如果往当前队列中 dispatch_async 一下，通过测试，他的优先级跟 performSelector:withObject:afterDelay: 是同等的，
//     换句话说就是谁先谁先执行
//     */
//    [self performSelector:@selector(test3) withObject:nil afterDelay:0];
//
//    /*
//    这里主要开启了一个异步线程，再加上 使用了 dispatch_async 函数 因此
//    NSLog(@"6"); 在此打印的比较随机
//     */
//    dispatch_async(dispatch_get_global_queue(0, 0), ^{
//        NSLog(@"6");
//    });
//
//    [self test1];
//
//    /*
//     综上所述:
//     执行的顺序为
//     test2
//     test1
//     NSLog(@"4");
//     NSLog(@"5");
//     test3
//
//     NSLog(@"6"); 的出现随机


//2020-02-16 20:33:30.548084+0800 gcd[2868:172654] 2
//2020-02-16 20:33:30.548263+0800 gcd[2868:172723] 6
//2020-02-16 20:33:30.548287+0800 gcd[2868:172654] 1
//2020-02-16 20:33:30.561348+0800 gcd[2868:172654] 4
//2020-02-16 20:33:30.561561+0800 gcd[2868:172654] 5
//2020-02-16 20:33:30.562641+0800 gcd[2868:172654] 3

//2020-02-16 20:33:57.776820+0800 gcd[2888:173295] 2
//2020-02-16 20:33:57.776980+0800 gcd[2888:173295] 1
//2020-02-16 20:33:57.776991+0800 gcd[2888:173477] 6
//2020-02-16 20:33:57.790145+0800 gcd[2888:173295] 4
//2020-02-16 20:33:57.790257+0800 gcd[2888:173295] 5
//2020-02-16 20:33:57.791210+0800 gcd[2888:173295] 3


//     */


@end
