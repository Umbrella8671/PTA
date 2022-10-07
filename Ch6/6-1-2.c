// 邻接表存储图的广度优先遍历
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>



/*----------图的定义及操作-----------*/
#define MaxVertexNum 10
typedef int Vertex;
typedef struct AdjNode* PtrToAdjNode;
struct AdjNode{
    Vertex Adj; // 邻接点下标
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
/*----------图的定义及操作结束-----------*/

bool Visited[MaxVertexNum];
void BFS(LGraph Graph, Vertex S, void(*Visit)(Vertex)){
    Queue Q;
    Vertex V;
    PtrToAdjNode W;
    Q = CreateQueue(MaxVertexNum);
    Visit(S);
    Visited[S] = true;
    Push(Q, S);
    while(!IsEmpty(Q)){
        Pop(Q, &V);
        for(W = Graph->G[V].FirstEdge; W; W = W->Next)
            if(!Visited[W->Adj]){
                Visit(W->Adj);
                Visited[W->Adj] = true;
                Push(Q, W->Adj);
            }
    }
}





/*----------队列的定义及操作-----------*/
typedef int ElementType;
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







