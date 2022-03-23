//
//  AppDelegate.swift
//  YayaSwift
//
//  Created by 黄方 on 2022/3/22.
//

import UIKit

@main
class AppDelegate: UIResponder, UIApplicationDelegate {

    var window: UIWindow?
    var loginVC: LoginVC?

    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
        // Override point for customization after application launch.
        self.window = UIWindow(frame: UIScreen.main.bounds)
        self.loginVC = LoginVC()
        
        let nav = UINavigationController(rootViewController: self.loginVC ?? UIViewController())
        nav.isNavigationBarHidden = true
        
        self.window!.rootViewController = nav
        self.window!.makeKeyAndVisible()
        return true
    }


}

