//
//  main.c
//  011-ThreadBiTree
//
//  Created by 黄方 on 2020/5/10.
//  Copyright © 2020 黄方. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include "math.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

/* 存储空间初始分配量 */
#define MAXSIZE 100
/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int Status;
typedef char CElemType;

typedef enum{
    Link = 0, //左孩子或右孩子
    Thread    //前驱或后继
}PointerTag;

typedef struct ThrBiTNode  /* 结点结构 */
{
    CElemType data;        /* 结点数据 */
    struct ThrBiTNode *lchild,*rchild; /* 左右孩子指针 */
    PointerTag lTag,rTag;
}ThrBiTNode,*ThreadBiTree;

//将字符串存入到数组T中
typedef char String[24]; /*  0号单元存放串的长度 */
Status strAssign(String s,char *chars)
{
    int i;
    if(strlen(chars)>MAXSIZE)
        return ERROR;
    else
    {
        s[0]=strlen(chars);
        for(i=1;i<=s[0];i++)
            s[i]=*(chars+i-1);
        return OK;
    }
}

//创建二叉树
static int indexs = 1;
static String str;
void createBiTree(ThreadBiTree *T){
    CElemType data = str[indexs++];
    if (data == '#') {
        *T = NULL;
    }else{
        *T = (ThreadBiTree)malloc(sizeof(ThrBiTNode));
        if (!*T) {
            exit(0);
        }
        (*T)->data = data;//给结点赋值
        createBiTree(&(*T)->lchild);//创建左子树
        if ((*T)->lchild) {
            (*T)->lTag = Link;
        }
        createBiTree(&(*T)->rchild);//创建右子树
        if ((*T)->rchild) {
            (*T)->rTag = Link;
        }
    }
}

ThreadBiTree pre; /* 全局变量,始终指向刚刚访问过的结点 */

//中序遍历将某结点线索化
void inThreading(ThreadBiTree p){
    if (p) {
        //递归左子树线索化
        inThreading(p->lchild);
        
        if (!p->lchild) { //无左孩子
            p->lTag = Thread; //前驱线索
            p->lchild = pre;  //左孩子指针指向前驱
        }
        
        if (!pre->rchild) { //前驱没有右孩子
            pre->rchild = p; //后继线索
            pre->rTag = Thread; //前驱右孩子指针指向后继(当前结点p)
        }
        pre = p; //pre赋值
        //递归右子树线索化
        inThreading(p->rchild);
    }
}

//中序遍历二叉树T,将其中序线索化,thead为头结点
Status inOrderThreading(ThreadBiTree *thead , ThreadBiTree T){
    //创建头结点
    *thead = (ThreadBiTree)malloc(sizeof(ThrBiTNode));
    if (!*thead) {
        return ERROR;
    }
    (*thead)->lTag = Link;
    (*thead)->rTag = Thread;
    (*thead)->rchild = (*thead);
    if (!T) {
        return ERROR;
    }else{
        (*thead)->lchild = T;
        pre = (*thead);
        inThreading(T);
        
        pre->rchild = *thead;//最后一个结点的右孩子线索化
        pre->rTag = Thread;
        
        (*thead)->rchild = pre;//头结点rchild指向最后一个结点
    }
    
    return OK;
}

//打印
Status visit(CElemType e)
{
    printf("%c ",e);
    return OK;
}

//中序遍历线索二叉树
void inOrderTraverse(ThreadBiTree T){
    ThreadBiTree p = T->lchild; //p为根结点
    while (p!=T) {
        //遍历左子树
        while (p->lTag == Link) {
            p=p->lchild;
        }
        visit(p->data);
        while (p->rTag == Thread && p->rchild != T) {
            p=p->rchild;
            visit(p->data);
        }
        p = p->rchild;
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    ThreadBiTree H,T;
    
    //StrAssign(str,"ABDH#K###E##CFI###G#J##");
    strAssign(str,"ABDH##I##EJ###CF##G##");
    
    createBiTree(&T); /* 按前序产生二叉树 */
    inOrderThreading(&H,T); /* 中序遍历,并中序线索化二叉树 */
    inOrderTraverse(H);
    printf("\n");
    return 0;
}
