//
//  main.c
//  006-LinkQueue
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

typedef int Status;
typedef int QElemType; /* QElemType类型根据实际情况而定，这里假设为int */

typedef struct QueueNode    /* 结点结构 */
{
    QElemType data;
    struct QueueNode *next;
}QueueNode,*QueuePtr;

typedef struct            /* 队列的链表结构 */
{
    QueuePtr front,rear; /* 队头、队尾指针 */
    int count; //队列长度
}LinkQueue;

//初始化队列
Status initQueue(LinkQueue *q){
    q->front = q->rear = (QueuePtr) malloc(sizeof(QueueNode));
    if (q->front == NULL) {
        return ERROR;
    }
    q->front->next = NULL;
    q->count = 0;
    return OK;
}

//销毁队列
Status destory(LinkQueue *q){
    while (q->front) {
        //q->rear作为一个临时结点
        q->rear = q->front->next;
        free(q->front);
        q->front = q->rear;
    }
    q->count = 0;
    return OK;
}

////清空队列
Status clearQueue(LinkQueue *q){
    QueuePtr p = q->front->next;
    q->rear = q->front;
    q->front->next = NULL;
    q->count = 0;
    while (p) {
        QueuePtr temp = p;
        p=p->next;
        free(temp);
    }
    
    return OK;
}

//判断队列是否为空
Status queueIsEmpty(LinkQueue q){
    if (q.front == q.rear && q.count == 0) {
        return TRUE;
    }else{
        return FALSE;
    }
}

//获取队列长度
int queueLenght(LinkQueue q){
    return q.count;
}

//获取对头
Status getFront(LinkQueue q, QElemType *e){
    if (q.rear == q.front) {
        return ERROR;
    }
    *e = q.front->next->data;
    return OK;
}

//队列插入元素
Status push(LinkQueue *q, QElemType e){
    QueuePtr p = (QueuePtr)malloc(sizeof(QueueNode));
    if (p==NULL) {
        return ERROR;
    }
    p->data = e;
    p->next = NULL;
    
    q->rear->next = p;
    q->rear = p;
    q->count++;
    return OK;
}

//队列删除元素
Status pop(LinkQueue *q, QElemType *e){
    if (q->rear == q->front) {
        printf("此队列为空\n");
        return ERROR;
    }
    QueuePtr p = q->front->next;
    *e = p->data;
    q->front->next = p->next;
    if (p == q->rear) {
        q->rear = q->front;
    }
    free(p);
    q->count--;
    return OK;
}

//遍历
void display(LinkQueue q){
    if (q.front == q.rear) {
        printf("此为空队列！\n");
    }
    
    QueuePtr p = q.front->next;
    while (p) {
        printf("%d   ",p->data);
        p = p->next;
    }
    printf("\n");
}

int main(int argc, const char * argv[]) {
    // insert code here...
    Status j = 0;
     int i=0;
     QElemType d;
     LinkQueue q;
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
