// 哈夫曼编码

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXN 64

/*-----堆定义-----*/
#define MinElem -1

typedef struct HTNode* ElementType;
typedef struct HNode* Heap;
struct HNode{
    ElementType* Data;
    int Size;
    int Capitity;
};
typedef Heap MinHeap;

MinHeap CearteHeap(int MaxSize);
void Insert(MinHeap H, ElementType x);
ElementType DeleteMin(MinHeap H);
void PercDown(MinHeap H, int p);
void BuildHeap(MinHeap H);
/*-----堆定义结束-----*/

/*-----哈夫曼树定义-----*/
typedef struct HTNode* HuffmanTree;
struct HTNode{
    struct HTNode* lchild;
    struct HTNode* rchild;
    int Weight;
    bool exist;
};

HuffmanTree Huffman(MinHeap H);
int WPL(HuffmanTree T, int Depth);
bool IsHuffCode(HuffmanTree* T, char* code, int Pos);
void clear(HuffmanTree HT);
/*-----哈夫曼树定义结束-----*/

int main(){
    int N, i, K, c[MAXN];
    char ch;
    HuffmanTree T, HT;
    MinHeap H;
    scanf("%d", &N);
    H = CearteHeap(N);
    for(i = 1; i <= N; i++){
        T = (HuffmanTree)(malloc(sizeof(struct HTNode)));
        scanf(" %c%d", &ch, &c[i - 1]);
        T->Weight = c[i - 1];
        T->lchild = T->rchild = NULL;
        H->Data[i] = T;
        H->Size++;
    }
    T = Huffman(H);
    int CodeLen = WPL(T, 0);
    clear(T);
    int Len = 0, sLen, maxLen;
    bool flag = true;
    scanf("%d", &K);
    char code[MAXN][MAXN];
    char s[2000];
    while(K--){
        maxLen = -1; 
        flag = true;
        for(i = 0; i < N; i++){
            scanf(" %c%s", &ch, s);
            sLen = strlen(s);
            if(sLen > maxLen) maxLen = sLen;
            Len += (sLen * c[i]);
            strcpy(code[i], s);
        }
        if(Len != CodeLen || maxLen > N - 1)
            flag = false;
        else{
            for(i = 0; i < N; i++)
                if(!IsHuffCode(&HT, code[i], 0))break;
            if(i != N)
                flag = false;
        }
        if(flag)
            printf("Yes\n"); 
        else
            printf("No\n");
        clear(HT);
        HT = NULL;
        Len = 0;
    }
}

HuffmanTree Huffman(MinHeap H){
    int i, N;
    HuffmanTree T;
    BuildHeap(H);
    N = H->Size;
    for(i = 1; i < N; i++){
        T = (HuffmanTree)malloc(sizeof(struct HTNode));
        T->lchild = DeleteMin(H);
        T->rchild = DeleteMin(H);
        T->Weight = T->lchild->Weight + T->rchild->Weight;
        Insert(H, T);
    }
    return DeleteMin(H);
}
int WPL(HuffmanTree T, int Depth){
    if(!T->lchild && !T->rchild)
        return T->Weight * Depth;
    else 
        return WPL(T->lchild, Depth + 1) + WPL(T->rchild, Depth + 1);
}
HuffmanTree CreateHTNode(){
    HuffmanTree T = (HuffmanTree)malloc(sizeof(struct HTNode));
    T->exist = false;
    T->lchild = T->rchild = NULL;
    return T;
}

bool IsHuffCode(HuffmanTree* T, char* code, int Pos){
    bool f1 = true, f2 = true;
    if(!(*T))
        (*T) = CreateHTNode();
    else if((*T)->exist)
        return false;
    if(!code[Pos]){
        if((*T)->exist || (*T)->lchild != NULL || (*T)->rchild != NULL)
            return false;
        (*T)->exist = true;
    }else if(code[Pos] == '0')
        f1 = IsHuffCode(&(*T)->lchild, code, Pos + 1);
    else if(code[Pos] == '1')
        f2 = IsHuffCode(&(*T)->rchild, code, Pos + 1);
    return (f1 && f2);
}

void clear(HuffmanTree HT){
    if(HT){
        clear(HT->lchild);
        clear(HT->rchild);
        free(HT);
    }
}

MinHeap CearteHeap(int MaxSize){
    MinHeap H;
    H = (MinHeap)malloc(sizeof(struct HNode));
    H->Data = (ElementType*)malloc(sizeof(ElementType) * (MaxSize + 1));
    H->Data[0] = (HuffmanTree)malloc(sizeof(struct HTNode));
    H->Data[0]->Weight = MinElem;
    H->Data[0]->lchild = H->Data[0]->rchild = NULL;
    H->Capitity = MaxSize;
    H->Size = 0;
    return H;
}
void Insert(MinHeap H, ElementType x){
    int i;
    for(i = ++H->Size; H->Data[i / 2]->Weight > x->Weight; i /= 2)
        H->Data[i] = H->Data[i / 2];
    H->Data[i] = x;
}
ElementType DeleteMin(MinHeap H){
    ElementType x = H->Data[1];
    H->Data[1] = H->Data[H->Size--];
    PercDown(H, 1);
    return x;
}
void PercDown(MinHeap H, int p){
    int parent, child;
    ElementType x;
    x = H->Data[p];
    for(parent = p; (2 * parent) <= H->Size; parent = child){
        child = 2 * parent;
        if((child + 1) != H->Size && H->Data[child]->Weight > H->Data[child + 1]->Weight) ++child;
        if(H->Data[child]->Weight > x->Weight) break;
        H->Data[parent] = H->Data[child];
    }
    H->Data[parent] = x;
}
void BuildHeap(MinHeap H){
      for(int i = H->Size / 2; i >= 1; i--)
        PercDown(H, i);
}
