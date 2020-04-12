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

算法思想:循环La和Lb链表，将Lb中的节点依次取出插入到La中，返回La

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

/*
作业2:
题目:
已知两个链表A和B分别表示两个集合.其元素递增排列. 设计一个算法,用于求出A与B的交集,并存储在A链表中;
例如:
La = {2,4,6,8}; Lb = {4,6,8,10};
Lc = {4,6,8}

关键词:依次摘取2个表中相等的元素重新进行链接,删除其他不等的元素;

算法思想:循环La和Lb链表，将La中节点值不存在Lb中的节点删除，返回La

*/

LinkList intersection(LinkList *La, LinkList *Lb){
    if ((*La) == NULL || (*La)->next == NULL || (*Lb) == NULL || (*Lb)->next==NULL) {
        return NULL;
    }
    
    LinkList Pa = (*La);
    LinkList Pb = (*Lb)->next;
    while (Pa->next!=NULL && Pb!=NULL) {
        LinkList temp;
        if (Pa->next->data>Pb->data) {
            //当Pa的下一个节点的值大于Pb的值时，Pb往后移
            Pb = Pb->next;
        }else if (Pa->next->data<Pb->data){
            //当Pa的下一个节点的值小于Pb的值时，删除Pa的下一个节点，将Pa的next指向下一个节点的节点
            temp = Pa->next;
            Pa->next = temp->next;
            free(temp);
        }else{
            //当Pa的下一个节点的值等于Pb的值时，留下Pa，Pa往后移，Pb往后移
            Pa = Pa->next;
            Pb = Pb->next;
        }
    }
    //当La的长度超出Lb时，将超出的那部分删掉
    if (Pb==NULL && Pa->next != NULL) {
        Pa->next = NULL;
    }
    //释放Lb
    free(*Lb);
    return *La;
}

/*
作业3:
题目:
设计一个算法,将链表中所有节点的链接方向"原地旋转",即要求仅仅利用原表的存储空间. 换句话说,要求算法空间复杂度为O(1);
例如:L={0,2,4,6,8,10}, 逆转后: L = {10,8,6,4,2,0};

关键词:不能开辟新的空间,只能改变指针的指向; 可以考虑逐个摘取结点,利用前插法创建链表的思想,将结点一次插入到头结点的后面; 因为先插入的结点为表尾,后插入的结点为表头,即可实现链表的逆转;

算法思想:
 利用原有的头结点*L,p为工作指针, 初始时p指向首元结点. 因为摘取的结点依次向前插入;
*/

LinkList reversal(LinkList *L){
    if (*L == NULL && (*L)->next==NULL) {
        return ERROR;
    }
    
    LinkList p = (*L)->next;
    (*L)->next = NULL;
    
    while (p!=NULL) {
        LinkList temp = p->next;
        p->next = (*L)->next;
        (*L)->next = p;
        p = temp;
    }
    
    return *L;
}


/*
作业4:
题目:
设计一个算法,删除递增有序链表中值大于等于mink且小于等于maxk(mink,maxk是给定的两个参数,其值可以和表中的元素相同,也可以不同)的所有元素;

算法思想:循环遍历*L,p为工作指针,当p的值大于等于mink且小于等于maxk时，删除p
*/

void deleteMinMax(LinkList *L, int min, int max)
{
    if (*L == NULL || (*L)->next == NULL) {
        return;
    }
    LinkList p = *L;
    while (p->next!=NULL) {
        LinkList temp = p->next;
        if (temp->data>=min && temp->data<=max) {
            p->next = temp->next;
            free(temp);
        }else{
            p = temp;
        }
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    Status iStatus;
    LinkList La,Lb;
    iStatus = initList(&La);
    iStatus = initList(&Lb);
    
    //    ---------作业1--------
//    for(int j = 1;j<=4;j++)
//    {
//        iStatus = insertList(&La, j, j);
//    }
//    printf("La:");
//    display(La);
//
//    for(int j = 2,i = 1;j<8;j+=2,i++)
//    {
//        iStatus = insertList(&Lb, i, j);
//    }
//    printf("Lb:");
//    display(Lb);
//
//    La = mergeList(&La, &Lb);
//    display(La);
    
    // ---------作业2--------
//    for(int j = 2,i = 1;j<=8;j+=2,i++)
//    {
//        iStatus = insertList(&La, i, j);
//    }
//    printf("La:");
//    display(La);
//
//    for(int j = 4,i = 1;j<=10;j+=2,i++)
//    {
//        iStatus = insertList(&Lb, i, j);
//    }
//    printf("Lb:");
//    display(Lb);
//    La = intersection(&La, &Lb);
//    display(La);
    
    // ---------作业3--------
//
//    for(int j = 0,i = 1;j<=10;j+=2,i++)
//    {
//        iStatus = insertList(&La, i, j);
//    }
//    printf("La:");
//    display(La);
//
//    La = reversal(&La);
//    printf("La:");
//    display(La);
    
    // ---------作业4--------
    for(int j = 1;j<=10;j++)
    {
        iStatus = insertList(&La, j, j);
    }
    printf("La:");
    display(La);
    
    deleteMinMax(&La, 4, 8);
    printf("La:");
    display(La);
    
    return 0;
}
