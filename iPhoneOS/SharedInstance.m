//
//  SharedInstance.m
//  iPhoneOS
//
//  Created by XLsn0w on 2020/2/21.
//  Copyright © 2020 XLsn0w. All rights reserved.
//

#import "SharedInstance.h"

@implementation SharedInstance

//+ (instancetype)sharedInstance {
//    return [[self alloc] init];
//}
//
//- (instancetype)init {
//    if (self = [super init]) {
//
//    }
//    return self;
//}
//+ (instancetype)allocWithZone:(struct _NSZone *)zone {
//    static SharedInstance *singleClass = nil;
//    static dispatch_once_t onceToken;
//    dispatch_once(&onceToken, ^{
//        singleClass = [super allocWithZone:zone];//最先执行，只执行了一次
//    });
//    return singleClass;
//}

// 要是自己用的话，直接用shareInstance方法创建没啥问题，
// 但是如果同组或者别人没注意用alloc创建、或者别人不小心使用copy、mutableCopy就可能产生两个实例，也就不存在单例。
// 所以要封堵 所有初始化的方法 如alloc, copy,mutableCopy,new
static SharedInstance* _instance = nil;
+ (instancetype)shared {
    static dispatch_once_t onceToken ;
    dispatch_once(&onceToken, ^{
        _instance = [[super allocWithZone:NULL] init] ;
        //不是使用alloc方法，而是调用[[super allocWithZone:NULL] init]
        //已经重载allocWithZone基本的对象分配方法，所以要借用父类（NSObject）的功能来帮助出处理底层内存分配的杂物
    }) ;
    return _instance ;
    }
 
 //用alloc返回也是唯一实例
+ (instancetype)allocWithZone:(struct _NSZone *)zone {
    return [SharedInstance shared] ;
}
//使用copy也是返回唯一实例
- (id)copyWithZone:(NSZone *)zone {
    return [SharedInstance shared] ;//return _instance;
}
 //使用mutablecopy也是返回唯一实例
- (id)mutableCopyWithZone:(NSZone *)zone {
    return [SharedInstance shared] ;
}

@end
