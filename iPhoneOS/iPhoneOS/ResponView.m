//
//  ResponView.m
//  iPhoneOS
//
//  Created by XLsn0w on 2020/2/16.
//  Copyright © 2020 XLsn0w. All rights reserved.
//

#import "ResponView.h"

@implementation ResponView

/*
事件的传递和响应分两个链：

传递链：由系统向离用户最近的view传递。UIKit –> active app’s event queue –> window –> root view –>……–>lowest view

响应链：由离用户最近的view向系统传递。initial view –> super view –> …..–> view controller –> window –> Application


*/

@end
