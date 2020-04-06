//
//  TapLabel.h
//  Medicine
//
//  Created by Mac on 2019/4/9.
//  Copyright © 2019 XLsn0w. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef void(^TapLabelAction)(void);

NS_ASSUME_NONNULL_BEGIN

@interface TapLabel : UILabel

@property (nonatomic, copy) TapLabelAction tapLabelAction;

@end

NS_ASSUME_NONNULL_END
