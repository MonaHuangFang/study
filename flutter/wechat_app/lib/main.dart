import 'package:flutter/material.dart';
import 'package:wechatapp/root_page.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      theme: ThemeData(
        highlightColor: Color.fromRGBO(0, 0, 0, 0),
        splashColor: Color.fromRGBO(0, 0, 0, 0),
        primarySwatch: Colors.yellow,
      ),
      home: RootPage(),
      debugShowCheckedModeBanner: false,
    );
  }
}
