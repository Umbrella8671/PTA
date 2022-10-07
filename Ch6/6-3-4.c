// 拯救007(升级版)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define MAXVERTEXNUM 101
#define INF 65535

struct Dot{
    int x;
    int y;
};
struct GNode{
    int Nv;
    struct Dot* G;
    int D;
    int Link[MAXVERTEXNUM][MAXVERTEXNUM];
};
typedef struct GNode* MGraph;
bool Visited[MAXVERTEXNUM] = {false, };

MGraph BuildGraph(){
    int V, W;
    struct Dot dot;
    MGraph Graph = (MGraph)malloc(sizeof(struct GNode));
    scanf("%d%d", &Graph->Nv, &Graph->D);
    Graph->G = (struct Dot*)malloc(sizeof(struct Dot) * Graph->Nv);
    for(V = 0; V < Graph->Nv; V++){
        scanf("%d%d", &dot.x, &dot.y);
        Graph->G[V] = dot; 
    }
    for(V = 0; V < Graph->Nv + 1; V++){
        for(W = 0; W < Graph->Nv + 1; W++)
            Graph->Link[V][W] = INF;
        Graph->Link[V][V] = 0;
    }
    return Graph;
}
bool FirstJump(MGraph Graph, int W){
    double f1 = Graph->D + 7.5;
    double f2 = sqrt(pow(Graph->G[W].x, 2) + pow(Graph->G[W].y, 2));
    if(f2 <= f1)
        return true;
    else
        return false;
}

bool Jump(MGraph Graph, int V, int W){
    int x = Graph->G[W].x - Graph->G[V].x;
    int y = Graph->G[W].y - Graph->G[V].y;
    int dist = (int)pow((double)x, 2) + pow((double)y, 2);
    if(dist <= Graph->D * Graph->D)
        return true;
    else
        return false;
}
bool IsSafe(MGraph Graph, int V){
    int x = Graph->D - (50 - abs(Graph->G[V].x));
    int y = Graph->D - (50 - abs(Graph->G[V].y));
    if(x >= 0 || y >= 0)
        return true;
    else
        return false;
}
bool IsLegel(MGraph Graph, int V){
    double dis = pow(Graph->G[V].x, 2) + pow(Graph->G[V].y, 2);
    if(dis <= pow(7.5, 2) || abs(Graph->G[V].x) >= 50 || abs(Graph->G[V].y) >= 50)
        return false;
    else
        return true;
}
void _dfs(MGraph Graph, int V){
    Visited[V] = true;
    if(IsSafe(Graph, V))
        Graph->Link[V][Graph->Nv] = Graph->Link[Graph->Nv][V] = 1;
    int W;
    for(W = 0; W < Graph->Nv; W++){
        if(Jump(Graph, V, W) && Graph->Link[V][W] == INF && Visited[W]) Visited[W] = false;
        if(!Visited[W] && Jump(Graph, V, W)){
            Graph->Link[V][W] = Graph->Link[W][V] = 1;
            _dfs(Graph, W);
        }
    } 
}
void DFS(MGraph Graph){
    for(int V = 0; V < Graph->Nv; V++){
        if(!Visited[V])
            _dfs(Graph, V);
    }
}
void Out(int a[][MAXVERTEXNUM], int N){
    for(int i = 0; i < N; i++)
        printf("%5d ", i);
    printf("\n");
    for(int i = 0; i < N; i++){
        printf("%d: ", i);
        for(int j = 0; j < N; j++)
            printf("%5d ", a[i][j]);
        printf("\n");
    }
}
int Floyd(MGraph Graph, int Path[][MAXVERTEXNUM], int *start){
    int i, j, k;
    for(i = 0; i < Graph->Nv + 1; i++)
        for(j = 0; j < Graph->Nv + 1; j++)
            Path[i][j] = -1;
    for(k = 0; k < Graph->Nv + 1; k++)
        for(i = 0; i < Graph->Nv + 1; i++){
            if(Graph->Link[i][k] == INF)continue;
            for(j = 0; j < Graph->Nv + 1; j++){
                if(Graph->Link[k][j] == INF)continue;
                if(Graph->Link[i][j] > Graph->Link[i][k] + Graph->Link[k][j]){
                    Graph->Link[i][j] = Graph->Link[i][k] + Graph->Link[k][j];
                    Path[i][j] = k;
                }
            }
        }
    
    int Min = INF, dist;
    for(i = 0; i < Graph->Nv; i++)
        if(IsLegel(Graph, i) && FirstJump(Graph, i) && Graph->Link[i][Graph->Nv] < Min){
            Min = Graph->Link[i][Graph->Nv];
            *start = i;
            dist = pow(Graph->G[i].x, 2) + pow(Graph->G[i].y, 2);
        }else if(Graph->Link[i][Graph->Nv] == Min && pow(Graph->G[i].x, 2) + pow(Graph->G[i].y, 2) < dist){
            dist = pow(Graph->G[i].x, 2) + pow(Graph->G[i].y, 2);
            *start = i;
        }
    return Min;
}
void PrintPath(MGraph Graph, int Path[][MAXVERTEXNUM], int start, int end){
    if(Path[start][end] == -1){
        printf("%d %d\n", Graph->G[start].x, Graph->G[start].y);
        return;
    }
    PrintPath(Graph, Path, start, Path[start][end]);
    PrintPath(Graph, Path, Path[start][end], end);
}

void Save007(MGraph Graph){
    if(Graph->D >= 42.5){
        printf("1\n");
        return;
    }
    DFS(Graph);
    int Path[MAXVERTEXNUM][MAXVERTEXNUM];
    int Min, start, end;
    end = Graph->Nv;
    Min = Floyd(Graph, Path, &start);
    if(Min != INF){
        printf("%d\n", Min + 1);
        PrintPath(Graph, Path, start, end);
    }
    else
        printf("0\n");
}

int main(){
    MGraph G = BuildGraph();
    Save007(G);
}

