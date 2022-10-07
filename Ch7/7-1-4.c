// 统计工龄

#include <stdio.h>

#define MAXN 51

int main(){
    int N, temp;
    scanf("%d", &N);
    int Count[MAXN] = {0};
    for(int i = 0; i < N; i++){
        scanf("%d", &temp);
        Count[temp]++;
    }
    for(int i = 0; i < MAXN; i++){
        if(Count[i])
            printf("%d:%d\n", i, Count[i]);
    }
}