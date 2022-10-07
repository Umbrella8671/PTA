#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct Node *PtrToNode;
struct Node
{
    ElementType Data; /* 存储结点数据 */
    PtrToNode Next;   /* 指向下一个结点的指针 */
};
typedef PtrToNode List; /* 定义单链表类型 */

List ReadInput()       /* 裁判实现，细节不表 */
{
    int n, v;
    scanf("%d", &n);
    List node;
    List L = (List)malloc(sizeof(struct Node));
    List p = L;
    for(int i = 0; i < n; i++){
        scanf("%d", &v);
        node = (List)malloc(sizeof(struct Node));
        node->Data = v;
        node->Next = NULL;
        p->Next = node;
        p = p->Next;
    }
    return L;
}
void PrintList(List L) /* 裁判实现，细节不表 */
{
    List p = L->Next;
    while(p){
        printf("%d ", p->Data);
        p = p->Next;
    }
}
void K_Reverse(List L, int K);

int main()
{
    List L;
    int K;

    L = ReadInput();
    scanf("%d", &K);
    K_Reverse(L, K);
    PrintList(L);

    return 0;
}

/* 你的代码将被嵌在这里 */

void K_Reverse(List L, int K)
{
    int elemnum = 0;
    List ptr = L->Next;
    while (ptr)
    {
        elemnum++;
        ptr = ptr->Next;
    }
    int len = 0;
    List  old, new, temp, head;
    head = L;
    for (int i = 1; i <= elemnum / K; i++)
    {
        new = head->Next;
        old = new->Next;
        ptr = head->Next;

        len = K - 1;
        while(len--){
            temp = old->Next;
            old->Next = new;
            new = old;
            old = temp;
        }

        head->Next = new;
        ptr->Next = old;
        head = ptr;
    }
}