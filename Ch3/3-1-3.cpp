// 3-1.3 求链表的倒数第m个元素
#include<iostream>
using namespace std;

typedef int ElementType;

typedef struct Node* PtrToNode;
struct Node{
    ElementType Data;
    PtrToNode Next;
};
typedef PtrToNode List;

// 相当于在输入时统计了链表长度
ElementType Find(List L, int m, int n){
    if(m > n)
        return -1;
    int cnt = 0;
    PtrToNode ptr = L->Next;
    while(cnt++ < n - m)
        ptr = ptr->Next;
    return ptr->Data;
}
// 两个指针避免统计长度
ElementType Find(List L, int m){
    PtrToNode p1 = L, p2 = L;
    int Count = 0;
    while(p1 && (++Count <= m))
        p1 = p1->Next;
    if(Count <= m)
        return -1;
    while(p1){
        p1 = p1->Next;
        p2 = p2->Next;
    }
    return p2->Data;
}


int ReadInput(List &L){
    L = new Node;
    L->Next = nullptr;
    int number = 0;
    ElementType Data;
    PtrToNode ptr = L;
    while(cin >> Data){
        number++;
        PtrToNode newnode = new Node;
        newnode->Data = Data;
        newnode->Next = nullptr;
        ptr->Next = newnode;
        ptr = newnode;
    }
    if(!L->Next){
        delete L;
        L = nullptr;
    }
    cin.clear();
    return number;
}

int main(){
    List L;
    int n = ReadInput(L);
    int m;
    cin >> m;
    ElementType result = Find(L, m);
    if(result == -1)
        cout << "ERROR\n";
    else
        cout << result << endl;
}
