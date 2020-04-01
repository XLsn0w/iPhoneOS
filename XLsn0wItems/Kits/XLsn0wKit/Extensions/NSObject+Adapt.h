//
//  NSObject+Adapt.h
//  XLsn0wItems
//
//  Created by XLsn0w on 2020/3/6.
//  Copyright © 2020 XLsn0w. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSObject (Adapt)

- (UIEdgeInsets)safeAreaInset;
- (BOOL)isHairHead;
- (CGFloat)topHeight;
- (CGFloat)bottomHeight;

@end

NS_ASSUME_NONNULL_END
