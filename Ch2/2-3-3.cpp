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
#include<algorithm>
using namespace std;
const int MAXN = 1e4;


typedef struct Node* PtrtoNode;
struct Node {
    int Data;
    PtrtoNode Next;
    Node() :Data(INT_MIN), Next(nullptr) {}
    Node(int x, PtrtoNode p) : Data(x), Next(p) {}
    Node(const Node& e) :Data(e.Data), Next(nullptr) {
        if (e.Next) {
            Next = new Node();
            Next->Data = e.Next->Data;
            Next->Next = e.Next->Next;
        }
    }
    ~Node() { delete Next; }
};
typedef PtrtoNode List;


List CreatLsit(){
    List L = new Node(INT_MIN, nullptr);
    int n;
    PtrtoNode ptr = L;
    while(cin >> n){
        if(n == -1)
            break;
        ptr->Next = new Node(n, nullptr);
        ptr = ptr->Next;    
    }
    if(!L->Next)
        return nullptr;
    return L;
}
void PrintList(List L){
    if(!L){
        cout << "NULL\n";
        return;
    }
    PtrtoNode ptr = L->Next;
    while(ptr && ptr->Next){
        cout << ptr->Data << " ";
        ptr = ptr->Next;
    }
    cout << ptr->Data << endl;
}
List Unit(List L1, List L2){
    if(!L1 || !L2)
        return nullptr;
    List L = new Node(0, nullptr);
    List pt1 = L1->Next, pt2 = L2->Next, pt = L;
    while(pt1 && pt2){
        if(pt1->Data == pt2->Data){
            pt->Next = new Node(pt1->Data, nullptr);
            pt1 = pt1->Next; pt2 = pt2->Next;
            pt = pt->Next;
        }
        else if(pt1->Data < pt2->Data)
            pt1 = pt1->Next;
        else
            pt2 = pt2->Next;
    }
    if(!L->Next)
        return nullptr;
    return L;
}
int main(){
    List L1 = CreatLsit();
    List L2 = CreatLsit();
    List L = Unit(L1, L2);
    PrintList(L);
}