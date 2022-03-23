//
//  loginvc.swift
//  YayaSwift
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
        idLayout?.backgroundColor = rgb(102, 102, 102)
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
        var holderText = "帐号 或 车主号码";
        var placeholder = NSMutableAttributedString(string: holderText)
        placeholder.addAttribute(NSAttributedString.Key.foregroundColor, value: rgba(180, 175, 175, 1), range: NSMakeRange(0, holderText.count))
        self.idField?.attributedPlaceholder = placeholder;
        self.idField?.keyboardType = UIKeyboardType.numberPad;
        idLayout?.addSubview(self.idField ?? UITextField())
        
        let pwdLayout = MyLinearLayout(orientation: MyOrientation_Horz)
        pwdLayout?.myWidth = 240
        pwdLayout?.myHeight = 40
        pwdLayout?.gravity = MyGravity_Vert_Center
        pwdLayout?.backgroundColor = rgba(102, 102, 102, 1)
        pwdLayout?.layer.masksToBounds = true
        pwdLayout?.layer.cornerRadius = 20
        rootLayout?.addSubview(pwdLayout ?? MyLinearLayout())
        
        let pwdImg = UIImageView(image: UIImage(named: "account"))
        pwdImg.mySize = CGSize(width: 24, height: 24)
        pwdImg.myLeft = 8
        pwdLayout?.addSubview(pwdImg)
        
        self.pwdField = UITextField()
        self.pwdField?.myLeft = 8
        self.pwdField?.myVertMargin = 0
        self.pwdField?.weight = 1
        holderText = "密码";
        placeholder = NSMutableAttributedString(string: holderText)
        placeholder.addAttribute(NSAttributedString.Key.foregroundColor, value: rgba(180, 175,175, 1), range: NSMakeRange(0, holderText.count))
        self.pwdField?.attributedPlaceholder = placeholder;
        pwdLayout?.addSubview(self.pwdField ?? UITextField())
        
        let LoginItem = UIButton()
        LoginItem.mySize = CGSize(width: 260, height: 70);
        LoginItem.titleLabel?.font = UIFont.systemFont(ofSize: 18)
        LoginItem.setTitle("登录", for: UIControl.State.normal)
        LoginItem.setBackgroundImage(UIImage(named: "login_btn"), for: UIControl.State.normal)
        LoginItem.addTarget(self, action: #selector(loginItemPress(_:)), for: UIControl.Event.touchUpInside)
        rootLayout?.addSubview(LoginItem)
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
    @objc func loginItemPress(_ sender : UIButton){
        
    }
}
