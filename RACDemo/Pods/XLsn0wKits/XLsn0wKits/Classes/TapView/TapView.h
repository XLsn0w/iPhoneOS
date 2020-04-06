//
//  TapView.h
//  TimeForest
//
//  Created by TimeForest on 2018/10/30.
//  Copyright © 2018 TimeForest. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef void(^TapViewAction)(void);
typedef void(^TapViewTagAction)(NSInteger tag);

@interface TapView : UIImageView

@property (nonatomic, copy) TapViewAction tapViewAction;
@property (nonatomic, copy) TapViewTagAction tapViewTagAction;

- (void)clipRoundCornersFromView:(UIView*)view;

@end

NS_ASSUME_NONNULL_END
