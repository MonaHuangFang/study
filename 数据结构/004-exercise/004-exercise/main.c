//
//  main.c
//  004-exercise
//
//  Created by Mona on 2020/4/11.
//  Copyright © 2020 Mona. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"

#define ERROR 0
#define OK 1

typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int Elemtype; /* ElemType类型根据实际情况而定，这里假设为int */

typedef struct Node{
    Elemtype data;
    struct Node *next;
}Node;

typedef struct Node *LinkList;

Status initList(LinkList *L){
    //链表头节点开辟空间
    *L = (LinkList)malloc(sizeof(Node));
    if (*L == NULL) {
        return ERROR;
    }
    //将头节点next指向NULL
    (*L)->next = NULL;
    return OK;
}

Status insertList(LinkList *L, int i, Elemtype data){
    if (*L == NULL) {
        return ERROR;
    }
    LinkList p = (*L);
    int j = 1;
    
    while (j<i && p!=NULL) {
        p = p->next;
        j++;
    }
    if (p==NULL) {
        return ERROR;
    }
    LinkList temp = (LinkList)malloc(sizeof(Node));
    temp->data = data;
    temp->next = p->next;
    p->next = temp;
    return OK;
}

void display(LinkList L){
    if (L == NULL || L->next == NULL) {
        return;
    }
    LinkList p = L->next;
    while (p!=NULL) {
        printf("%5d",p->data);
        p = p->next;
    }
    printf("\n");
}

/*

作业1:
题目:
将2个递增的有序链表合并为一个有序链表; 要求结果链表仍然使用两个链表的存储空间,不另外占用其他的存储空间. 表中不允许有重复的数据

关键词:递增有序链表,不允许有重复数据,保留递增关系(后插法)
     不占用额外的存储空间指的是不能开辟新节点,赋值在链接到链表上;

算法思想:
(1)假设待合并的链表为La和Lb,将Lb中的节点依次取出插入到La中. Pa 和 Pb 分别是La,Lb的工作指针.初始化为相应链表的首元结点
(2)从首元结点开始比较, 当两个链表La 和Lb 均未到达表尾结点时,比较Pa->next和Pb,取较小值放入到Pa->next位置.
(3)如果两个表中的元素相等,删除Lb表中的元素,这样确保合并后表中无重复的元素;
(4)当La到表尾结点为空时,Lb还未到表尾,将Lb后的所有节点都移到La表后,释放链表Lb的头结点,返回La;

*/

LinkList mergeList(LinkList *La, LinkList *Lb){
    if (La == NULL || Lb == NULL || (*Lb)->next==NULL) {
        return NULL;
    }
    
    LinkList Pa = (*La);
    LinkList Pb = (*Lb)->next;
    while (Pb != NULL&& Pa->next != NULL) {
        if (Pa->next->data>Pb->data) {
            //将Pb从Lb链表中移出
            (*Lb)->next = Pb->next;
            //将Pb的next指向Pa的next
            Pb->next = Pa->next;
            Pa->next = Pb;
            Pa = Pb;
            Pb = (*Lb)->next;
        }else if (Pa->next->data<Pb->data){
            Pa = Pa->next;
        }else if (Pa->next->data==Pb->data){
            Pa = Pa->next;
    
            LinkList temp = Pb;
            //将Pb从Lb链表中移出
            (*Lb)->next = Pb->next;
            Pb = (*Lb)->next;
            free(temp);
        }
    }
    
    if (Pa->next == NULL&&Pb!=NULL) {
        Pa->next = Pb;
    }
    free(*Lb);
    return *La;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    Status iStatus;
    LinkList La,Lb;
    iStatus = initList(&La);
    iStatus = initList(&Lb);
    
    //    ---------作业1--------
    for(int j = 1;j<=3;j++)
    {
        iStatus = insertList(&La, j, j);
    }
    printf("La:");
    display(La);

    for(int j = 3,i = 1;j<10;j+=3,i++)
    {
        iStatus = insertList(&Lb, i, j);
    }
    printf("Lb:");
    display(Lb);
    
    La = mergeList(&La, &Lb);
    display(La);
    
    return 0;
}
