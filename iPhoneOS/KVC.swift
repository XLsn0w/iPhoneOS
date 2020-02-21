//
//  KVC.swift
//  iPhoneOS
//
//  Created by XLsn0w on 2020/2/20.
//  Copyright © 2020 XLsn0w. All rights reserved.
//

import UIKit

class KVC: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }
    

    /*
    KVC，键-值编码，使用字符串直接访问对象的属性。

    底层实现，当一个对象调用setValue方法时，方法内部会做以下操作：

    检查是否存在相应key的set方法，如果存在，就调用set方法

    如果set方法不存在，就会查找与key相同名称并且带下划线的成员属性，如果有，则直接给成员属性赋值

    如果没有找到_key，就会查找相同名称的属性key，如果有就直接赋值

    如果还没找到，则调用valueForUndefinedKey：和setValue：forUndefinedKey：方法


     
    */

}
