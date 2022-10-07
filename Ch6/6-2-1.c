// 列出连通集(DFS,BFS)
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


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

typedef struct ENode* PtrToENode;
struct ENode{
    Vertex v1, v2;
};
typedef PtrToENode Edge;

LGraph CreateGraph(int VertexNum);
void InsertEdge(LGraph Grapg, Edge E);
LGraph BuildGraph();
void DFS(LGraph Graph);
void BFS(LGraph Graph);
/*----------图的定义及操作结束-----------*/





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
/*----------图的定义及操作结束-----------*/


bool Visited[MaxVertexNum] = {false,};


void PrintG(LGraph Graph){
    for(Vertex V = 0; V < Graph->Nv; V++){
        printf("%d", V);
        for(PtrToAdjNode W = Graph->G[V].FirstEdge->Next; W; W = W->Next)
            printf("-->%d", W->Adj);
        printf("\n");
    }
}
int main(){
    LGraph Graph = BuildGraph();
    //PrintG(Graph);
    DFS(Graph);
    for(int i = 0; i < Graph->Nv; i++) Visited[i] = false;
    BFS(Graph);
    return 0;
}



LGraph CreateGraph(int VertexNum){
    Vertex V;
    LGraph Graph;
    Graph = (LGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    for(V = 0; V < Graph->Nv; V++){
        Graph->G[V].FirstEdge = (PtrToAdjNode)malloc(sizeof(struct AdjNode));
        Graph->G[V].FirstEdge->Next = NULL;
    }
    return Graph;
}
void InsertEdge(LGraph Graph, Edge E){
    PtrToAdjNode NewNode, p;
    NewNode = (PtrToAdjNode)malloc(sizeof(struct AdjNode));
    NewNode->Adj = E->v2; NewNode->Next = NULL;
    p = Graph->G[E->v1].FirstEdge;
    while(p->Next && p->Next->Adj < NewNode->Adj) p = p->Next;
    NewNode->Next = p->Next; p->Next = NewNode;
    
    NewNode = (PtrToAdjNode)malloc(sizeof(struct AdjNode));
    NewNode->Adj = E->v1; NewNode->Next = NULL;
    p = Graph->G[E->v2].FirstEdge;
    while(p->Next && p->Next->Adj < NewNode->Adj) p = p->Next;
    NewNode->Next = p->Next; p->Next = NewNode;
}
LGraph BuildGraph(){
    LGraph Graph;
    Edge E;
    int Nv, i;
    scanf("%d", &Nv);
    Graph = CreateGraph(Nv);

    scanf("%d", &Graph->Ne);
    if(Graph->Ne != 0){
        E = (Edge)malloc(sizeof(struct ENode));
        for(i = 0; i < Graph->Ne; i++){
            scanf("%d%d", &E->v1, &E->v2);
            InsertEdge(Graph, E);
        }
    }
    return Graph;
}

void _dfs(LGraph Graph, Vertex V){
    Visited[V] = true;
    printf(" %d", V);
    for(PtrToAdjNode W = Graph->G[V].FirstEdge->Next; W; W = W->Next)
        if(!Visited[W->Adj]){
            _dfs(Graph, W->Adj);
        }
}
void DFS(LGraph Graph){
    for(Vertex V = 0; V < Graph->Nv; V++){
        if(!Visited[V]){
            printf("{");
            _dfs(Graph, V);
            printf(" }\n");
        }
    }
}


void BFS(LGraph Graph){
    Vertex V, p;
    Queue Q = CreateQueue(Graph->Nv);
    for(V = 0; V < Graph->Nv; V++){
        if(!Visited[V]){
            printf("{ %d", V);
            Visited[V] = true;
            Push(Q, V);
            while(!IsEmpty(Q)){
                Pop(Q, &p);
                for(PtrToAdjNode W = Graph->G[p].FirstEdge->Next; W; W = W->Next){
                    if(!Visited[W->Adj]){
                        Visited[W->Adj] = true;
                        printf(" %d", W->Adj);
                        Push(Q, W->Adj);
                    }
                }
            }
            printf(" }\n");
        }
        
    }
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


