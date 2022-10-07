#include<iostream>
#include<ios>
#include<iomanip>
#include<string>
#include<cstring>
#include<cmath>
#include<stack>
#include<queue>
#include<vector>
#include<climits>
#include<cctype>
using namespace std;
const int MAXN = 1e5;

typedef struct Node *PtrtoNode;
struct Node{
    int Data;
    PtrtoNode Next;
    Node(int x, PtrtoNode p) : Data(x), Next(p){}
    ~Node(){delete Next;}
};
typedef PtrtoNode List;

List CreatLsit(){
    List L = new Node(INT_MIN, nullptr);
    char n;
    PtrtoNode ptr = L;
    while(n = cin.get()){
        if(n == '\n')
            break;
        if(isdigit(n)){
            ptr->Next = new Node(n - '0', nullptr);
            ptr = ptr->Next;
        }
    }
    return L;
}
void PrintList(List L){
    PtrtoNode ptr = L->Next;
    while(ptr){
        cout << ptr->Data << " ";
        ptr = ptr->Next;
    }
    cout << endl;
}
List Insert(List L, int x){
    PtrtoNode ptr = L;
    PtrtoNode pre = ptr;
    while(ptr && ptr->Data < x){
        pre = ptr;
        ptr = ptr->Next;
    }
    pre->Next = new Node(x, ptr);
    return L;
}

int main(){
    List L = CreatLsit();
    //PrintList(L);

    int x;
    cin >> x;
    List Lnew = Insert(L, x);
    PrintList(Lnew);
}

