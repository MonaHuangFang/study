//
//  common.swift
//  YayaTest
//
//  Created by 黄方 on 2022/3/22.
//

import Foundation
import UIKit

let kScreenWidth = UIScreen.main.bounds.width

let rgba = {(r: CGFloat, g: CGFloat, b: CGFloat, a: CGFloat) -> UIColor in
    return UIColor(red: r / 255.0, green: g / 255.0, blue: b / 255.0, alpha: a)
}

let rgb = {(r: CGFloat, g: CGFloat, b: CGFloat) -> UIColor in
    return UIColor(red: r / 255.0, green: g / 255.0, blue: b / 255.0, alpha: 1)
}

class PublicDataCache {
    static var shareInstance : PublicDataCache {
        struct Static {
            static let instance : PublicDataCache = PublicDataCache()
        }
        return Static.instance
    }
    
    var isLogin : Bool {
        didSet{
            UserDefaults.standard.set(self.isLogin, forKey: "isLogin")
        }
    }
    
    private init(){
        let userDefault = UserDefaults.standard
        self.isLogin = userDefault.bool(forKey: "isLogin")
    }
    
}
