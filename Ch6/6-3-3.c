// 天梯地图
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
    int flag;
    int dist, time;
};
typedef PtrToENode Edge;

typedef struct GNode* PtrToGNode;
struct GNode{
    int Nv; // 顶点数
    int Ne; // 边数
    int Dist[MaxVertexNum][MaxVertexNum];
    int Time[MaxVertexNum][MaxVertexNum];
    Vertex S, D;
};
typedef PtrToGNode MGraph;

MGraph CreateMGraph(int VertexNum);
void InsertEdge(MGraph Graph, Edge E);
MGraph BuildMGraph();

Vertex FindMin(MGraph Graph, int a[], int Collected[]);

void Time_Dijstra(MGraph Graph, int Time[], Vertex Path[], Vertex S);
void Dist_Dijstra(MGraph Graph, int Dist[], Vertex Path[], Vertex S);
Vertex* GetPath(Vertex Path[], Vertex S, Vertex D, int* VertexNum);

int main(){
    MGraph Graph;
    Graph = BuildMGraph();
    Vertex Path1[MaxVertexNum], Path2[MaxVertexNum];
    int VertexNumTime, VertexNumDist, i;
    int Time[MaxVertexNum], Dist[MaxVertexNum];
    Time_Dijstra(Graph, Time, Path1, Graph->S);
    Dist_Dijstra(Graph, Dist, Path2, Graph->S);
    Vertex* PathTime, *PathDist;
    PathTime = GetPath(Path1, Graph->S, Graph->D, &VertexNumTime);
    PathDist = GetPath(Path2, Graph->S, Graph->D, &VertexNumDist);
    
    bool flag = false;
    if(VertexNumTime == VertexNumDist){
        for(i = 0; i < VertexNumTime; i++)
            if(PathTime[i] != PathDist[i])
                break;
        flag = (i == VertexNumTime);
    }
    if(flag){
        printf("Time = %d; Distance = %d: %d", Time[Graph->D], Dist[Graph->D], PathTime[0]);
        for(i = 1; i < VertexNumTime; i++)
            printf(" => %d", PathTime[i]);
        printf("\n");
    }else{
        printf("Time = %d: %d", Time[Graph->D], PathTime[0]);
        for(i = 1; i < VertexNumTime; i++)
            printf(" => %d", PathTime[i]);
        printf("\n");
        printf("Distance = %d: %d", Dist[Graph->D], PathDist[0]);
        for(i = 1; i < VertexNumDist; i++)
            printf(" => %d", PathDist[i]);
        printf("\n");
    }
}

MGraph CreateMGraph(int VertexNum){
    Vertex V, W;
    MGraph Graph;
    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    for(V = 0; V < Graph->Nv; V++){
        for(W = 0; W < Graph->Nv; W++)
            Graph->Dist[V][W] = Graph->Time[V][W] = INFINITY;
    }
    return Graph;
}

void InsertEdge(MGraph Graph, Edge E){
    Graph->Time[E->v1][E->v2] = E->time;
    Graph->Dist[E->v1][E->v2] = E->dist;
    if(!E->flag){
        Graph->Time[E->v2][E->v1] = E->time;
        Graph->Dist[E->v2][E->v1] = E->dist;
    }
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
            scanf("%d%d%d%d%d", &E->v1, &E->v2, &E->flag, &E->dist, &E->time);
            InsertEdge(Graph, E);
        }
        free(E);    
    }
    scanf("%d%d", &Graph->S, &Graph->D);
    return Graph;
}
Vertex FindMin(MGraph Graph, int a[], int Collected[]){
    Vertex V, MinV;
    int Min = INFINITY;
    for(V = 0; V < Graph->Nv; V++)
        if(!Collected[V] && a[V] < Min){
            Min = a[V];
            MinV = V;
        }
    if(Min < INFINITY) return MinV;
    else return ERROR;
}

void Time_Dijstra(MGraph Graph, int Time[], Vertex Path[], Vertex S){
    Vertex Collected[MaxVertexNum] = {false, };
    Vertex V, W;
    int Dist[MaxVertexNum];
    for(V = 0; V < Graph->Nv; V++){
        Time[V] = Graph->Time[S][V];
        Dist[V] = Graph->Dist[S][V];
        Path[V] = S;
    }
    Collected[S] = true;
    Time[S] = Dist[S] = 0;
    while(true){
        V = FindMin(Graph, Time, Collected);
        if(V == ERROR) break;
        Collected[V] = true;
        for(W = 0; W < Graph->Nv; W++)
            if(Time[V] + Graph->Time[V][W] < Time[W]){
                Time[W] = Time[V] + Graph->Time[V][W];
                Dist[W] = Dist[V] + Graph->Dist[V][W];
                Path[W] = V;
            }else if(Time[W] == Time[V] + Graph->Time[V][W]
                && Dist[W] > Dist[V] + Graph->Dist[V][W]){
                    Dist[W] = Dist[V] + Graph->Dist[V][W];
                    Path[W] = V;
                }
    }
}
void Dist_Dijstra(MGraph Graph, int Dist[], Vertex Path[], Vertex S){
    Vertex Collected[MaxVertexNum] = {false, };
    Vertex V, W, VertexNum[MaxVertexNum];
    for(V = 0; V < Graph->Nv; V++){
        Dist[V] = Graph->Dist[S][V];
        VertexNum[V] = INFINITY;
        Path[V] = S;
    }
    Collected[S] = true;
    Dist[S] = VertexNum[S] = 0;
    while(true){
        V = FindMin(Graph, Dist, Collected);
        if(V == ERROR) break;
        Collected[V] = true;
        for(W = 0; W < Graph->Nv; W++)
            if(Dist[W] > Dist[V] + Graph->Dist[V][W]){
                Dist[W] = Dist[V] + Graph->Dist[V][W];
                VertexNum[W] = VertexNum[V] + 1;
                Path[W] = V;
            }else if(Dist[W] == Dist[V] + Graph->Dist[V][W]
                && VertexNum[W] > VertexNum[V] + 1){
                    VertexNum[W] = VertexNum[V] + 1;
                    Path[W] = V;
                }
    }
}

Vertex* GetPath(Vertex Path[], Vertex S, Vertex D, int* VertexNum){
    Vertex Next, V, W;
    Vertex road[MaxVertexNum];
    int Cnt = 0;
    Next = D;
    road[Cnt++] = D;
    while(Next != S){
        road[Cnt++] = Path[Next];
        Next = Path[Next];
    }
    Vertex* ans = (Vertex*)malloc(sizeof(Vertex) * Cnt);
    for(V = 0, W = Cnt - 1; W >= 0; W--, V++)
        ans[V] = road[W];
    *VertexNum = Cnt;
    return ans;
}



// 10 12
// 0 6 1 5 2
// 0 5 1 3 6
// 0 7 1 2 1
// 6 3 1 3 1
// 6 2 1 5 2
// 5 2 1 4 7
// 7 8 1 1 1
// 8 4 1 3 1
// 4 2 1 1 1
// 3 1 1 2 2
// 1 9 1 2 1
// 2 9 1 1 1
// 0 9

