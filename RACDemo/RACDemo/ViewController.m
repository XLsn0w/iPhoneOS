//
//  ViewController.m
//  RACDemo
//
//  Created by XLsn0w on 2020/4/5.
//  Copyright © 2020 XLsn0w. All rights reserved.
//

//Swift访问OC
//统一在桥接文件(ProductName-Bridging-Header.h)中导入需要暴露给Swift的OC类即可在Swift中访问。
//
//OC访问Swift
//设置Defines Module 为Yes
//在OC类中导入ProductName-Swift.h文件，即可访问Swift中暴露给OC的属性和方法。
//1、Swift4.0中想要暴露给OC的方法和属性前面都需添加@objc；
//2、Swift的class需要继承与NSObject。

#import "ViewController.h"
//#import "RACDemo-Swift.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    
}


@end
