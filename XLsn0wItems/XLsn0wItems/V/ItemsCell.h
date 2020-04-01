
#import <UIKit/UIKit.h>

@class ItemsModel;

NS_ASSUME_NONNULL_BEGIN

@interface ItemsCell : UICollectionViewCell

@property (nonatomic, strong) UIImageView* goodsIcon;
@property (nonatomic, strong) UILabel *title;
@property (nonatomic, strong) UILabel *subtitle;
@property (nonatomic, strong) UILabel *price;

- (void)addModel:(ItemsModel*)model;
- (void)addModelForText:(ItemsModel*)model;// 图片耗资源不加载 文本可以加载

@end

NS_ASSUME_NONNULL_END
