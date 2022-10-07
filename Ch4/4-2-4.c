// 搜索树判断

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TNode* BinTree;
struct TNode{
    int data;
    BinTree Left;
    BinTree Right;
};

BinTree Build1(BinTree T, int x){
    if(!T){
        T = (BinTree)malloc(sizeof(struct TNode));
        T->data = x;
        T->Left = T->Right = NULL;
    }else{
        if(x < T->data)
            T->Left = Build1(T->Left, x);
        else
            T->Right = Build1(T->Right, x);
    }
    return T;
}
BinTree Build2(BinTree T, int x){
    if(!T){
        T = (BinTree)malloc(sizeof(struct TNode));
        T->data = x;
        T->Left = T->Right = NULL;
    }else{
        if(x >= T->data)
            T->Left = Build2(T->Left, x);
        else
            T->Right = Build2(T->Right, x);
    }
    return T;
}
int Cnt = 0;
int pre[1000], post[1000], source[1000];
void Pre(BinTree T){
    if(T){
        pre[Cnt++] = T->data;
        Pre(T->Left);
        Pre(T->Right);
    }
}
void Post(BinTree T){
    if(T){
        Post(T->Left);
        Post(T->Right);
        post[Cnt++] = T->data;
    }
}
bool IsBshTree(){
    for(int i = 0; i < Cnt; i++)
        if(pre[i] != source[i])
            return false;
    return true;
}
void OutPut(){
    printf("YES\n");
    printf("%d", post[0]);
    for(int i = 1; i < Cnt; i++)
        printf(" %d", post[i]);
}
int main(){
    int n;
    BinTree head1 = NULL, head2 = NULL;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &source[i]);
        head1 = Build1(head1, source[i]);
        head2 = Build2(head2, source[i]);
    }
    bool flag = false;
    Cnt = 0;
    Pre(head1);
    if(IsBshTree()){
        Cnt = 0;
        Post(head1);
        OutPut();
        flag = true;
    }else{
        Cnt = 0;
        Pre(head2);
        if(IsBshTree()){
            Cnt = 0;
            Post(head2);
            OutPut();
            flag = true;
        }
    }
    if(!flag)
        printf("NO\n");
}