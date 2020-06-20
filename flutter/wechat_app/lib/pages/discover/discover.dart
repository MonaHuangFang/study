import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:wechatapp/pages/discover/discover_cell.dart';

class DiscoverPage extends StatefulWidget {
  @override
  _DiscoverPageState createState() => _DiscoverPageState();
}

class _DiscoverPageState extends State<DiscoverPage> {
  Color _themeColor = Color.fromRGBO(220, 220, 220, 1);

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        backgroundColor: _themeColor,
        centerTitle: true, //专门为了安卓使用的属性
        title: Text('发现'),
        elevation: 0.0, //底部边栏
      ),
      body: Container(
        color: _themeColor,
        height: 800,
        child: ListView(
          children: [
            DiscoverCell(
              icon: 'images/朋友圈.png',
              title: '朋友圈',
            ),
            DiscoverCell(
              icon: 'images/扫一扫2.png',
              title: '扫一扫',
              hasSection: true,
              hasBottomLine: true,
            ),
            DiscoverCell(
              icon: 'images/摇一摇.png',
              title: '摇一摇',
            ),
            DiscoverCell(
              icon: 'images/看一看icon.png',
              title: '看一看',
              hasSection: true,
              hasBottomLine: true,
            ),
            DiscoverCell(
              icon: 'images/搜一搜 2.png',
              title: '搜一搜',
            ),
            DiscoverCell(
              icon: 'images/附近的人icon.png',
              title: '附近的人',
              hasSection: true,
            ),
            DiscoverCell(
              icon: 'images/购物.png',
              title: '购物',
              subTitle: '618限时特价',
              subImage: 'images/badge.png',
              hasSection: true,
              hasBottomLine: true,
            ),
            DiscoverCell(
              icon: 'images/游戏.png',
              title: '游戏',
            ),
            DiscoverCell(
              icon: 'images/小程序.png',
              title: '小程序',
              hasSection: true,
            ),
          ],
        ),
      ),
    );
  }
}
