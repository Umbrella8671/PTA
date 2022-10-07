// 整形关键字的平方探测法散列映射

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define ERROR -1
#define MAXTABLESIZE 10007
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
    int CurrentPos = Hash(Key, H->TableSize), NewPos;
    NewPos = CurrentPos;
    int Cnt = 0;
    while(H->TheCells[NewPos].info != Empty &&
        (H->TheCells[NewPos].Data != Key)){
        Cnt++;
        NewPos = CurrentPos + Cnt * Cnt;
        if(NewPos >= H->TableSize)
            NewPos %= H->TableSize;
        if(NewPos == CurrentPos)
            return ERROR;
    }
    return NewPos;
}
void InsertAndOutput(ElementType Key, HashTable H){
    int Pos = Find(H, Key);
    if(Pos != ERROR && H->TheCells[Pos].info == Empty){
        H->TheCells[Pos].Data = Key;
        H->TheCells[Pos].info = Legitimate;
        printf("%d", Pos);
    }else
        printf("-");
}
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
int main(){
    int N, MSize, Key, i;
    HashTable H;
    scanf("%d%d", &MSize, &N);
    H = InitializeTable(FindPrime(MSize));
    scanf("%d", &Key);
    InsertAndOutput(Key, H);
    for(i = 1; i < N; i++){
        scanf("%d", &Key);
        printf(" ");
        InsertAndOutput(Key, H);
    }
    printf("\n");
}