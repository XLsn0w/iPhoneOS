//
//  BaseCollectionViewCell.m
//  xiaolvlan
//
//  Created by mac on 2019/3/26.
//  Copyright © 2019年 mac. All rights reserved.
//

#import "BaseCollectionViewCell.h"

@implementation BaseCollectionViewCell

- (UINavigationController*)currentNav {
    return [self getCurrentVCWithCurrentView:self].navigationController;
}

- (UIViewController *)getCurrentVCWithCurrentView:(UIView *)currentView {
    for (UIView *next = currentView ; next ; next = next.superview) {
        UIResponder *nextResponder = [next nextResponder];
        if ([nextResponder isKindOfClass:[UIViewController class]]) {
            return (UIViewController *)nextResponder;
        }
    }
    return nil;
}

- (instancetype)initWithFrame:(CGRect)frame{
    if (self = [super initWithFrame:frame]) {
        
    }
    return self;
}

- (void)addDataFromModel:(id)model {
    
}

- (void)addData:(id)model {
    
}

- (void)clipRoundCornersFromView:(UIView*)view {
    UIBezierPath *maskPath = [UIBezierPath bezierPathWithRoundedRect:view.bounds byRoundingCorners:UIRectCornerTopLeft | UIRectCornerTopRight cornerRadii:CGSizeMake(6, 6)];
    
    CAShapeLayer *maskLayer = [CAShapeLayer layer];
    
    maskLayer.frame = view.bounds;
    
    maskLayer.path = maskPath.CGPath;
    
    view.layer.mask = maskLayer;
}

- (void)clipRoundCornersFromViewBottomLeft:(UIView*)view {
    UIBezierPath *maskPath = [UIBezierPath bezierPathWithRoundedRect:view.bounds byRoundingCorners:UIRectCornerBottomLeft | UIRectCornerTopRight cornerRadii:CGSizeMake(20, 20)];
    
    CAShapeLayer *maskLayer = [CAShapeLayer layer];
    
    maskLayer.frame = view.bounds;
    
    maskLayer.path = maskPath.CGPath;
    
    view.layer.mask = maskLayer;
}

@end
