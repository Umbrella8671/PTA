// 插入or归并排序

#include <stdio.h>
#include <stdlib.h>

int IsInsertion(int *A, int *B, int N);
void PrintResults(int *B, int N);
void NextInsertion(int *B, int N, int K);
int MergeLength(int *B, int N);
void NextMerge(int *B, int N);
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
        NextMerge(B, N);
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
void PrintResults(int *B, int N){
    int i;
    printf("%d", B[0]);
    for(i = 1; i < N; i++)printf(" %d", B[i]);
    printf("\n");
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
int MergeLength(int *B, int N){
    int i, l;
    for(l = 2; l <= N; l *= 2){
        for(i = l; i < N; i += (l + l))
            if(B[i - 1] > B[i])break;
        if(i < N)break;
    }
    return l;
}
void NextMerge(int *B, int N){
    int i, p1, p2, p, L;
    int *tmp;
    tmp = (int *)malloc(sizeof(int) * N);
    printf("Merge Sort\n");
    L = MergeLength(B, N);
    p = 0;
    for(i = 0; i < (N - L - L); i += (L + L)){
        p1 = i; p2 = i + L;
        while(p1 < (i + L) && p2 < (i + L + L)){
            if(B[p1] > B[p2]) tmp[p++] = B[p2++];
            else tmp[p++] = B[p1++];
        }
        while(p1 < (i + L)) tmp[p++] = B[p1++];
        while(p2 < (i + L + L)) tmp[p++] = B[p2++];
    }
    if((N - i) > L){
        p1 = i; p2 = i + L;
        while(p1 < (i + L) && p2 < N){
            if(B[p1] > B[p2]) tmp[p++] = B[p2++];
            else tmp[p++] = B[p1++];
        }
        while(p1 < i + L) tmp[p++] = B[p1++];
        while(p2 < N) tmp[p++] = B[p2++];
    }else
        while(i < N) tmp[i] = B[i++];
    PrintResults(tmp, N); 
}