
#import "ItemsCell.h"
#import "ItemsModel.h"

@implementation ItemsCell

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        self.backgroundColor = AppWhiteColor;
        self.alpha = 1;
        self.opaque = YES;
        [self drawSubviews];
    }
    return self;
}

- (void)drawSubviews {
    _goodsIcon = [[UIImageView alloc] init];
    [self addSubview:_goodsIcon];
    [_goodsIcon mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(0);
        make.width.mas_equalTo((kScreenWidth-15*2-0)/2);
        make.height.mas_equalTo((kScreenWidth-15*2-0)/2);
        make.top.mas_equalTo(0);
    }];
    [_goodsIcon centerClip];
    
    _title = [[UILabel alloc] init];
    [self addSubview:_title];
    [_title mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(0);
        make.width.mas_equalTo((kScreenWidth-15*2-0)/2);
        make.top.mas_equalTo(self->_goodsIcon.mas_bottom).offset(10);
    }];
    [_title addTextFont:AppBoldSystemFont(18) textColor:UIColor.blackColor text:@""];

    _subtitle = [[UILabel alloc] init];
    [self addSubview:_subtitle];
    [_subtitle mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(0);
        make.width.mas_equalTo((kScreenWidth-15*2-0)/2);
        make.bottom.mas_equalTo(-10);
    }];
    [_subtitle addTextFont:AppSystemFont(13) textColor:HexColor(@"#333333") text:@""];
    
    _price = [[UILabel alloc] init];
    [self addSubview:_price];
    [_price mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(self.mas_right).offset(-30);
        make.width.mas_equalTo((kScreenWidth-15*2-0)/2);
        make.bottom.mas_equalTo(-10);
    }];
    [_price addTextFont:AppSystemFont(15) textColor:UIColor.redColor text:@""];
}

- (void)addModel:(ItemsModel*)model {
    if (isNotNull(model)) {
        [_goodsIcon setImageFromURLString:model.image];
        if (isNotNull(model.name)) {
            _title.text = model.name;
        }
        if (isNotNull(model.descr)) {
            _subtitle.text = model.descr;
        }
        if (isNotNull(model.price)) {
            _price.text = [NSString stringWithFormat:@"¥%@", model.price];
        }
        [model setIsLoad:YES];
    } else {
        _goodsIcon.image = [UIImage imageNamed:@"placeholderAppImage"];
        [model setIsLoad:NO];
    }
}

- (void)addModelForText:(ItemsModel*)model {
    _goodsIcon.image = [UIImage imageNamed:@"placeholderAppImage"];
    if (isNotNull(model)) {
        if (isNotNull(model.name)) {
            _title.text = model.name;
        }
        if (isNotNull(model.descr)) {
            _subtitle.text = model.descr;
        }
        if (isNotNull(model.price)) {
            _price.text = [NSString stringWithFormat:@"¥%@", model.price];
        }
    }
}

@end
