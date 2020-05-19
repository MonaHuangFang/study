//
//  main.c
//  014-ShortestPath
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

/*用于存储最短路径下标的数组*/
typedef int Patharc[MAXVEX];
/*用于存储到各点最短路径权值的和*/
typedef int ShortPathTable[MAXVEX];

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
    
    G->arc[0][1]=1;
    G->arc[0][2]=5;
    G->arc[1][2]=3;
    G->arc[1][3]=7;
    G->arc[1][4]=5;
    
    G->arc[2][4]=1;
    G->arc[2][5]=7;
    G->arc[3][4]=2;
    G->arc[3][6]=3;
    G->arc[4][5]=3;
    
    G->arc[4][6]=6;
    G->arc[4][7]=9;
    G->arc[5][7]=5;
    G->arc[6][7]=2;
    G->arc[6][8]=7;
    
    G->arc[7][8]=4;
    
    //无向图是对称矩阵
    for (int i = 0; i<G->numNodes; i++) {
        for (int j = i; j<G->numNodes; j++) {
            G->arc[j][i] = G->arc[i][j];
        }
    }
}

//求网图中两点间的最短距离
//Dijkstra 算法
/*
G: 网图;
v0: V0开始的顶点;
p[v]: 前驱顶点下标;
d[v]: 表示从V0到V的最短路径长度和;
*/
void ShortestPath_Dijkstra(MGraph G, int v0, Patharc *p, ShortPathTable *d){
    int min, k = 0;
    int final[MAXVEX]; //final[w] = 1 表示求得顶点V0~Vw的最短路径
    
    //初始化数据
    for (int i = 0; i<G.numNodes; i++) {
        final[i] = 0;
        (*d)[i] = G.arc[v0][i];
        (*p)[i] = v0;
        if(i == v0){
            final[i] = 1;
            (*p)[i] = -1;
        }
    }
    
    //主循环，求的v0到某个顶点的最短路径
    for (int i = 0; i<G.numNodes; i++) {
        min = INFINITYC;
        
        for (int j = 0; j<G.numNodes; j++) {
            if (final[j] == 0 && (*d)[j] < min) {
                k = j;
                min = (*d)[j];
            }
        }
        
        final[k] = 1;
        
        for (int j = 0; j<G.numNodes; j++) {
            if (final[j] == 0 && (min + G.arc[k][j])<(*d)[j]) {
                (*d)[j] = min + G.arc[k][j];
                (*p)[j] = k;
            }
        }
    }
}

typedef int Floyd_Patharc[MAXVEX][MAXVEX];
typedef int Floyd_ShortPathTable[MAXVEX][MAXVEX];

//Floyd算法，求网图G中各顶点v到其余顶点w的最短路径P[v][w]及带权长度D[v][w]。
//Patharc 和 ShortPathTable 都是二维数组;
void ShortestPath_Floyd(MGraph G, Floyd_Patharc *p, Floyd_ShortPathTable *d){
    //初始化d和p矩阵
    for (int i = 0; i<G.numNodes; i++) {
        for (int j = 0; j< G.numNodes; j++) {
            (*d)[i][j] = G.arc[i][j];
            (*p)[i][j] = j;
        }
    }
    //k表示经过的中转顶点
    for (int k = 0; k<G.numNodes; k++) {
        for (int i = 0; i<G.numNodes; i++) {
            for (int j = 0; j< G.numNodes; j++) {
                if ((*d)[i][j] > (*d)[i][k] + (*d)[k][j]) {
                    (*d)[i][j] = (*d)[i][k] + (*d)[k][j];
                    (*p)[i][j] = (*p)[i][k];
                }
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    MGraph G;
    createMGraph(&G);
    
//    Patharc p;
//    ShortPathTable d;
//    ShortestPath_Dijkstra(G, 0, &p, &d);
//    printf("最短路径路线：\n");
//    for (int i = 1; i<G.numNodes; i++) {
//        printf("v0 -> v%d :",i);
//        int j = i;
//        while (p[j] != -1) {
//            printf("%d ",p[j]);
//            j = p[j];
//        }
//        printf("\n");
//    }
//
//    for (int i = 1; i<G.numNodes; i++) {
//        printf("v0 - v%d : %d \n",i,d[i]);
//    }
    int k;
    Floyd_Patharc p1;
    Floyd_ShortPathTable d1;
    ShortestPath_Floyd(G, &p1, &d1);
     printf("各顶点间最短路径如下:\n");
    for (int i = 0; i<G.numNodes; i++) {
        for (int j = i+1; j<G.numNodes; j++) {
            printf("v%d-v%d weight: %d",i,j,d1[i][j]);
            k = p1[i][j];
            printf(" path: %d",i);
            while (k!=j) {
                printf(" -> %d",k);
                k = p1[k][j];
            }
            printf(" -> %d\n",j);
        }
        printf("\n");
    }
    
    printf("最短路径D数组\n");
    for(int i=0; i<G.numNodes; i++)
    {
        for(int j=0; j<G.numNodes; j++)
        {
            printf("%d\t",d1[i][j]);
        }
        printf("\n");
    }
    //打印最终变换后的最短路径P数组
    printf("最短路径P数组\n");
    for(int i=0; i<G.numNodes; i++)
    {
        for(int j=0; j<G.numNodes; j++)
        {
            printf("%d\t",p1[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
