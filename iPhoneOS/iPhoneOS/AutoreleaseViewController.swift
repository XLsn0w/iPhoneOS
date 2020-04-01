//
//  AutoreleaseViewController.swift
//  iPhoneOS
//
//  Created by XLsn0w on 2020/2/18.
//  Copyright © 2020 XLsn0w. All rights reserved.
//

import UIKit

class AutoreleaseViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        
        
    }
    //   https://opensource.apple.com/source/objc4/objc4-532/
    func loadBigData() {
        if let path = Bundle.main
            .path(forResource: "big", ofType: "jpg") {

            for i in 1...10000 {
                let data = NSData(contentsOfFile: path)
                
                autoreleasepool {
                    //let data = NSData.dataWithContentsOfFile(
                        //path, options: nil, error: nil)

                    Thread.sleep(forTimeInterval: 0.5)
                }
            }
        }
    }

    /*      https://opensource.apple.com/source/objc4/objc4-532/

     autorelease还跟runloop有关联？答案是肯定的，iOS很多内容都跟runloop有千丝万缕的关联，谁也离不开谁。
     
     app启动之后，苹果在主线程runloop里注册了两个observer，
     
     第一个 Observer 监视的事件是 Entry(即将进入Loop)，其回调内会调用 _objc_autoreleasePoolPush() 创建自动释放池。其 优先级最高，保证创建释放池发生在其他所有回调之前。
     
     第二个 Observer 监视了两个事件： BeforeWaiting(准备进入休眠) 时调用_objc_autoreleasePoolPop() 和 _objc_autoreleasePoolPush() 释放旧的池并创建新池；Exit(即将退出Loop) 时调用 _objc_autoreleasePoolPop() 来释放自动释放池。
     这个 Observer 的优先级最低，保证其释放池子发生在其他所有回调之后，
     
     正因为这套机制的存在，我们不需要关心autorelease的存在

  //
     class AutoreleasePoolPage {
         #if PROTECT_AUTORELEASEPOOL
             4096;  // must be multiple of vm page size
         #else
             4096;  // size and alignment, power of 2
         #endif
         magic_t const magic;
         id *next;
         pthread_t const thread;
         AutoreleasePoolPage * const parent;
         AutoreleasePoolPage *child;
         uint32_t const depth;
         uint32_t hiwat;
     }
     
    */

}
