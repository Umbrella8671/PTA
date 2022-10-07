// 修理牧场

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define Swap(a, b) a ^= b, b ^= a, a ^= b 

typedef struct HNode* Heap;
struct HNode{
    int *data;
    int Size;
};

typedef Heap MinHeap;

MinHeap CreateMinHeap(int n){
    MinHeap H = (MinHeap)malloc(sizeof(struct HNode));
    H->data = (int*)malloc(sizeof(int) * n);
    H->data[0] = -1;
    H->Size = 0;
    return H;
}
void Insert(MinHeap H, int x){
    int i;
    for(i = ++H->Size; H->data[i / 2] > x; i /= 2)
        H->data[i] = H->data[i / 2];
    H->data[i] = x;
}
void HeapAdjust(MinHeap H){
    int x = H->data[1];
    int i = 1, j = 2 * i;
    while(j <= H->Size){
        if(j + 1 <= H->Size && H->data[j] > H->data[j + 1]) ++j;
        if(H->data[j] > x) break;
        H->data[j / 2] = H->data[j];
        i = j; j *= 2;
    }
    H->data[i] = x;
}
int Push(MinHeap H){
    int x = H->data[1];
    Swap(H->data[1], H->data[H->Size]);
    //H->data[H->Size] = 0;
    H->Size--;
    HeapAdjust(H);
    return x;
}
int main(){
    int N;
    scanf("%d", &N);
    MinHeap H = CreateMinHeap(N);
    int x, y, z;
    int sum = 0;
    while(N--){
        scanf("%d", &x);
        Insert(H, x);
    }

    while(H->Size != 1){
        x = Push(H);
        y = Push(H);
        z = x + y;
        sum += z; 
        Insert(H, z);
    }
    printf("%d\n", sum);
}
