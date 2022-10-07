// 特殊堆栈

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 10001

struct SNode{
    int data[MAXN];
    int Size;
    int top;
};
typedef struct SNode* Stack;
int A1[MAXN], A2[MAXN];
int Size1 = 0, Size2 = 0;

bool CompareBig(int a, int b){
    return a > b;
}
bool CompareSmall(int a, int b){
    return a < b;
}

void Insert(int A[], int* Size, int x, bool (*compare)(int a, int b)){
    int i;
    for(i = ++(*Size); i != 1 && compare(x, A[i / 2]); i /= 2)
        A[i] = A[i / 2];
    A[i] = x;

}
int Del(int A[], int *Size, bool (*compare)(int a, int b)){
    int Delx = A[1];
    int x = A[(*Size)--];
    int parent, child;
    for(parent = 1; 2 * parent <= (*Size); parent = child){
        child = 2 * parent;
        if(child + 1 != (*Size) && compare(A[child + 1], A[child])) ++child;
        if(compare(x, A[child])) break;
        A[parent] = A[child];
    }
    A[parent] = x;
    return Delx;
}
void Adjust(int A[], int *Size, int x, bool (*compare)(int a, int b)){
    int parent, child, k;
    for(k = 1; k <= (*Size); k++)
        if(A[k] == x)break;
    if(k > (*Size))return;
    A[k] = A[1];
    A[1] = A[(*Size)--];
    for(parent = 1; 2 * parent <= (*Size); parent = child){
        child = 2 * parent;
        if(child + 1 != (*Size) && compare(A[child + 1], A[child])) ++child;
        if(!compare(A[parent], A[child]))
            A[parent] = A[child];
    }
}
Stack CreateStack(){
    Stack S;
    S = (Stack)malloc(sizeof(struct SNode));
    S->Size = MAXN;
    S->top = -1;
    return S;
}
bool IsEmpty(Stack S){
    return S->top == -1;
}
int Pop(Stack S){
    int x = S->data[S->top--];
    Adjust(A1, &Size1, x, CompareBig);
    Adjust(A2, &Size2, x, CompareSmall);
    int t = Size1 - Size2;
    if(t == 2)
        Insert(A2, &Size2, Del(A1, &Size1, CompareBig), CompareSmall);
    else if(t == -1)
        Insert(A1, &Size1, Del(A2, &Size2, CompareSmall), CompareBig);
    return x;
}
void Push(Stack S, int x){
    S->data[++S->top] = x;
    if(Size1 == 0)
        Insert(A1, &Size1, x, CompareBig);
    else{
        if(x > A1[1])
            Insert(A2, &Size2, x, CompareSmall);
        else
            Insert(A1, &Size1, x, CompareBig);
        int t = Size1 - Size2;
        if(t == 2)
            Insert(A2, &Size2, Del(A1, &Size1, CompareBig), CompareSmall);
        else if(t == -1)
            Insert(A1, &Size1, Del(A2, &Size2, CompareSmall), CompareBig);
    }
}
int PeekMedian(Stack S){
    return A1[1];
}

int main(){
    Stack S;
    S = CreateStack();
    char inst[15];
    int N, x, t;
    scanf("%d", &N);
    while(N--){
        scanf("%s", inst);
        t = strcmp("Pop", inst);
        if(t < 0){
            scanf("%d", &x);
            Push(S, x);
        }else if(t > 0){
            if(IsEmpty(S))
                printf("Invalid\n");
            else{
                x = PeekMedian(S);
                printf("%d\n", x);
            }
        }else if(t == 0){
            if(IsEmpty(S))
                printf("Invalid\n");
            else{
                x = Pop(S);
                printf("%d\n", x);
            }
        }
    }
}



// 17
// Pop
// PeekMedian
// Push 3
// PeekMedian
// Push 2
// PeekMedian
// Push 1
// PeekMedian
// Pop
// Pop
// Push 5
// Push 4
// PeekMedian
// Pop
// Pop
// Pop
// Pop
