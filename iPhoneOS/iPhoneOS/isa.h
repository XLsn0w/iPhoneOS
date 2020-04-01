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
