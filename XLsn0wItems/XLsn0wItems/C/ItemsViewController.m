
#import "ItemsViewController.h"
#import "ItemsCell.h"
#import "ItemsModel.h"
#import "ItemsVM.h"

@interface ItemsViewController ()

@property (nonatomic, strong) UICollectionView *collectionView;
@property (nonatomic, strong) ItemsVM *vm;

@end

@implementation ItemsViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self config];
}

- (void)config {
    self.view.backgroundColor = AppViewBackgroundColor;
    self.navigationItem.title = @"XLsn0wItems";
    [self.vm loadListData];
}

#pragma mark - lazy load

- (ItemsVM *)vm {
    if (!_vm) {
        _vm = [[ItemsVM alloc] init];
        _vm.collectionView = [self collectionView];
        _vm.viewController = self;
    }
    return _vm;
}

- (UICollectionView *)collectionView {
    if (!_collectionView) {
        UICollectionViewFlowLayout* layout = [[UICollectionViewFlowLayout alloc] init];
        _collectionView = [[UICollectionView alloc] initWithFrame:CGRectMake(0, self.topHeight, kScreenWidth, kScreenHeight-self.topHeight-self.bottomHeight) collectionViewLayout:layout];
        [self.view addSubview:_collectionView];
        _collectionView.backgroundColor = AppWhiteColor;
        [_collectionView registerClass:[ItemsCell class] forCellWithReuseIdentifier:@"ItemsCell"];
        _collectionView.delegate = _vm;
        _collectionView.dataSource = _vm;
        [self collectionViewConfig];
    }
    return _collectionView;
}

- (void)collectionViewConfig {
    self.extendedLayoutIncludesOpaqueBars = YES;
    if (@available(iOS 11.0, *)) {
        _collectionView.contentInsetAdjustmentBehavior = UIScrollViewContentInsetAdjustmentNever;
    } else {
        self.automaticallyAdjustsScrollViewInsets = NO;
    }
    @WeakObj(self);// add Footer Refresh
    [_collectionView addFooterRefresh:YES footerAction:^(NSInteger pageIndex) {
        [selfWeak.vm loadMoreListData:pageIndex];
    }];
}

@end
