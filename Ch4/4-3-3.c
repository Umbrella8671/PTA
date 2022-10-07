// 完全二叉搜索树

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXSIZE 1010

typedef int BinTree[MAXSIZE];

int CompInt(const void* a, const void* b){
    return *(const int *)a - *(const int*)b;
}

void LevelTraversal(BinTree BT, int i, int N, int ar[], int *j){
    if(i < N){
        LevelTraversal(BT, 2 * i + 1, N, ar, j);
        BT[i] = ar[(*j)++];
        LevelTraversal(BT, 2 * i + 2, N, ar, j);
    }
}

int main(){
    int N, i;
    BinTree BT;
    scanf("%d", &N);
    int ar[MAXSIZE];
    for(i = 0; i < N; i++)
        scanf("%d", &ar[i]);
    qsort(ar, N, sizeof(int), CompInt);
    i = 0;
    LevelTraversal(BT, 0, N, ar, &i);
    printf("%d", BT[0]);
    for(i = 1; i < N; i++)
        printf(" %d", BT[i]);
}
