// 字符串关键字的散列映射
// 移位操作

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXS 8 /* 最大字符串长度*/
#define MAXD 3 /* 参与散列映射计算的字符个数*/
#define MAXB 5 /* 每个字符占的位数*/
#define MASK ((1 << (MAXD * MAXB)) - 1)

typedef char ElementType[MAXS + 1];
enum EntryType{Legitimate, Empty};
struct HashEntry{
    ElementType Element;
    enum EntryType info;
};
struct HashTbl{
    int TableSize;
    struct HashEntry* TheCells;
};
typedef struct HashTbl* HashTable;

HashTable InitializeTable(int TableSize){
    HashTable H = (HashTable)malloc(sizeof(struct HashTbl));
    H->TableSize = TableSize;
    H->TheCells = (struct HashEntry*)malloc(sizeof(struct HashEntry) * TableSize);
    while(TableSize)
        H->TheCells[--TableSize].info = Empty;
    return H;
}
int Hash(char* Key, int P){
    int h = 0;
    while(*Key != '\0')
        h = (h << MAXB) + (*Key++ - 'A');
    return ((h & MASK) % P);
}
int Find(HashTable H, char* Key){
    int inc, Cnt = 0;
    int Next, Pos;
    Next = Pos = Hash(Key, H->TableSize);
    while(H->TheCells[Next].info != Empty &&
        (strcmp(H->TheCells[Next].Element, Key))){
        if(++Cnt % 2)
            inc = ((Cnt + 1) * (Cnt + 1)) >> 2;
        else
            inc = -(Cnt * Cnt) >> 2;
        Next = Pos + inc;
        if(Next < 0)    Next += H->TableSize;
        else if(Next >= H->TableSize)
            Next -= H->TableSize;
    }
    
    return Next;
}
void InsertAndOutput(ElementType Key, HashTable H){
    int Pos = Find(H, Key);
    if(H->TheCells[Pos].info == Empty){
        H->TheCells[Pos].info = Legitimate;
        strcpy(H->TheCells[Pos].Element, Key);
    }
    printf("%d", Pos);
}

int main(){
    int N, P, i;
    ElementType Key;
    HashTable H;
    scanf("%d%d", &N, &P);
    H = InitializeTable(P);
    scanf("%s", Key);
    InsertAndOutput(Key, H);
    for(i = 1; i < N; i++){
        scanf("%s", Key);
        printf(" ");
        InsertAndOutput(Key, H);
    }
    printf("\n");
}