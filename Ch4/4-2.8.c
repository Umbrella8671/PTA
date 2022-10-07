// 部落

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXSIZE 20000

typedef int SetType[MAXSIZE];
void InitSet(SetType S){
    for(int i = 0; i < MAXSIZE; i++)
        S[i] = MAXSIZE + 1;
}
void Union(SetType S, int root1, int root2){
    if(S[root1] < S[root2]){
        S[root1] += S[root2];
        S[root2] = root1;
    }else{
        S[root2] += S[root1];
        S[root1] = root2;
    }
}
int FindRoot(SetType S, int x){
    if(S[x] < 0)
        return x;
    else
        return S[x] = FindRoot(S, S[x]);
}

int main(){
    int N, Q;
    int total = 0, Cycle = 0, i;
    SetType S;
    InitSet(S);
    scanf("%d", &N);
    while(N--){
        int K;
        scanf("%d", &K);
        int a[MAXSIZE];
        for(i = 0; i < K; i++){
            scanf("%d", &a[i]);
            if(S[a[i] - 1]  == MAXSIZE + 1)
                S[a[i] - 1] = -1;
        }
        for(i = 1; i < K; i++)
            Union(S, FindRoot(S, a[i - 1] - 1), FindRoot(S, a[i] - 1));
    }
    for(i = 0; S[i] != MAXSIZE + 1; i++){
        total++;
        if(S[i] < 0)
            Cycle++;
    }    
    printf("%d %d\n", total, Cycle);
    scanf("%d", &Q);
    while(Q--){
        int x, y;
        scanf("%d%d", &x, &y);
        if(FindRoot(S, x - 1) == FindRoot(S, y - 1))
            printf("Y\n");
        else
            printf("N\n");
    }

}