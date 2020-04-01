//
//  BaseCollectionViewCell.h
//  xiaolvlan
//
//  Created by mac on 2019/3/26.
//  Copyright © 2019年 mac. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface BaseCollectionViewCell : UICollectionViewCell

- (UINavigationController*)currentNav;
- (void)addData:(id)model;
- (void)clipRoundCornersFromView:(UIView*)view;
- (void)addDataFromModel:(id)model;
- (void)clipRoundCornersFromViewBottomLeft:(UIView*)view;
- (BOOL)isInReview;

@end

NS_ASSUME_NONNULL_END
