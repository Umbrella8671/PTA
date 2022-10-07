// 列出叶节点

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define Null -1

typedef struct TNode* BinTree;
struct TNode{
    int Left;
    int Right;
};

int n;
BinTree BuildBinTree(){
    BinTree T = (BinTree)malloc(sizeof(struct TNode) * (n + 1));
    char s[4];
    for(int i = 0; i < n; i++){
        gets(s);
        T[i].Left = ('0' <= s[0] && s[0] <= '9') ? s[0] - '0' : Null;
        T[i].Right = ('0' <= s[2] && s[2] <= '9') ? s[2] - '0' : Null;
    }
    return T;
}
int Findroot(BinTree T){
    int check[11] = {0};
    int i = 0;
    for(i = 0; i < n; i++){
        if(T[i].Left != Null)
            check[T[i].Left] = 1;
        if(T[i].Right != Null)    
            check[T[i].Right] = 1;
    }
    for(i = 0; i < n; i++)
        if(!check[i])
            break;
    return i;
}
void Output(BinTree T){
    int flag = 0, flag1 = 0, flag2 = 0;
    int root = Findroot(T);

    int front, back;
    front = 0, back = -1;
    int queue[MAXSIZE + 1];
    
    queue[++back] = root;
    while(front <= back){
        if(root != Null){
            root = queue[front++];
            
            if(T[root].Left != Null)
                queue[++back] = T[root].Left, flag1 = 1;
            else
                flag1 = 0;
            
            if(T[root].Right != Null)
                queue[++back] = T[root].Right, flag2 = 1;
            else 
                flag2 = 0;
            
            if(!flag1 && !flag2){
                if(flag)
                    printf(" %d", root);
                else
                    printf("%d", root);
                flag++;
            }
        }
    }
}

int main(){
    scanf("%d", &n);
    getchar();
    BinTree T = BuildBinTree();
    Output(T);
}