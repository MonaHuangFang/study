//
//  common.swift
//  YayaTest
//
//  Created by 黄方 on 2022/3/22.
//

import Foundation
import UIKit

let kScreenWidth = UIScreen.main.bounds.width

func rgba(r: CGFloat, g: CGFloat, b: CGFloat, a: CGFloat) -> UIColor{
    return UIColor(red: r / 255.0, green: g / 255.0, blue: b / 255.0, alpha: a)
}
