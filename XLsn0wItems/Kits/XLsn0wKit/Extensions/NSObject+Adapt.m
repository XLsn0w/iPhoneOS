//
//  NSObject+Adapt.m
//  XLsn0wItems
//
//  Created by XLsn0w on 2020/3/6.
//  Copyright © 2020 XLsn0w. All rights reserved.
//

#import "NSObject+Adapt.h"

@implementation NSObject (Adapt)

- (UIWindow *)keyWindow {
    return [UIApplication sharedApplication].keyWindow;
}

- (UIEdgeInsets)safeAreaInset {
    if (@available(iOS 11.0, *)) {
        if (self.keyWindow) {
            return self.keyWindow.safeAreaInsets;
        }
    }
    return UIEdgeInsetsZero;
}

- (BOOL)isHairHead {
    if (UIInterfaceOrientationIsLandscape([UIApplication sharedApplication].statusBarOrientation)) {
        return self.safeAreaInset.left > 0.0f;
    } else {// ios12 非刘海屏状态栏 20.0f
        return self.safeAreaInset.top > 20.0f;
    }
}

- (CGFloat)topHeight {
    if ([self isHairHead] == YES) {
        return 44 + [self safeAreaInset].top;
    } else {
        return 44;
    }
}

- (CGFloat)bottomHeight {//no tabbar
    if ([self isHairHead] == YES) {
        return 0 + [self safeAreaInset].bottom;
    } else {
        return 0;
    }
}

@end
