// 新浪微博热门话题

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAXTABLESIZE 100007
#define MAXWEIBOSIZE 141
#define MAXTOPICSIZE 141
struct LNode{
    char Topic[MAXTOPICSIZE];
    int Cnt;
    int SerialNumber;
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
PtrToLNode CreateLNode(char Topic[MAXTOPICSIZE], int SerialNumber){
    PtrToLNode Node = (PtrToLNode)malloc(sizeof(struct LNode));
    strcpy(Node->Topic, Topic);
    Node->Cnt = 1;
    Node->SerialNumber = SerialNumber;
    Node->Next = NULL;
    return Node;
}
HashTable InitializeTable(int TableSize){
    HashTable H = (HashTable)malloc(sizeof(struct TblNode));
    H->TableSize = TableSize;
    H->Heads = (PtrToLNode)malloc(sizeof(struct LNode) * H->TableSize);
    while(TableSize){
        --TableSize;
        strcpy(H->Heads[TableSize].Topic, "\0");
        H->Heads[TableSize].Cnt = 1;
        H->Heads[TableSize].Next = NULL;
    }
    return H;
}
int Hash(char Topic[MAXTOPICSIZE], int TableSize){
    int H = 0;
    if(Topic[0] <= 'z' && Topic[0] >= 'a')
        H = Topic[0] - 'a' + 10;
    else if(Topic[0] <= '9' && Topic[0] >= '0')
        H = Topic[0] - '0';
    return H;
}
void Insert(HashTable H, char Topic[MAXTOPICSIZE], int SerialNumber){
    int Pos = Hash(Topic, H->TableSize);
    PtrToLNode Ptr = &H->Heads[Pos];
    while(Ptr->Next){
        Ptr = Ptr->Next;
        if(!strcmp(Ptr->Topic, Topic)){
            if(Ptr->SerialNumber != SerialNumber){
                Ptr->Cnt++;
                Ptr->SerialNumber = SerialNumber;
            }else
                return;
        }
    }
    Ptr->Next = CreateLNode(Topic, SerialNumber);
}
void ReadTopics(HashTable H, int t){
    char WeiBo[MAXWEIBOSIZE], Topic[MAXTOPICSIZE];
    int SerialNumber;
    int flag_join, flag_space;
    SerialNumber = t;
    gets(WeiBo);
    flag_join = 0, flag_space = 0;
    for(char* i = WeiBo, *j = Topic; *i != '\0'; i++){
        if(flag_join == 1){
            switch(*i){
            case '#':
                flag_join = 0;
                while(*(j - 1) == ' ')   j--;
                *j = '\0';
                if (strlen(Topic) > 0)//两个连续的#是空话题，不予计数 
                    Insert(H, Topic, SerialNumber);
                j = Topic;
                break;
            case '0'...'9':
            case 'a'...'z':
                *j++ = *i;
                flag_space = 1;
                break;
            case 'A'...'Z':
                *j++ = *i - 'A' + 'a';
                flag_space = 1;
                break;
            default:
                if(flag_space == 1){
                    *j++ = ' ';
                    flag_space = 0;
                }break;
            }
        }else if(*i == '#'){
            flag_join = 1;
            flag_space = 0;
        }
    }
    
}
void Output(HashTable H){
    char Topic[MAXTOPICSIZE];
    int TopicCnt = 0, TopicNum = 0;
    PtrToLNode ptr;
    for(int i = 0; i < H->TableSize; i++){
        ptr = H->Heads[i].Next;
        while(ptr){
            if(ptr->Cnt > TopicCnt){
                TopicCnt = ptr->Cnt;
                TopicNum = 0;
                strcpy(Topic, ptr->Topic);
            }else if(ptr->Cnt == TopicCnt){
                ++TopicNum;
                if(strcmp(ptr->Topic, Topic) < 0)
                    strcpy(Topic, ptr->Topic);
            }
            ptr = ptr->Next;
        }
    }
    Topic[0] = Topic[0] - 'a' + 'A';
    printf("%s\n%d\n", Topic, TopicCnt);
    if(TopicNum >= 1)
        printf("And %d more ...\n", TopicNum);
}
int main(){
    int N;
    scanf("%d\n", &N);
    HashTable H = InitializeTable(37);
    int i = 1;
    while(i <= N)
        ReadTopics(H, i++); 
    Output(H);
}















