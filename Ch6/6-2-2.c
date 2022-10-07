// 汉密尔顿回路

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/*----------图的定义及操作-----------*/
#define MaxVertexNum 200
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

MGraph CreateGraph(int VertexNum);
void InsertEdge(MGraph Graph, Edge E);
MGraph BuildGraph();
/*----------图的定义及操作结束-----------*/


bool IsHamilton(MGraph Graph, Vertex V[]){
    int i;
    int Visited[MaxVertexNum] = {0, };
    for(i = 0; i < Graph->Nv; i++){
        if(Graph->G[V[i]][V[i + 1]] == 1) 
            Visited[V[i + 1]] = 1;
        else 
            break;
    }
    if(i != Graph->Nv)return false;
    for(i = 0; i < Graph->Nv; i++)
        if(Visited[i] == 0)
            break;
    if(i == Graph->Nv)
        return true;
    else
        return false;
}


int main(){
    MGraph Graph = BuildGraph();
    int K, N, i, tmp;
    bool flag = false;
    Vertex V[MaxVertexNum + 1];
    scanf("%d", &K);
    while(K--){
        scanf("%d", &N);
        if(N != Graph->Nv + 1){
            for(i = 0; i < N; i++)
                scanf("%d", &tmp);
            flag = false;
        }
        else{
            for(i = 0; i < N; i++){
                scanf("%d", &V[i]);
                V[i]--;
            }
            flag = IsHamilton(Graph, V);
        }
        if(flag) printf("YES\n");
        else printf("NO\n");
    }
}


MGraph CreateGraph(int VertexNum){
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
MGraph BuildGraph(){
    MGraph Graph;
    Edge E;
    int Nv, i;
    scanf("%d", &Nv);
    Graph = CreateGraph(Nv);
    scanf("%d", &(Graph->Ne));
    if(Graph->Ne != 0){
        E = (Edge)malloc(sizeof(struct ENode));
        for(i = 0; i < Graph->Ne; i++){
            scanf("%d%d", &E->v1, &E->v2);
            E->v1--, E->v2--;
            E->Weight = 1;
            InsertEdge(Graph, E);
        }
        free(E);    
    }
    return Graph;
}

