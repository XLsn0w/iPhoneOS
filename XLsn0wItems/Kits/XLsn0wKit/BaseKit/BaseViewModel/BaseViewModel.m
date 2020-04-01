//
//  BaseViewModel.m
//  XLsn0wItems
//
//  Created by XLsn0w on 2020/3/7.
//  Copyright © 2020 XLsn0w. All rights reserved.
//

#import "BaseViewModel.h"

@implementation BaseViewModel

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
     failure:(void (^)(NSError * error))failure {
    // 初始化Request
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:url] cachePolicy:NSURLRequestReloadIgnoringCacheData timeoutInterval:15.0];

    // http method
    [request setHTTPMethod:@"POST"];
    // http header
    [request addValue:@"application/x-www-form-urlencoded" forHTTPHeaderField:@"Content-Type"];
    // http body
    NSMutableString *paraString = [NSMutableString string];
    for (NSString *key in [params allKeys]) {
        [paraString appendFormat:@"&%@=%@", key, params[key]];
    }
    [paraString deleteCharactersInRange:NSMakeRange(0, 1)]; // 删除多余的&号
    [request setHTTPBody:[paraString dataUsingEncoding:NSUTF8StringEncoding]];

    // 初始化AFManager
    AFURLSessionManager *manager = [[AFURLSessionManager alloc] initWithSessionConfiguration: [NSURLSessionConfiguration defaultSessionConfiguration]];
    AFJSONResponseSerializer *serializer = [AFJSONResponseSerializer serializer];
    serializer.acceptableContentTypes = [NSSet setWithObjects:
                                         @"text/plain",
                                         @"application/json",
                                         @"text/html", nil];
    manager.responseSerializer = serializer;
    
     [MBProgressHUD showActivityMessageInWindow:@"加载中..."];

    // 构建请求任务
    NSURLSessionDataTask *dataTask = [manager dataTaskWithRequest:request completionHandler:^(NSURLResponse * _Nonnull response, id  _Nullable responseObject, NSError * _Nullable error) {
        
        if (error) {
            if (failure) {
                failure(error);
            }
            // 请求失败
            NSLog(@"Request failed with reason '%@'", [error localizedDescription]);
        } else {
            // 请求成功
            if (success) {
                success(responseObject);
            }
            NSLog(@"Request success with responseObject - \n %@", responseObject);
        }
        [MBProgressHUD hideHUD];
    }];

    // 发起请求
    [dataTask resume];
}

- (NSString *)convertJSONString:(NSDictionary *)dictionary {
    NSError *error;
    NSString *JSONString = [NSString string];
    if (isNotNull(dictionary)) {
        NSData *jsonData = [NSJSONSerialization dataWithJSONObject:dictionary options:NSJSONWritingPrettyPrinted error:&error];
        if (!jsonData) {
            XLsn0wLog(@"%@",error);
        }else{
            JSONString = [[NSString alloc]initWithData:jsonData encoding:NSUTF8StringEncoding];
        }
    }
    return JSONString;
}


@end
