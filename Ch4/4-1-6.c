// 树种统计

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10000
#define MAXS 30

typedef struct TNode* Bintree;
struct TNode{
    char Data[MAXS + 1];
    int cnt;
    Bintree Left;
    Bintree Right;
};
Bintree Insert(Bintree T, char *data){
    if(!T){
        T = (Bintree)malloc(sizeof(struct TNode));
        strcpy(T->Data, data);
        T->cnt = 1;
        T->Left = T->Right = NULL;
    }else{
        int cmp = strcmp(data, T->Data);
        if(cmp < 0)
            T->Left = Insert(T->Left, data);
        else if(cmp > 0)
            T->Right = Insert(T->Right, data);
        else
            T->cnt++;
    }
    return T;
}
void Inorder(Bintree T, int total){
    if(!T)
        return;
    else{
        
        Inorder(T->Left, total);
        printf("%s %.4lf%c\n", T->Data, (double)T->cnt / total * 100, '%');
        Inorder(T->Right, total);
    }
}
int main(){
    int n;
    char name[MAXS + 1];
    Bintree T = NULL;
    scanf("%d", &n);
    getchar();
    for(int i = 0; i < n; i++){
        gets(name);
        T = Insert(T, name);
    }
    Inorder(T, n);
}