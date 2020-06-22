import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:wechatapp/const.dart';

class ChatPage extends StatefulWidget {
  @override
  _ChatPageState createState() => _ChatPageState();
}

class _ChatPageState extends State<ChatPage> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('微信'),
        backgroundColor: themeColor,
        actions: [
          GestureDetector(
            child: Container(
              margin: EdgeInsets.only(right: 10),
              child: PopupMenuButton(
                offset: Offset(0,60),
                child: Image.asset('images/圆加.png',width: 25,),
                itemBuilder: (BuildContext context){
                  return <PopupMenuItem<String>>[
                    PopupMenuItem(child: Text("发起群聊"),),
                    PopupMenuItem(child: Text("发起群聊"),),
                  ];
                },
              ),
            ),
            onTap: (){

            },
          )
        ],
      ),
      body: Center(
        child: Text('微信页面'),
      ),
    );
  }
}
