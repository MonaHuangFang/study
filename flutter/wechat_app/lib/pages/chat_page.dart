import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:wechatapp/const.dart';
import 'package:http/http.dart' as http;
import 'dart:convert';

class ChatPage extends StatefulWidget {
  @override
  _ChatPageState createState() => _ChatPageState();
}

class _ChatPageState extends State<ChatPage> {
  
  
  Widget _buildPopMenuItem(String image, String title) {
    return Row(
      children: [
        Image.asset(
          image,
          width: 20,
        ),
        SizedBox(
          width: 20,
        ),
        Text(
          title,
          style: TextStyle(color: Colors.white),
        )
      ],
    );
  }
  
  @override
  void initState() {
    // TODO: implement initState
    super.initState();

//    getDatas();
  }
  
  Future <List<ChatModel>> getDatas() async {
    final response = await http.get('http://rap2.taobao.org:38080/app/mock/258722/api/chat/list');
    if(response.statusCode == 200){
      final responseBody = json.decode(response.body);
      List<ChatModel> chatList = responseBody['datas'].map<ChatModel>((item){
        return ChatModel.fromJson(item);
      }).toList();
      return chatList;
    }else{
      throw Exception('statusCode:${response.statusCode}');
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('微信'),
        backgroundColor: themeColor,
        actions: [
          //右上角按钮
          Container(
            margin: EdgeInsets.only(right: 10),
            child: PopupMenuButton(
              offset: Offset(0, 60),
              child: Image.asset(
                'images/圆加.png',
                width: 25,
              ),
              itemBuilder: (BuildContext context) {
                return <PopupMenuItem<String>>[
                  PopupMenuItem(
                    child: _buildPopMenuItem('images/发起群聊.png', '发起群聊'),
                  ),
                  PopupMenuItem(
                    child: _buildPopMenuItem('images/添加朋友.png', '添加朋友'),
                  ),
                  PopupMenuItem(
                    child: _buildPopMenuItem('images/扫一扫1.png', '扫一扫'),
                  ),
                  PopupMenuItem(
                    child: _buildPopMenuItem('images/收付款.png', '收付款'),
                  ),
                ];
              },
            ),
          )
        ],
      ),
      body: Container(
        child: FutureBuilder(
          future: getDatas(),
          builder: (BuildContext context, AsyncSnapshot snapshot){
            if(snapshot.connectionState == ConnectionState.waiting){
              return Text('加载中。。。');
            }
            return ListView(
              children: snapshot.data.map<Widget>((ChatModel item){
                return ListTile(
                  title: Text(item.name),
                  subtitle: Container(
                    height: 20,
                    child: Text(item.message,overflow: TextOverflow.ellipsis,),
                  ),
                  leading: CircleAvatar(
                    backgroundImage: NetworkImage(item.avatar),
                  ),
                );
              }).toList(),
            );
          },
        ),
      ),
    );
  }
}

class ChatModel {
  final String name;
  final String message;
  final String avatar;

  ChatModel({this.avatar, this.name, this.message});

  factory ChatModel.fromJson(Map json){
    return ChatModel(
      name: json['name'],
      message: json['message'],
      avatar: json['avatar']
    );
  }
}
