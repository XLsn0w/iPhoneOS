
#import "ItemsVM.h"
#import "ItemsCell.h"
#import "ItemsModel.h"

#define kListURL  @"http://devmobile.zhuawawa.site/neckpets/getBlindBoxSeriesLitByTabType.json"
#define kPageSize @(20)
#define kToken    @"8ed7ddfde5ca37849b7c43591957d7fb73adc2a1"

@interface ItemsVM ()

@end

@implementation ItemsVM

- (NSMutableArray *)datas {
    if (!_datas) {
        _datas = [NSMutableArray array];
    }
    return _datas;
}

- (void)loadListData {
    @WeakObj(self);
    [self.datas removeAllObjects];
    NSDictionary* params = @{@"requestData":@{@"pageSize"  :kPageSize,
                                              @"pageNumber":@(1),
                                              @"userToken" :kToken}};
    [self POST:kListURL
       params:params
      success:^(id _Nonnull responseObject) {
        if (isNotNull(responseObject[@"data"])) {
            for (NSDictionary* dic in responseObject[@"data"]) {
                ItemsModel *model = [ItemsModel yy_modelWithDictionary:dic];
                model.isLoad = YES;//第一次允许加载
                [self.datas addObject:model];
            }
        }
        [selfWeak.collectionView reloadData];
    }
      failure:^(NSError * _Nonnull error) {
        
    }];
}

- (void)loadMoreListData:(NSInteger)pageIndex {
    @WeakObj(self);
    
    NSDictionary* params = @{@"requestData":@{@"pageSize":kPageSize,
                                              @"pageNumber":@(pageIndex),
                                              @"userToken":kToken}};
    [self POST:kListURL
       params:params
      success:^(id _Nonnull responseObject) {
        if (isNotNull(responseObject[@"data"])) {
            for (NSDictionary* dic in responseObject[@"data"]) {
                ItemsModel *model = [ItemsModel yy_modelWithDictionary:dic];
                model.isLoad = NO;//装到数组中，滚动不加载
                [self.datas addObject:model];
                dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                    [self addModelToCells];//延迟准备数据，再显示
                });
            }
        } else {
            [XLsn0wShow showCenterWithText:@"没有更多数据啦"];
        }
        [selfWeak.collectionView reloadData];
    }
      failure:^(NSError * _Nonnull error) {
        
    }];
}

#pragma mark collectionView代理方法
//返回section个数
- (NSInteger)numberOfSectionsInCollectionView:(UICollectionView *)collectionView {
    return 1;
}

//每个section的item个数
- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    return self.datas.count;
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath {
    ItemsCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:@"ItemsCell" forIndexPath:indexPath];
    ItemsModel* model = self.datas[indexPath.item];
    if (model.isLoad == YES) {
        [cell addModel:model];
    } else {
        [cell addModelForText:model];
    }
    return cell;
}

//设置每个item的尺寸
- (CGSize)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)collectionViewLayout sizeForItemAtIndexPath:(NSIndexPath *)indexPath {
    return CGSizeMake((kScreenWidth-15*2-0)/2, (kScreenWidth-15*2-0)/2+60);
}

//设置每个item的UIEdgeInsets
- (UIEdgeInsets)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)collectionViewLayout insetForSectionAtIndex:(NSInteger)section {
    return UIEdgeInsetsMake(10, 10, 10, 10);
}

//设置每个item水平间距
- (CGFloat)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)collectionViewLayout minimumInteritemSpacingForSectionAtIndex:(NSInteger)section {
    return 10;
}

//设置每个item垂直间距
- (CGFloat)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)collectionViewLayout minimumLineSpacingForSectionAtIndex:(NSInteger)section {
    return 10;
}

//点击item方法
- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath {

}

#pragma mark - UIScrollView Delegate

- (void)scrollViewDidEndDragging:(UIScrollView *)scrollView willDecelerate:(BOOL)decelerate{
    //滑动时 加载占位图
    if (!decelerate) {
        [self addModelToCells];
    }
}

- (void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView {
    // 停止滑动 加载数据
    [self addModelToCells];
}

- (void)addModelToCells {
    NSArray *visibleItems = [self.collectionView indexPathsForVisibleItems];
    for (NSIndexPath *indexPath in visibleItems) {
        ItemsCell * cell = (ItemsCell *)[self.collectionView cellForItemAtIndexPath:indexPath];
        ItemsModel* model = self.datas[indexPath.item];
        [cell addModel:model];
    }
}

@end
