// 插入排序or堆排序
#include <stdio.h>
#include <stdlib.h>

#define Swap(a, b) a ^= b, b ^= a, a ^= b

int IsInsertion(int *A, int *B, int N);
void PrintResults(int *B, int N);
void NextInsertion(int *B, int N, int K);
void Adjust(int *B, int i, int N);
void NextHeap(int *B, int N);
int main(){
    int N, i, K;
    int *A, *B;
    scanf("%d", &N);
    A = (int *)malloc(sizeof(int) * N);
    B = (int *)malloc(sizeof(int) * N);
    for(i = 0; i < N; i++) scanf("%d", &A[i]);
    for(i = 0; i < N; i++) scanf("%d", &B[i]);
    if(K = IsInsertion(A, B, N))
        NextInsertion(B, N, K);
    else
        NextHeap(B, N);
}
int IsInsertion(int *A, int *B, int N){
    int i, k;
    for(i = 1; i < N; i++)
        if(B[i] < B[i - 1])break;
    k = i;
    for(; i < N; i++)
        if(A[i] != B[i])break;
    if(i == N)  return k;
    else    return 0;
}
void NextInsertion(int *B, int N, int K){
    int i, tmp;
    printf("Insertion Sort\n");
    tmp = B[K];
    for(i = K - 1; i >= 0; i--)
        if(tmp < B[i])  B[i + 1] = B[i];
        else break;
    B[i + 1] = tmp;
    PrintResults(B, N);
}
void Adjust(int *B, int i, int N){
    int Child, temp;
    for(temp = B[i]; 2 * i + 1 < N; i = Child){
        Child = 2 * i + 1;
        if(Child + 1 < N && B[Child + 1] > B[Child])
            ++Child;
        if(temp < B[Child])
            B[i] = B[Child];
        else
            break;
    }
    B[i] = temp;
}
void NextHeap(int *B, int N){
    int i;
    printf("Heap Sort\n");
    for(i = N - 1; i >= 0 && B[i] > B[0]; i--);
    Swap(B[0], B[i]);
    Adjust(B, 0, i);
    PrintResults(B, N);
}
void PrintResults(int *B, int N){
    int i;
    printf("%d", B[0]);
    for(i = 1; i < N; i++)printf(" %d", B[i]);
    printf("\n");
}