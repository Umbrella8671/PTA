// 关键路径

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
ElementType Pop(Stack S);
ElementType Peek(Stack S);
/*----------栈的定义及操作结束-----------*/

bool TopSort(LGraph Graph, Stack T, int Earliest[]);
void CriticalPath(LGraph Graph);

int main(){
    LGraph Graph;
    Graph = BuildLGraph();
    CriticalPath(Graph);
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
            E->v1--, E->v2--;
            InsertEdge(Graph, E);
        }
    }
    return Graph;
}

bool TopSort(LGraph Graph, Stack T, int Earliest[]){
    int Indegree[MaxVertexNum] = {0, }, cnt;
    Vertex V;
    PtrToAdjNode W;
    Stack S = CreateStack();
    
    for(V = 0; V < Graph->Nv; V++)
        for(W = Graph->G[V].FirstEdge; W; W = W->Next)
            Indegree[W->Adj]++;
    
    for(V = 0; V < Graph->Nv; V++)
        if(!Indegree[V])
            Push(S, V);
    cnt = 0;
    while(!IsEmpty(S)){
        V = Pop(S);
        Push(T, V);
        cnt++;
        for(W = Graph->G[V].FirstEdge; W; W = W->Next){
            if(!(--Indegree[W->Adj]))
                Push(S, W->Adj);
            if(Earliest[V] + W->Weight > Earliest[W->Adj])
                Earliest[W->Adj] = Earliest[V] + W->Weight;
        }
    }
    return cnt == Graph->Nv;
}

void CriticalPath(LGraph Graph){
    Stack S = CreateStack();
    int Earliest[MaxVertexNum];
    if(!TopSort(Graph, S, Earliest)){
        printf("0\n");
        return;
    }
    int i, k, Weight, Latest[MaxVertexNum];
    int MaxTime = 0;
    for(i = 0; i < Graph->Nv; i++)
        MaxTime = Earliest[i] > MaxTime ? Earliest[i] : MaxTime;
    PtrToAdjNode p;
    for(i = 0; i < Graph->Nv; i++)
        Latest[i] = MaxTime;
    while(!IsEmpty(S)){
        for(i = Pop(S), p = Graph->G[i].FirstEdge; p; p = p->Next){
            k = p->Adj;
            Weight = p->Weight;
            if(Latest[k] - Weight < Latest[i])
                Latest[i] = Latest[k] - Weight;
        }
    }
   
    printf("%d\n", MaxTime);
    
    for(i = 0; i < Graph->Nv; i++)
        if(Earliest[i] == Latest[i]){
            p = Graph->G[i].FirstEdge;
            while(p){
                if(Earliest[p->Adj] == Latest[p->Adj] && p->Weight + Earliest[i] == Earliest[p->Adj])
                    printf("%d->%d\n", i + 1, p->Adj + 1);
                p = p->Next;
            }
        }
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
ElementType Pop(Stack S){
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
