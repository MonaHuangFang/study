//
//  AppDelegate.m
//  KVOTest
//
//  Created by 黄方 on 2022/3/27.
//

#import "AppDelegate.h"
#import "ViewController.h"

@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    self.window = [UIWindow.alloc initWithFrame:UIScreen.mainScreen.bounds];
    ViewController *vc = ViewController.alloc.init;
    UINavigationController *nav = [UINavigationController.alloc initWithRootViewController:vc];
    
    self.window.rootViewController = nav;
    
    [self.window makeKeyAndVisible];
    
    
    
    return YES;
}



@end
