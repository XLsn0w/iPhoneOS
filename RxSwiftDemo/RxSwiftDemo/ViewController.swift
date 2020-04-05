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
    
    @IBOutlet weak var label: UILabel!
    @IBOutlet weak var input: UITextField!
    @IBOutlet weak var btn: UIButton!
    let disposeBag = DisposeBag()
    let person = Person();

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        
        self.person.addObserver(self, forKeyPath: "name", options: .new, context: nil)
        
//        self.person.rx.observeWeakly(String.self, "name")
//                  .subscribe(onNext: { (value) in
//                      print("rx KVO == \(value!)")
//                  })
//              .disposed(by: disposeBag)
        
        Timer.scheduledTimer(timeInterval: 3, target: self, selector: #selector(timeSelect), userInfo: nil, repeats: true)
        
//        RX中的timer和OC不一样，rx中的timer是一种自己定义的状态，进行不断的改变达到类似于OC的timer的效果，所以rx的timer不受runloop的影响。
        var timer:Observable<Any>!
     //   timer = Observable.interval(3, scheduler: MainScheduler.instance)
        
//        timer = Observable<Int>.interval(5, scheduler: MainScheduler.instance)//放在主线程执行 MainScheduler.instance
//                timer.subscribe(onNext: { (num) in
//                    print(num)
//                })
//                .disposed(by:disposeBag)
//
//        NotificationCenter.default.rx.notification(UIResponder.keyboardWillShowNotification)
//                   .subscribe(onNext: { (noti) in
//                       print("接收到键盘弹出\(noti)")
//                   })
//                   .disposed(by: disposeBag)
        
        let tap = UITapGestureRecognizer()
        self.label.addGestureRecognizer(tap)
        self.label.isUserInteractionEnabled = true

        tap.rx.event
            .subscribe(onNext: { (tap) in
                print("label被点击了")
            })
        .disposed(by: disposeBag)
        
        self.input.rx.text.orEmpty
                   .subscribe(onNext: { (text) in
                       print(text)
                   })
                   .disposed(by: disposeBag)
        
        self.btn.rx.tap
        .subscribe(onNext: { () in
            print("bbuttonb被点击了~~~~")
        })
        .disposed(by: disposeBag)
    }
    
    @objc func timeSelect() {
        print("----")
    }

    override func observeValue(forKeyPath keyPath: String?, of object: Any?, change: [NSKeyValueChangeKey : Any]?, context: UnsafeMutableRawPointer?) {
        print(change?[.newKey] as? String ?? "完了，没拿到值")
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
          print("touch")
          NotificationCenter.default.post(name: NSNotification.Name("testNotifi"), object: self, userInfo: ["post":"通知接收的消息到了"])
          self.view.endEditing(false)
//          self.person.name += "+呵呵哒";
      }

}

