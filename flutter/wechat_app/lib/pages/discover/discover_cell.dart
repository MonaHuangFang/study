import 'package:flutter/material.dart';
import 'package:wechatapp/pages/discover/discover_detail.dart';

class DiscoverCell extends StatefulWidget {
  final String icon;
  final String title;
  final String subTitle;
  final String subImage;
  final bool hasBottomLine; //底部是否有线
  final bool hasSection; //头部section

  const DiscoverCell({Key key, this.icon, this.title, this.subTitle, this.subImage, this.hasBottomLine = false, this.hasSection = false}) : super(key: key);

  @override
  _DiscoverCellState createState() => _DiscoverCellState();
}

class _DiscoverCellState extends State<DiscoverCell> {
  Color _currentColor = Colors.white;


  @override
  Widget build(BuildContext context) {
    return GestureDetector(
        onTap: (){

          Navigator.of(context).push(MaterialPageRoute(
              builder: (BuildContext context) => DiscoverDetailPage(title: widget.title,)
          ));
          setState(() {
            _currentColor = Colors.white;
          });
        },
        onTapDown: (TapDownDetails details){
          setState(() {
            _currentColor = Colors.grey;
          });
        },
        onTapCancel: (){
          setState(() {
            _currentColor = Colors.white;
          });
        },
        child: Column(
          children: [
            widget.hasSection ? SizedBox(height: 10,):Container(),
            Container(
              height: 54,
              color: _currentColor,
              padding: EdgeInsets.all(10),
              child: Row(
                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                crossAxisAlignment: CrossAxisAlignment.center,
                children: [
                  Row(
                    children: [
                      Image(image: AssetImage(widget.icon),width: 20,),
                      SizedBox(width: 15,),
                      Text(widget.title),
                    ],
                  ),
                  Row(
                    children: [
                      widget.subTitle != null ? Text('${widget.subTitle}  ') : Container(),
                      widget.subImage != null ? Image.asset(widget.subImage,width: 12,) :Container(),
                      SizedBox(width: 5),
                      Image.asset('images/icon_right.png',width: 15,)
                    ],
                  )
                ],
              ),
            ),
            widget.hasBottomLine ? Row(
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

