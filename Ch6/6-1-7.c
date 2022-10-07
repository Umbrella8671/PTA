// 公路村村通(Kruskal算法)

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

/*-----最小堆定义-----*/
typedef struct ENode Elm;

void Swap(Elm *a, Elm *b);
void PercDown(Edge ESet, int p, int N);
void InitializeESet(LGraph Graph, Edge ESet);
int GetEdge(Edge ESet, int CurrentSize);
/*-----最小堆定义结束-----*/


/*-----关于顶点并查集-----*/
typedef Vertex ElementType;     // 默认集合元素
typedef Vertex SetName;         // 默认用根节点下标做集合名称
typedef ElementType SetType[MaxVertexNum];  // 集合类型

void InitializeVSet(SetType S, int N);
void Union(SetType S, SetName root1, SetName root2);
SetName Find(SetType S, ElementType x);
/*-----关于顶点并查集-----*/

bool CheckCycle(SetType VSet, Vertex V1, Vertex V2);
int Kruskal(LGraph Graph);

int main(){
    printf("%d\n", Kruskal(BuildLGraph()));
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
            scanf("%d%d%d", &E->v1, &E->v2, &E->Weight);
            E->v1--, E->v2--;
            InsertEdge(Graph, E);
        }
    }
    return Graph;
}



void Swap(Elm *a, Elm *b){
    Elm temp = *a; *a = *b; *b = temp;
}
// 将N个元素边数组中以ESet[p]为根的子堆调整为关于Weight的最小堆
void PercDown(Edge ESet, int p, int N){
    int Parent, Child;
    struct ENode x;

    x = ESet[p];
    for(Parent = p; (Parent * 2 + 1) < N; Parent = Child){
        Child = 2 * Parent + 1;
        if(Child + 1 < N && ESet[Child + 1].Weight < ESet[Child].Weight) ++Child;
        if(ESet[Child].Weight >= x.Weight) break;
        ESet[Parent] = ESet[Child];
    }
    ESet[Parent] = x;
}
void InitializeESet(LGraph Graph, Edge ESet){
    Vertex V;
    PtrToAdjNode W;
    int ECount;
    
    ECount = 0;
    for(V = 0; V < Graph->Nv; V++)
        for(W = Graph->G[V].FirstEdge; W; W = W->Next)
        // 避免重复录入无向图的边，只收V1<V2的边
            if(V < W->Adj){
                ESet[ECount].v1 = V;
                ESet[ECount].v2 = W->Adj;
                ESet[ECount++].Weight = W->Weight;
            }
    // 初始化为最小堆
    for(ECount = Graph->Ne / 2; ECount >= 0; ECount--)
        PercDown(ESet, ECount, Graph->Ne);
}
int GetEdge(Edge ESet, int CurrentSize){
    // 给定当前最小堆的SIZE，将当前最小边位置弹出，并调整最小堆
    Swap(&ESet[0], &ESet[CurrentSize - 1]);
    PercDown(ESet, 0, CurrentSize - 1);
    
    return CurrentSize - 1;
}



void InitializeVSet(SetType S, int N){
    ElementType X;
    for(X = 0; X < N; X++) S[X] = -1;
}
void Union(SetType S, SetName root1, SetName root2){
    if(S[root2] < S[root1]){
        S[root2] += S[root1];
        S[root1] = root2;
    }else{
        S[root1] += S[root2];
        S[root2] = root1;
    }
}
SetName Find(SetType S, ElementType x){
    if(S[x] < 0)
        return x;
    return S[x] = Find(S, S[x]);
}



bool CheckCycle(SetType VSet, Vertex V1, Vertex V2){
    Vertex root1, root2;
    root1 = Find(VSet, V1);
    root2 = Find(VSet, V2);

    if(root1 == root2)  // V1与V2连通,同一个连通集
        return false;
    Union(VSet, root1, root2);
    return true;
}
int Kruskal(LGraph Graph){
    WeightType TotalWeight;
    int ECount, NextEdge;
    SetType VSet;
    Edge ESet; // 边数组
    //struct ENode ESet[15];
    InitializeVSet(VSet, Graph->Nv);
    ESet = (Edge)malloc(sizeof(struct ENode) * Graph->Ne);
    InitializeESet(Graph, ESet);
    TotalWeight = 0;    //初始化权重和
    ECount = 0; //初始化收录的边数

    NextEdge = Graph->Ne;   // 原始边集规模
    while(ECount < Graph->Nv - 1){
        NextEdge = GetEdge(ESet, NextEdge);
        if(NextEdge < 0) // 边集已空s
            break;
        if(CheckCycle(VSet, ESet[NextEdge].v1, ESet[NextEdge].v2)){
            // 不构成回路
            TotalWeight += ESet[NextEdge].Weight;
            ECount++;   //生成树边数加1
        }
    }
    if(ECount < Graph->Nv - 1)
        TotalWeight = -1;
    
    return TotalWeight;
}