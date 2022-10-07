// 寻找大富翁
#include <stdio.h>
#include <stdlib.h>
#define MAXN 10

typedef int ElementType;
void InsertionSort(ElementType A[], int N){
    int i, j;
    ElementType temp;
    for(i = 1; i < N; i++){
        temp = A[i];
        for(j = i; j > 0 && temp > A[j - 1]; j--)
            A[j] = A[j - 1];
        A[j] = temp;
    }
}
void Adjust(ElementType A[], int i, int N){
    int Child;
    ElementType temp;
    for(temp = A[i]; 2 * i + 1 < N; i = Child){
        Child = 2 * i + 1;
        if(Child != N - 1 && A[Child + 1] < A[Child])
            Child++;
        if(temp > A[Child])
            A[i] = A[Child];
        else break;
    }
    A[i] = temp;
}
int main(){
    int N, M, i;
    ElementType A[MAXN], temp;
    scanf("%d %d", &N, &M);
    if(N > MAXN){
        for(i = 0; i < M; i++)
            scanf("%d", &A[i]);
        for(i = (M - 1) >> 2; i >= 0; i--)
            Adjust(A, i, M);
        for(i = M; i < N; i++){
            scanf("%d", &temp);
            if(temp > A[0]){
                A[0] = temp;
                Adjust(A, 0,  M);
            }
        }
        for(i = M - 1; i >= 0; i--){
            temp = A[0]; A[0] = A[i]; A[i] = temp;
            Adjust(A, 0, i);
        }
    }else{
        for(i = 0; i < N; i++)
            scanf("%d", &A[i]);
        InsertionSort(A, N);
    }
    if(N < M)  M = N;
    printf("%d", A[0]);
    for(i = 1; i < M; i++)
        printf(" %d", A[i]);
    printf("\n");
}