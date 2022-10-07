//  QQ账户的申请与登录
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAXTABLESIZE 100003
#define MAXACCOUNTSIZE 11
#define MAXPASSWORDSIZE 17
#define ERROR -1
typedef enum {Legitimate, Empty}EntryType;

struct HashEntry{
    char Account[MAXACCOUNTSIZE];
    char Password[MAXPASSWORDSIZE];
    EntryType info;
};
typedef struct HashEntry Cell;
struct TblNode{
    int TableSize;
    Cell* TheCells;
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
HashTable InitializeTable(int TableSize){
    HashTable H = (HashTable)malloc(sizeof(struct TblNode));
    H->TableSize = TableSize;
    H->TheCells = (struct HashEntry*)malloc(sizeof(struct HashEntry) * TableSize);
    while(TableSize)
        H->TheCells[--TableSize].info = Empty;
    return H;
}
int Hash(char* Account, int TableSize){
    int length = strlen(Account);
    return (atoi(Account + length - 7) % TableSize);
}
int Find(HashTable H, char* Account){
    int CurPos, NewPos, i = 0;
    NewPos = CurPos = Hash(Account, H->TableSize);
    while(H->TheCells[NewPos].info != Empty && strcmp(H->TheCells[NewPos].Account, Account)){
        i++;
        NewPos = CurPos + i;
        if(NewPos >= H->TableSize)
            NewPos -= H->TableSize;
        if(NewPos == CurPos)
            return ERROR;
    }
    return NewPos;
}
bool NewAccount(HashTable H, char* Account, char* Password){
    int Pos = Find(H, Account);
    if(Pos == ERROR)
        return false;
    if(H->TheCells[Pos].info == Empty){
        H->TheCells[Pos].info = Legitimate;
        strcpy(H->TheCells[Pos].Account, Account);
        strcpy(H->TheCells[Pos].Password, Password);
        return true;
    }else
        return false;
}
int LoginAccount(HashTable H, char* Account, char* Password){
    int Pos = Find(H, Account);
    if(Pos == ERROR)
        return ERROR;
    if(H->TheCells[Pos].info != Empty && !strcmp(H->TheCells[Pos].Account, Account))
        if(!strcmp(H->TheCells[Pos].Password, Password))
            return true;
        else
            return false;
    else
        return ERROR;
}
int main(){
    char Account[MAXACCOUNTSIZE], Password[MAXPASSWORDSIZE];
    char ch;
    int N;
    scanf("%d", &N);
    getchar();
    HashTable H = InitializeTable(FindPrime(N));
    while(N--){
        int flag;
        scanf("%c%s%s", &ch, Account, Password);
        getchar();
        if(ch == 'L'){
            flag = LoginAccount(H, Account, Password);
            if(flag == -1)
                printf("ERROR: Not Exist\n");
            else if(flag == 0)
                printf("ERROR: Wrong PW\n");
            else
                printf("Login: OK\n");
        }else{
            flag = NewAccount(H, Account, Password);
            if(flag == 0)
                printf("ERROR: Exist\n");
            else
                printf("New: OK\n");
        }
    }
}