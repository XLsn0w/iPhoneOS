//
//  KVO.swift
//  iPhoneOS
//
//  Created by XLsn0w on 2020/2/17.
//  Copyright © 2020 XLsn0w. All rights reserved.
//

import UIKit

class KVO: UIView {

    /*
    五、KVO (Key-value observing)
    KVO是观察者模式的另一实现。
    使用了isa混写(isa-swizzling)来实现KVO

    使用setter方法改变值KVO会生效，使用setValue:forKey即KVC改变值KVO也会生效，因为KVC会去调用setter方法

    - (void)setValue:(id)value
    {
        [self willChangeValueForKey:@"key"];
        
        [super setValue:value];
        
        [self didChangeValueForKey:@"key"];
    }
    那么通过直接赋值成员变量会触发KVO吗？
    不会，因为不会调用setter方法，需要加上
    willChangeValueForKey和didChangeValueForKey方法来手动触发才行
    六、KVC(Key-value coding)

    -(id)valueForKey:(NSString *)key;

    -(void)setValue:(id)value forKey:(NSString *)key;
    KVC就是指iOS的开发中，可以允许开发者通过Key名直接访问对象的属性，或者给对象的属性赋值。而不需要调用明确的存取方法。这样就可以在运行时动态地访问和修改对象的属性。而不是在编译时确定，这也是iOS开发中的黑魔法之一。很多高级的iOS开发技巧都是基于KVC实现的

    当调用setValue：属性值 forKey：@”name“的代码时，，底层的执行机制如下：

    程序优先调用set<Key>:属性值方法，代码通过setter方法完成设置。注意，这里的<key>是指成员变量名，首字母大小写要符合KVC的命名规则，下同
    如果没有找到setName：方法，KVC机制会检查+ (BOOL)accessInstanceVariablesDirectly方法有没有返回YES，默认该方法会返回YES，如果你重写了该方法让其返回NO的话，那么在这一步KVC会执行setValue：forUndefinedKey：方法，不过一般开发者不会这么做。所以KVC机制会搜索该类里面有没有名为<key>的成员变量，无论该变量是在类接口处定义，还是在类实现处定义，也无论用了什么样的访问修饰符，只在存在以<key>命名的变量，KVC都可以对该成员变量赋值。
    如果该类即没有set<key>：方法，也没有_<key>成员变量，KVC机制会搜索_is<Key>的成员变量。
    和上面一样，如果该类即没有set<Key>：方法，也没有_<key>和_is<Key>成员变量，KVC机制再会继续搜索<key>和is<Key>的成员变量。再给它们赋值。
    如果上面列出的方法或者成员变量都不存在，系统将会执行该对象的setValue：forUndefinedKey：方法，默认是抛出异常。
    即如果没有找到Set<Key>方法的话，会按照_key，_iskey，key，iskey的顺序搜索成员并进行赋值操作。

    如果开发者想让这个类禁用KVC，那么重写+ (BOOL)accessInstanceVariablesDirectly方法让其返回NO即可，这样的话如果KVC没有找到set<Key>:属性名时，会直接用setValue：forUndefinedKey：方法。

    当调用valueForKey：@”name“的代码时，KVC对key的搜索方式不同于setValue：属性值 forKey：@”name“，其搜索方式如下：

    首先按get<Key>,<key>,is<Key>的顺序方法查找getter方法，找到的话会直接调用。如果是BOOL或者Int等值类型， 会将其包装成一个NSNumber对象。
    如果上面的getter没有找到，KVC则会查找countOf<Key>,objectIn<Key>AtIndex或<Key>AtIndexes格式的方法。如果countOf<Key>方法和另外两个方法中的一个被找到，那么就会返回一个可以响应NSArray所有方法的代理集合(它是NSKeyValueArray，是NSArray的子类)，调用这个代理集合的方法，或者说给这个代理集合发送属于NSArray的方法，就会以countOf<Key>,objectIn<Key>AtIndex或<Key>AtIndexes这几个方法组合的形式调用。还有一个可选的get<Key>:range:方法。所以你想重新定义KVC的一些功能，你可以添加这些方法，需要注意的是你的方法名要符合KVC的标准命名方法，包括方法签名。
    如果上面的方法没有找到，那么会同时查找countOf<Key>，enumeratorOf<Key>,memberOf<Key>格式的方法。如果这三个方法都找到，那么就返回一个可以响应NSSet所的方法的代理集合，和上面一样，给这个代理集合发NSSet的消息，就会以countOf<Key>，enumeratorOf<Key>,memberOf<Key>组合的形式调用。
    如果还没有找到，再检查类方法+ (BOOL)accessInstanceVariablesDirectly,如果返回YES(默认行为)，那么和先前的设值一样，会按_<key>,_is<Key>,<key>,is<Key>的顺序搜索成员变量名，这里不推荐这么做，因为这样直接访问实例变量破坏了封装性，使代码更脆弱。如果重写了类方法+ (BOOL)accessInstanceVariablesDirectly返回NO的话，那么会直接调用valueForUndefinedKey:方法，默认是抛出异常。
    七、属性关键字
    1.读写权限：readonly,readwrite(默认)
    2.原子性: atomic(默认)，nonatomic。atomic读写线程安全，但效率低，而且不是绝对的安全，比如如果修饰的是数组，那么对数组的读写是安全的，但如果是操作数组进行添加移除其中对象的还，就不保证安全了。
    3.引用计数：

    retain/strong
    assign：修饰基本数据类型，修饰对象类型时，不改变其引用计数，会产生悬垂指针，修饰的对象在被释放后，assign指针仍然指向原对象内存地址，如果使用assign指针继续访问原对象的话，就可能会导致内存泄漏或程序异常
    weak：不改变被修饰对象的引用计数，所指对象在被释放后，weak指针会自动置为nil
    copy：分为深拷贝和浅拷贝
    浅拷贝：对内存地址的复制，让目标对象指针和原对象指向同一片内存空间会增加引用计数
    深拷贝：对对象内容的复制，开辟新的内存空间

    image.png
    可变对象的copy和mutableCopy都是深拷贝
    不可变对象的copy是浅拷贝，mutableCopy是深拷贝
    copy方法返回的都是不可变对象

    @property (nonatomic, copy) NSMutableArray * array;这样写有什么影响？
    因为copy方法返回的都是不可变对象，所以array对象实际上是不可变的，如果对其进行可变操作如添加移除对象，则会造成程序crash
    64人点赞
    iOS面试题


    作者：Theendisthebegi
    链接：https://www.jianshu.com/p/e70bac443cf2
    来源：简书
    著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
    */

}
