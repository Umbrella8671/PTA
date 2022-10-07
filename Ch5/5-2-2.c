//  电话聊天狂人
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAXTABLESIZE 100003

typedef char ElementType[12];
typedef struct LNode* PtrToLNode;
struct LNode{
    ElementType Data;
    PtrToLNode Next;
    int Count;
};
typedef PtrToLNode List;
typedef struct TblNode* HashTable;
struct TblNode{
    int TableSize;
    List Heads;
};
bool isPrime(int x){
    if(x <= 3)  return x > 1;
    if(x % 6 != 1 && x % 6 != 5)
        return false;
    for(int i = 5; i <= sqrt(x); i++)
        if(x % i == 0 || x % (i + 2) == 0)
            return false;
    return true;
}
int FindPrime(int MSize){
    int i;
    for(i = MSize; i <= MAXTABLESIZE; i++)
        if(isPrime(i))
            break;
    return i;
}
PtrToLNode CreateLNode(ElementType data){
    PtrToLNode Node = (PtrToLNode)malloc(sizeof(struct LNode));
    strcpy(Node->Data, data);
    Node->Next = NULL;
    Node->Count = 1;
    return Node;
}
HashTable InitializeTable(int TableSize){
    HashTable H = (HashTable)malloc(sizeof(struct TblNode));
    H->TableSize = TableSize;
    H->Heads = (List)malloc(sizeof(struct LNode) * H->TableSize);
    while(TableSize){
        --TableSize;
        strcpy(H->Heads[TableSize].Data, "NULL");
        H->Heads[TableSize].Count = 1;
        H->Heads[TableSize].Next = NULL;
    }
    return H;
}
int Hash(ElementType PhoneNum, int TableSize){
    int length = strlen(PhoneNum);
    int p = 0;
    for(int i = length - 1; i >= length - 5; i--)
        p += ((PhoneNum[i] - '0') * pow(10, length - i - 1));
    return (p % 100000) % TableSize;
}
void Insert(HashTable H, ElementType PhoneNum){
    int Pos = Hash(PhoneNum, H->TableSize);
    PtrToLNode ptr = &H->Heads[Pos];
    while(ptr->Next){
        ptr = ptr->Next;
        if(!strcmp(ptr->Data, PhoneNum))
            ptr->Count++;
    }
    ptr->Next = CreateLNode(PhoneNum);
}
void Output(HashTable H){
    ElementType PhoneNum;
    PtrToLNode ptr;
    int i, Cnt = 0, total = 0;
    for(i = 0; i < H->TableSize; i++){
        ptr = H->Heads[i].Next;
        while(ptr){
            if(ptr->Count > Cnt){
                Cnt = ptr->Count;
                strcpy(PhoneNum, ptr->Data);
                total = 1;
            }else if(ptr->Count == Cnt){
                ++total;
                if(strcmp(ptr->Data, PhoneNum) < 0)
                    strcpy(PhoneNum, ptr->Data);
            }
            ptr = ptr->Next;
        }
    }
    printf("%s %d", PhoneNum, Cnt);
    if(total > 1)   printf(" %d", total);
    printf("\n"); 
}
int main(){
    int N;
    ElementType PhoneNum1, PhoneNum2;
    scanf("%d", &N);
    HashTable H = InitializeTable(FindPrime(N));
    while(N--){
        scanf("%s%s", PhoneNum1, PhoneNum2);
        Insert(H, PhoneNum1);
        Insert(H, PhoneNum2);
    }
    Output(H);
}
