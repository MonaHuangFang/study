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

//初始化创建首元结点
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
    
    LinkList target;
    if (i==1) {
        //当插入的位置为首元结点时，获取首元结点的前一结点
        target = (*L)->prior;
    }else{
        // 获取插入位置的前一结点
        int j = 1;
        target = *L;
        while (j < i && target->next != *L) {
            target = target->next;
            j++;
        }
        if (j>i) return ERROR;
    }
    
    LinkList temp = (LinkList)malloc(sizeof(Node));
    if (temp == NULL) return ERROR;
    temp->data = data;
    //将插入结点的前驱指向插入位置的前一结点
    temp->prior = target;
    //将插入结点的前后驱指向插入位置的结点
    temp->next = target->next;
    //将插入位置的前一结点的后驱指向插入的结点
    target->next = temp;
    //将插入位置的原结点的前驱指向插入的结点
    temp->next->prior = temp;
    if (i == 1) {
        //当插入的位置为首元结点时，插入的结点变成首元结点
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
    while (j < i&&temp->next != *L) {
        temp = temp->next;
        j++;
    }
    
    if (j<i&&temp->next == *L) {
        //输入的位置超过了链表的长度
        return ERROR;
    }
    if (i==1) {
        //当删除的结点时首元结点时，首元结点的下一个结点将成为新的首元结点
        *L = temp->next;
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
