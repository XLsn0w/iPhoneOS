//
//  TapLabel.m
//  Medicine
//
//  Created by Mac on 2019/4/9.
//  Copyright © 2019 XLsn0w. All rights reserved.
//

#import "TapLabel.h"
//#import "ReactiveObjC.h"

@implementation TapLabel

- (instancetype)init {
    self = [super init];
    if (self) {
        self.userInteractionEnabled = YES;
        UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc]initWithTarget:self action:@selector(tapAction:)];
        [self addGestureRecognizer:tap];
    }
    return self;
}

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        self.userInteractionEnabled = YES;
//        UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc] init];
//        [self addGestureRecognizer:tap];
        UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc]initWithTarget:self action:@selector(tapAction:)];
        [self addGestureRecognizer:tap];
//        [tap.rac_gestureSignal subscribeNext:^(__kindof UIGestureRecognizer * _Nullable x) {
//            if (self.tapLabelAction) {
//                self.tapLabelAction();
//            }
//        }];
    }
    return self;
}

- (void)tapAction:(UITapGestureRecognizer*)tap {
    if (self.tapLabelAction) {
        self.tapLabelAction();
    }
}

@end
