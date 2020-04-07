//
//  main.c
//  003-linkList2
//
//  Created by Mona on 2020/4/6.
//  Copyright © 2020 Mona. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"

#define ERROR 0
#define OK 1

typedef int Status;/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType;/* ElemType类型根据实际情况而定，这里假设为int */

typedef struct Node{
    ElemType data;
    struct Node *prior;
    struct Node *next;
}Node;

typedef struct Node * LinkList;

Status initList(LinkList *L,int value){
    *L = (LinkList)malloc(sizeof(Node));
    if(*L == NULL) return ERROR;
    
    (*L)->next = (*L);
    (*L)->prior = (*L);
    (*L)->data = value;
    return OK;
}

Status insertList(LinkList *L, int i, ElemType data){
    if (*L == NULL) return ERROR;
    if (i<1) return ERROR;
    
    LinkList target = *L;
    int j = 1;
    while (j < i && target->next != *L) {
        target = target->next;
        j++;
    }
    
    if (j>i) return ERROR;
    
    LinkList temp = (LinkList)malloc(sizeof(Node));
    if (temp == NULL) return ERROR;
    
    temp->data = data;
    temp->prior = target;
    temp->next = target->next;
    target->next = temp;
    temp->next->prior = temp;
    if (i == 1) {
        (*L) = temp;
    }
    return OK;
}

Status deleteList(LinkList *L ,int i){
    if (*L == NULL) return ERROR;
    if (i<1) return ERROR;
    
    LinkList temp = (*L);
    if (temp->next == *L) {
        *L = NULL;
        free(*L);
        return OK;
    }
    
    int j = 1;
    while (j < i) {
        temp = temp->next;
        j++;
    }
    
    temp->prior->next = temp->next;
    temp->next->prior = temp->prior;
    
    free(temp);
    
    return OK;
}

void display(LinkList L){
    if (L==NULL) {
        printf("打印的链表为空!\n");
        return;
    }else{
        printf("链表数据为：");
        LinkList temp = L;
        do{
            printf("%5d",temp->data);
            temp = temp->next;
        }while (temp != L);
        printf("\n");
    }
}

int main(int argc, const char * argv[]) {
    LinkList L;
    Status status;
    int index, value;
    
    printf("创建链表首元结点输入数据：");
    scanf("%d",&value);
    status =  initList(&L,value);
    display(L);
    
    printf("请输入插入的位置和数据:");
    scanf("%d %d",&index,&value);
    status = insertList(&L, index, value);
    display(L);

    printf("请输入插入的位置和数据:");
    scanf("%d %d",&index,&value);
    status = insertList(&L, index, value);
    display(L);

    printf("请输入插入的位置和数据:");
    scanf("%d %d",&index,&value);
    status = insertList(&L, index, value);
    display(L);

    printf("请输入插入的位置和数据:");
    scanf("%d %d",&index,&value);
    status = insertList(&L, index, value);
    display(L);
    
    printf("请输入删除的位置:");
    scanf("%d",&index);
    status = deleteList(&L, index);
    display(L);
    
    printf("请输入删除的位置:");
    scanf("%d",&index);
    status = deleteList(&L, index);
    display(L);
    
    return 0;
}
