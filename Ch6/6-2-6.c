// 最短工期

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

bool TopSort(LGraph Graph, Vertex TopOrder[], int Earliest[]);


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


int main(){
    LGraph Graph;
    Graph = BuildLGraph();
    Vertex TopOrder[MaxVertexNum] = {0, };
    int Earliest[MaxVertexNum] = {0, };
    if(TopSort(Graph, TopOrder, Earliest)){
        int Early = 0;
        for(int i = 0; i < Graph->Nv; i++)
            Early = Earliest[i] > Early ? Earliest[i] : Early;
        printf("%d\n", Early);
    }else
        printf("Impossible\n");
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
            scanf("%d%d%d", &E->v1, &E->v2, &E->Weight);
            InsertEdge(Graph, E);
        }
    }
    return Graph;
}

bool TopSort(LGraph Graph, Vertex TopOrder[], int Earliest[]){
    int Indegree[MaxVertexNum] = {0, }, cnt;
    Vertex V;
    PtrToAdjNode W;
    Queue Q = CreateQueue(Graph->Nv);
    
    for(V = 0; V < Graph->Nv; V++)
        for(W = Graph->G[V].FirstEdge; W; W = W->Next)
            Indegree[W->Adj]++;
    
    for(V = 0; V < Graph->Nv; V++)
        if(!Indegree[V])
            Push(Q, V);
    cnt = 0;
    while(!IsEmpty(Q)){
        Pop(Q, &V);
        TopOrder[cnt++] = V;
        for(W = Graph->G[V].FirstEdge; W; W = W->Next){
            if(!(--Indegree[W->Adj]))
                Push(Q, W->Adj);
            if(Earliest[V] + W->Weight > Earliest[W->Adj])
                Earliest[W->Adj] = Earliest[V] + W->Weight;
        }
    }
    return cnt == Graph->Nv;
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