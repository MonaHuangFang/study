//
//  main.c
//  005-Stack
//
//  Created by Huangf on 2020/4/13.
//  Copyright © 2020 Huangf. All rights reserved.
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

int main(int argc, const char * argv[]) {
    // insert code here...
    OrderStack s;
    int e;
    if (initStack(&s) == OK) {
        for (int i = 1; i<10; i++) {
            push(&s, i);
        }
    }
    printf("顺序栈中元素为:\n");
    display(s);
    
    pop(&s, &e);
    printf("弹出栈顶元素为: %d\n",e);
    display(s);
    printf("是否为空栈:%d\n",stackIsEmpty(s));
    getTop(s, &e);
    printf("栈顶元素:%d \n栈长度:%d\n",e,stackCount(s));
    clearStack(&s);
    printf("是否已经清空栈 %d, 栈长度为:%d\n",stackIsEmpty(s),stackCount(s));
    return 0;
}
