// 邻接矩阵存储图的深度优先遍历
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MaxVertexNum 10

typedef struct GNode* PtrToGNode;
struct GNode{
    int Nv; // 顶点数
    int Ne; // 边数
    int G[MaxVertexNum][MaxVertexNum];
};
typedef PtrToGNode MGraph;
typedef int Vertex;
bool Visited[MaxVertexNum];
void DFS(MGraph Graph, Vertex v, void(*Visit)(Vertex)){
    Vertex w;
    Visit(v);
    Visited[v] = true;
    for(w = 0; w < Graph->Nv; w++)
        if(!Visited[w] && Graph->G[v][w] < INFINITY)
            DFS(Graph, w, Visit);
}
