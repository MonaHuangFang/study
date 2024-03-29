//
//  LGViewController.m
//  003---自定义KVO
//
//  Created by cooci on 2019/1/5.
//  Copyright © 2019 cooci. All rights reserved.
//

#import "LGViewController.h"
#import "LGPerson.h"
#import <objc/runtime.h>
#import "NSObject+Kt_Extension.h"

@interface LGViewController ()
@property (nonatomic, strong) LGPerson *person;
@end

@implementation LGViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = UIColor.greenColor;
    self.person = [[LGPerson alloc] init];
    [self.person kt_addObserverKeyPath:@"nickName" block:^(id  _Nullable newVal, id  _Nullable oldVal) {
        NSLog(@"%@ --- %@",oldVal,newVal);
    }];
//    [self.person lg_addObserver:self forKeyPath:@"name" options:(NSKeyValueObservingOptionNew) context:NULL];
    self.person.nickName = @"KC";
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
    self.person.nickName = [NSString stringWithFormat:@"%@+",self.person.nickName];
}


- (void)dealloc{
//    [self.person kt_removeObserverKeyPath:@"nickName"];
    NSLog(@"end");
}


#pragma mark - 遍历方法-ivar-property
- (void)printClassAllMethod:(Class)cls{
    unsigned int count = 0;
    Method *methodList = class_copyMethodList(cls, &count);
    for (int i = 0; i<count; i++) {
        Method method = methodList[i];
        SEL sel = method_getName(method);
        IMP imp = class_getMethodImplementation(cls, sel);
        NSLog(@"%@-%p",NSStringFromSelector(sel),imp);
    }
    free(methodList);
}

#pragma mark - 遍历类以及子类
- (void)printClasses:(Class)cls{
    
    /// 注册类的总数
    int count = objc_getClassList(NULL, 0);
    /// 创建一个数组， 其中包含给定对象
    NSMutableArray *mArray = [NSMutableArray arrayWithObject:cls];
    /// 获取所有已注册的类
    Class* classes = (Class*)malloc(sizeof(Class)*count);
    objc_getClassList(classes, count);
    for (int i = 0; i<count; i++) {
        if (cls == class_getSuperclass(classes[i])) {
            [mArray addObject:classes[i]];
        }
    }
    free(classes);
    NSLog(@"classes = %@", mArray);
}
@end
