//
//  main.c
//  012-MGraph
//
//  Created by 黄方 on 2020/5/14.
//  Copyright © 2020 黄方. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"

#define MAXVEX 10 /* 最大顶点数，应由用户定义 */
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;    /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int BOOL; /* BOOL是布尔类型,其值是TRUE或FALSE */
typedef char VertexType; /* 顶点类型应由用户定义  */
typedef int EdgeType; /* 边上的权值类型应由用户定义 */

typedef struct{
    VertexType vexs[MAXVEX]; //顶点表
    EdgeType arc[MAXVEX][MAXVEX];  //邻接矩阵
    int numNodes, numEdges;
} MGraph;

//输入构建邻接矩阵
void createMGraph(MGraph *G){
    int i,j,k,w;
    printf("输入顶点数和边数：\n");
    scanf("%d,%d",&G->numNodes,&G->numEdges);
    printf("顶点数:%d,边数:%d\n",G->numNodes,G->numEdges);
    //输入顶点信息
    printf("输入顶点信息：\n");
    for (i = 0; i < G->numNodes; i++) {
        getchar();
        scanf("%c",&G->vexs[i]);
    }
    //初始化邻接矩阵
    for (i = 0 ; i < G->numNodes; i++) {
        for (j = 0; j < G->numNodes; j++) {
            G->arc[i][j] = 0;
        }
    }
    
    //输入边表信息
    for (k = 0; k < G->numEdges; k++) {
        printf("输入顶点i到顶点j的边的权值\n");
        scanf("%d,%d,%d",&i,&j,&w);
        
        G->arc[i][j] = w;
        G->arc[j][i] = G->arc[i][j];
    }
    //打印邻接矩阵
    for (i = 0; i < G->numNodes; i++) {
        printf("\n");
        for (j = 0; j < G->numNodes; j++) {
            printf("%d ",G->arc[i][j]);
        }
    }
    printf("\n");
}
//构建一个固定邻接矩阵
void createMGraph2(MGraph *G){
    //确定图的顶点数和边数
    G->numNodes = 9;
    G->numEdges = 15;
    
    //读入顶点的值
    G->vexs[0] = 'A';
    G->vexs[1] = 'B';
    G->vexs[2] = 'C';
    G->vexs[3] = 'D';
    G->vexs[4] = 'E';
    G->vexs[5] = 'F';
    G->vexs[6] = 'G';
    G->vexs[7] = 'H';
    G->vexs[8] = 'I';
    
    //初始化图的边数
    for (int i = 0; i<G->numNodes; i++) {
        for (int j = 0; j<G->numNodes; j++) {
            G->arc[i][j] = 0;
        }
    }
    
    //输入图的连接信息
    G->arc[0][1]=1;
    G->arc[0][5]=1;
    
    G->arc[1][2]=1;
    G->arc[1][8]=1;
    G->arc[1][6]=1;
    
    G->arc[2][3]=1;
    G->arc[2][8]=1;
    
    G->arc[3][4]=1;
    G->arc[3][7]=1;
    G->arc[3][6]=1;
    G->arc[3][8]=1;
    
    G->arc[4][5]=1;
    G->arc[4][7]=1;
    
    G->arc[5][6]=1;
    
    G->arc[6][7]=1;
    
    //无向图是对称矩阵
    for (int i = 0; i<G->numNodes; i++) {
        for (int j = i; j<G->numNodes; j++) {
            G->arc[j][i] = G->arc[i][j];
        }
    }
}

//DFS遍历
BOOL visited[MAXVEX]; //访问标志的数组

void DFS(MGraph G, int i){
    visited[i] = TRUE;
    printf("%c ",G.vexs[i]);
    for (int j = 0; j<G.numNodes; j++) {
        if (G.arc[i][j] == 1 && !visited[j]) {
            DFS(G, j);
        }
    }
}

void DFSTravese(MGraph G){
    //初始化visited数组
    for (int i = 0; i<G.numNodes; i++) {
        visited[i] = FALSE;
    }
    //从某个顶点开始遍历
    for (int i = 0; i<G.numNodes; i++) {
        if (!visited[i]) {
            DFS(G, i);
        }
    }
    printf("\n");
}

//广度优先遍历需要用到的队列结构与相关功能函数

#define MAXSIZE 10 /* 存储空间初始分配量 */

/* 循环队列的顺序存储结构 */
typedef struct
{
    int data[MAXSIZE];
    int front;        /* 头指针 */
    int rear;        /* 尾指针，若队列不空，指向队列尾元素的下一个位置 */
}Queue;

//初始化队列
Status initQueue(Queue *Q){
    Q->front = 0;
    Q->rear = 0;
    return OK;
}

//判断队列是否为空
Status queueIsEmpty(Queue Q){
    if (Q.front == Q.rear) {
        return TRUE;
    }else{
        return FALSE;
    }
}

//入队
Status enterQueue(Queue *Q, int e){
    if ((Q->rear+1)%MAXSIZE == Q->front) {
        return ERROR;
    }
    Q->data[Q->rear] = e;
    Q->rear = (Q->rear+1)%MAXSIZE;
    return OK;
}

//出队
Status deleteQueue(Queue *Q, int *e){
    if (queueIsEmpty(*Q)) {
        return ERROR;
    }
    *e = Q->data[Q->front];
    Q->front = (Q->front + 1)%MAXSIZE;
    return OK;
}

void BFSTraverse(MGraph G){
    //创建队列
    Queue Q;
    initQueue(&Q);
    //初始化标志数组
    for (int i = 0; i<G.numNodes; i++) {
        visited[i] = FALSE;
    }
    for (int i = 0; i<G.numNodes; i++) {
        if (!visited[i]) {
            visited[i] = TRUE;
            printf("%c ",G.vexs[i]);
            enterQueue(&Q, i);
            while (!queueIsEmpty(Q)) {
                int e;
                deleteQueue(&Q, &e);
                for (int j = 0; j<G.numNodes; j++) {
                    if (G.arc[e][j] == 1 && !visited[j]) {
                        visited[j] = TRUE;
                        printf("%c ",G.vexs[j]);
                        enterQueue(&Q, j);
                    }
                }
            }
        }
        
    }
    printf("\n");
}

int main(int argc, const char * argv[]) {
    // insert code here...
    MGraph G;
    createMGraph2(&G);
    DFSTravese(G);
    BFSTraverse(G);
    printf("\n");
    return 0;
}
