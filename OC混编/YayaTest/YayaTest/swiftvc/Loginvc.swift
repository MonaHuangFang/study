//
//  Loginvc.swift
//  YayaTest
//
//  Created by 黄方 on 2022/3/22.
//

import UIKit
import MyLayout

class LoginVC : UIViewController{
    var idField : UITextField?
    var pwdField : UITextField?
    
    override func loadView() {
        super.loadView()
        let rootLayout = MyLinearLayout(orientation: MyOrientation_Vert)
        rootLayout?.myMargin = 0
        rootLayout?.backgroundImage = UIImage(named: "all_bg")
        rootLayout?.subviewVSpace = 20
        rootLayout?.gravity = MyGravity_Horz_Center
        self.view.addSubview(rootLayout ?? MyLinearLayout())
        
        let topLayout = MyRelativeLayout()
        topLayout.myHorzMargin = 0
        topLayout.myHeight = kScreenWidth * 193 / 320
        rootLayout?.addSubview(topLayout)
        
        let iconImg = UIImageView(image: UIImage(named: "login_logo"))
        iconImg.myHorzMargin = 5
        iconImg.myBottom = 20
        iconImg.myHeight = (kScreenWidth-10)*10/31
        topLayout.addSubview(iconImg)
        
        let idLayout = MyLinearLayout(orientation: MyOrientation_Horz)
        idLayout?.myWidth = 240
        idLayout?.myHeight = 40
        idLayout?.gravity = MyGravity_Vert_Center
        idLayout?.backgroundColor = rgba(r: 102, g: 102, b: 102, a: 1)
        idLayout?.layer.masksToBounds = true
        idLayout?.layer.cornerRadius = 20
        rootLayout?.addSubview(idLayout ?? MyLinearLayout())
        
        let idImg = UIImageView(image: UIImage(named: "account"))
        idImg.mySize = CGSize(width: 24, height: 24)
        idImg.myLeft = 8
        idLayout?.addSubview(idImg)
        
        self.idField = UITextField()
        self.idField?.myLeft = 8
        self.idField?.myVertMargin = 0
        self.idField?.weight = 1
        self.idField?.placeholder = "帐号 或 车主号码"
        idLayout?.addSubview(self.idField ?? UITextField())
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
    }
}
