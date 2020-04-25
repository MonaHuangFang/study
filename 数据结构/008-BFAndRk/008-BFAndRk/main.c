//
//  main.c
//  008-BFAndRk
//
//  Created by 黄方 on 2020/4/25.
//  Copyright © 2020 黄方. All rights reserved.
//

#include <stdio.h>
#include "string.h"
#include "stdlib.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 40    /* 存储空间初始分配量 */
#define d 26 //进制
typedef int Status;   /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef char String[MAXSIZE + 1];

//生成一个S[0]为字符串长度的字符串S
Status strAssign(String S,char *c){
    
    if (strlen(c)>MAXSIZE) {
        return ERROR;
    }else{
        S[0] = strlen(c);
        for (int i = 1; i<=S[0]; i++) {
            S[i] = c[i-1];
        }
    }
    return OK;
}

//打印字符串S
void stringPrint(String S){
    for (int i = 1; i<=S[0]; i++) {
        printf("%c",S[i]);
    }
    printf("\n");
}

/*
1. BF算法-爆发匹配算法
思路:
1. 分别利用计数指针i和j指示主串S和模式T中当前正待比较的字符位置,i初值为1,j的初值为1;
2. 如果2个串均为比较到串尾,即i和j均小于等于S和T的长度时, 则循环执行以下的操作:
* S[i]和T[j]比较,若相等,则i 和 j分别指示串中下一个位置,继续比较后续的字符;
* 若不相等,指针后退重新开始匹配. 从主串的下一个字符串(i = i - j + 2)起再重新和模式第一个字符(j = 1)比较;
3. 如果j > T.length, 说明模式T中的每个字符串依次和主串S找中的一个连续字符序列相等,则匹配成功,返回和模式T中第一个字符的字符在主串S中的序号(i-T.length);否则匹配失败,返回0;
*/

int index_BF(String S, String T){
    //i为主串下标
    int i = 1;
    //j为子串下标
    int j = 1;
    
    while (i<=S[0]&&j<=T[0]) {
        if (S[i] == T[j]) {
            //比较两个字母相等时，比较下一个字母
            i++;
            j++;
        }else{
            //不想等时，从主串开始比较的字符的下一个字母重新开始比较，j赋值为1
            i = i - j +2;
            j = 1;
        }
    }
    //当子串全部遍历完成，则匹配成功
    if(j>T[0]){
        return i-T[0];
    }
    return -1;
}

/*
2. RK算法-字符串匹配
思路:用哈希值相等来比较,设计哈希公式：(T[i]-'a')*d^(T.length-i),i从1开始
 1.算出子串的哈希值，比较i位置的主串上与子串长度相等的字母的哈希值，
 2.当哈希值不相等的时候，计算下i+1位置的值等于i位置的值减去最高位的值再乘以进制，再加上i+T.length位置的值
 3.当相等时，再进行二次字母匹配
*/

int index_RK(String S, String T){
    //A T的哈希值
    unsigned int A = 0;
    //St S中与T长度相等的字符的哈希值
    unsigned int St = 0;
    
    //获取A和St的哈希值
    for (int i = 1; i<=T[0]; i++) {
        A = (A * d) + T[i] -'a';
        St = (St *d) + S[i] - 'a';
    }
    int hValue = getMaxValue(T[0]);
    for (int i = 1; i<=S[0] - T[0] +1; i++) {
        if (A == St) {
            if (isMatch(S, i, T)) {
                return i;
            }
        }else{
            St = (St - (S[i] - 'a')*hValue)*d + S[i+T[0]]-'a';
        }
    }
    
    return -1;
}

//算出d进制下的最高位
int getMaxValue(int m){
    int h = 1;
    for (int i = 0; i<m-1; i++) {
        h = h * d;
    }
    return h;
}

//二次字母匹配
Status isMatch(String S, int i, String T){
    for (int j = i; j<=T[0]; j++) {
        if(S[j] != T[j-i+1])
            return FALSE;
    }
    return TRUE;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    int i;
    String s1,s2;
    
    strAssign(s1, "abcdex");
    printf("s1子串为");
    stringPrint(s1);
    
    
    strAssign(s2, "dex");
    printf("s2子串为");
    stringPrint(s2);
    
    i = index_RK(s1, s2);
    printf("i = %d\n",i);
    return 0;
}
