// 哈利波特的考试(Floyd算法)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERROR -1

/*----------图的定义及操作-----------*/
#define MaxVertexNum 100
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
void Floyd(MGraph Graph, WeightType D[][MaxVertexNum]);

WeightType FindMaxDist(WeightType D[][MaxVertexNum], int i, int N);
void FindAnimal(MGraph Graph);


int main(){
    MGraph Graph = BuildMGraph();
    FindAnimal(Graph);
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
            scanf("%d%d%d", &E->v1, &E->v2, &E->Weight);
            E->v1--, E->v2--;
            InsertEdge(Graph, E);
        }
        free(E);    
    }
    return Graph;
}

void Floyd(MGraph Graph, WeightType D[][MaxVertexNum]){
    Vertex i, j, k;
    for(i = 0; i < Graph->Nv; i++)
        for(j = 0; j < Graph->Nv; j++)
            D[i][j] = Graph->G[i][j];
    for(k = 0; k < Graph->Nv; k++)
        for(i = 0; i < Graph->Nv; i++)
            for(j = 0; j < Graph->Nv; j++)
                if(D[i][k] + D[k][j] < D[i][j])
                    D[i][j] = D[i][k] + D[k][j];
}

WeightType FindMaxDist(WeightType D[][MaxVertexNum], int i, int N){
    WeightType MaxDist = 0;
    for(int j = 0; j < N; j++){
        if(i != j && D[i][j] > MaxDist)
            MaxDist = D[i][j];
    }
    return MaxDist;
}
void FindAnimal(MGraph Graph){
    WeightType D[MaxVertexNum][MaxVertexNum], MaxDist, MinDist;
    Floyd(Graph, D);
    MinDist = INFINITY;
    Vertex animal, i;
    for(i = 0; i < Graph->Nv; i++){
        MaxDist = FindMaxDist(D, i, Graph->Nv);
        if(MaxDist == INFINITY){
            printf("0\n");
            return;
        }

        if(MinDist > MaxDist){
            MinDist = MaxDist; animal = i + 1;
        }
    }
    printf("%d %d\n", animal, MinDist);
}