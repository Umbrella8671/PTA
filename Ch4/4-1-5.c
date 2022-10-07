// 顺序二叉树公共祖先

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXSIZE 10001
#define Swap(a, b) a ^= b, b ^= a, a ^= b

typedef struct TNode* Tree;
struct TNode{
    int Data[MAXSIZE];
    int Last;
};
int NCA(int p1, int p2){
    while(p1 != p2){
        if(p1 > p2) Swap(p1, p2);
        while(p2 > p1)  p2 /= 2;
    }
    return p1;
}
int main(){
    Tree root = (Tree)malloc(sizeof(struct TNode));
    root->Last = 0;
    root->Data[0] = 0;
    int n, p, p1, p2;
    scanf("%d", &n);
    for(root->Last = 1; root->Last <= n; root->Last++)
        scanf("%d", &root->Data[root->Last]);
    scanf("%d %d", &p1, &p2);
    if(root->Data[p1] && root->Data[p2]){
        p = NCA(p1, p2);
        printf("%d %d\n", p, root->Data[p]);
    }else{
        if(!root->Data[p1])
            printf("ERROR: T[%d] is NULL\n", p1);
        else
            printf("ERROR: T[%d] is NULL\n", p2);
    }
}
