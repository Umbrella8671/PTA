// 基础实验8-1.1 单身狗

#include <stdio.h>
#include <stdlib.h>
#define MAXN 100000

int CompareInt(const void* a, const void* b){
    return *(const int*)a - *(const int*)b;
}
int main(){
    int map[MAXN], isarrive[MAXN], Come[MAXN], ans[MAXN]; 
    int i, N, M, id1, id2;

    for(i = 0; i < MAXN; i++){
        map[i] = -1;
        isarrive[i] = 0;
        Come[i] = 0;
        ans[i] = 0;
    }
    scanf("%d", &N);
    for(i = 0; i < N; i++){
        scanf("%d%d", &id1, &id2);
        map[id1] = id2;
        map[id2] = id1;
    }
    scanf("%d", &M);
    int k = 0;
    for(i = 0; i < M; i++){
        scanf("%d", &id1);
        isarrive[id1] = 1;
        Come[i] = id1;
    }
    for(i = 0; i < M; i++){
        id1 = Come[i];
        id2 = map[id1];
        if(id2 == -1 || isarrive[id2] == 0)
            ans[k++] = id1;
    }
    qsort(ans, k, sizeof(int), CompareInt);
    printf("%d\n", k);
    if(k > 0){
        printf("%05d", ans[0]);
        for(i = 1; i < k; i++)
            printf(" %05d", ans[i]);
    }
}
