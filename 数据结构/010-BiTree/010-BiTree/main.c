//
//  main.c
//  010-BiTree
//
//  Created by 黄方 on 2020/4/26.
//  Copyright © 2020 黄方. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"
#include "math.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAX_TREE_SIZE 100 /* 二叉树的最大结点数 */

typedef int Status;        /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int CElemType;      /* 树结点的数据类型，目前暂定为整型 */

typedef CElemType OrderBiTree[MAX_TREE_SIZE];
CElemType Nil = 0;

typedef struct {
    int level; //结点层
    int order; //本层的序号(按照满二叉树给定序号规则)
} NodePosition;

//构造空二叉树
Status initBiTree(OrderBiTree T){
    for (int i = 0; i<MAX_TREE_SIZE; i++) {
        T[i] = Nil;
    }
    return OK;
}

//按层序次序依次给二叉树结点赋值
Status creatBiTree(OrderBiTree T){
    int maxNode = 10;
    for (int i = 0; i<MAX_TREE_SIZE; i++) {
        if (i<maxNode) {
            T[i] = i+1;
            if (i!=0 && T[i]!=Nil && T[(i+1)/2-1] == Nil) {
                return ERROR;
            }
        }else{
            T[i] = Nil;
        }
    }
    
    return OK;
}

//由于清空二叉树与初始化二叉树是一致的
#define clearBiTree initBiTree


//判断二叉树是否为空
Status biTreeIsEmpty(OrderBiTree T){
    if (T[0] == Nil) {
        return TRUE;
    }else{
        return FALSE;
    }
}

//获取二叉树的深度
int getDepthFromBiTree(OrderBiTree T){
    int i;
    //获取二叉树T的最后一个结点的序列号
    for (i = MAX_TREE_SIZE-1; i>=0; i--) {
        if (T[i] != Nil) {
            break;
        }
    }
    //根据二叉树性质：深度为K的二叉树最多有2^k-1 个结点
    int j = -1;
    do {
        j++;
    } while (pow(2, j)<=i);
    
    return j;
}

//根据结点位置获取结点的值
CElemType getValueWithPosition(OrderBiTree T, NodePosition p){
    //p.level层第一个结点的序列号，根结点序列号从1开始
    int index = pow(2, p.level-1);
    
    //p.level层p.order位置结点的序列号
    index = index+p.level-1;
    return T[index-1];
}

//给处于位置e的结点赋值
Status setValueToPosition(OrderBiTree T, NodePosition e, CElemType value){
    int i = pow(2, e.level-1) + e.level-2;
    if (value== Nil || T[(i+1)/2-1] == Nil) {
        return ERROR;
    }
    T[i] = value;
    return OK;
}

//获取某结点的双亲结点
CElemType parentNode(OrderBiTree T, CElemType e){
    if (T[0] == Nil) {
        return Nil;
    }
    for (int i=0; i<MAX_TREE_SIZE; i++) {
        if (i != 0 &&T[i] == e) {
            return T[(i+1)/2-1];
        }
    }
    
    return Nil;
}

//获取某结点的左子结点
CElemType leftChildNode(OrderBiTree T,CElemType e){
    if (T[0] == Nil) {
        return Nil;
    }
    for (int i=0; i<MAX_TREE_SIZE-1; i++) {
        if (T[i] == e) {
            return T[(i+1)*2+1];
        }
    }
    
    return Nil;
}

//获取某结点的右子结点
CElemType rightChildNode(OrderBiTree T,CElemType e){
    if (T[0] == Nil) {
        return Nil;
    }
    for (int i=0; i<MAX_TREE_SIZE; i++) {
        if (T[i] == e) {
            return T[(i+1)*2+2];
        }
    }
    
    return Nil;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
