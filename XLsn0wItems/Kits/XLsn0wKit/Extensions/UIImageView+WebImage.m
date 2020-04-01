//
//  UIImageView+WebImage.m
//  TimeForest
//
//  Created by TimeForest on 2018/10/24.
//  Copyright © 2018 TimeForest. All rights reserved.
//

#import "UIImageView+WebImage.h"
#import "SDWebImageCompat.h"
#import "SDWebImageManager.h"
#import "UIImageView+WebImage.h"

@implementation UIImageView (WebImage)

- (void)setImageFromURLString:(NSString *)url placeholderImageName:(NSString *)placeholderImageName {
    if (isNotNull(url)) {
        [self sd_setImageWithURL:[NSURL URLWithString:url] placeholderImage:[UIImage imageNamed:placeholderImageName]];
    } else {
        self.image = [UIImage imageNamed:@"default_avatar"];
    }
}

- (void)setImageFromURLString:(NSString *)url {
    if (isNotNull(url)) {
        [self sd_setImageWithURL:[NSURL URLWithString:url] placeholderImage:[UIImage imageNamed:@"placeholderAppImage"]];
    } else {
        self.image = [UIImage imageNamed:@"placeholderAppImage"];
    }
}

///居中裁剪
- (void)centerClip {
    [self setContentScaleFactor:[[UIScreen mainScreen] scale]];
    self.contentMode =  UIViewContentModeScaleAspectFill;
    self.autoresizingMask = UIViewAutoresizingFlexibleHeight;
    self.clipsToBounds  = YES;
}

@end
