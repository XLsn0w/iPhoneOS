//
//  BaseViewModel.h
//  XLsn0wItems
//
//  Created by XLsn0w on 2020/3/7.
//  Copyright © 2020 XLsn0w. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface BaseViewModel : NSObject

/**
 *  POST请求
 @param url        请求网址
 @param params 请求参数
 @param success    成功回调
 @param failure    失败回调
 */
- (void)POST:(NSString *)url
      params:(NSDictionary *)params
     success:(void (^)(id responseObject))success
     failure:(void (^)(NSError * error))failure;

@end

NS_ASSUME_NONNULL_END
