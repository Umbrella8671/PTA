// 整形关键字的散列映射

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef int ElementType;
enum EntryType{Legitimate, Empty};
struct HashEntry{
    ElementType Data;
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
int Hash(ElementType Key, int P){
    return Key % P;
}
int Find(HashTable H, ElementType Key){
    int Pos = Hash(Key, H->TableSize);
    while(H->TheCells[Pos].info != Empty &&
        (H->TheCells[Pos].Data != Key)){
        Pos++;
        if(Pos == H->TableSize)
            Pos -= H->TableSize;
    }
    return Pos;
}
void InsertAndOutput(ElementType Key, HashTable H){
    int Pos = Find(H, Key);
    if(H->TheCells[Pos].info == Empty){
        H->TheCells[Pos].Data = Key;
        H->TheCells[Pos].info = Legitimate;
    }
    printf("%d", Pos);
}

int main(){
    int N, P, Key, i;
    HashTable H;
    scanf("%d%d", &N, &P);
    H = InitializeTable(P);
    scanf("%d", &Key);
    InsertAndOutput(Key, H);
    for(i = 1; i < N; i++){
        scanf("%d", &Key);
        printf(" ");
        InsertAndOutput(Key, H);
    }
    printf("\n");
}