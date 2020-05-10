//
//  main.c
//  010-LinkBiTree
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
CElemType Nil='#'; /* 字符型以空格符为空 */
typedef struct BiTNode  /* 结点结构 */
{
    CElemType data;        /* 结点数据 */
    struct BiTNode *lchild,*rchild; /* 左右孩子指针 */
}BiTNode,*LinkBiTree;

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

//二叉树的初始化
Status initBiTree(LinkBiTree *T){
    (*T) = NULL;
    return OK;
}

//销毁二叉树
void destory(LinkBiTree *T){
    if (*T) {
        if ((*T)->lchild) {
            destory(&(*T)->lchild);
        }
        if ((*T)->rchild) {
            destory(&(*T)->rchild);
        }
        
        free(*T);
        (*T) = NULL;
    }
}
#define ClearBiTree DestroyBiTree
//创建二叉树
static int indexs = 1;
static String str;
void createBiTree(LinkBiTree *T){
    CElemType data = str[indexs++];
    if (data == '#') {
        *T = NULL;
    }else{
        *T = (LinkBiTree)malloc(sizeof(BiTNode));
        if (!*T) {
            exit(0);
        }
        (*T)->data = data;//给结点赋值
        createBiTree(&(*T)->lchild);//创建左子树
        createBiTree(&(*T)->rchild);//创建右子树
    }
}

//判断二叉树是否为空
Status biTreeIsEmpty(LinkBiTree T){
    if (T) {
        return TRUE;
    }else{
        return FALSE;
    }
}

//获取二叉树的深度
int getDepthFromBiTree(LinkBiTree T){
    if (!T) {
        return 0;
    }
    int i,j;
    if (T->lchild) {
        i = getDepthFromBiTree(T->lchild);
    }else{
        i = 0;
    }
    if (T->rchild) {
        j = getDepthFromBiTree(T->rchild);
    }else{
        j = 0;
    }
    return i>j?(i+1):(j+1);
}

//根据结点位置获取结点的值
CElemType getValue(LinkBiTree T){
    if (T) {
        return T->data;
    }
    return Nil;
}

//给处于位置e的结点赋值
void setValue(LinkBiTree T, CElemType value){
    T->data = value;
}

//二叉树的遍历

//前序遍历

void preOrderTraverse(LinkBiTree T){
    if (T) {
        printf("%c",T->data);
        preOrderTraverse(T->lchild);
        preOrderTraverse(T->rchild);
    }
}

//中序遍历
void inOrderTraverse(LinkBiTree T){
    if (T) {
        inOrderTraverse(T->lchild);
        printf("%c",T->data);
        inOrderTraverse(T->rchild);
    }
}

// 后序遍历
void postOrderTraverse(LinkBiTree T)
{
    if (T) {
        postOrderTraverse(T->lchild);
        postOrderTraverse(T->rchild);
        printf("%c",T->data);
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    LinkBiTree T;
    CElemType e;
    
    initBiTree(&T);
    
    strAssign(str,"ABDH#K###E##CFI###G#J##");
    
    createBiTree(&T);
    printf("二叉树是否为空%d(1:是 0:否),树的深度=%d\n",biTreeIsEmpty(T),getDepthFromBiTree(T));
    
    e=getValue(T);
    printf("二叉树的根为: %c\n",e);
    
    printf("\n前序遍历二叉树:");
    preOrderTraverse(T);
    
    printf("\n中序遍历二叉树:");
    inOrderTraverse(T);
    
    printf("\n后序遍历二叉树:");
    postOrderTraverse(T);
    return 0;
}
