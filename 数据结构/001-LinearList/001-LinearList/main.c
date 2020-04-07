//
//  main.c
//  001-LinearList
//
//  Created by Mona on 2020/4/4.
//  Copyright © 2020 Mona. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"

#define MAXSIZE 100
#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;

typedef struct {
    ElemType *data;
    int length;
}LinerList;

Status initList(LinerList *L){
    L->data = malloc(sizeof(MAXSIZE));
    if (L->data == NULL) {
        return ERROR;
    }
    L->length = 0;
    return OK;
}

Status insertList(LinerList *L,int i,ElemType value){
    if (L->data==NULL) return ERROR;
    
    if (i<1||i>L->length+1) return ERROR;
    
    if (L->length == MAXSIZE) return ERROR;
    
    for (int j=L->length-1; j>=i; j--) {
        L->data[j] = L->data[j-1];
    }
    L->data[i-1] = value;
    
    L->length++;
    
    return OK;
}

Status deleteData(LinerList *L, int i){
    if (L->data==NULL || L->length==0) return ERROR;
    
    if (i<1 || i>L->length) return ERROR;
    
    for (int j = i-1; j<L->length; j++) {
        L->data[j] = L->data[j+1];
    }
    
    L->length--;
    
    return OK;
}

int searchItem(LinerList L, ElemType value){
    if (L.data==NULL || L.length==0) {
        return -1;
    }
    for (int i = 0; i<L.length; i++) {
        if (L.data[i] == value) {
            return i+1;
        }
    }
    return -1;
}

Status clearList(LinerList *L){
    L->length = 0;
    free(L->data);
    return OK;
}

void display(LinerList L){
    if (L.length == 0) {
        return;
    }
    printf("线性表数据：");
    for (int i = 0; i<L.length; i++) {
        printf("%d\t\t",L.data[i]);
    }
    printf("\n");
}

int main(int argc, const char * argv[]) {
    LinerList L;
    Status status;
    int index,value;
    ElemType e;
    
    status = initList(&L);
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
    
    printf("插入数据,打印链表:\n");
    display(L);
    
    printf("请输入删除的位置:");
    scanf("%d",&index);
    status = deleteData(&L, index);
    
    printf("删除数据,打印链表:\n");
    display(L);
    
    printf("请输入查找的数据:");
    scanf("%d", &e);
    index = searchItem(L, e);
    printf("\n%d的位置是：%d\n",e,index);
    
    
    return 0;
}
