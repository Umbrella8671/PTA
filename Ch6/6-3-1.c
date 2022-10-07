// 红色警报
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERROR -1

/*----------图的定义及操作-----------*/
#define MaxVertexNum 500
#define INFINITY 65535

typedef int Vertex;
typedef int WeightType;
typedef struct ENode* PtrToENode;
struct ENode{
    Vertex v1, v2;
    WeightType Weight;
};
typedef PtrToENode Edge;

typedef struct GNode* PtrToGNode;
struct GNode{
    int Nv; // 顶点数
    int Ne; // 边数
    WeightType G[MaxVertexNum][MaxVertexNum];
};
typedef PtrToGNode MGraph;

MGraph CreateMGraph(int VertexNum);
void InsertEdge(MGraph Graph, Edge E);
MGraph BuildMGraph();
/*----------图的定义及操作结束-----------*/

bool Visited[MaxVertexNum] = {false, };
bool flag[MaxVertexNum] = {false, };
int DFS(MGraph Graph);

int main(){
    MGraph Graph;
    Graph = BuildMGraph();
    int K, Cnt;
    scanf("%d", &K);
    Cnt = K;
    Vertex V, W;
    int CurCnt = 0, NewCnt = 0;

    while(K--){
        NewCnt = 0;
        scanf("%d", &V);
        
        CurCnt  = DFS(Graph);
        for(W = 0; W < Graph->Nv; W++)
            if(!flag[W]) Visited[W] = false;
        for(W = 0; W < Graph->Nv; W++){
            Graph->G[V][W] = INFINITY;
            Graph->G[W][V] = INFINITY;
        }
        NewCnt = DFS(Graph);

        if(NewCnt - CurCnt > 1)
                printf("Red Alert: City %d is lost!\n", V);
        else
            printf("City %d is lost.\n", V);
        flag[V] = true;
        for(V = 0; V < Graph->Nv; V++)
            if(!flag[V]) Visited[V] = false;
    }
    if(Cnt == Graph->Nv)
        printf("Game Over.\n");
}





MGraph CreateMGraph(int VertexNum){
    Vertex V, W;
    MGraph Graph;
    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    for(V = 0; V < Graph->Nv; V++){
        for(W = 0; W < Graph->Nv; W++)
            Graph->G[V][W] = INFINITY;
    }
    return Graph;
}

void InsertEdge(MGraph Graph, Edge E){
    Graph->G[E->v1][E->v2] = E->Weight;
    Graph->G[E->v2][E->v1] = E->Weight;
}
MGraph BuildMGraph(){
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
            E->Weight = 1;
            InsertEdge(Graph, E);
        }
        free(E);    
    }
    return Graph;
}
void _dfs(MGraph Graph, Vertex V){
    Visited[V] = true;
    Vertex W;
    for(W = 0; W < Graph->Nv; W++)
        if(!Visited[W] && Graph->G[V][W] < INFINITY)
            _dfs(Graph, W);  
}
int DFS(MGraph Graph){
    Vertex W;
    int Cnt = 0;
    for(W = 0; W < Graph->Nv; W++){
        if(!Visited[W]){
            Cnt++; 
            _dfs(Graph, W);  
        }
    }
    return Cnt;
}