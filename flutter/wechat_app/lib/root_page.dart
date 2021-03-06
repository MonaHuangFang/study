import "package:flutter/material.dart";
import 'package:wechatapp/pages/chat_page.dart';
import 'package:wechatapp/pages/discover/discover.dart';
import 'package:wechatapp/pages/friends/friends_page.dart';
import 'package:wechatapp/pages/mine_page.dart';

class RootPage extends StatefulWidget {
  @override
  _RootPageState createState() => _RootPageState();
}

class _RootPageState extends State<RootPage> {
  int _currentIndex = 0;
  List<Widget> _pages = [ChatPage(), FriendsPage(), DiscoverPage(), MinePage()];

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: _pages[_currentIndex],
      bottomNavigationBar: BottomNavigationBar(
          onTap: (index) {
            setState(() {
              _currentIndex = index;
            });
          },
          selectedFontSize: 12.0,
          currentIndex: _currentIndex,
          fixedColor: Colors.green,
          type: BottomNavigationBarType.fixed,
          items: [
            BottomNavigationBarItem(
              icon: Image.asset('images/tabbar_chat.png',width: 20, height: 20,),
              activeIcon: Image.asset('images/tabbar_chat_hl.png',width: 20, height: 20,),
              title: Text('微信'),
            ),
            BottomNavigationBarItem(
              icon: Image.asset('images/tabbar_friends.png',width: 20, height: 20,),
              activeIcon: Image.asset('images/tabbar_friends_hl.png',width: 20, height: 20,),
              title: Text('通讯录'),
            ),
            BottomNavigationBarItem(
              icon: Image.asset('images/tabbar_discover.png',width: 20, height: 20,),
              activeIcon: Image.asset('images/tabbar_discover_hl.png',width: 20, height: 20,),
              title: Text('发现'),
            ),
            BottomNavigationBarItem(
              icon: Image.asset('images/tabbar_mine.png',width: 20, height: 20,),
              activeIcon: Image.asset('images/tabbar_mine_hl.png',width: 20, height: 20,),
              title: Text('我'),
            ),
          ]),
    );
  }
}
