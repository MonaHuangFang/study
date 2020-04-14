//
//  main.c
//  005-LinkStack
//
//  Created by Mona on 2020/4/14.
//  Copyright © 2020 Mona. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef int SElemType; /* SElemType类型根据实际情况而定，这里假设为int */

//链式栈节点
typedef struct StackNode{
    SElemType data;
    struct StackNode *next;
}StackNode, *LinkStackNode;

//链式栈结构
typedef struct {
    LinkStackNode top;
    int count;
}LinkStack;

//构造空栈
Status initStack(LinkStack *s){
    s->top = NULL;
    s->count = 0;
    return OK;
}

//清空栈
Status clearStack(LinkStack *s){
    LinkStackNode p = s->top;
    
    if (p) {
        LinkStackNode q = p;
        p = p->next;
        free(q);
    }
    
    s->count = 0;
    return OK;
}

//判断是否为空栈
Status stackIsEmpty(LinkStack s){
    if (s.count == 0) {
        return TRUE;
    }else{
        return FALSE;
    }
}

//获取栈长度
int stackCount(LinkStack s){
    return s.count;
}

//获取栈顶
Status getTop(LinkStack s, SElemType *e){
    if (s.count == 0) {
        return ERROR;
    }
    *e = s.top->data;
    return OK;
}

//插入元素
Status push(LinkStack *s, SElemType e){
    LinkStackNode temp = (LinkStackNode)malloc(sizeof(StackNode));
    if (temp == NULL) {
        return ERROR;
    }
    temp->data = e;
    temp->next = s->top;
    s->top = temp;
    s->count++;
    return OK;
}

//删除元素
Status pop(LinkStack *s, SElemType *e){
    if (s->count == 0) {
        return ERROR;
    }
    *e = s->top->data;
    LinkStackNode p = s->top;
    s->top = p->next;
    free(p);
    s->count--;
    return OK;
}

//遍历
void display(LinkStack s){
    printf("栈内元素：");
    LinkStackNode p = s.top;
    while (p) {
        printf("%3d",p->data);
        p = p->next;
    }
    printf("\n");
}

int main(int argc, const char * argv[]) {
    // insert code here...
    LinkStack s;
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
