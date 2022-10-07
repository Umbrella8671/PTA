#include <iostream>
#include <queue>

using namespace std;

#define MAXN 30
typedef int ElementType;

typedef struct TNode *Position;
typedef Position BinTree;
struct TNode
{
    /* data */
    ElementType Data;
    BinTree Left;
    BinTree Right;
    TNode() = default;
    TNode(ElementType d, BinTree l, BinTree r) : Data(d), Left(l), Right(r){}
};

BinTree BuildTree(int Inorder[], int Postorder[], int N);
void PreorderTraversal(BinTree BT);



int main(){
    int Inorder[MAXN], Postorder[MAXN], N;
    cin >> N;
    for(int i = 0; i < N; i++)
        cin >> Postorder[i];
    
    for(int i = 0; i < N; i++)
        cin >> Inorder[i];

    PreorderTraversal(BuildTree(Inorder, Postorder, N));

}






BinTree BuildTree(int Inorder[], int Postorder[], int N){
    
    BinTree T;

    if(!N)
        return nullptr;
    int Llen = 0, Rlen = 0; 
    int cur = N - 1;
    for(Llen = 0; Inorder[Llen] != Postorder[cur]; Llen++);
    Rlen = N - Llen - 1;
    T = new TNode(Postorder[cur], nullptr, nullptr);
    
    T->Left = BuildTree(Inorder, Postorder, Llen);
    T->Right = BuildTree(Inorder + Llen + 1, Postorder + Llen, Rlen);
    
    return T;
}
void PreorderTraversal(BinTree BT){
    if(!BT)
        return;
    else{
        cout << BT->Data << " ";
        PreorderTraversal(BT->Left);
        PreorderTraversal(BT->Right);
    }
}


