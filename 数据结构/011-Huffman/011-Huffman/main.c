//
//  main.c
//  011-Huffman
//
//  Created by 黄方 on 2020/5/10.
//  Copyright © 2020 黄方. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"

const int MaxValue = 10000;//初始设定的权值最大值
const int MaxBit = 8;//初始设定的最大编码位数

//设定哈夫曼树为顺序存储
//哈夫曼树的结点结构
typedef struct HuffNode{
    int weight;       //权值
    int flag;         //标记是否已加入到树中 0为没加入，1为已加入
    int parent;       //该结点的双亲结点的下标
    int leftChild;    //该结点的左孩子结点的下标
    int rightChild;   //该结点的右孩子结点的下标
}HuffNode;

typedef struct Code//存放哈夫曼编码的数据元素结构
{
    int bit[MaxBit];//数组
    int start;  //编码的起始下标
    int weight;//字符的权值
}Code;

//构建哈夫曼树
void huffmanTree(int weight[], int n, HuffNode *h){
    //有n个叶子结点的树共有2*n-1个结点
    for (int i = 0; i<2*n-1; i++) {
        if (i<n) {
            h[i].weight = weight[i];
        }else{
            h[i].weight = 0;
        }
        h[i].parent = 0;
        h[i].flag = 0;
        h[i].leftChild = -1;
        h[i].rightChild = -1;
    }
    int m1,m2,x1,x2;
    for (int i = 0; i<n-1; i++) {
        m1 = MaxValue;  //存储权值最小的值
        m2 = MaxValue;  //存储权值第二小的值
        x1 = 0;   //存储权值最小的值的下标
        x2 = 0;   //存储权值第二小的值的下标
        for (int j = 0; j<n+i; j++) {
            if (h[j].weight<m1 && h[j].flag == 0) {
                m2 = m1;
                x2 = x1;
                m1 = h[j].weight;
                x1 = j;
            }else if (h[j].weight<m2 && h[j].flag == 0){
                m2 = h[j].weight;
                x2 = j;
            }
        }
        h[x1].parent = n+i;
        h[x2].parent = n+i;
        h[x1].flag = 1;
        h[x2].flag = 1;
        
        h[n+i].leftChild = x1;
        h[n+i].rightChild = x2;
        h[n+i].weight = m1+m2;
    }
}

void huffmanCode(HuffNode h[], int n, Code c[]){
    //创建一个结构为Code的结点
    Code *cd = (Code *)malloc(sizeof(Code));
    int child, parent;
    
    //求n个叶子结点的哈夫曼编码
    for (int i = 0; i<n; i++) {
        cd->start = 0;   //从0开始计数
        cd->weight = h[i].weight;  //获取结点的权值
        child = i;
        parent = h[i].parent;
        
        //由叶结点向上到根结点
        while (parent != 0) {
            if (h[parent].leftChild == child) {
                cd->bit[cd->start] = 0;//该结点为左孩子编码为0
            }else{
                cd->bit[cd->start] = 1;//该结点为右孩子编码为1
            }
            cd->start++;
            child = parent;
            parent = h[child].parent;
        }
        //将编码值反转
        for (int j = cd->start - 1; j>=0; j--) {
            int k = cd->start - 1- j;
            c[i].bit[k] = cd->bit[j];
        }
        c[i].weight = cd->weight;
        c[i].start = cd->start;
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    int i, j, n = 4, m = 0;
    
    //权值
    int weight[] = {2,4,5,7};
    
    //初始化哈夫曼树, 哈夫曼编码
    HuffNode *myHaffTree = malloc(sizeof(HuffNode)*2*n-1);
    Code *myHaffCode = malloc(sizeof(Code)*n);
    
    //1. 构建哈夫曼树
    huffmanTree(weight, n, myHaffTree);
    //2.根据哈夫曼树得到哈夫曼编码
    huffmanCode(myHaffTree, n, myHaffCode);
    //3.
    for (i = 0; i<n; i++)
    {
        printf("Weight = %d\n",myHaffCode[i].weight);
        for (j = 0; j<myHaffCode[i].start; j++)
            printf("%d",myHaffCode[i].bit[j]);
        m = m + myHaffCode[i].weight*myHaffCode[i].start;
         printf("\n");
    }
    printf("Huffman's WPS is:%d\n",m);
    return 0;
}
