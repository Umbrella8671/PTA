// 分离链接法的删除操作

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef int ElementType;
typedef struct LNode* PtrToLNode;
struct LNode{
    ElementType Data;
    PtrToLNode Next;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;

typedef struct TblNode* HashTable;
struct TblNode{
    int TableSize;
    List Heads;
};

Position Hash(ElementType Key, int TableSize){}
bool Delete(HashTable H, ElementType Key){
    Position P, t;
    int Pos;
    Pos = Hash(Key, H->TableSize);
    P = H->Heads + Pos;
    while(P->Next && strcmp(P->Next->Data, Key))
        P = P->Next;
    if(!P->Next)    return false;
    else{
        t = P->Next;
        P->Next = t->Next;
        free(t);
        return true;
    }
}

