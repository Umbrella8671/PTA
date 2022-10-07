// 最小生成树唯一性
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF 65565

#define MaxVertexNum 500
struct GNode{
    int Nv;
    int Ne;
};
typedef struct GNode* MGraph;

typedef struct{
    int V1, V2;
    int Weight;
}Edge;

MGraph Graph;
Edge *ESet;
int VSet[MaxVertexNum];
int Length = 0;
int Cnt = 0;

int Find(int x){
    if(VSet[x] < 0)
        return x;
    else return VSet[x] = Find(VSet[x]);
}
void Union(int u, int v){
    int root1 = Find(u);
    int root2 = Find(v);
    if(root1 == root2) return;
    if(VSet[root1] < VSet[root2]){
        VSet[root1] += VSet[root2];
        VSet[root2] = root1;
    }else{
        VSet[root2] += VSet[root1];
        VSet[root1] = root2;
    }
}


int CompareEdge(const void* a, const void* b){
    const Edge* ea = (const Edge*)a;
    const Edge* eb = (const Edge*)b;
    return (ea->Weight - eb->Weight);
}


void InitVSet(){
    for(int i = 0; i < Graph->Nv; i++)
        VSet[i] = -1;
}

void BuildGraph(){
    Graph = (MGraph)malloc(sizeof(struct GNode));
    scanf("%d%d", &Graph->Nv, &Graph->Ne);
    ESet = (Edge*)malloc(sizeof(Edge) * Graph->Ne);
    Edge E;
    InitVSet();
    for(int i = 0; i < Graph->Ne; i++){
        scanf("%d%d%d", &E.V1, &E.V2, &E.Weight);
        ESet[i].V1 = E.V1;
        ESet[i].V2 = E.V2;
        ESet[i].Weight = E.Weight;
        Union(E.V1 - 1, E.V2 -1);
    }
}
int GetConnection(){
    int Cnt = 0;
    for(int i = 0; i < Graph->Nv; i++)
        if(VSet[i] < 0)
            Cnt++;
    return Cnt;
}
bool Mst_is_unique(){
    InitVSet();
    int i, j, r1, r2, r3, r4, s;
    bool flag = true; 
    qsort(ESet, Graph->Ne, sizeof(Edge), CompareEdge);
    for(i = 0; i < Graph->Ne; i++){
        r1 = Find(ESet[i].V1 - 1);
        r2 = Find(ESet[i].V2 - 1);
        if(r1 != r2){
            if(flag){
                for(j = i + 1; j < Graph->Ne; j++)
                    if(ESet[j].Weight == ESet[i].Weight){
                        r3 = Find(ESet[j].V1 - 1);
                        r4 = Find(ESet[j].V2 - 1);
                        if(r1 == r3 && r2 == r4 || r1 == r4 && r2 == r3)
                            flag = false;
                    }
            }
            Union(r1, r2);
            s = ESet[i].Weight;
            Length += s;
        }
    }
    return flag;
}
int main(){
    BuildGraph();
    if((Cnt = GetConnection()) == 1){
        if(Mst_is_unique())
            printf("%d\nYes\n", Length);
        else
            printf("%d\nNo\n", Length);
    }else
        printf("No MST\n%d\n", Cnt);
}