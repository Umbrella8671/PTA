// 旅游规划(Dijkstra)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#define MaxVertexNum 500
#define INFINITY 65535

#define ERROR -1

typedef int Vertex;
typedef struct ENode* PtrToENode;
struct ENode{
    Vertex v1, v2;
    int dist, cost;
};
typedef PtrToENode Edge;

typedef struct GNode* PtrToGNode;
struct GNode{
    int Nv; // 顶点数
    int Ne; // 边数
    int Dist[MaxVertexNum][MaxVertexNum];
    int Cost[MaxVertexNum][MaxVertexNum];
    Vertex S, D;
};
typedef PtrToGNode MGraph;

MGraph CreateMGraph(int VertexNum);
void InsertEdge(MGraph Graph, Edge E);
MGraph BuildMGraph();

Vertex FindMinDist(MGraph Graph, int dist[], int collected[]);
void Dijkstra(MGraph Graph, int dist[], int cost[], Vertex S);


int main(){
    MGraph Graph = BuildMGraph();
    int* dist = (int*)malloc(sizeof(int) * Graph->Nv);
    int* cost = (int*)malloc(sizeof(int) * Graph->Nv);
    Dijkstra(Graph, dist, cost, Graph->S);
    printf("%d %d\n", dist[Graph->D], cost[Graph->D]);
    free(dist);free(cost);
}


MGraph CreateMGraph(int VertexNum){
    Vertex V, W;
    MGraph Graph;
    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    for(V = 0; V < Graph->Nv; V++){
        for(W = 0; W < Graph->Nv; W++)
            Graph->Dist[V][W] = Graph->Cost[V][W] = INFINITY;
    }
    return Graph;
}

void InsertEdge(MGraph Graph, Edge E){
    Graph->Cost[E->v1][E->v2] = E->cost;
    Graph->Dist[E->v1][E->v2] = E->dist;
    Graph->Cost[E->v2][E->v1] = E->cost;
    Graph->Dist[E->v2][E->v1] = E->dist;
}
MGraph BuildMGraph(){
    MGraph Graph;
    Edge E;
    int Nv, i;
    scanf("%d", &Nv);
    Graph = CreateMGraph(Nv);
    scanf("%d%d%d", &(Graph->Ne), &Graph->S, &Graph->D);
    if(Graph->Ne != 0){
        E = (Edge)malloc(sizeof(struct ENode));
        for(i = 0; i < Graph->Ne; i++){
            scanf("%d%d%d%d", &E->v1, &E->v2, &E->dist, &E->cost);
            InsertEdge(Graph, E);
        }
        free(E);    
    }
    return Graph;
}
Vertex FindMinDist(MGraph Graph, int dist[], int collected[]){
    Vertex MinV, V;
    int MinDist = INFINITY;
    for(V = 0; V < Graph->Nv; V++){
        if(collected[V] == false && dist[V] < MinDist){
            MinDist = dist[V];
            MinV = V;
        }
    }
    if(MinDist < INFINITY) return MinV;
    else return ERROR;
}
void Dijkstra(MGraph Graph, int dist[], int cost[], Vertex S){
    int collected[MaxVertexNum];
    Vertex V, W;
    for(V = 0; V < Graph->Nv; V++){
        dist[V] = Graph->Dist[S][V];
        cost[V] = Graph->Cost[S][V];
        collected[V] = false;
    }
    dist[S] = cost[S] = 0;
    collected[S] = true;
    while(true){
        V = FindMinDist(Graph, dist, collected);
        if(V == ERROR) break;
        collected[V] = true;
        for(W = 0; W < Graph->Nv; W++)
            if(collected[W] == false 
                && Graph->Dist[V][W] < INFINITY)
                if(dist[V] + Graph->Dist[V][W] < dist[W]){
                    dist[W] = dist[V] + Graph->Dist[V][W];
                    cost[W] = cost[V] + Graph->Cost[V][W];
                }else if(dist[V] + Graph->Dist[V][W] == dist[W]
                    && cost[V] + Graph->Cost[V][W] < cost[W]){
                    cost[W] = cost[V] + Graph->Cost[V][W];
                }
        
    }
}