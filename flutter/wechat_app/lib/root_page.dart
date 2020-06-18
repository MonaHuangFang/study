import "package:flutter/material.dart";
import 'package:wechatapp/pages/chat_page.dart';
import 'package:wechatapp/pages/discover.dart';
import 'package:wechatapp/pages/friends_page.dart';
import 'package:wechatapp/pages/mine_page.dart';

class RootPage extends StatefulWidget {
  @override
  _RootPageState createState() => _RootPageState();
}

class _RootPageState extends State<RootPage> {
  int _currentIndex = 0;
  List<Widget> _pages = [ChatPage(),FriendsPage(),DiscoverPage(),MinePage()];

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: _pages[_currentIndex],
      bottomNavigationBar: BottomNavigationBar(
        onTap: (index){
          setState(() {
            _currentIndex = index;
          });
        },
        currentIndex: _currentIndex,
          fixedColor: Colors.green,
          type: BottomNavigationBarType.fixed,
          items: [
            BottomNavigationBarItem(icon: Icon(Icons.chat), title: Text('微信')),
            BottomNavigationBarItem(
                icon: Icon(Icons.bookmark), title: Text('通讯录')),
            BottomNavigationBarItem(
                icon: Icon(Icons.history), title: Text('发现')),
            BottomNavigationBarItem(
                icon: Icon(Icons.person_outline), title: Text('我')),
          ]),
    );
  }
}
