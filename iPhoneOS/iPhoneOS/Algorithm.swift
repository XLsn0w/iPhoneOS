//
//  Algorithm.swift
//  iPhoneOS
//
//  Created by XLsn0w on 2020/2/22.
//  Copyright © 2020 XLsn0w. All rights reserved.
//

import UIKit

class Algorithm: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }
    

    /*
    // MARK: - 常用算法

    /**
     *  【选择排序】：最值出现在起始端
     *
     *  第1趟：在n个数中找到最小(大)数与第一个数交换位置
     *  第2趟：在剩下n-1个数中找到最小(大)数与第二个数交换位置
     *  重复这样的操作...依次与第三个、第四个...数交换位置
     *  第n-1趟，最终可实现数据的升序（降序）排列。
     *
     */
    void selectSort(int *arr, int length) {
        for (int i = 0; i < length - 1; i++) { //趟数
            for (int j = i + 1; j < length; j++) { //比较次数
                if (arr[i] > arr[j]) {
                    int temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
    }
     
    /**
     *  【冒泡排序】：相邻元素两两比较，比较完一趟，最值出现在末尾
     *  第1趟：依次比较相邻的两个数，不断交换（小数放前，大数放后）逐个推进，最值最后出现在第n个元素位置
     *  第2趟：依次比较相邻的两个数，不断交换（小数放前，大数放后）逐个推进，最值最后出现在第n-1个元素位置
     *   ……   ……
     *  第n-1趟：依次比较相邻的两个数，不断交换（小数放前，大数放后）逐个推进，最值最后出现在第2个元素位置
     */
    void bublleSort(int *arr, int length) {
        for(int i = 0; i < length - 1; i++) { //趟数
            for(int j = 0; j < length - i - 1; j++) { //比较次数
                if(arr[j] > arr[j+1]) {
                    int temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
            }
        }
    }
     
    /**
     *  折半插入查找：优化查找时间（不用遍历全部数据）
     *
     *  折半查找的原理：
     *   1> 数组必须是有序的
     *   2> 必须已知min和max（知道范围）
     *   3> 动态计算mid的值，取出mid对应的值进行比较
     *   4> 如果mid对应的值大于要查找的值，那么max要变小为mid-1
     *   5> 如果mid对应的值小于要查找的值，那么min要变大为mid+1
     *
     */
     
    // 已知一个有序数组, 和一个key, 要求从数组中找到key对应的索引位置
    int findKey(int *arr, int length, int key) {
        int min = 0, max = length - 1, mid;
        while (min <= max) {
            mid = (min + max) / 2; //计算中间值
            if (key > arr[mid]) {
                min = mid + 1;
            } else if (key < arr[mid]) {
                max = mid - 1;
            } else {
                return mid;
            }
        }
        return -1;
    }
    */

}
