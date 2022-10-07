// 六度空间 

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
unsigned long int BFS(LGraph Graph, Vertex V);

void Clear(){
    for(int i = 0; i < MaxVertexNum; i++) Visited[i] = false;
}
int main(){
    LGraph Graph = BuildLGraph();
    for(Vertex V = 0; V < Graph->Nv; V++){
        unsigned long int Count = BFS(Graph, V);
        Clear();
        printf("%d:%.2lf%%\n", V + 1, (double)Count / Graph->Nv * 100);
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
            E->v1--, E->v2--, E->Weight = 0;
            InsertEdge(Graph, E);
        }
    }
    return Graph;
}
unsigned long int BFS(LGraph Graph, Vertex V){
    Visited[V] = true;
    int level , last, tail;
    unsigned long int Count;
    level = 0, Count = 1;
    last = V;
    Queue Q = CreateQueue(Graph->Nv);
    Push(Q, V);
    while(!IsEmpty(Q)){
        Pop(Q, &V);
        for(PtrToAdjNode padj = Graph->G[V].FirstEdge; padj; padj = padj->Next)
            if(!Visited[padj->Adj]){
                Visited[padj->Adj] = true;
                Push(Q, padj->Adj);
                Count++;
                tail = padj->Adj;
            }
        if(V == last){
            level++; last = tail;
        }
        if(level == 6) break;
    }
    return Count;
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


