//
//  AppDelegate.m
//  YayaTest
//
//  Created by 黄方 on 2022/3/21.
//

#import "AppDelegate.h"
#import "ViewController.h"
#import "YayaTest-Swift.h"

@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    self.window = [[UIWindow alloc] initWithFrame:UIScreen.mainScreen.bounds];
    
    LoginVC *vc = LoginVC.alloc.init;
    self.window.rootViewController = vc;
    [self.window makeKeyAndVisible];
    
    return YES;
}




@end
