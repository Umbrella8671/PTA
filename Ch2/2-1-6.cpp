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


List CreatLsit();
bool DeleteList(List &L);
void PrintList(List L);
List Merge(List &L1, List &L2);

int main(){
    List L1 = CreatLsit();
    List L2 = CreatLsit();
    List L3 = Merge(L1, L2);
    PrintList(L3);
    PrintList(L1);
    PrintList(L2);
}

List CreatLsit(){
    List L = new Node(INT_MIN, nullptr);
    int n;
    PtrtoNode ptr = L;
    while(cin >> n){
        ptr->Next = new Node(n, nullptr);
        ptr = ptr->Next;    
    }
    cin.clear();
    return L;
}
bool DeleteList(List &L) {
    PtrtoNode ptr = L, remove;
    while (ptr) {
        remove = ptr;
        ptr = ptr->Next;
        remove->Next = nullptr;
        delete remove;
    }
    L = nullptr;
    return true;
}
void PrintList(List L){
    if(!L)
        return;
    PtrtoNode ptr = L->Next;
    while(ptr){
        cout << ptr->Data << " ";
        ptr = ptr->Next;
    }
    cout << endl;
}
List Merge(List &L1, List &L2){
    List L3 = new Node(INT_MIN, nullptr);
    PtrtoNode ptr1 = L1->Next, ptr2 = L2->Next, ptr3 = L3;
    while(ptr1 && ptr2){
        if(ptr1->Data < ptr2->Data){
            ptr3->Next = new Node(*ptr1);
            ptr3 = ptr3->Next;
            ptr1 = ptr1->Next;
        }
        else{
            ptr3->Next = new Node(*ptr2);
            ptr3 = ptr3->Next;
            ptr2 = ptr2->Next;
        }
    }
    while(ptr1){
        ptr3->Next = new Node(*ptr3);
        ptr3 = ptr3->Next;
        ptr1 = ptr1->Next;
    }
    while(ptr2){
        ptr3->Next = new Node(*ptr2);
        ptr3 = ptr3->Next;
        ptr2 = ptr2->Next;
    }
    DeleteList(L1);
    DeleteList(L2);
    return L3;
}
