// 与零交换(表排序)
#include <stdio.h>

#define Swap(a, b) a ^= b, b ^= a, a ^= b
#define MAXN 100000

int main(){
    int i, Tmp, Next, N, Cnt, flag;
    int A[MAXN], T[MAXN];
    scanf("%d", &N);
    for(i = 0; i < N; i++){
        scanf("%d", &A[i]);
        T[A[i]] = i;
    }
    Cnt = 0;
    for(i = 0; i < N; i++){
        if(T[i] == i)continue; //位置正确不处理
        flag = 0;
        Tmp = T[i]; // 第i个元素临时存放，相当于把0换到环里
        T[i] = i;   // 标识环结束
        Cnt++;
        if(Tmp == 0)flag = 1;   // 标识0在环中
        while(Tmp != T[Tmp]){   // 环未结束
            Next = T[Tmp];
            Swap(A[Tmp], A[Next]);
            T[Tmp] = Tmp;
            Tmp = Next;
            if(Tmp == 0)flag = 1;
            Cnt++;
        }
        if(flag) Cnt--;
        else Cnt++;
    }
    printf("%d\n", Cnt);
    for(i = 0; i < N; i++)
        printf("%d ", A[i]);
}