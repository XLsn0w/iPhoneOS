
#import "BaseModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface ItemsModel : BaseModel

@property (nonatomic, copy) NSString* name;
@property (nonatomic, copy) NSString* descr;
@property (nonatomic, copy) NSString* price;
@property (nonatomic, copy) NSString* image;
@property (nonatomic, assign) BOOL isLoad; // 是否加载网络图片

@end

NS_ASSUME_NONNULL_END
