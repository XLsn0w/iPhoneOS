
#import "BaseViewModel.h"

@class ItemsModel;
@class ItemsViewController;

@interface ItemsVM : BaseViewModel <UICollectionViewDataSource, UICollectionViewDelegate>

@property (nonatomic,strong) NSMutableArray *datas;
@property (nonatomic, strong) UICollectionView *collectionView;
@property (nonatomic, weak) ItemsViewController *viewController;

//获取数据
- (void)loadListData;
- (void)loadMoreListData:(NSInteger)pageIndex;

@end
