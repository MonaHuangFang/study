//
//  main.c
//  007-StackWork
//
//  Created by 黄方 on 2020/4/20.
//  Copyright © 2020 黄方. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;
typedef int SElemType; /* SElemType类型根据实际情况而定，这里假设为int */

//顺序栈结构
typedef struct {
    SElemType data[MAXSIZE];
    int top;
}OrderStack;

//构建空栈
Status initStack(OrderStack *s){
    s->top = -1;
    return OK;
}

//清空栈
Status clearStack(OrderStack *s){
    s->top = -1;
    return OK;
}
//判断是否空栈
Status stackIsEmpty(OrderStack s){
    if (s.top == -1) {
        return TRUE;
    }else{
        return FALSE;
    }
}

//返回栈的长度
int stackCount(OrderStack s){
    return s.top + 1;
}

//获取栈顶
Status getTop(OrderStack s, SElemType *e){
    if (s.top == -1) {
        return ERROR;
    }else{
        *e = s.data[s.top];
        return OK;
    }
}

//获取栈底
int getBottom(OrderStack s){
    return s.data[0];
}

//插入元素
Status push(OrderStack *s, SElemType e){
    //栈满
    if (s->top == MAXSIZE - 1) {
        return ERROR;
    }
    
    s->top ++ ;
    s->data[s->top] = e;
    
    return OK;
}

//删除元素
Status pop(OrderStack *s, SElemType *e){
    if (s->top == -1) {
        return ERROR;
    }
    *e = s->data[s->top];
    s->top--;
    return OK;
}

//遍历
void display(OrderStack s){
    printf("栈内元素：");
    for (int i = 0; i<=s.top; i++) {
        printf("%3d",s.data[i]);
    }
    printf("\n");
}

//1、十进制转八进制
void conversion(int n){
    OrderStack s;
    SElemType e;
    initStack(&s);
    while (n) {
        push(&s, n%8);
        n = n/8;
    }
    while (!stackIsEmpty(s)) {
        pop(&s, &e);
        printf("%d",e);
    }
    printf("\n");
}

//2、杨辉三角
int** generate(int rows){
    
    int **res = (int **)malloc(sizeof(int *) * rows);
    for (int i = 0; i<rows; i++) {
        res[i] = (int*)malloc(sizeof(int)*(i+1));
        res[i][0] = 1;
        res[i][i] = 1;
        for (int j = 1; j<i; j++) {
            res[i][j] = res[i-1][j-1]+res[i-1][j];
        }
    }
    return res;
}

//3、爬楼梯问题
/*
 方法一:递归求解法
 找到递归方程式：f(n) = f(n-1) + f(n-2);
 递归边界：f(1) = 1 ; f(2) = 2;
 */
int climbStairs_1(int n){
    if (n<1)
        return 0;
    else if (n==1)
        return 1;
    else if (n==2)
        return 2;
    else
        return climbStairs_1(n-1)+climbStairs_1(n-2);
}

/*
方法二:动态规划法
*/
int climbStairs_2(int n){
    int *sum = (int *)malloc(sizeof(int)*(n+1));
    sum[0] = 0;
    sum[1] = 1;
    sum[2] = 2;
    for (int i = 3; i<=n; i++) {
        sum[i] = sum[i-1]+sum[i-2];
    }
    
    return sum[n];
}

//4、每日温度问题
/*方法一：暴力法*/
int * dailyTemperatures_1(int *T,int size){
    int *result = (int *)malloc(sizeof(int)*size);
    result[size-1] = 0;
    for (int i = 0; i<size-1; i++) {
        if (T[i] == T[i-1]) {
            result[i] = result[i-1]==0?0:result[i-1]-1;
        }else{
            for (int j = i+1; j<size; j++) {
                result[i] = 0;
                if (T[j]>T[i]) {
                    result[i] = j-i;
                    break;
                }
            }
        }
    }
    
    return result;
}

/*方法二：跳跃对比法*/
int * dailyTemperatures_2(int *T,int size){
    int *result = (int *)malloc(sizeof(int)*size);
    result[size-1] = 0;
    for (int i = size-2; i>=0; i--) {
        for (int j = i+1; j<size; j += result[j]) {
            if (T[j]>T[i]) {
                result[i] = j-i;
                break;
            }else {
                if (result[j] == 0){
                    result[i] = 0;
                    break;
                }
            }
        }
    }
    
    return result;
}

/*方法三：栈方法*/
int * dailyTemperatures_3(int *T,int size){
    int *result = (int *)malloc(sizeof(int)*size);
    OrderStack iStack;
    initStack(&iStack);
    
    for (int i = 0; i<size; i++) {
        result[i] = 0;
    }
    clearStack(&iStack);
    for (int i = 0; i<size; i++) {
        push(&iStack, i);
        for (int j = i+1; j<size; j++) {
            if (T[i]<T[j]) {
                result[i] = stackCount(iStack);
                clearStack(&iStack);
                break;
            }else{
                push(&iStack, j);
            }
        }
    }
    clearStack(&iStack);
    return result;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    //进制转换
//    conversion(1348);
    
    //杨辉三角
//    int rows = 8;
//    int **result;
//    result = generate(rows);
//    for (int i = 0; i < rows; i++) {
//        for (int j = 0;  j<=i; j++) {
//            printf(" %d ",result[i][j]);
//        }
//        printf("\n");
//    }
    
    //爬楼梯问题
//    int reslut = 0;
//    reslut = climbStairs_1(20);
//    printf("%d\n",reslut);
//
//    reslut = climbStairs_2(20);
//    printf("%d\n",reslut);
    
    //每日温度问题
//    int test[8]= {73, 74, 75, 71, 69, 72, 76, 73};
//    int test[8]= {73, 74, 75, 75, 69, 72, 76, 73};
    int  test[10]= {73, 74, 75, 71, 69, 78, 76, 73};
    int  *result;
    
//    result = dailyTemperatures_1(test, 8);
//    result = dailyTemperatures_2(test, 8);
    result = dailyTemperatures_3(test, 8);
    
    for (int i = 0; i < 8;i++ ) {
        printf("%d ",test[i]);
    }
    printf("\n");
    
    for (int i = 0; i < 8;i++ ) {
        printf("%d ",result[i]);
    }
    printf("\n");
    
    return 0;
}
