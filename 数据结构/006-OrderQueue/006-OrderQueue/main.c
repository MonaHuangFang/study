//
//  main.c
//  006-OrderQueue 顺序队列表示与操作实现
//
//  Created by 黄方 on 2020/4/19.
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
typedef int QElemType; /* QElemType类型根据实际情况而定，这里假设为int */

//循环队列的顺序存储结构
typedef struct{
    QElemType data[MAXSIZE];
    int front;
    int rear;
}OrderQueue;

//初始化队列
Status initQueue(OrderQueue *q){
    q->front = 0;
    q->rear = 0;
    return OK;
}

//清空队列
Status clearQueue(OrderQueue *q){
    q->front = q->rear = 0;
    return OK;
}

//判断队列是否为空
Status queueIsEmpty(OrderQueue q){
    if (q.front == q.rear) {
        return TRUE;
    }else{
        return FALSE;
    }
}

//获取队列长度
int queueLenght(OrderQueue q){
    return (q.rear+MAXSIZE - q.front)%MAXSIZE;
}

//获取对头
Status getFront(OrderQueue q, QElemType *e){
    if (q.rear == q.front) {
        return ERROR;
    }
    *e = q.data[q.front];
    return OK;
}

//队列插入元素
Status push(OrderQueue *q, QElemType e){
    if ((q->rear+1)%MAXSIZE == q->front) {
        printf("此队列已满\n");
        return ERROR;
    }
    
    q->data[q->rear] = e;
    q->rear = (q->rear + 1) %MAXSIZE;
    return OK;
}

//队列删除元素
Status pop(OrderQueue *q, QElemType *e){
    if (q->rear == q->front) {
        printf("此队列为空\n");
        return ERROR;
    }
    *e = q->data[q->front];
    q->front = (q->front + 1) %MAXSIZE;
    return OK;
}

//遍历
void display(OrderQueue q){
    if (q.front == q.rear) {
        printf("此为空队列！\n");
    }
    
    int i;
    i = q.front;
    while (i != q.rear) {
        printf("%d   ",q.data[i]);
        i = (i + 1)%MAXSIZE;
    }
    printf("\n");
}

int main(int argc, const char * argv[]) {
    // insert code here...
     Status j = 0;
     int i=0;
     QElemType d;
     OrderQueue q;
     initQueue(&q);
     printf("初始化队列后，队列空否？%u(1:空 0:否)\n",queueIsEmpty(q));
     
     printf("入队:\n");
     while (i < 10) {
         push(&q, i);
         i++;
     }
     display(q);
     printf("队列长度为: %d\n",queueLenght(q));
     printf("现在队列空否？%u(1:空 0:否)\n",queueIsEmpty(q));
     printf("出队:\n");
    
    //出队
     pop(&q, &d);
     printf("出队的元素:%d\n",d);
     display(q);
     printf("队列长度为: %d\n",queueLenght(q));

     //获取队头
     j=getFront(q,&d);
     if(j)
         printf("现在队头元素为: %d\n",d);
     clearQueue(&q);
     printf("清空队列后, 队列空否？%u(1:空 0:否)\n",queueIsEmpty(q));
    return 0;
}
