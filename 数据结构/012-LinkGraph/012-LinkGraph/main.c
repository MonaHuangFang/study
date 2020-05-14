//
//  main.c
//  012-LinkGraph
//
//  Created by 黄方 on 2020/5/14.
//  Copyright © 2020 黄方. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define M 100
#define MAXVEX 10 /* 最大顶点数，应由用户定义 */
typedef int Status;    /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef char Element;
typedef int BOOL;

typedef struct{
    char vexs[MAXVEX]; //顶点表
    int arc[MAXVEX][MAXVEX];  //邻接矩阵
    int numNodes, numEdges;
} MGraph;

//邻接表结点
typedef struct Node{
    int adj_vex_index;//顶点的下标
    Element data;
    struct Node *next; //下一个
}EdgeNode;

//顶点表结点
typedef struct vNode{
    Element data;
    EdgeNode *firstEdge;
}VexNode,AdjList[M];

//图的结构
typedef struct Craph{
    AdjList adjList; //顶点表
    int numNodes; //顶点个数
    int numEdges; //边的个数
    BOOL is_directed; //是否有向图
}Graph, *LinkGraph;

//创建邻接表
void createLinkGraph(LinkGraph *G){
    int i, j ,k;
    EdgeNode *p;
    printf("输入顶点数目,边数和有向？：\n");
    scanf("%d,%d,%d",&(*G)->numNodes,&(*G)->numEdges,&(*G)->is_directed);
    
    printf("输入顶点信息：\n");
    for (i = 0; i<(*G)->numNodes; i++) {
        getchar();
        scanf("%c",&(*G)->adjList[i].data);
        (*G)->adjList[i].firstEdge = NULL;
    }
    
    printf("输入边信息：\n");
    for (k = 0; k<(*G)->numEdges; k++) {
        scanf("%d %d",&i,&j);
        //创建一个新的结点
        p = (EdgeNode *)malloc(sizeof(EdgeNode));
        //下标为j
        p->adj_vex_index = j;
        //头插法
        p->next = (*G)->adjList[i].firstEdge;
        (*G)->adjList[i].firstEdge = p;
        
        if (!(*G)->is_directed) {//无向图
            p = (EdgeNode *)malloc(sizeof(EdgeNode));
            p->adj_vex_index = i;
            p->next = (*G)->adjList[j].firstEdge;
            (*G)->adjList[j].firstEdge = p;
        }
    }
}

//打印邻接表
void putGraph(LinkGraph G){
    printf("邻接表中存储信息:\n");
    for (int i = 0; i<G->numNodes; i++) {
        EdgeNode *p = G->adjList[i].firstEdge;
        while (p) {
            printf("%c->%c ",G->adjList[i].data,G->adjList[p->adj_vex_index].data);
            p = p->next;
        }
        printf("\n");
    }
}

//构建一个固定邻接矩阵
void createMGraph(MGraph *G){
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

//通过固定邻接矩阵构建一个固定邻接表
void createLinkGraph2(MGraph G ,LinkGraph *LG){
    
    *LG = (LinkGraph)malloc(sizeof(Graph));
    (*LG)->numNodes = G.numNodes;
    (*LG)->numEdges = G.numEdges;
    
    for (int i = 0; i<G.numNodes; i++) {
        (*LG)->adjList[i].data = G.vexs[i];
        (*LG)->adjList[i].firstEdge = NULL;
    }
    
    EdgeNode *e;
    for (int i = 0; i<G.numNodes; i++) {
        for (int j = 0; j<G.numNodes; j++) {
            if (G.arc[i][j] == 1) {
                e = (EdgeNode *)malloc(sizeof(EdgeNode));
                e->adj_vex_index = j;
                e->next = (*LG)->adjList[i].firstEdge;
                (*LG)->adjList[i].firstEdge = e;
            }
        }
    }
}

BOOL visited[MAXVEX]; //访问标志的数组
void DFS(LinkGraph G, int i){
    EdgeNode *p;
    visited[i] = TRUE;
    //打印某顶点
    printf("%c ",G->adjList[i].data);
    p = G->adjList[i].firstEdge;
    while (p) {
        if (!visited[p->adj_vex_index]) {
            DFS(G, p->adj_vex_index);
        }
        p = p->next;
    }
}

void DFSTraverse(LinkGraph G){
    //初始化visited数组
    for (int i = 0; i<G->numNodes; i++) {
        visited[i] = FALSE;
    }
    
    for (int i = 0; i<G->numNodes; i++) {
        if (!visited[i]) {
            DFS(G, i);
        }
    }
    printf("\n");
}

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

void BFSTraverse(LinkGraph G){
    //创建队列
    Queue Q;
    initQueue(&Q);
    //初始化标志数组
    for (int i = 0; i<G->numNodes; i++) {
        visited[i] = FALSE;
    }
    EdgeNode *p;
    for (int i = 0; i<G->numNodes; i++) {
        if (!visited[i]) {
            visited[i] = TRUE;
            printf("%c ",G->adjList[i].data);
            enterQueue(&Q, i);
            while (!queueIsEmpty(Q)) {
                int e;
                deleteQueue(&Q, &e);
                p = G->adjList[e].firstEdge;
                while (p) {
                    if (!visited[p->adj_vex_index]) {
                        visited[p->adj_vex_index] = TRUE;
                        printf("%c ",G->adjList[p->adj_vex_index].data);
                        enterQueue(&Q, p->adj_vex_index);
                    }
                    p = p->next;
                }
            }
        }
        
    }
    printf("\n");
}

int main(int argc, const char * argv[]) {
    // insert code here...
//    LinkGraph g = (Graph *)malloc(sizeof(Graph));
//    createLinkGraph(&g);
//    putGraph(g);
    MGraph G;
    LinkGraph LG;
    createMGraph(&G);
    createLinkGraph2(G, &LG);
    
    DFSTraverse(LG);
    BFSTraverse(LG);
    
    return 0;
}
