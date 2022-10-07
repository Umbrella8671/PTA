// 航空公司VIP客户查询

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAXTABLESIZE 100003
#define MAXIDSIZE 19

struct LNode{
    char ID[MAXIDSIZE];
    int distance;
    struct LNode* Next;
};
typedef struct LNode* PtrToLNode;
struct TblNode{
    int TableSize;
    struct LNode* Heads;
};
typedef struct TblNode* HashTable;
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
PtrToLNode CreateLNode(char ID[MAXIDSIZE], int distance){
    PtrToLNode Node = (PtrToLNode)malloc(sizeof(struct LNode));
    strcpy(Node->ID, ID);
    Node->distance = distance;
    Node->Next = NULL;
    return Node;
}
HashTable InitializeTable(int TableSize){
    HashTable H = (HashTable)malloc(sizeof(struct TblNode));
    H->TableSize = TableSize;
    H->Heads = (PtrToLNode)malloc(sizeof(struct LNode) * H->TableSize);
    while(TableSize){
        --TableSize;
        strcpy(H->Heads[TableSize].ID, "NULL");
        H->Heads[TableSize].Next = NULL;
    }
    return H;
}
int Hash(char ID[MAXIDSIZE], int TableSize){
    int H = (ID[9] - '0') * 10 + (ID[11] - '0');
    H = H * 10 + (ID[13] - '0');
    H = H * 10 + (ID[15] - '0');
    H = H * 10 + (ID[16] - '0');
    H = H * 10 + ((ID[17] == 'x') ? 10 : (ID[17] - '0'));
    return H % TableSize;
}
void Insert(HashTable H, int K, char ID[MAXIDSIZE], int distance){
    int Pos = Hash(ID, H->TableSize);
    PtrToLNode Ptr = &H->Heads[Pos];
    while(Ptr->Next){
        if(!strcmp(Ptr->ID, ID)){
            Ptr->distance += (distance < K ? K : distance);
            return;
        }
        Ptr = Ptr->Next;
    }
    if(!strcmp(Ptr->ID, ID))
        Ptr->distance += (distance < K ? K : distance);
    else
        Ptr->Next = CreateLNode(ID, distance < K ? K : distance);
}
int Find(HashTable H, char ID[MAXIDSIZE]){
    int Pos = Hash(ID, H->TableSize);
    PtrToLNode ptr = H->Heads[Pos].Next;
    while(ptr){
        if(!strcmp(ptr->ID, ID))
            return ptr->distance;
        ptr = ptr->Next;
    }
    return -1;
}
int main(){
    int N, K, distance;
    char ID[MAXIDSIZE];
    scanf("%d%d", &N, &K);
    HashTable H = InitializeTable(FindPrime(N));
    while(N--){
        scanf("%s%d", ID, &distance);
        Insert(H, K, ID, distance);
    }
    int M;
    scanf("%d", &M);
    while(M--){
        scanf("%s", ID);
        distance = Find(H, ID);
        if(distance != -1)
            printf("%d\n", distance);
        else
            printf("No Info\n");
    }
}