//
//  main.c
//  002-LinkList
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
    struct Node *next;
}Node;

typedef struct Node *LinkList;

Status initList(LinkList *L,ElemType data){
    *L = (LinkList)malloc(sizeof(Node));
    if (*L==NULL) return ERROR;
    
    (*L)->data = data;
    (*L)->next = (*L);
    return OK;
}

Status insertList(LinkList *L, int i, ElemType data){
    if (*L == NULL) return ERROR;
    if (i<1) return ERROR;
    
    LinkList temp = (LinkList)malloc(sizeof(Node));
    if (temp == NULL) return ERROR;
    temp->data = data;
    
    LinkList target;
    if (i == 1) {
        for (target = *L; target->next != *L; target = target->next);
        target->next = temp;
        temp->next = *L;
        *L = temp;
    }else{
        int j;
        for (j = 1, target = *L; target->next != *L && j<i-1; j++,target = target->next);
        temp->next = target->next;
        target->next = temp;
    }
    return OK;
}

Status deleteList(LinkList *L, int i){
    if (*L == NULL)  return ERROR;
    
    if ((*L)->next == *L) {
        *L = NULL;
        free(*L);
        return OK;
    }
    LinkList temp, target;
    if (i == 1) {
        temp = *L;
        for (target = *L; target->next != *L; target = target->next);
        target->next = temp->next;
        *L = target->next;
        free(temp);
    }else{
        int j;
        for (j = 1, target = *L; target->next != *L && j<i-1; j++,target = target->next);
        
        if (target->next == *L) {
            return ERROR;
        }
        temp = target->next;
        target->next = temp->next;
        free(temp);
    }
    return OK;
}

int searchValue(LinkList L, int value){
    LinkList temp = L;
    int i = 1;
    
    while (temp->next != L && temp->data != value) {
        i++;
        temp = temp->next;
    }
    if (temp->next == L && temp->data != value) {
        return -1;
    }
    return i;
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
    // insert code here...
    LinkList L;
    Status status;
    int index, value;
    
    printf("请输入创建链表首元结点的数据：");
    scanf("%d",&value);
    status =  initList(&L, value);

    printf("请输入插入的位置和数据:");
    scanf("%d %d",&index,&value);
    status = insertList(&L, index, value);

    printf("请输入插入的位置和数据:");
    scanf("%d %d",&index,&value);
    status = insertList(&L, index, value);

    printf("请输入插入的位置和数据:");
    scanf("%d %d",&index,&value);
    status = insertList(&L, index, value);

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
