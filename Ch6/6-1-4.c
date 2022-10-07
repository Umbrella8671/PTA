// 地下迷宫探索
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


/*----------图的定义及操作-----------*/
#define MaxVertexNum 1000
typedef int Vertex;

typedef struct ENode* PtrToENode;
struct ENode{
    Vertex v1, v2;
};
typedef PtrToENode Edge;

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
    Vertex S;
};
typedef PtrToGNode LGraph;

bool Visited[MaxVertexNum] = {false,};

LGraph CreateLGraph(int VertexNum);
void InsertEdge(LGraph Graph, Edge E);
LGraph BuildLGraph();
/*----------图的定义及操作结束-----------*/



/*----------栈的定义及操作-----------*/
typedef Vertex ElementType;
typedef struct SNode* PtrToSNode;
struct SNode{
    ElementType Data;
    PtrToSNode Next;
};
typedef PtrToSNode Stack;

Stack CreateStack();
bool IsEmpty(Stack S);
bool Push(Stack S, ElementType x);
bool Pop(Stack S);
ElementType Peek(Stack S);
/*----------栈的定义及操作结束-----------*/


void NonRec_DFS(LGraph Graph, Vertex V);
void DFS(LGraph Graph, Vertex V);

int main(){
    LGraph Graph = BuildLGraph();
    //NonRec_DFS(Graph, Graph->S);
    DFS(Graph, Graph->S);
    int i;
    for(i = 0; i < Graph->Nv; i++)
        if(!Visited[i]) break;
    if(i < Graph->Nv)
        printf(" 0\n");
    else printf("\n");
}



LGraph CreateLGraph(int VertexNum){
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
LGraph BuildLGraph(){
    LGraph Graph;
    Edge E;
    int Nv, i;
    scanf("%d", &Nv);
    Graph = CreateLGraph(Nv);

    scanf("%d%d", &Graph->Ne, &Graph->S);
    Graph->S--;
    if(Graph->Ne != 0){
        E = (Edge)malloc(sizeof(struct ENode));
        for(i = 0; i < Graph->Ne; i++){
            scanf("%d%d", &E->v1, &E->v2);
            E->v1--, E->v2--;
            InsertEdge(Graph, E);
        }
    }
    return Graph;
}



Stack CreateStack(){
    Stack S;
    S = (Stack)malloc(sizeof(struct SNode));
    S->Next = NULL;
    return S;
}
bool IsEmpty(Stack S){
    return S->Next == NULL;
}
bool Push(Stack S, ElementType x){
    PtrToSNode TmpCell;
    TmpCell = (PtrToSNode)malloc(sizeof(struct SNode));
    TmpCell->Data = x;
    TmpCell->Next = S->Next;
    S->Next = TmpCell;
    return true;
}
bool Pop(Stack S){
    PtrToSNode FirstCell;
    ElementType TopElem;
    FirstCell = S->Next;
    TopElem = FirstCell->Data;
    S->Next = FirstCell->Next;
    free(FirstCell);
    return TopElem;
}
ElementType Peek(Stack S){
    return S->Next->Data;
}



void NonRec_DFS(LGraph Graph, Vertex V){
    PtrToAdjNode p;
    Stack S = CreateStack();
    Visited[V] = true;
    printf("%d", V + 1);
    Push(S, V);
    while(!IsEmpty(S)){
        V = Peek(S);
        for(p = Graph->G[V].FirstEdge->Next; p; p = p->Next){
            if(!Visited[p->Adj]){
                Visited[p->Adj] = true;
                printf(" %d", p->Adj + 1);
                Push(S, p->Adj);
                break;
            }
            
        }
        if(!p){
            V = Peek(S);
            Pop(S);
            if(!IsEmpty(S))
                printf(" %d", Peek(S) + 1);
        }
    }
}
void DFS(LGraph Graph, Vertex V){
    PtrToAdjNode p;
    Visited[V] = true;
    if(V == Graph->S)
        printf("%d", V + 1);
    else
        printf(" %d", V + 1);
    for(p = Graph->G[V].FirstEdge->Next; p; p = p->Next)
         if(!Visited[p->Adj]){
            DFS(Graph, p->Adj);
            printf(" %d", V + 1);
        }
}

