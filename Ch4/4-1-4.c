// 堆中的路径

#include <stdio.h>
#include <stdlib.h>

#define MINDATA -10001

typedef struct HNode *Heap;
struct HNode
{
    /* data */
    int Data[100];
    int Size;
    int Capacity;
};

typedef Heap MinHeap;

MinHeap CreateHeap(int MaxSize){
    MinHeap H = (MinHeap)malloc(sizeof(struct HNode));
    //H->Data = (int*)malloc(sizeof(int) * (MaxSize + 1));
    H->Size = 0;
    H->Capacity = MaxSize;
    H->Data[0] = MINDATA;
    return H;
}
void Insert(MinHeap H, int x){
    int i;
    for(i = ++H->Size; H->Data[i / 2] > x; i /= 2)
        H->Data[i] = H->Data[i / 2];
    H->Data[i] = x;
}
int main(){
    int n, m, i, j;
    scanf("%d%d", &n, &m);
    MinHeap H = CreateHeap(n);
    for(i = 0; i < n; i++){
        scanf("%d", &j);
        Insert(H, j);
    }
    for(i = 0; i < m; i++){
        scanf("%d", &j);
        printf("%d", H->Data[j]);
        for(j = j / 2; j >= 1; j /= 2)
            printf(" %d", H->Data[j]);
        printf("\n");
    }
}
