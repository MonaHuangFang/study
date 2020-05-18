//
//  main.c
//  013-MSTree
//
//  Created by 黄方 on 2020/5/17.
//  Copyright © 2020 黄方. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"

#define MAXVEX 20 /* 最大顶点数，应由用户定义 */
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define INFINITYC 65535

typedef struct{
    int arc[MAXVEX][MAXVEX];  //邻接矩阵
    int numNodes, numEdges;
} MGraph;

//构建一个固定邻接矩阵
void createMGraph(MGraph *G){
    //确定图的顶点数和边数
    G->numNodes = 9;
    G->numEdges = 15;
    
    //初始化图的边数
    for (int i = 0; i<G->numNodes; i++) {
        for (int j = 0; j<G->numNodes; j++) {
            if (i == j) {
                G->arc[i][j] = 0;
            }else{
                G->arc[i][j] = INFINITYC;
            }
            
        }
    }
    
    //输入图的连接信息
    G->arc[0][1]=10;
    G->arc[0][5]=11;
    G->arc[1][2]=18;
    G->arc[1][8]=12;
    G->arc[1][6]=16;
    G->arc[2][8]=8;
    G->arc[2][3]=22;
    G->arc[3][8]=21;
    G->arc[3][6]=24;
    G->arc[3][7]=16;
    G->arc[3][4]=20;
    G->arc[4][7]=7;
    G->arc[4][5]=26;
    G->arc[5][6]=17;
    G->arc[6][7]=19;
    
    //无向图是对称矩阵
    for (int i = 0; i<G->numNodes; i++) {
        for (int j = i; j<G->numNodes; j++) {
            G->arc[j][i] = G->arc[i][j];
        }
    }
}

//Prim算法
void MiniSpanTree_Prim(MGraph G){
    int min;
    int sum = 0;
    
    int adjvex[MAXVEX];//保存相关顶点下标，如顶点0和顶点相连，则adjvex[1] = 0;
    int lowcost[MAXVEX];//保存相关顶点的权值
    
    //当v0加入生成树，adjvex和lowcost数组的值初始化
    for (int i = 0; i<G.numNodes; i++) {
        lowcost[i] = G.arc[0][i];
        adjvex[i] = 0;
    }
    
    //循环除0以外的全部顶点，找到lowcost数组中最小的顶点k
    for (int i = 1; i<G.numNodes; i++) {
        min = INFINITYC;
        int j = 1;
        int k = 0;
        while (j<G.numNodes) {
            if (lowcost[j] != 0 && lowcost[j]<min) {
                min = lowcost[j];
                k = j;
            }
            j++;
        }
        printf("v%d - v%d = %d\n",adjvex[k],k,G.arc[adjvex[k]][k]);
        sum += G.arc[adjvex[k]][k];
        lowcost[k] = 0; //顶点k已加入生成树
        
        //更新lowcost数组和adjvex数组
        for (j = 1; j<G.numNodes; j++) {
            if (lowcost[j] != 0 && G.arc[k][j]<lowcost[j]) {
                lowcost[j] = G.arc[k][j];
                adjvex[j] = k;
            }
        }
    }
    printf("sum = %d\n",sum);
}

/* 边表数组Edge结构的定义 */
typedef struct
{
    int begin;
    int end;
    int weight;
}Edge;

/* 根据权值进行排序 */
void sort(Edge edges[],MGraph G)
{
    //对权值进行排序(从小到大)
    int i, j;
    Edge temp;
    for ( i = 0; i < G.numEdges; i++)
    {
        for ( j = i + 1; j < G.numEdges; j++)
        {
            if (edges[i].weight > edges[j].weight)
            {
                temp = edges[i];
                edges[i] = edges[j];
                edges[j] = temp;
            }
        }
    }
    
    printf("边集数组根据权值排序之后的为:\n");
    for (i = 0; i < G.numEdges; i++)
    {
        printf("v%d - v%d = %d\n", edges[i].begin, edges[i].end, edges[i].weight);
    }
}

//根据顶点f以及parent数组,可以找到当前顶点的尾部下标; 帮助我们判断2点之间是否存在闭环问题;
int Find(int *parent, int f)
{
    while ( parent[f] > 0)
    {
        f = parent[f];
    }
    return f;
}

//kruskal算法
void MiniSpanTree_Kruskal(MGraph G){
    int sum = 0;
    /* 定义一数组用来判断边与边是否形成环路,用来记录顶点间的连接关系. 通过它来防止最小生成树产生闭环;*/
    int parent[MAXVEX];
    //边表数组
    Edge edges[MAXVEX];
    int k = 0;
    //根据邻接矩阵生成边表数组
    for (int i = 0; i<G.numNodes; i++) {
        for (int j = i+1; j<G.numNodes; j++) {
            if (G.arc[i][j]<INFINITYC) {
                edges[k].begin = i;
                edges[k].end = j;
                edges[k].weight = G.arc[i][j];
                k++;
            }
        }
    }
    
    //将边表数组排序
    sort(edges, G);
    
    //初始化parent 值为0
    for (int i = 0; i<MAXVEX; i++) {
        parent[i] = 0;
    }
    int n,m;
    for (int i = 0; i<G.numEdges; i++) {
        n = Find(parent, edges[i].begin);
        m = Find(parent, edges[i].end);
        if (n != m) {
            parent[n] = m; //更新parent数组
            //非闭环情况下，且根据权值从小到大的排序边表数组，此时的边i是没有加入到生成树的最小边
            sum  += edges[i].weight; //边i加入的生成树
        }
    }
    printf("sum = %d\n",sum);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    MGraph G;
    createMGraph(&G);
//    MiniSpanTree_Prim(G);
    MiniSpanTree_Kruskal(G);
    return 0;
}
