
#import "ItemsModel.h"

@implementation ItemsModel

+ (NSDictionary *)modelCustomPropertyMapper {
    return @{@"descr" : @"description"};
}

// for Undefined Key
- (void)setValue:(id)value forUndefinedKey:(NSString *)key {

}

@end
