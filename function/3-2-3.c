#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;

typedef struct Node *PtrToNode;
struct Node
{
    ElementType Data; /* 存储结点数据 */
    PtrToNode Next;   /* 指向下一个结点的指针 */
};
typedef PtrToNode List; /* 定义单链表类型 */

void ReadInput(List L1, List L2);    /* 裁判实现，细节不表 */
void PrintSublist(PtrToNode StartP); /* 裁判实现，细节不表 */
PtrToNode Suffix(List L1, List L2);

int main()
{
    List L1, L2;
    PtrToNode P;

    L1 = (List)malloc(sizeof(struct Node));
    L2 = (List)malloc(sizeof(struct Node));
    L1->Next = L2->Next = NULL;
    ReadInput(L1, L2);
    P = Suffix(L1, L2);
    PrintSublist(P);

    return 0;
}

/* 你的代码将被嵌在这里 */
PtrToNode Suffix(List L1, List L2)
{
    List pt1 = L1->Next, pt2 = L2->Next;
    int len1 = 0, len2 = 0;

    while(pt1)
    {
        len1++;
        pt1 = pt1->Next;
    }
    while(pt2)
    {
        len2++;
        pt2 = pt2->Next;
    }

    int sub = len1 > len2 ? len1 - len2 : len2 - len1;
    pt1 = L1->Next;
    pt2 = L2->Next;
    
    if(len1 > len2)
        while(sub--)
            pt1 = pt1->Next;
    else
        while(sub--)
            pt2 = pt2->Next;
    while(pt1 && pt2)
        if(pt1 == pt2)
            return pt1;
        else    
        {
            pt1 = pt1->Next;
            pt2 = pt2->Next;
        }
    return NULL;
}