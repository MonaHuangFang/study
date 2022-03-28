//
//  ViewController.m
//  KVOTest
//
//  Created by 黄方 on 2022/3/27.
//

#import "ViewController.h"
#import "LGViewController.h"
#import "LGPerson.h"
#import <objc/runtime.h>

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.view.backgroundColor = UIColor.whiteColor;
    self.navigationItem.rightBarButtonItem = [UIBarButtonItem.alloc initWithTitle:@"Push" style:(UIBarButtonItemStyleDone) target:self action:@selector(pushNextVC:)];
}

-(void)pushNextVC:(UIButton *)sender{
    LGViewController *vc = LGViewController.alloc.init;
    [self.navigationController pushViewController:vc animated:YES];
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
    [self printClasses:[LGPerson class]];
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
    NSLog(@"ViewController == classes = %@", mArray);
}


@end
