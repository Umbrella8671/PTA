// 魔法优惠券
#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000000

int CompareInt(const void* a, const void* b){
    return *(const int*)b - *(const int*)a;
}
int main(){
    int N, M, i, j, sum, tmp;
    int Coupon[MAXN], Price[MAXN];
    
    scanf("%d", &N);
    for(i = 0; i < N; i++) scanf("%d", &Coupon[i]);
    qsort(Coupon, N, sizeof(int), CompareInt);
    
    scanf("%d", &M);
    for(i = 0; i < M; i++) scanf("%d", &Price[i]);
    qsort(Price, M, sizeof(int), CompareInt);

    i = 0, j = 0, sum = 0;
    int t = N < M ? N : M;
    while(i < t){
        tmp = Coupon[i] * Price[i];
        ++i;
        if(tmp > 0)
            sum += tmp;
        else
            break;
    }
    if(i != t){
        i = N - 1, j = M - 1;
        tmp = Coupon[i] * Price[j];
        while(tmp > 0){
            sum += tmp;
            i--, j--;
            tmp = Coupon[i] * Price[j];
        }
    }
    printf("%d\n", sum);
}