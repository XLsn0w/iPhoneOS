# 创建私有CocoaPods库

```


$ pod lib create XLsn0wKits

找到路径XLsn0wKits/XLsn0wKits/Classes的"ReplaceMe.m"文件删除，然后将自己所需要的文件放到这里目录下

cd到Example路径下， 执行pod install 更新Example项目中的pod


$ cd XLsn0wKits

$ pod lib lint

$ pod spec lint

$ pod repo add XLsn0wKits https://github.com/XLsn0w/podspec.git

$ pod repo push XLsn0wKits XLsn0wKits.podspec --sources=https://github.com/XLsn0w/podspec.git



```

[![CI Status](https://img.shields.io/travis/xlsn0w/XLsn0wKits.svg?style=flat)](https://travis-ci.org/xlsn0w/XLsn0wKits)
[![Version](https://img.shields.io/cocoapods/v/XLsn0wKits.svg?style=flat)](https://cocoapods.org/pods/XLsn0wKits)
[![License](https://img.shields.io/cocoapods/l/XLsn0wKits.svg?style=flat)](https://cocoapods.org/pods/XLsn0wKits)
[![Platform](https://img.shields.io/cocoapods/p/XLsn0wKits.svg?style=flat)](https://cocoapods.org/pods/XLsn0wKits)

## Example

To run the example project, clone the repo, and run `pod install` from the Example directory first.

## Requirements

## Installation

XLsn0wKits is available through [CocoaPods](https://cocoapods.org). To install
it, simply add the following line to your Podfile:

```ruby
pod 'XLsn0wKits'
```

## Author

xlsn0w, xlsn0wios@gmail.com

## License

XLsn0wKits is available under the MIT license. See the LICENSE file for more info.
