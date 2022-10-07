// 哥尼斯堡的“七桥问题”
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MaxVertexNum 1000

typedef int Vertex;
typedef struct ENode* PtrToENode;
struct ENode{
    Vertex v1, v2;
};
typedef PtrToENode Edge;

typedef struct GNode* PtrToGNode;
struct GNode{
    int Nv; // 顶点数
    int Ne; // 边数
    int G[MaxVertexNum][MaxVertexNum];
    int Degree[MaxVertexNum];
};
typedef PtrToGNode MGraph;
bool Visited[MaxVertexNum]= {false,};

MGraph CreateMGraph(int VertexNum){
    Vertex V, W;
    MGraph Graph;
    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    for(V = 0; V < Graph->Nv; V++){
        Graph->Degree[V] = 0;
        for(W = 0; W < Graph->Nv; W++)
            Graph->G[V][W] = 0;
    }
    return Graph;
}

void InsertEdge(MGraph Graph, Edge E){
    Graph->G[E->v1][E->v2] = 1;
    Graph->Degree[E->v1]++;
    Graph->G[E->v2][E->v1] = 1;
    Graph->Degree[E->v2]++;
}
MGraph BuildGraph(){
    MGraph Graph;
    Edge E;
    int Nv, i;
    scanf("%d", &Nv);
    Graph = CreateMGraph(Nv);
    scanf("%d", &(Graph->Ne));
    if(Graph->Ne != 0){
        E = (Edge)malloc(sizeof(struct ENode));
        for(i = 0; i < Graph->Ne; i++){
            scanf("%d%d", &E->v1, &E->v2);
            E->v1--, E->v2--;
            InsertEdge(Graph, E);
        }
        free(E);    
    }
    return Graph;
}
bool CheckG(MGraph Graph){
    Vertex V;
    for(V = 0; V < Graph->Nv; V++)
        if(Graph->Degree[V] % 2 != 0) return false;
    return true;
}

void DFS(MGraph Graph, Vertex v){
    Vertex w;
    Visited[v] = true;
    for(w = 0; w < Graph->Nv; w++)
        if(!Visited[w] && Graph->G[v][w] == 1)
            DFS(Graph, w);
}
int main(){
    Vertex V;
    MGraph Graph = BuildGraph();
    DFS(Graph, 0);
    for(V = 0; V < Graph->Nv; V++)
        if(!Visited[V])break;
    if(V < Graph->Nv)printf("0\n");
    else
        printf("%d\n", CheckG(Graph));
}


