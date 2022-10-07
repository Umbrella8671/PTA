// Windows消息队列

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXSIZE 100000

typedef struct{
    char msg[11];
    int priority;
}Msg;
typedef struct HNode* Heap;
struct HNode{
    Msg* data;
    int Size;
};

typedef Heap MinHeap;

MinHeap CreateMinHeap(int n){
    MinHeap H = (MinHeap)malloc(sizeof(struct HNode));
    H->data = (Msg*)malloc(sizeof(Msg) * n);
    H->data[0].priority = -1;
    H->Size = 0;
    return H;
}
void HeapAdjust(MinHeap H){
    Msg x = H->data[1];
    int i = 1, j = 2 * i;
    while(j <= H->Size){
        if(j + 1 <= H->Size && H->data[j].priority > H->data[j + 1].priority) ++j;
        if(H->data[j].priority > x.priority) break;
        H->data[j / 2] = H->data[j];
        i = j; j *= 2;
    }
    H->data[i] = x;
}

void PutMsg(MinHeap H, Msg msg){
    int i;
    for(i = ++H->Size; H->data[i / 2].priority > msg.priority; i /= 2)
        H->data[i] = H->data[i / 2];
    H->data[i] = msg;
}
Msg GetMsg(MinHeap H){
    Msg msg = H->data[1];
    Msg temp = msg;
    H->data[1] = H->data[H->Size];
    H->data[H->Size] = temp;
    H->Size--;
    HeapAdjust(H);
    return msg;
}

int main(){
    int N;
    scanf("%d", &N);
    char Inst[4];
    MinHeap H = CreateMinHeap(N);
    while(N--){
        scanf("%s", Inst);
        Msg msg;
        if(strcmp("GET", Inst) == 0)
            if(H->Size){
                msg = GetMsg(H);
                printf("%s\n", msg.msg);
            }else
                printf("EMPTY QUEUE!\n");
        else{
            scanf("%s%d", msg.msg, &msg.priority);
            PutMsg(H, msg);
        }
    }
}
