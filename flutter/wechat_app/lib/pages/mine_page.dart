import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:wechatapp/const.dart';
import 'package:wechatapp/pages/discover/discover_cell.dart';

class MinePage extends StatefulWidget {
  @override
  _MinePageState createState() => _MinePageState();
}

class _MinePageState extends State<MinePage> {
  Widget _headerWidget(){
    return Container(
      color: Colors.white,
      height: 200,
      child: Container(
        margin: EdgeInsets.only(top: 100,bottom: 20),
        padding: EdgeInsets.all(10),
        child: Row(
          crossAxisAlignment: CrossAxisAlignment.center,
          children: [
            //头像
            Container(
              margin: EdgeInsets.only(left: 10),
              height: 50,
              width: 50,
              decoration: BoxDecoration(
                borderRadius: BorderRadius.circular(8),
                image: DecorationImage(image: AssetImage('images/Hank.png'))
              ),
            ),
            Expanded(
              child: Container(
                margin: EdgeInsets.only(left: 10),
                height: 50,
                child: Column(
                  mainAxisAlignment: MainAxisAlignment.spaceAround,
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: [
                    Text('Hank'),
                    Row(
                      mainAxisAlignment: MainAxisAlignment.spaceBetween,
                      children: [
                        Text('微信号:1234',style: TextStyle(color: Colors.grey,fontSize: 13),),
                        Image.asset('images/icon_right.png',width: 15,),
                      ],
                    )
                  ],
                ),
              ),
            )
          ],
        ),
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Stack(
        children: [
          //列表
          Container(
            color: themeColor,
            child: MediaQuery.removePadding(
              removeTop: true,
              context: context,
              child: ListView(
                children: [
                  //头部
                  _headerWidget(),
                  DiscoverCell(
                    icon: 'images/微信 支付.png',
                    title: '支付',
                    hasSection: true,
                  ),
                  DiscoverCell(
                    icon: 'images/微信收藏.png',
                    title: '收藏',
                    hasSection: true,
                    hasBottomLine: true,
                  ),
                  DiscoverCell(
                    icon: 'images/微信相册.png',
                    title: '相册',
                    hasBottomLine: true,
                  ),
                  DiscoverCell(
                    icon: 'images/微信卡包.png',
                    title: '卡包',
                    hasBottomLine: true,
                  ),
                  DiscoverCell(
                    icon: 'images/微信表情.png',
                    title: '表情',
                  ),
                  DiscoverCell(
                    icon: 'images/微信设置.png',
                    title: '设置',
                    hasSection: true,
                  ),
                ],
              ),
            ),
          ),
          //相机
          Positioned(
            top: 40,
            right: 10,
            child: Image.asset(
              "images/相机.png",
              width: 20,
            ),
          )
        ],
      ),
    );
  }
}
