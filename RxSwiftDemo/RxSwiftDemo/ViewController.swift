//
//  ViewController.swift
//  RxSwiftDemo
//
//  Created by XLsn0w on 2020/4/5.
//  Copyright © 2020 XLsn0w. All rights reserved.
//

import UIKit
import RxSwift

class ViewController: UIViewController {
    
    let disposeBag = DisposeBag()

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
    }

    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
          print("touch")
          NotificationCenter.default.post(name: NSNotification.Name("testNotifi"), object: self, userInfo: ["post":"通知接收的消息到了"])
          self.view.endEditing(false)
//          self.person.name += "+呵呵哒";
      }

}

