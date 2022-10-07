// 拯救007 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define MAXVERTEXNUM 100

struct Dot{
    int x;
    int y;
};
struct GNode{
    int Nv;
    struct Dot* G;
    int D;  
};
typedef struct GNode* MGraph;

MGraph BuildGraph(){
    int V;
    struct Dot dot;
    MGraph Graph = (MGraph)malloc(sizeof(struct GNode));
    scanf("%d%d", &Graph->Nv, &Graph->D);
    Graph->G = (struct Dot*)malloc(sizeof(struct Dot) * Graph->Nv);
    for(V = 0; V < Graph->Nv; V++){
        scanf("%d%d", &dot.x, &dot.y);
        Graph->G[V] = dot;
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
    double dist = sqrt(pow((double)x, 2) + pow((double)y, 2));
    if(dist <= Graph->D)
        return true;
    else
        return false;
}
bool IsSafe(MGraph Graph, int V){
    int x = 50 - abs(Graph->G[V].x) - Graph->D;
    int y = 50 - abs(Graph->G[V].y) - Graph->D;
    if(x <= 0 || y <= 0)
        return true;
    else  
        return false;
}
bool Visited[MAXVERTEXNUM] = {false, };
bool DFS(MGraph Graph, int V){
    Visited[V] = true;
    if(IsSafe(Graph, V)) return true;
    int W;
    bool answer;
    for(W = 0; W < Graph->Nv; W++){
        if(!Visited[W] && Jump(Graph, V, W)){
            answer = DFS(Graph, W);
            if(answer) break;
        }
    }
    return answer;
}
void Save007(MGraph Graph){
    int V;
    bool answer;
    for(V = 0; V < Graph->Nv; V++){
        if(!Visited[V] && FirstJump(Graph, V)){
            answer = DFS(Graph, V);
            if(answer)break;
        }
    }
    if(answer) printf("Yes\n");
    else printf("No\n");
}
int main(){
    Save007(BuildGraph());
}