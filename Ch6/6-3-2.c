// 社交网络图中结点的“重要性”计算
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MaxVertexNum 1000
typedef int Vertex;
typedef int WeightType;

typedef struct ENode* PtrToENode;
struct ENode{
    Vertex v1, v2;
    WeightType Weight;
};
typedef PtrToENode Edge;

typedef struct AdjNode* PtrToAdjNode;
struct AdjNode{
    Vertex Adj; // 邻接点下标
    WeightType Weight; // 边权重
    PtrToAdjNode Next; // 指向下一个邻接点的指针
};

/*顶点表头指针定义*/
typedef struct VNode{
    PtrToAdjNode FirstEdge; // 边表头指针
}AdjList[MaxVertexNum]; // 邻接表类型


typedef struct GNode* PtrToGNode;
struct GNode{
    int Nv;
    int Ne;
    AdjList G;
};
typedef PtrToGNode LGraph;

LGraph CreateLGraph(int VertexNum);
void InsertEdge(LGraph Graph, Edge E);
LGraph BuildLGraph();

/*----------队列的定义及操作-----------*/
typedef Vertex ElementType;
typedef struct QNode* PtrToQNode;
struct QNode{
    ElementType* Data;
    int Front, Rear;
    int MaxSize;
};
typedef PtrToQNode Queue;

Queue CreateQueue(int MaxSize);
bool IsFull(Queue Q);
bool IsEmpty(Queue Q);
bool Push(Queue Q, ElementType x);
bool Pop(Queue Q, ElementType* x);
/*----------队列的定义及操作结束-----------*/

bool Visited[MaxVertexNum] = {false, };

void BFS(LGraph Grapg, Vertex V, int D[]);
int DFS(LGraph Graph);
void Clear(){
    for(int i = 0; i < MaxVertexNum; i++) Visited[i] = false;
}



int main(){
    LGraph Graph = BuildLGraph();
    int K, total, D[MaxVertexNum];
    Vertex V, W;
    scanf("%d", &K);
    if(DFS(Graph) == 1){
        while(K--){
            scanf("%d", &V);
            Clear();
            BFS(Graph, V - 1, D);
            for(total = 0, W = 0; W < Graph->Nv; W++)
                total += D[W];
            printf("Cc(%d)=%.2lf\n", V, (double)(Graph->Nv - 1) / total);
        }
    }else{
        while(K--){
            scanf("%d", &V);
            printf("Cc(%d)=0.00\n", V);
        }
    }
}



LGraph CreateLGraph(int VertexNum){
    Vertex V;
    LGraph Graph;
    Graph = (LGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    for(V = 0; V < Graph->Nv; V++)
        Graph->G[V].FirstEdge = NULL;
    
    return Graph;
}
void InsertEdge(LGraph Graph, Edge E){
    PtrToAdjNode NewNode;
    NewNode = (PtrToAdjNode)malloc(sizeof(struct AdjNode));
    NewNode->Adj = E->v2; NewNode->Weight = E->Weight; 
    NewNode->Next = Graph->G[E->v1].FirstEdge;
    Graph->G[E->v1].FirstEdge = NewNode;
    
    NewNode = (PtrToAdjNode)malloc(sizeof(struct AdjNode));
    NewNode->Adj = E->v1; NewNode->Weight = E->Weight;
    NewNode->Next = Graph->G[E->v2].FirstEdge;
    Graph->G[E->v2].FirstEdge = NewNode;
}
LGraph BuildLGraph(){
    LGraph Graph;
    Edge E;
    int Nv, i;
    scanf("%d", &Nv);
    Graph = CreateLGraph(Nv);

    scanf("%d", &Graph->Ne);
    if(Graph->Ne != 0){
        E = (Edge)malloc(sizeof(struct ENode));
        for(i = 0; i < Graph->Ne; i++){
            scanf("%d%d", &E->v1, &E->v2);
            E->v1--, E->v2--, E->Weight = 1;
            InsertEdge(Graph, E);
        }
    }
    return Graph;
}
void BFS(LGraph Graph, Vertex V, int D[]){
    PtrToAdjNode Padj;
    Queue Q = CreateQueue(Graph->Nv);
    Push(Q, V);
    int layer, last, tail;
    layer = 1;
    last = V;
    Visited[V] = true;
    D[V] = 0;
    while(!IsEmpty(Q)){
        Pop(Q, &V);
        for(Padj = Graph->G[V].FirstEdge; Padj; Padj = Padj->Next)
            if(!Visited[Padj->Adj]){
                Visited[Padj->Adj] = true;
                D[Padj->Adj] = layer;
                Push(Q, Padj->Adj);
                tail = Padj->Adj;
            }
        if(V == last){
            layer++; last = tail;
        }
    }
}
void _dfs(LGraph Graph, Vertex V){
    Visited[V] = true;
    PtrToAdjNode W;
    for(W = Graph->G[V].FirstEdge; W; W = W->Next)
        if(!Visited[W->Adj])
            _dfs(Graph, W->Adj);
}
int DFS(LGraph Graph){
    int Cnt = 0;
    for(Vertex V = 0; V < Graph->Nv; V++)
        if(!Visited[V]){
            Cnt++;
            _dfs(Graph, V);
        }
    return Cnt;
}



Queue CreateQueue(int MaxSize){
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->Data = (ElementType*)malloc(sizeof(ElementType) * MaxSize + 1);
    Q->Front = Q->Rear = 0;
    Q->MaxSize = MaxSize;
    return Q;
}
bool IsFull(Queue Q){
    return (Q->Rear + 1) % Q->MaxSize == Q->Front;
}
bool IsEmpty(Queue Q){
    return Q->Front == Q->Rear;
}
bool Push(Queue Q, ElementType x){
    if(IsFull(Q))
        return false;
    Q->Rear = (Q->Rear + 1) % Q->MaxSize;
    Q->Data[Q->Rear] = x;
    return true;
}
bool Pop(Queue Q, ElementType* x){
    if(IsEmpty(Q))
        return false;
    Q->Front = (Q->Front + 1) % Q->MaxSize;
    *x = Q->Data[Q->Front];
    return true;
}