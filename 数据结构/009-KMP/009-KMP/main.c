//
//  main.c
//  009-KMP
//
//  Created by 黄方 on 2020/4/25.
//  Copyright © 2020 黄方. All rights reserved.
//

#include <stdio.h>
#include "string.h"
#include "stdlib.h"

#define OK 1
#define ERROR 0

#define MAXSIZE 40    /* 存储空间初始分配量 */
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

//返回串的元素个数
int strLength(String S)
{
    return S[0];
}

//获取子串的next数组
void getNext(String S, int *next){
    if (S[0]==0 || S == NULL) {
        return;
    }
    next[1] = 0;
    int j = 1;
    int i = 0;
    while (j<S[0]) {
        if (i == 0|| S[i] == S[j]) {
            i++;
            j++;
            next[j] = i;
        }else{
            i = next[i];
        }
    }
}

//获取子串的next优化数组
void getNext2(String S, int *next){
    if (S[0]==0 || S == NULL) {
        return;
    }
    next[1] = 0;
    int j = 1;
    int i = 0;
    while (j<S[0]) {
        if (i == 0|| S[i] == S[j]) {
            i++;
            j++;
            if (S[j] == S[i]) {
                next[j] = next[i];
            }else{
                next[j] = i;
            }
        }else{
            i = next[i];
        }
    }
}

//输出Next数组值
void nextPrint(int next[],int length)
{
    int i;
    for(i=1;i<=length;i++)
        printf("%d",next[i]);
    printf("\n");
}

//KMP匹配算法
int index_KMP(String S, String T){
    int i = 1;
    int j = 1;
    int next[T[0]+1];
    //getNext(T, next);
    getNext2(T, next);
    while (i<=S[0] && j<=T[0]) {
        if (j==0||S[i]==T[j]) {
            i++;
            j++;
        }else{
            j = next[j];
        }
    }
    
    if (j > T[0]) {
        return i-T[0];
    }else{
        return -1;
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    int i,*p;
    String s1,s2;
    int Status;
    
    /*关于next数组的求解*/
    strAssign(s1,"aaaaax");
    printf("子串为: ");
    stringPrint(s1);
    i=strLength(s1);
    p=(int*)malloc((i+1)*sizeof(int));
    getNext(s1,p);
    printf("Next为: ");
    nextPrint(p,strLength(s1));
    printf("\n");
    
    //KMP算法调用
    strAssign(s1,"abcababca");
    printf("主串为: ");
    stringPrint(s1);
    strAssign(s2,"abab");
    printf("子串为: ");
    stringPrint(s2);
    Status = index_KMP(s1,s2);
    printf("主串和子串在第%d个字符处首次匹配（KMP算法）[返回位置为负数表示没有匹配] \n",Status);
    return 0;
}
