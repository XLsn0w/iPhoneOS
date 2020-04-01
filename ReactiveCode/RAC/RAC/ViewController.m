//
//  ViewController.m
//  RAC
//
//  Created by XLsn0w on 2020/4/1.
//  Copyright © 2020 XLsn0w. All rights reserved.
//

#import "ViewController.h"
#import <ReactiveObjC.h>

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    RACSignal* viewWillAppearSignal = [self rac_signalForSelector:@selector(viewWillAppear:)];
    [viewWillAppearSignal subscribeNext:^(id  _Nullable x) {// viewWillAppear方法被调用
        
    }];

    
    // 1 信号未被创建
    RACSignal *racSignal = [RACSignal createSignal:^RACDisposable *(id subscriber) {
        
        // 3 信号被激活，开始发送事件
        
        [subscriber sendNext:@"👦🏻"];
        [subscriber sendCompleted];
        
        RACDisposable* disposable = [RACDisposable disposableWithBlock:^{
            // 6 订阅流程结束，可清理资源
        }];
        return disposable;
        
    }];

    // 2 信号已被创建，未被订阅（未激活）
    [racSignal subscribeNext:^(id  _Nullable x) {//信号已被订阅，可接收next类型事件
        
    } error:^(NSError * _Nullable error) {//发送next与completed类型事件时，此处不会走到
        
    } completed:^{//信号已被订阅，可接收completed类型事件
        
    }];

}


@end
