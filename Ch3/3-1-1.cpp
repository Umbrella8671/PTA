//案例3-1.1:线性表元素的区间删除

#include<iostream>
using namespace std;


const int MAXSIZE = 1e5;
typedef int Position;

typedef struct LNode* List;
struct LNode{
    int Data[MAXSIZE];
    Position Last;
};


List Delete(List L, int minD, int maxD){
    int i, p;
    for(i = 0; i < L->Last; i++)
        if(L->Data[i] < maxD && L->Data[i] > minD)
            break;
    p = i;
    for(; i <= L->Last; i++)
        if(!(L->Data[i] < maxD && L->Data[i] > minD))
            L->Data[p++] = L->Data[i];
    L->Last = p - 1;    
    return L;
    
}

int main(){
    List L = new LNode;
    int last, minD, maxD;
    cin >> last >> minD >> maxD;
    for(int i = 0; i <= last; i++)
        cin >> L->Data[i];
    L->Last = last;
    Delete(L, minD, maxD);
    for(int i = 0; i <= L->Last; i++)
        cout << L->Data[i] << " ";
    cout << endl << L->Last << endl;
}