// 二叉搜索树最近公共祖先

#include <stdio.h>
#include <stdlib.h>


#define MAXN 10001
typedef struct BSTNode* BSTree;
struct BSTNode{
    int Key;
    BSTree left, right;
};
int preorder[MAXN], inorder[MAXN];


BSTree Create(int rootloc, int start, int len){
    if(len < 1) return NULL;
    int Left_len = 0;
    for(Left_len = 0; preorder[rootloc] != inorder[start + Left_len]; Left_len++);
    BSTree T;
    T = (BSTree)malloc(sizeof(struct BSTNode));
    T->Key = preorder[rootloc];
    T->left = Create(rootloc + 1, start, Left_len);
    T->right = Create(rootloc + Left_len + 1, start + Left_len + 1, len - Left_len - 1);
    return T;
}
int CompareInt(const void*a, const void* b){
    return *(const int*)a - *(const int*)b;
}
int IsExist(BSTree T, int x){
    if(T == NULL)
        return 0;
    else if(x == T->Key)
        return 1;
    else if(x < T->Key)
        return IsExist(T->left, x);
    else if(x > T->Key)
        return IsExist(T->right, x);
    else
        return 0;
}
int Find(BSTree T, int x, int y){
    if(x > T->Key && y > T->Key)
        return Find(T->right, x, y);
    else if(x < T->Key && y < T->Key)
        return Find(T->left, x, y);
    else 
        return T->Key;
}

int main(){
    int N, M;
    scanf("%d%d", &M, &N);
    for(int i = 0; i < N; i++){
        scanf("%d", preorder + i);
        inorder[i] = preorder[i];
    }
    qsort(inorder, N, sizeof(int), CompareInt);
    BSTree T;
    T = Create(0, 0, N);
    //Traverse(T);
    int u, v, k, flag1, flag2;
    while(M--){
        scanf("%d%d", &u, &v);
        flag1 = IsExist(T, u);
        flag2 = IsExist(T, v);
        if(flag1 == 0 && flag2 == 0)printf("ERROR: %d and %d are not found.\n", u, v);
        else if(flag1 == 0)printf("ERROR: %d is not found.\n", u);
        else if(flag2 == 0)printf("ERROR: %d is not found.\n", v);
        else{
            k = Find(T, u, v);
            if(k == u)printf("%d is an ancestor of %d.\n", u, v);
            else if(k == v)printf("%d is an ancestor of %d.\n", v, u);
            else printf("LCA of %d and %d is %d.\n", u, v, k);
        }
    }
}