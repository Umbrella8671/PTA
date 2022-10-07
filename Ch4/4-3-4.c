// 笛卡尔树

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define MAXSIZE 1010

typedef struct TNode* BinTree;
struct TNode{
    int K1;
    int K2;
    int lchild;
    int rchild;
};
BinTree CreateBinTree(int N){
    BinTree T = (BinTree)malloc(sizeof(struct TNode) * N);
    for(int i = 0; i < N; i++){
        T[i].K1 = T[i].K2 = T[i].lchild = T[i].rchild = -1;
        scanf("%d%d%d%d", &T[i].K1, &T[i].K2, &T[i].lchild, &T[i].rchild);
    }
    return T;
}
int Find(BinTree T, int N){
    bool check[MAXSIZE] = {false};
    int i;
    for(i = 0; i < N; i++){
        if(T[i].lchild != -1)
            check[T[i].lchild] = true;
        if(T[i].rchild != -1)
            check[T[i].rchild] = true;
    }
    for(i = 0; check[i]; i++);
    return i;
}

bool IS_BST(BinTree T, int root, int *min, int *max){
    // min, max是整个树的上下界
    
    int lmin, lmax, rmin, rmax;
    bool Left_flag, Right_flag;
    
    // 空树
    if(root == -1)   return true;

    // 单节点
    if(T[root].lchild == -1 && T[root].rchild == -1){
        *min = *max = T[root].K1;
        return true;
    }

    Left_flag = Right_flag = false;

    // 左子树(有左子树判断是否是， 或者没有左子树)
    if(T[root].lchild == -1 || 
        IS_BST(T, T[root].lchild, &lmin, &lmax) && T[root].K1 > lmax)
        Left_flag = true;
    
    // 右子树(有右子树判断是否是， 或者没有右子树)
    if(T[root].rchild == -1||
        IS_BST(T, T[root].rchild, &rmin, &rmax) && T[root].K1 < rmin)
        Right_flag = true;
    
    // 左右子树是否都是二叉搜索树
        if(Left_flag && Right_flag){
            // 更新下界
            if(T[root].lchild != -1)    (*min) = lmin;
            else                        (*min) = T[root].K1;
            // 更新上界
            if(T[root].rchild != -1)    (*max) = rmax;
            else                        (*max) = T[root].K1;
            return true;
        }else
            return false;
}
bool IsBTS(BinTree T, int root){
    int maxT, minT;
    minT = maxT = -1;
    return IS_BST(T, root, &minT, &maxT);
}
bool IS_Heap(BinTree T, int root, int *k2){
    int lk2 = -1, rk2 = -1;
    
    // 空树
    if(root == -1)  return true;

    if(T[root].lchild == -1 && T[root].rchild == -1){
        (*k2) = T[root].K2;
        return true;
    }
    bool Left_flag = IS_Heap(T, T[root].lchild, &lk2);
    bool Right_flag = IS_Heap(T, T[root].rchild, &rk2);
    (*k2) = T[root].K2;
    if(lk2 == -1)   lk2 = (*k2) + 1;
    if(rk2 == -1)   rk2 = (*k2) + 1;
    if(Left_flag && Right_flag)
        if(lk2 < rk2)
            return (*k2) < lk2;
        else
            return (*k2) < rk2;
    else
        return false;
}

bool IsHeap(BinTree T, int root){
    int k2;
    return IS_Heap(T, root, &k2);
}

int main(){
    int N;
    scanf("%d", &N);
    BinTree T = CreateBinTree(N);
    int root = Find(T, N);
    bool BTS_flag = IsBTS(T, root);
    bool Heap_flag = IsHeap(T, root);
    
    if(BTS_flag && Heap_flag)
        printf("YES\n");
    else
        printf("NO\n");
}

