import 'package:flutter/material.dart';
import 'package:wechatapp/pages/discover/discover_detail.dart';

class DiscoverCell extends StatelessWidget {
  final String icon;
  final String title;
  final String subTitle;
  final String subImage;
  final bool hasBottomLine; //底部是否有线
  final bool hasSection; //头部section

  const DiscoverCell({Key key, this.icon, this.title, this.subTitle, this.subImage, this.hasBottomLine = false, this.hasSection = false}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return GestureDetector(
      onTap: (){
        Navigator.of(context).push(MaterialPageRoute(
          builder: (BuildContext context) => DiscoverDetailPage(title: title,)
        ));

      },
      child: Column(
        children: [
          hasSection ? SizedBox(height: 10,):Container(),
          Container(
            height: 54,
            color: Colors.white,
            padding: EdgeInsets.all(10),
            child: Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              crossAxisAlignment: CrossAxisAlignment.center,
              children: [
                Row(
                  children: [
                    Image(image: AssetImage(icon),width: 20,),
                    SizedBox(width: 15,),
                    Text(title),
                  ],
                ),
                Row(
                  children: [
                    subTitle != null ? Text('$subTitle  ') : Container(),
                    subImage != null ? Image.asset(subImage,width: 12,) :Container(),
                    SizedBox(width: 5),
                    Image.asset('images/icon_right.png',width: 15,)
                  ],
                )
              ],
            ),
          ),
          hasBottomLine ? Row(
            children: [
              Container(
                width: 40,
                height: 0.5,
                color: Colors.white,
              ),
              Container(
                height: 0.5,
                color: Colors.grey,
              )
            ],
          ) : Container(),
        ],
      )
    );
  }
}
