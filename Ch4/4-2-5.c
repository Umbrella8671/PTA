
// 堆判断

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MiNDATA -10001

typedef  struct HNode* Heap;
struct HNode{
    int *data;
    int Size;
};
typedef Heap MinHeap;

MinHeap CreatHeap(int N){
    MinHeap H = (MinHeap)malloc(sizeof(struct HNode));
    H->data = (int*)malloc(sizeof(int) * (N + 1));
    H->Size = 0;
    H->data[0] = MiNDATA;
    return H;
}
void Insert(MinHeap H, int X){
    int i;
    for(i = ++H->Size; H->data[i / 2] > X; i /= 2)
        H->data[i] = H->data[i / 2];
    H->data[i] = X;
}
int Find(MinHeap H, int X){
    int i;
    for(i = 0; i < H->Size; i++)
        if(H->data[i] == X)
            break;
    return i;
}
int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    MinHeap H = CreatHeap(N);
    int x, y;
    for(int i = 0; i < N; i++){
        scanf("%d", &x);
        Insert(H, x);
    }
    // for(int i = 1; i <= N; i++)
    //     printf("%d ", H->data[i]);
    char s[10];
    while(M--){
        scanf("%d %s", &x, s);
        if(!strcmp("and", s)){
            scanf("%d", &y);
            scanf("%s", s);
            scanf("%s", s);
            if((Find(H, x) / 2) == (Find(H, y) / 2))
                puts("T");
            else
                puts("F");
        }else{
            scanf("%s", s);
            if(!strcmp("a", s)){
                scanf("%s", s);
                scanf("%s", s);
                scanf("%d", &y);
                if((Find(H, x) / 2) == Find(H, y))
                    puts("T");
                else
                    puts("F");
            }else{
                scanf("%s", s);
                if(!strcmp("root", s)){
                    if(1 == Find(H, x))
                        puts("T");
                    else    
                        puts("F");
                }else{
                    scanf("%s", s);
                    scanf("%d", &y);
                    if((Find(H, y) / 2) == Find(H, x))
                        puts("T");
                    else
                        puts("F");
                }
            }
        }
    }
}