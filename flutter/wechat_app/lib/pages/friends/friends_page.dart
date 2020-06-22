import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:wechatapp/const.dart';
import 'package:wechatapp/pages/discover/discover_detail.dart';
import 'package:wechatapp/pages/friends/index_bar.dart';

import 'friends_data.dart';

class FriendsPage extends StatefulWidget {
  @override
  _FriendsPageState createState() => _FriendsPageState();
}

class _FriendsPageState extends State<FriendsPage> {
  final List<Friends> _listDatas = [];

  ScrollController _scrollController = ScrollController();

  final Map _groupOffsetMap = {
    INDEX_WORDS[0]: 0.0,
    INDEX_WORDS[1]: 0.0,
  };

  @override
  void initState() {
    // TODO: implement initState
    super.initState();

//    _listDatas.addAll(datas);
    _listDatas..addAll(datas)..addAll(datas);

    //排序
    _listDatas.sort((Friends a, Friends b) {
      return a.indexLetter.compareTo(b.indexLetter);
    });

    var _groupOffset = 54.5 * 4;
    //经过循环计算,将每一个头的位置算出来.放入字典!
    for (int i = 0; i < _listDatas.length; i++) {
      if (i>0 && _listDatas[i].indexLetter == _listDatas[i - 1].indexLetter) {
        //此时没有头部,只需要加偏移量就好了!
        _groupOffset += 54.5;
      } else {
        //这部分就是有头部的Cell了!
        _groupOffsetMap.addAll({_listDatas[i].indexLetter: _groupOffset});
        _groupOffset += 84.5;
      }
    }
  }

  final List<Friends> _headerData = [
    Friends(avatar: "images/新的朋友.png", name: "新的朋友"),
    Friends(avatar: "images/群聊.png", name: "群聊"),
    Friends(avatar: "images/标签.png", name: "标签"),
    Friends(avatar: "images/公众号.png", name: "公众号"),
  ];

  Widget _itemFoeRom(BuildContext context, int index) {
    if (index < _headerData.length) {
      return _FriendCell(
        imageAssets: _headerData[index].avatar,
        name: _headerData[index].name,
      );
    } else {
      bool _hideGroup = index - _headerData.length > 0 &&
          _listDatas[index - _headerData.length].indexLetter ==
              _listDatas[index - _headerData.length - 1].indexLetter;

      return _FriendCell(
        avatar: _listDatas[index - _headerData.length].avatar,
        name: _listDatas[index - _headerData.length].name,
        group: _hideGroup
            ? null
            : _listDatas[index - _headerData.length].indexLetter,
      );
    }
  }

  @override
  Widget build(BuildContext context) {

    return Scaffold(
      appBar: AppBar(
        backgroundColor: themeColor,
        title: Text('通讯录'),
        actions: [
          GestureDetector(
            onTap: () {
              Navigator.of(context).push(MaterialPageRoute(
                  builder: (context) => DiscoverDetailPage(
                        title: '添加朋友',
                      )));
            },
            child: Container(
              margin: EdgeInsets.only(right: 10),
              child: Image.asset(
                'images/icon_friends_add.png',
                width: 25,
              ),
            ),
          )
        ],
      ),
      body: Stack(
        children: [
          //列表
          Container(
            child: ListView.builder(
              controller: _scrollController,
              itemCount: _headerData.length + _listDatas.length,
              itemBuilder: _itemFoeRom,
            ),
          ),
          //检索控件
          IndexBar(
            indexBarCallBack: (str){
              print('选中了：$str');
              if(_groupOffsetMap[str] != null){
                _scrollController.animateTo(_groupOffsetMap[str], duration: Duration(microseconds: 1000), curve: Curves.easeIn);
              }
            },
          )
        ],
      ),
    );
  }
}

class _FriendCell extends StatelessWidget {
  final String avatar;
  final String name;
  final String group;
  final String imageAssets;

  const _FriendCell(
      {Key key, this.avatar, this.name, this.group, this.imageAssets})
      : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Column(
      children: [
        group != null
            ? Container(
                alignment: Alignment.centerLeft,
                height: 30,
                color: themeColor,
                padding: EdgeInsets.only(left: 10),
                child: Text(
                  group,
                  style: TextStyle(color: Colors.grey),
                ),
              )
            : Container(),
        Container(
          color: Colors.white,
          child: Row(
            crossAxisAlignment: CrossAxisAlignment.center,
            children: [
              Container(
                margin: EdgeInsets.all(10),
                width: 34,
                height: 34,
                decoration: BoxDecoration(
                  borderRadius: BorderRadius.circular(6),
                  image: DecorationImage(
                      image: imageAssets != null
                          ? AssetImage(imageAssets)
                          : NetworkImage(avatar)),
                ),
              ),
              Text(name)
            ],
          ),
        ),
        Container(
          margin: EdgeInsets.only(left: 50),
          height: 0.5,
          color: themeColor,
        )
      ],
    );
  }
}
