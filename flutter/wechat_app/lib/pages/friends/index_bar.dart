import 'package:flutter/material.dart';

import '../../const.dart';

class IndexBar extends StatefulWidget {
  void Function(String str) indexBarCallBack;

  IndexBar({this.indexBarCallBack});

  @override
  _IndexBarState createState() => _IndexBarState();
}

class _IndexBarState extends State<IndexBar> {
  Color _bgColor = Color.fromRGBO(0, 0, 0, 0);
  Color _textColor = Colors.black87;

  double _indicatorY = 0.0;
  String _indicatorText = 'A';
  bool _indocatorHidden = true;

  int getIndex(BuildContext context, Offset globalPosition){
    RenderBox box = context.findRenderObject();
    double y = box.globalToLocal(globalPosition).dy;
    //每个字母的高度
    var itemHeight = ScreenHeight(context)/2/INDEX_WORDS.length;
    //第几个字母
    int index = (y ~/ itemHeight).clamp(0, INDEX_WORDS.length - 1);
    return index;
  }

  @override
  Widget build(BuildContext context) {
    List<Widget> words = [];
    for(int i = 0; i<INDEX_WORDS.length; i++){
      words.add(
          Expanded(
            child: Text(INDEX_WORDS[i],style: TextStyle(fontSize: 10,color: _textColor),),
          )
      );
    }
    return Positioned(
      right: 0,
      top: ScreenHeight(context)/8,
      height: ScreenHeight(context)/2,
      width: 70,
      child:Row(
        children: [
          Container(
            width: 50,
            alignment: Alignment(0, _indicatorY),
            child: _indocatorHidden ? null : Container(
              width: 50,
              height: 33,
              alignment: Alignment(-0.1,0),
              decoration: BoxDecoration(
                image: DecorationImage(image: AssetImage('images/气泡.png'),fit: BoxFit.fitHeight),
              ),
              child: Text(_indicatorText,style: TextStyle(color: Colors.white),
              ),
            ),
          ),
          GestureDetector(
            child: Container(
              color: _bgColor,
              child: Column(
                children: words,
              ),
            ),
            onVerticalDragDown: (DragDownDetails details){
              int index = getIndex(context, details.globalPosition);
              widget.indexBarCallBack(INDEX_WORDS[index]);
              setState(() {
                _bgColor = Color.fromRGBO(1, 1, 1, 0.4);
                _textColor = Colors.white;
              });
            },
            onVerticalDragUpdate: (DragUpdateDetails details){
              int index = getIndex(context, details.globalPosition);
              widget.indexBarCallBack(INDEX_WORDS[index]);
              setState(() {
                _indicatorText = INDEX_WORDS[index];
                _indicatorY = 2.12 / 28*index - 1.06;
                _indocatorHidden = false;
              });
            },
            onVerticalDragEnd: (DragEndDetails details){
              setState(() {
                _bgColor = Color.fromRGBO(0, 0, 0, 0);
                _textColor = Colors.black87;
                _indocatorHidden = true;
              });
            },
          )
        ],
      ),
    );
  }
}

const INDEX_WORDS = [
  '🔍',
  '☆',
  'A',
  'B',
  'C',
  'D',
  'E',
  'F',
  'G',
  'H',
  'I',
  'J',
  'K',
  'L',
  'M',
  'N',
  'O',
  'P',
  'Q',
  'R',
  'S',
  'T',
  'U',
  'V',
  'W',
  'X',
  'Y',
  'Z'
];
